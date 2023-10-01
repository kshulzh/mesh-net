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

#include "io/connection/connection_buffered.h"
#include "services/message.h"
#include "services/handlers.h"
#include "log/logger.h"


void connection_buffer_read(connection_buffer*thiz) {
    buffer * b= list_find_first(&(thiz->buffers),buffer_is_free());
    if(b == 0) {
        LOG_WARN("No free buffers")
        return;
    }
    b->is_locked = 1;
    buffer_reset(b);
    int count = thiz->c->read_array(thiz->c, b->start, b->size, 0);
    if(count>0 ) {
        thiz->on_read_handler(thiz, b);
    }
    b->is_locked = 0;
}

void default_on_read_handler(void *thiz, buffer *b) {
    connection_buffer *thizz = (connection_buffer*) thiz;
    message *m = message_of_buffer(b);
    m->c = thizz->c;
    handle_message(m);
    b->is_locked = 0;
}

connection_buffer * new_connection_buffer(connection *c) {
    connection_buffer * cb = New(connection_buffer);
    cb->c = c;
    cb->on_read_handler = default_on_read_handler;
    cb->buffers = ((instance*)c->r->inst)->buffers;
    return cb;
}