target_sources(${TARGET_NAME}
        PRIVATE
        io/readers/readers.c
        io/writers/writers.c
        io/buffer.c
        services/handler.c
        utils/predicate.c
        services/message.c
        model/instance.c
        io/connection/connection_buffered.c
        containers/list.c
        devices/device.c

        )