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

#include "io/connection/connection.h"

char predicate_device_by_id(void *thiz, void *params) {
    device *thiz_ = (device *) thiz;
    unsigned long id = (unsigned long) params;
    return thiz_->id == id;
}

predicate *connection_device_by_id(unsigned long id) {
    return new_predicate(predicate_device_by_id, (void *) id);
}