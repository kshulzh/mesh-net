package com.github.kshulzh.mesh_net.android.core

import java.util.Random

object Instance {
    val id: ULong = Random().nextLong().toULong()

    fun init() {
        init(id.toLong())
    }

    external fun init(id: Long)

    external fun start()

    external fun stop()

    external fun destroy()

    external fun devices(): ULongArray
}