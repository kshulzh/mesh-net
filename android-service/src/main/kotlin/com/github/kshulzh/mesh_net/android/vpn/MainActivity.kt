@file:Suppress("Since15")

package com.github.kshulzh.mesh_net.android.vpn

import android.annotation.SuppressLint
import android.app.Activity
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothManager
import android.content.BroadcastReceiver
import android.content.Context
import android.content.Intent
import android.content.IntentFilter
import android.net.VpnService
import android.os.Bundle
import android.os.Handler
import android.os.Message
import android.widget.Button
import android.widget.Toast
import com.example.myapplication.R
import com.github.kshulzh.mesh_net.android.core.Instance
import com.github.kshulzh.mesh_net.android.core.bluetooth.BluetoothChatService
import com.github.kshulzh.mesh_net.android.core.bluetooth.BluetoothRadar
import com.github.kshulzh.mesh_net.android.core.bluetooth.Constants
import com.github.kshulzh.mesh_net.android.core.bluetooth.setup
import com.github.kshulzh.mesh_net.android.core.connectionAsk
import com.github.kshulzh.mesh_net.android.core.connectionGetStruct
import java.net.DatagramPacket
import java.net.DatagramSocket
import java.net.InetSocketAddress

class MainActivity : Activity() {
    init {
        System.loadLibrary("myapplication")
    }

    private val VPN_REQUEST_CODE = 0x0F
    private val REQUEST_ENABLE_BT = 0xD
    lateinit var bluetoothManager: BluetoothManager
    lateinit var bluetoothAdapter: BluetoothAdapter
    lateinit var bluetoothChatService: BluetoothChatService

    @SuppressLint("NewApi")
    var datagram = Thread {
        var datagramPacket = DatagramPacket(ByteArray(3000), 3000)
        var upds = DatagramSocket(5555)
        while (!Thread.interrupted()) {
            upds.receive(datagramPacket)
            println(datagramPacket.data.decodeToString())
        }

    }

    @SuppressLint("MissingPermission")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        val turnOn = findViewById<Button>(R.id.turn_on)
        val turnOnBt = findViewById<Button>(R.id.turn_on_bt)
        val turnOnMn = findViewById<Button>(R.id.turn_on_mn)
        val turnOffMn = findViewById<Button>(R.id.turn_off_mn)
        val ask = findViewById<Button>(R.id.ask)
        val struct = findViewById<Button>(R.id.struct)
        val udp = findViewById<Button>(R.id.udp)

        val filter = IntentFilter(BluetoothDevice.ACTION_FOUND)
        registerReceiver(receiver, filter)
        val filter1 = IntentFilter(BluetoothAdapter.ACTION_DISCOVERY_FINISHED)
        registerReceiver(receiver, filter1)
        bluetoothManager = getSystemService(BluetoothManager::class.java)
        bluetoothAdapter = bluetoothManager.adapter!!
        val bluetoothRadar = BluetoothRadar(bluetoothAdapter)
        bluetoothChatService =
            BluetoothChatService(this.applicationContext, mHandler, bluetoothRadar)
        bluetoothChatService.start()
        Instance.nothing()
        setup(bluetoothRadar)

        turnOn.setOnClickListener {
            startVpn()
        }

        turnOnBt.setOnClickListener {
            startBluetooth()
        }
        turnOnMn.setOnClickListener {
            bluetoothAdapter.bondedDevices.forEach {
                bluetoothChatService.connect(it, false)
            }
        }

        turnOffMn.setOnClickListener {
            Instance.stop()
        }

        ask.setOnClickListener {
            connectionAsk(bluetoothChatService.bluetoothConnection?.devPtr!!)
        }

        struct.setOnClickListener {
            connectionGetStruct(bluetoothChatService.bluetoothConnection?.devPtr!!)
        }
        datagram.start()

