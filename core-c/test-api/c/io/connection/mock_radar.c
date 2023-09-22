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

//
// Created by kirill on 18.09.23.
//

#include "devices/device.h"
#include "io/connection/mock_radar.h"

void mock_radar_start(void *thiz) {
    ((mock_radar*) thiz)->is_running = 1;
}

void mock_radar_stop(void *thiz) {
    ((mock_radar*) thiz)->is_running = 0;
}


char mock_radar_is_started(void *thiz) {
    return ((mock_radar*) thiz)->is_running;
}


void mock_radar_set_properties(void *thiz, void *) {

}


void *mock_radar_get_properties(void *thiz) {

}


void mock_on_find_device_handler(void *thiz, void (*on_find_device_handler)(void *thiz,void *)) {
    ((mock_radar*) thiz)->on_find_device_handler = on_find_device_handler;
}

radar* new_mock_radar() {
    mock_radar* r = (mock_radar *)(malloc(sizeof(mock_radar)));
    r->r.start = mock_radar_start;
    r->r.stop = mock_radar_stop;
    r->r.is_running = mock_radar_is_started;
    r->r.get_properties = mock_radar_get_properties;
    r->r.set_properties = mock_radar_set_properties;
    r->r.on_find_device_handler = mock_on_find_device_handler;
    r->queue.first = 0;
    r->queue.size = 0;
    r->queue.last = 0;
    return &(r->r);
}

void mock_radar_find(void *thiz) {
    mock_radar * thiz_ = (mock_radar*) thiz;
    if(thiz_->is_running && thiz_->queue.size) {
        thiz_->on_find_device_handler(thiz,(void *)list_remove_first(&(thiz_->queue)));
    }
}

void mock_radar_add_to_queue(void *thiz,void *d) {
    mock_radar * thiz_ = (mock_radar*) thiz;
    list_add(&(thiz_->queue),d);
}
