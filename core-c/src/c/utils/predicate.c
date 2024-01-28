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

#include "utils/predicate.h"
#include "utils/malloc.h"

predicate *TRUE = 0;

predicate *new_predicate(char (*p)(void *thiz, void *params),
                         void *params) {
    predicate *p1 = (predicate *) mem_alloc(sizeof(predicate));
    p1->predicate = p;
    p1->params = params;
    return p1;
}

char is(predicate *p, void *thiz) {
    return p->predicate(thiz, p->params);
}

char predicate_equals(void *thiz, void *other) {
    return thiz == other;
}

predicate *equals(void *thiz) {
    return new_predicate(predicate_equals, thiz);
}

char predicate_true(void *thiz, void *params) {
    return 1;
}

predicate *_true() {
    if (TRUE == 0) {
        return TRUE = new_predicate(predicate_true, 0);
    }
    return TRUE;
}