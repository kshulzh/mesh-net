package com.github.kshulzh.mesh_net.android.core.bluetooth

import android.annotation.SuppressLint
import android.bluetooth.BluetoothDevice
import java.io.ByteArrayInputStream

val connectionPool: MutableMap<String, BluetoothConnection> = mutableMapOf()

class BluetoothConnection(
    val bluetoothChatService: BluetoothChatService,
    val bluetoothDevice: BluetoothDevice,
    var inputStream: ByteArrayInputStream = ByteArrayInputStream(ByteArray(0))
) {
    var devPtr = 0L


    @SuppressLint("MissingPermission")
    fun open() {
        //bluetoothChatService.connect(this,false)

    }

    fun close() {

    }

    fun isConnected(): Boolean {
        return true
    }

    fun read(data: ByteArray, size: Int): Int {
        if (inputStream.available() > 0) {
            return inputStream.read(data)
        }
        return 0
    }

    fun write(data: ByteArray, size: Int) {
        //bluetoothChatService.connect(this,false)
        bluetoothChatService.write(data)
    }
}