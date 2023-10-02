package com.github.kshulzh.mesh_net.android.vpn

import android.app.PendingIntent
import android.content.Intent
import android.net.VpnService
import android.os.ParcelFileDescriptor
import com.example.myapplication.R
import java.io.FileInputStream
import java.io.FileOutputStream
import java.nio.ByteBuffer
import java.nio.channels.FileChannel
import java.util.concurrent.ArrayBlockingQueue
import java.util.concurrent.BlockingQueue
import java.util.concurrent.ExecutorService
import java.util.concurrent.Executors
import kotlin.system.exitProcess

class LocalVpnService : VpnService() {
    private var vpnInterface: ParcelFileDescriptor? = null

    private val pendingIntent: PendingIntent? = null
    private val VPN_ADDRESS = "10.0.0.2"

    private val VPN_ROUTE = "10.0.0.0"

    private val VPN_DNS = "8.8.8.8"

    private val input: BlockingQueue<ByteBuffer> = ArrayBlockingQueue(1000)

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

    override fun onStartCommand(intent: Intent?, flags: Int, startId: Int): Int {
        return START_STICKY
    }

    private fun cleanup() {
        input.clear()
        vpnInterface!!.close()
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
                    println(it.array().size)
                    input.put(it)
                }
            }

        }

        fun readPacket(fc: FileChannel, handler: (ByteBuffer) -> Unit) {
            var bufferToNetwork = ByteBuffer.allocate(17000)
            val readBytes: Int = vpnInput.read(bufferToNetwork)
            if (readBytes > 0) {
                bufferToNetwork.flip()
                handler.invoke(bufferToNetwork)
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
            while (isRunning) {
                var bb = input.take()
                var p = IPv4Packet()
                p.set(bb.array().toUByteArray())
                println("${mapIpToString(p.src)} -> ${mapIpToString(p.dest)}")
                bb.array()
                //vpnOutput.write1()
            }

        }
    }
}

fun FileChannel.write1(bb: ByteBuffer) {
    while (bb.hasRemaining()) {
        val w: Int = write(bb)
    }
}