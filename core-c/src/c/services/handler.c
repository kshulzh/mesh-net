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

#include "services/handlers.h"

message_handler *message_handlers() {
    static message_handler message_handlers1[256];
    return message_handlers1;
}

void handle_message(message *m) {
    buffer  b1;
    buffer_init(&b1,100,m->bytes);
    connection_message cm = *decode_connection_message(&b1);
    message_handlers()[cm.bm.type](m);
}

