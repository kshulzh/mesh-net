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

#include "devices/mock_device.h"
#include "devices/device.h"

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

mock_device* new_mock_device(device *d) {
    mock_device* md = New(mock_device);
    md->d = *d;
    radar *r = new_mock_radar();
    r->inst = &(md->inst);
    list_add(&(md->inst.radars),r);

    return md;
}

void mock_device_link(mock_device* md1,mock_device* md2) {
    mock_connection* mc1 = new_mock_connection1(256);
    mock_connection* mc2 = new_mock_connection1(256);
    mock_connection_link(mc1,mc2);
    mock_radar_add_to_queue(list_find_first(&md1->inst.radars,_true()),&(mc1->c));
    mock_radar_add_to_queue(list_find_first(&md2->inst.radars,_true()),&(mc2->c));
}

void mock_device_find(mock_device *md) {
    mock_radar_find(list_find_first(&md->inst.radars,_true()));
}