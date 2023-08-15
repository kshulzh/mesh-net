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

#ifndef MESH_NET_MOCK_RADAR_H
#define MESH_NET_MOCK_RADAR_H

#include <cstdlib>
#include "../../../src/headers/devices/device.h"
#include "../../../src/headers/io/connection/radar.h"
#include "../../../src/headers/containers/list.h"

typedef struct {
    radar radar;
    bool is_running;
    list queue;

} mock_radar;

void mock_radar_start(void *thiz) {
    ((mock_radar*) thiz)->is_running = true;
}

void mock_radar_stop(void *thiz) {
    ((mock_radar*) thiz)->is_running = false;
}


bool mock_radar_is_started(void *thiz) {
    return ((mock_radar*) thiz)->is_running;
}


void mock_radar_set_properties(void *thiz, void *) {

}


void *mock_radar_get_properties(void *thiz) {

}


void mock_on_find_device_handler(void *thiz, void (*on_find_device_handler)(device *)) {

}

radar* new_mock_radar() {
    mock_radar* r = (mock_radar *)(malloc(sizeof(mock_radar)));
    r->radar.start = ::mock_radar_start;
    r->radar.stop = ::mock_radar_stop;
    r->radar.is_started = ::mock_radar_is_started;
    r->radar.get_properties = ::mock_radar_get_properties;
    r->radar.set_properties = ::mock_radar_set_properties;
    r->radar.on_find_device_handler = ::mock_on_find_device_handler;
    return &(r->radar);
}
#endif //MESH_NET_MOCK_RADAR_H
