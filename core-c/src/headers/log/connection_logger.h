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

#ifndef MESH_NET_CONNECTION_LOGGER_H
#define MESH_NET_CONNECTION_LOGGER_H

#include "logger.h"
#include "../io/connection/connection.h"

LOGM_METHOD(connection, connection);

#define CONNECTION_LOG_LEVEL LOG_LEVEL_DEBUG
#if LOG_LEVEL_FATAL <= CONNECTION_LOG_LEVEL
#define CONNECTION_LOG_FATAL(c, message, args...) LOGM(connection,"FATAL",c,message,args)
#else
#define CONNECTION_LOG_FATAL(c, message, args...)
#endif

#if LOG_LEVEL_ERROR <= CONNECTION_LOG_LEVEL
#define CONNECTION_LOG_ERROR(c, message, args...) LOGM(connection,"ERROR",c,message,args)
#else
#define CONNECTION_LOG_ERROR(c, message, args...)
#endif

#if LOG_LEVEL_WARN <= CONNECTION_LOG_LEVEL
#define CONNECTION_LOG_WARN(c, message, args...) LOGM(connection,"WARN",c,message,args)
#else
#define CONNECTION_LOG_WARN(c, message, args...)
#endif

#if LOG_LEVEL_INFO <= CONNECTION_LOG_LEVEL
#define CONNECTION_LOG_INFO(c, message, args...) LOGM(connection,"INFO",c,message,args)
#else
#define CONNECTION_LOG_INFO(c, message, args...)
#endif

#if LOG_LEVEL_DEBUG <= CONNECTION_LOG_LEVEL
#define CONNECTION_LOG_DEBUG(c, message, args...) LOGM(connection,"DEBUG",c,message,args)
#else
#define CONNECTION_LOG_DEBUG(c, message, args...)
#endif

#if LOG_LEVEL_TRACE <= CONNECTION_LOG_LEVEL
#define CONNECTION_LOG_TRACE(c, message, args...) LOGM(connection,"TRACE",c,message,args)
#else
#define CONNECTION_LOG_TRACE(c, message, args...)
#endif

#endif //MESH_NET_CONNECTION_LOGGER_H
