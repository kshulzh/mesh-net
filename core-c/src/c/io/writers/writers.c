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

#include "io/writers/writers.h"

void encode_char_array(buffer *b, array_char *a) {
//    encode_uint32(b,a->size);
//    encode_link(b,(void*) 1);
    //write_int_to_buffer(b,a->size);
    write_dump(b, &(a->size), sizeof(uint32_t));
    write_dump(b, a->elements, a->size);
}
