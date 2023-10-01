//
// Created by kirill on 28.09.23.
//

#ifndef MESH_NET_ROUTE_FUNCTIONS_H
#define MESH_NET_ROUTE_FUNCTIONS_H

#include "model/instance.h"
void route_udp(instance *c, unsigned long id,char *msg, unsigned int size);

void route_udp_res(instance *c, char *msg, unsigned int size);

#endif //MESH_NET_ROUTE_FUNCTIONS_H
