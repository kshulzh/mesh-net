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

#ifndef MESH_NET_LOGGER_H
#define MESH_NET_LOGGER_H

#include<stdio.h>
#include<time.h>
#include <string.h>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define LOG_LEVEL_OFF 0
#define LOG_LEVEL_FATAL 100
#define LOG_LEVEL_ERROR 200
#define LOG_LEVEL_WARN 300
#define LOG_LEVEL_INFO 400
#define LOG_LEVEL_DEBUG 500
#define LOG_LEVEL_TRACE 600
#define LOG_LEVEL_ALL 0x0fffffff

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_INFO
#endif

void print_meta(char *level);

#define LOG(level, message, args...) \
print_meta(level);                 \
printf("[%s:%d] ", __FILENAME__, __LINE__); \
printf( message , args );          \
printf("\n");

#if LOG_LEVEL_FATAL <= LOG_LEVEL
#define LOG_FATAL_P(message, args...) LOG("FATAL",message,args)
#define LOG_FATAL(message) LOG("FATAL",message,NULL)
#else
#define LOG_FATAL_P(message, args...)
#define LOG_FATAL(message)
#endif

#if LOG_LEVEL_ERROR <= LOG_LEVEL
#define LOG_ERROR_P(message, args...) LOG("ERROR",message,args)
#define LOG_ERROR(message) LOG("ERROR",message,NULL)
#else
#define LOG_ERROR_P(message, args...)
#define LOG_ERROR(message)
#endif

#if LOG_LEVEL_WARN <= LOG_LEVEL
#define LOG_WARN_P(message, args...) LOG("WARN",message,args)
#define LOG_WARN(message) LOG("WARN",message,NULL)
#else
#define LOG_WARN_P(message, args...)
#define LOG_WARN(message)
#endif

#if LOG_LEVEL_INFO <= LOG_LEVEL
#define LOG_INFO_P(message, args...) LOG("INFO",message,args)
#define LOG_INFO(message) LOG("INFO",message,NULL)
#else
#define LOG_INFO_P(message, args...)
#define LOG_INFO(message)
#endif

#if LOG_LEVEL_DEBUG <= LOG_LEVEL
#define LOG_DEBUG_P(message, args...) LOG("DEBUG",message,args)
#define LOG_DEBUG(message) LOG("DEBUG",message,NULL)
#else
#define LOG_DEBUG_P(message, args...)
#define LOG_DEBUG(message)
#endif

#if LOG_LEVEL_TRACE <= LOG_LEVEL
#define LOG_TRACE_P(message, args...) LOG("TRACE",message,args)
#define LOG_TRACE(message) LOG("TRACE",message,NULL)
#else
#define LOG_TRACE_P(message, args...)
#define LOG_TRACE(message)
#endif

#define LOGM_METHOD_NAME(name) name##_print_log
#define LOGM_METHOD(name, type) void LOGM_METHOD_NAME(name)(type *o, char *level, char *file, int line, char *msg, ...)
#define LOGM(name, level, meta, msg, args...) LOGM_METHOD_NAME(name)(meta, level, __FILENAME__, __LINE__, msg, args)
#endif //MESH_NET_LOGGER_H
