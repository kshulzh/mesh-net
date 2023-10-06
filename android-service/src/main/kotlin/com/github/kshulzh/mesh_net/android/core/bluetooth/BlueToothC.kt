package com.github.kshulzh.mesh_net.android.core.bluetooth

import android.bluetooth.BluetoothDevice

fun setup(bluetoothRadar: BluetoothRadar) {
    if (bluetoothRadar.radarPtr == 0L) {
        bluetoothRadar.radarPtr = setup1(bluetoothRadar)
    }
}

val devices = mutableSetOf<BluetoothDevice>()
external fun setup1(bluetoothRadar: BluetoothRadar): Long

external fun addToRadar(radarPtr: Long, socket: BluetoothConnection): Long

