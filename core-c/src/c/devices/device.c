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

#include "devices/device.h"

device *new_device(
        unsigned long id,
        unsigned long user_id) {
    device *d = New(device);
    d->id = id;
    d->user_id = user_id;
    return d;
}

char predicate_device_equals(void *thiz, void *params) {
    device *d1 = (device *) thiz;
    device *d2 = (device *) params;
    return d1 == d2 || (d1->id == d2->id && d1->user_id == d2->user_id);
}

predicate *device_equals(void *thiz) {
    return new_predicate(predicate_device_equals, thiz);
}

void encode_device(buffer *b, void *d) {
    write_long_to_buffer(b,((device*) d)->id);
    write_long_to_buffer(b,((device*) d)->user_id);
}

void encode_device_id(buffer *b, void *d) {
    write_long_to_buffer(b,((device*) d)->id);
}

void *decode_device(buffer *b) {
    return new_device(read_long_from_buffer(b), read_long_from_buffer(b));
}

void free_device(void *d) {
    mem_free((device *) d);
}

clone(device)