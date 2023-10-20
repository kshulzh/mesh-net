package com.github.kshulzh.mesh_net.android.vpn

import android.app.PendingIntent
import android.content.Intent
import android.net.VpnService
import android.os.Message
import android.os.ParcelFileDescriptor
import com.github.kshulzh.mesh_net.R
import com.github.kshulzh.mesh_net.android.core.Instance
import com.github.kshulzh.mesh_net.android.core.routeUdp
import java.io.FileInputStream
import java.io.FileOutputStream
import java.nio.ByteBuffer
import java.nio.channels.FileChannel
import java.util.concurrent.ArrayBlockingQueue
import java.util.concurrent.BlockingQueue
import java.util.concurrent.ExecutorService
import java.util.concurrent.Executors
import kotlin.system.exitProcess

fun <K, V> Map<K, V>.getKeyByVal(v: V): K? {
    this.entries.forEach {
        if (it.value == v) {
            return it.key
        }
    }

    return null
}

class LocalVpnService : VpnService() {
    private var vpnInterface: ParcelFileDescriptor? = null

    private val pendingIntent: PendingIntent? = null
    private val VPN_ADDRESS = "10.0.0.2"

    private val VPN_ROUTE = "10.0.0.0"

    private val VPN_DNS = "8.8.8.8"
    lateinit var vpnOutput: FileChannel

    var routeIp2IdMap: MutableMap<UInt, ULong> = mutableMapOf()
    var maxIp = 0xa000003u
    var hostIp = 0xa000001u

    private val input: BlockingQueue<ByteArray> = ArrayBlockingQueue(1000)

    private val output: BlockingQueue<ByteBuffer> = ArrayBlockingQueue(1000)

    private var executorService: ExecutorService? = null


    override fun onCreate() {
        super.onCreate()
        setupVpn()
        executorService = Executors.newFixedThreadPool(10)
        executorService!!.submit(
            VpnRunnable(
                vpnInterface!!
            )
        )

        executorService!!.submit(
            VpnRunnableProcessor(
                vpnInterface!!
            )
        )
        executorService!!.submit(
            VpnRunnableWriter(
                vpnInterface!!
            )
        )
        registerUdpCallBack()
        updateIpList()
    }

    override fun onDestroy() {
        super.onDestroy()
        executorService!!.shutdownNow()
        cleanup()
    }

    fun setupVpn() {
        try {
            if (vpnInterface == null) {
                val builder: Builder = Builder()
                builder.addAddress(VPN_ADDRESS, 32)
                builder.addRoute(VPN_ROUTE, 24)
                builder.addDnsServer(VPN_DNS)
                vpnInterface = builder.setSession(getString(R.string.app_name)).establish()
            }
        } catch (e: Exception) {
            e.printStackTrace()
            exitProcess(0)
        }
    }

    external fun registerUdpCallBack()

    fun write(packet: ByteArray, src: Long) {
        Thread {
            try {
                updateIpList()
                var iPv4Packet = IPv4Packet()
                iPv4Packet.set(packet.toUByteArray())

                iPv4Packet.src = getIpById(src.toULong())
                iPv4Packet.dest = 0xa000002u
                println("write ${mapIpToString(iPv4Packet.src)} -> ${mapIpToString(iPv4Packet.dest)}")
                var array = iPv4Packet.toArray()
                if (iPv4Packet.protocol.toUInt() == 17u) {
                    array[26] = 0
                    array[27] = 0
                }
                var bb = ByteBuffer.wrap(array)
                output.add(bb)
            } catch (e: Exception) {
                e.printStackTrace()
            }
        }.start()

    }

    fun getIpById(id: ULong): UInt {
        var ip = routeIp2IdMap.getKeyByVal(id)
        if (ip == null) {
            ip = maxIp
            maxIp++
            routeIp2IdMap[ip] = id
        }

        return ip
    }

    fun updateIpList() {
        var ids = Instance.devices()
        routeIp2IdMap[hostIp] = ids[0]
        routeIp2IdMap[0xa000002u] = ids[0]
        ids.forEach {
            getIpById(it)
        }
        if (updateDevicesHandler != null) {
            mainExecutor1?.execute {
                updateDevicesHandler?.handleMessage(Message().apply {
                    obj = routeIp2IdMap
                })
            }
        }
    }

    fun getIdByIp(ip: UInt): ULong {
        updateIpList()
        var id = routeIp2IdMap[ip]
        return id!!
    }

    override fun onStartCommand(intent: Intent?, flags: Int, startId: Int): Int {
        return START_STICKY
    }

    private fun cleanup() {
        input.clear()
        vpnInterface!!.close()
        vpnOutput.close()
    }

    inner class VpnRunnable(
        var vpnInterface: ParcelFileDescriptor
    ) : Runnable {
        lateinit var vpnInput: FileChannel
        var isRunning = true
        override fun run() {
            vpnInput = FileInputStream(vpnInterface.fileDescriptor).channel
            while (isRunning and !Thread.interrupted()) {
                readPacket(vpnInput) {
                    input.put(it)
                }
            }

        }

        fun readPacket(fc: FileChannel, handler: (ByteArray) -> Unit) {
            var bufferToNetwork = ByteBuffer.allocate(2000)
            val readBytes: Int = vpnInput.read(bufferToNetwork)
            bufferToNetwork = bufferToNetwork.position(0) as ByteBuffer

            if (readBytes > 0) {
                val bytes = ByteArray(readBytes)
                bufferToNetwork.get(bytes, 0, bytes.size)
                handler.invoke(bytes)
            }
        }
    }

    inner class VpnRunnableProcessor(
        var vpnInterface: ParcelFileDescriptor
    ) : Runnable {
        var isRunning = true
        lateinit var vpnOutput: FileChannel
        override fun run() {
            vpnOutput = FileOutputStream(vpnInterface.fileDescriptor).channel
            while (isRunning and !Thread.interrupted()) {
                try {
                    var bb = input.take()
                    updateIpList()
                    var p = IPv4Packet()
                    p.set(bb.toUByteArray())
                    println("${mapIpToString(p.src)} -> ${mapIpToString(p.dest)}")
                    var id = getIdByIp(p.dest)
                    routeUdp(id.toLong(), p.toArray(), bb.size)
                } catch (e: Exception) {
                    e.printStackTrace()
                }
            }

        }
    }

    inner class VpnRunnableWriter(
        var vpnInterface: ParcelFileDescriptor
    ) : Runnable {
        var isRunning = true
        lateinit var vpnOutput: FileChannel
        override fun run() {
            vpnOutput = FileOutputStream(vpnInterface.fileDescriptor).channel
            while (isRunning and !Thread.interrupted()) {
                var bb = output.take()
                vpnOutput.write1(bb)
            }

        }
    }
}

fun FileChannel.write1(bb: ByteBuffer) {
    val w: Int = write(bb)
    while (bb.hasRemaining()) {
        val w: Int = write(bb)
    }
}