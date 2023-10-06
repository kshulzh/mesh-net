package com.github.kshulzh.mesh_net.android.vpn

import org.junit.Test

class IPv4PacketTest {
    @Test
    fun shouldDecodePacket() {
        var array = arrayOf(
            0x45,
            0x0,
            0x0,
            0x28,
            0x44,
            0xC6,
            0x40,
            0x0,
            0x40,
            0x6,
            0xDA,
            0x3D,
            0xC0,
            0xA8,
            0x0,
            0x65,
            0x8E,
            0xFA,
            0xCB,
            0xC4,
            0xA1,
            0x9,
            0x1,
            0xBB,
            0xB0,
            0xB8,
            0xDD,
            0xE4,
            0x0,
            0x0,
            0x0,
            0x0,
            0x50,
            0x4,
            0x0,
            0x0,
            0x62,
            0xB2,
            0x0,
            0x0
        ).map { it.toUByte() }.toUByteArray()
        var packet = IPv4Packet()
        packet.set(array)
        var cs = packet.checkSum;
        var arrayres = packet.toArray().toUByteArray()
        assert(cs ==packet.checkSum)
    }
}