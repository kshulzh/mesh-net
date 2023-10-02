package com.github.kshulzh.mesh_net.android.vpn

class IPv4Packet {
    var version: UByte = 4U
    var ihl: UByte = 0U
    var dscp: UByte = 0U
    var ecn: UByte = 0U
    var lenght: UShort = 0U
    var identification: UShort = 0U
    var flag1: Boolean = false
    var df: Boolean = false
    var mf: Boolean = false
    var fragmentOffset: UShort = 0U
    var ttl: UByte = 0U
    var protocol: UByte = 0U
    var checkSum: UShort = 0U
    var src: UInt = 0U
    var dest: UInt = 0U
    var params: List<UInt> = listOf()
    var data: UByteArray = UByteArray(0)
}

fun IPv4Packet.toArray(): ByteArray {
    this.ihl = (5 + params.size).toUByte()
    this.lenght = (20 + params.size * 4 + data.size).toUShort()
    var bytes = ByteArray(this.lenght.toInt())
    bytes[0] = (version.toUInt().shl(4).toUByte() + (ihl and 0xfu)).toByte()
    bytes[1] = (dscp.toUInt().shl(2).toUByte() + (ecn and 0x3u)).toByte()
    bytes[2] = (lenght.toUInt().shr(8) and 0xffu).toByte()
    bytes[3] = (lenght.toUInt() and 0xffu).toByte()
    bytes[4] = (identification.toUInt().shr(8) and 0xffu).toByte()
    bytes[5] = (identification.toUInt() and 0xffu).toByte()
    bytes[6] =
        (flag1.toInt().shl(7) or df.toInt().shl(6) or mf.toInt().shl(5) or (fragmentOffset.toInt()
            .shl(8).and(0x1f))).toByte()
    bytes[7] = (fragmentOffset.toUInt() and 0xffu).toByte()
    bytes[8] = ttl.toByte()
    bytes[9] = protocol.toByte()
    bytes[10] = (checkSum.toUInt().shr(8) and 0xffu).toByte()
    bytes[11] = (checkSum.toUInt() and 0xffu).toByte()

    bytes[12] = (src.shr(24) and 0xffu).toByte()
    bytes[13] = (src.shr(16) and 0xffu).toByte()
    bytes[14] = (src.shr(8) and 0xffu).toByte()
    bytes[15] = (src and 0xffu).toByte()

    bytes[16] = (dest.shr(24) and 0xffu).toByte()
    bytes[17] = (dest.shr(16) and 0xffu).toByte()
    bytes[18] = (dest.shr(8) and 0xffu).toByte()
    bytes[19] = (dest and 0xffu).toByte()

    var i = 20
    params.forEach {
        bytes[i] = (it.shr(24) and 0xffu).toByte()
        bytes[i + 1] = (it.shr(16) and 0xffu).toByte()
        bytes[i + 2] = (it.shr(8) and 0xffu).toByte()
        bytes[i + 3] = (it and 0xffu).toByte()
        i += 4
    }
    data.forEach {
        bytes[i] = it.toByte()
        i++
    }

    return bytes
}

fun IPv4Packet.set(bytes: UByteArray) {
    version = bytes[0].toUInt().shr(4).toUByte()
    ihl = bytes[0].toUInt().and(0xfu).toUByte()
    dscp = bytes[1].toUInt().shr(2).toUByte()
    ecn = bytes[1].toUInt().and(0x3u).toUByte()
    lenght = ((bytes[2].toUInt().shl(8)) or bytes[3].toUInt()).toUShort()
    identification = (bytes[4].toUInt().shl(8) or bytes[5].toUInt()).toUShort()
    flag1 = (bytes[6].toUInt().shr(7)).toBoolean()
    df = (bytes[6].toUInt().shr(6)).toBoolean()
    mf = (bytes[6].toUInt().shr(5)).toBoolean()
    fragmentOffset = (bytes[6].toUInt().and(0x1fu) or bytes[7].toUInt()).toUShort()
    ttl = bytes[8].toUByte()
    protocol = bytes[9].toUByte()
    checkSum = (bytes[10].toUInt().shl(8) or bytes[11].toUInt()).toUShort()
    src = (bytes[12].toUInt().shl(24) or bytes[13].toUInt().shl(16) or bytes[14].toUInt()
        .shl(8) or bytes[15].toUInt())
    dest = (bytes[16].toUInt().shl(24) or bytes[17].toUInt().shl(16) or bytes[18].toUInt()
        .shl(8) or bytes[19].toUInt())
    var i = 16
    params = (0 until (ihl.toInt() - 5)).map {
        i += 4
        (bytes[i].toUInt().shl(24) or bytes[i + 1].toUInt().shl(16) or bytes[i + 2].toUInt()
            .shl(8) or bytes[i + 3].toUInt())
    }
    i += 4
    data = UByteArray((lenght - i.toUShort()).toInt()) {
        bytes[it + i.toInt()].toUByte()
    }
}


fun Boolean.toInt() = if (this) 1 else 0

fun UInt.toBoolean() = this == 1u

fun mapIpToString(ip: UInt): String {
    return "${ip.shr(24)}.${ip.shr(16).and(0xffu)}.${ip.shr(8).and(0xffu)}.${ip.and(0xffu)}"
}
