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

#include <stdarg.h>
#include "log/connection_logger.h"

LOGM_METHOD(connection, connection) {
    va_list ap;
    instance *inst = o->r->inst;
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    char *c = asctime(timeinfo);
    int i;
    for (i = 0; c[i] != '\n'; i++);
    c[i] = '\0';

    printf("[inst:%llu][con:%llu][%s][%s][%s:%d]", inst->this_device.id, o->d.id, c, level, file, line);


    va_start(ap, msg);
    vprintf(msg, ap);
    printf("\n");
}