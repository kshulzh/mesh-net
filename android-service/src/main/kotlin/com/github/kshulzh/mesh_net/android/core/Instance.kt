package com.github.kshulzh.mesh_net.android.core

import java.util.Random

object Instance {
    init {
        init(Random().nextLong())
    }

    fun nothing() {

    }

    external fun init(id: Long)

    external fun start()

    external fun stop()

    external fun destroy()

    external fun devices(): ULongArray
}