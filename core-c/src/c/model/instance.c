//
// Created by kirill on 20.09.23.
//

#include "models/instance.h"
#include "io/connection/connection_buffered.h"

void instance_run(instance * inst) {
    for_each((&(inst->radars)), radar, {
        if(temp->is_running(temp)) {
            temp->scan(temp);
        }
    });

    for_each((&(inst->buffered_connections)), connection_buffer, {
        connection_buffer_read(temp);
    });
}
