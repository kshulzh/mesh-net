/*
 * Copyright (c) 2023-2024. Kirill Shulzhenko
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "io/connection/connection_buffered.h"
#include "model/instance.h"

instance *new_instance(device *d) {
    instance *i = New(instance);
    i->this_device = *d;
    i->g = new_graph(d);

    list_reset(&i->radars);
    list_reset(&i->devices);
    list_reset(&i->buffers);
    list_reset(&i->connections);
    list_reset(&i->buffered_connections);
    list_add(&i->devices, d);
    i->g->equals = predicate_device_equals;
    i->g->encode = encode_device;
    i->g->e_free = free_device;


    return i;
}

void instance_run(instance *inst) {
    for_each((&(inst->radars)), radar, {
        if (temp->is_running(temp)) {
            temp->scan(temp);
        }
    });

    for_each((&(inst->buffered_connections)), connection_buffer, {
        connection_buffer_read(temp);
    });
}

void instance_add_radar(instance *inst, void *r) {
    list_add(&inst->radars, r);
    ((radar *) r)->inst = inst;
}
