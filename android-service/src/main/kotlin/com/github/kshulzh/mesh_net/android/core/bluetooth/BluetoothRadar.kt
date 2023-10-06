package com.github.kshulzh.mesh_net.android.core.bluetooth

import android.annotation.SuppressLint
import android.bluetooth.BluetoothAdapter

class BluetoothRadar(val bluetoothAdapter: BluetoothAdapter) {
    var radarPtr: Long = 0

    @SuppressLint("MissingPermission")
    fun start() {
        bluetoothAdapter.startDiscovery()
    }

    @SuppressLint("MissingPermission")
    fun stop() {
        bluetoothAdapter.startDiscovery()
    }

    @SuppressLint("MissingPermission")
    fun isDiscovering(): Boolean {
        return bluetoothAdapter.isDiscovering
    }

    fun scan() {

    }
}