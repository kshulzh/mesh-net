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

#include "io/buffer.h"
#include "utils/new.h"
#include "io/readers/readers.h"
#include "utils/math.h"
#include "io/connection/mock_connection.h"
#include "log/logger.h"


void mock_connection_open(void *thiz) {
    mock_connection *mc = (mock_connection *) thiz;
    mc->is_opened = 1;
}

void mock_connection_close(void *thiz) {
    mock_connection *mc = (mock_connection *) thiz;
    mc->is_opened = 0;

}

char mock_connection_is_connected(void *thiz) {
    mock_connection *mc = (mock_connection *) thiz;
    return mc->is_opened;
}

int32_t mock_connection_read_array(void *thiz, uint8_t *array, uint32_t size, uint32_t offset) {
    mock_connection *mc = (mock_connection *) thiz;
    if (mc->is_opened == 0) {
        return -1;
    }
    buffer *b = list_find_first(mc->buffers, buffer_is_locked());
    if (b == 0) {
        LOG_TRACE("No free buffers for read")
        return -1;
    }
    int s = min(size, (b->temp) - (b->start));
    mem_copy(array, b->start, s);
    b->is_locked = 0;
    return s;
}


int32_t mock_connection_write_array(void *thiz, uint8_t *data, uint32_t size) {
    mock_connection *mc = (mock_connection *) thiz;
    if (mc->is_opened == 0) {
        return -1;
    }
    mock_connection *mc_other = (mock_connection *) mc->paired;
    buffer *b = list_find_first(mc_other->buffers, buffer_is_free());

    b->is_locked = 1;
    buffer_reset(b);
    write_to_buffer(b, data, size);
    mc_other->is_ready = 1;
    return 0;
}

void *mock_connection_get_properties(void *thiz) {
    mock_connection *mc = (mock_connection *) thiz;
    return 0;
}

void mock_connection_set_properties(void *thiz, void *) {

}

mock_connection *new_mock_connection(list *buffers) {
    mock_connection *mc = New(mock_connection);

    mc->c.open = mock_connection_open;
    mc->c.close = mock_connection_close;
    mc->c.is_connected = mock_connection_is_connected;

    mc->c.set_properties = mock_connection_set_properties;
    mc->c.get_properties = mock_connection_get_properties;

    mc->c.read_array = mock_connection_read_array;

    mc->c.write_array = mock_connection_write_array;

    mc->buffers = buffers;
    mc->c.d.id = 0;
    mc->c.d.user_id = 0;

    return mc;
}

mock_connection *new_mock_connection1(int size) {
    char *b1 = (char *) mem_alloc(size * sizeof(char));
    buffer *buf1 = New(buffer);
    buffer_init(buf1, size, b1);
    return new_mock_connection(buf1);
}

void mock_connection_link(mock_connection *c1, mock_connection *c2) {
    c1->paired = c2;
    c2->paired = c1;
}