        udp.setOnClickListener {
            println("sending")
            Thread {

                var str = "hello".encodeToByteArray()
                var datagramPacket =
                    DatagramPacket(str, str.size, InetSocketAddress("10.0.0.3", 5555))

                var upds = DatagramSocket()
                upds.send(datagramPacket)
            }.start()
        }
        startBluetooth()
        startMN()
    }

    @SuppressLint("MissingPermission")
    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)
        if (requestCode == VPN_REQUEST_CODE && resultCode == RESULT_OK) {
            startService(Intent(this, LocalVpnService::class.java))
        } else if (requestCode == REQUEST_ENABLE_BT && resultCode == RESULT_OK) {
            startBluetooth()
        }
    }

    private fun startVpn() {
        val vpnIntent = VpnService.prepare(this)
        if (vpnIntent != null) startActivityForResult(
            vpnIntent,
            VPN_REQUEST_CODE
        ) else onActivityResult(VPN_REQUEST_CODE, RESULT_OK, null)
    }

    @SuppressLint("MissingPermission")
    private fun startBluetooth() {
        if (!bluetoothAdapter.isEnabled) {
            val enableBtIntent = Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE)
            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT)
        }
    }

    @SuppressLint("MissingPermission")
    fun startMN() {
        Thread(object : Runnable {
            override fun run() {
                Instance.start()
            }
        }).start()
    }

    // Create a BroadcastReceiver for ACTION_FOUND.
    private val receiver = object : BroadcastReceiver() {

        @SuppressLint("MissingPermission")
        override fun onReceive(context: Context, intent: Intent) {
            println(intent.action)
            val action: String = intent.action!!
            when (action) {
                BluetoothDevice.ACTION_FOUND -> {
                    // Discovery has found a device. Get the BluetoothDevice
                    // object and its info from the Intent.
                    val device: BluetoothDevice =
                        intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE)!!
                    val deviceName = device.name
                    val deviceHardwareAddress = device.address // MAC address
                    println("$deviceName $deviceHardwareAddress")
                }
            }
        }
    }

    override fun onDestroy() {
        super.onDestroy()
        bluetoothChatService.stop()
        unregisterReceiver(receiver)
    }

    private val mHandler: Handler = object : Handler() {
        override fun handleMessage(msg: Message) {
            val activity = this@MainActivity
            when (msg.what) {
                Constants.MESSAGE_STATE_CHANGE -> when (msg.arg1) {
                    BluetoothChatService.STATE_CONNECTED -> {
//                        setStatus(getString(R.string.title_connected_to, mConnectedDeviceName))
//                        mConversationArrayAdapter.clear()
                    }

                    BluetoothChatService.STATE_CONNECTING -> {
                        //setStatus(R.string.title_connecting)
                    }

                    BluetoothChatService.STATE_LISTEN, BluetoothChatService.STATE_NONE -> {
//                        setStatus(
//                            R.string.title_not_connected
//                        )
                    }
                }

                Constants.MESSAGE_WRITE -> {
                    val writeBuf = msg.obj as ByteArray
                    // construct a string from the buffer
                    val writeMessage = writeBuf.decodeToString()
                    //mConversationArrayAdapter.add("Me:  $writeMessage")
                    Toast.makeText(
                        activity, writeMessage, Toast.LENGTH_SHORT
                    ).show()
                }

                Constants.MESSAGE_READ -> {
                    val readBuf = msg.obj as ByteArray
                    // construct a string from the valid bytes in the buffer
                    val readMessage = readBuf.decodeToString()
                    Toast.makeText(
                        activity, readMessage, Toast.LENGTH_SHORT
                    ).show()
                    //mConversationArrayAdapter.add(mConnectedDeviceName + ":  " + readMessage)
                }

                Constants.MESSAGE_DEVICE_NAME -> {
                    // save the connected device's name
                    //mConnectedDeviceName = msg.data.getString(Constants.DEVICE_NAME)
                    if (null != activity) {
                        Toast.makeText(
                            activity, "Connected to "
                                    + msg.data.getString(Constants.DEVICE_NAME), Toast.LENGTH_SHORT
                        ).show()
                    }
                }

                Constants.MESSAGE_TOAST -> if (null != activity) {
                    Toast.makeText(
                        activity, msg.data.getString(Constants.TOAST),
                        Toast.LENGTH_SHORT
                    ).show()
                }
            }
        }
    }
}