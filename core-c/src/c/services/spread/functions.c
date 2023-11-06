/*
 * Copyright (c) 2023. Kirill Shulzhenko
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

#include "services/spread/functions.h"
#include "services/spread/messages.h"
#include "services/utils.h"

static uint8_t id = 0;
void spread_udp(instance *c, uint8_t *msg, uint32_t size) {
    spread_udp_message sum;
    sum.sm.type = UDP;
    sum.sm.bm.type = SPREAD;
    array_char ac;
    ac.size = size;
    ac.elements = msg;
    sum.msg = &ac;
    sum.src_id = c->this_device.id;
    sum.sm.bm.message_id = (c->this_device.id <<8) | id++;
    buffer * b= list_find_first(&c->buffers,buffer_is_free());

    if(b!=0) {
        b->is_locked = 1;
        buffer_reset(b);
        encode_spread_udp_message(b,&sum);
        sum.sm.bm.size = buffer_message_set_size(b);
        for_each((&(c->connections)),connection,{
            temp->write_array(temp,b->start,b->temp - b->start);
        })
        b->is_locked = 0;
    }
}

void spread_udp_res(message *m) {
    instance *i = m->c->r->inst;
    for_each((&(i->connections)),connection,{
        if(temp->d.id != m->c->d.id) {
            temp->write_array(temp,m->bytes,m->bm.size);
        }
    })
}