//
// Created by kirill on 30.09.23.
//
#include "io/connection/connection.h"

char predicate_device_by_id(void *thiz, void *params) {
    device* thiz_ = (device*) thiz;
    unsigned long id = (unsigned long )params;
    return thiz_->id == id;
}

predicate * connection_device_by_id(unsigned long id) {
    return new_predicate(predicate_device_by_id, (void *) id);
}