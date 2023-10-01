//
// Created by kirill on 30.09.23.
//

#include "services/route/messages.h"
#include "io/writers/writers.h"
#include "services/utils.h"
#include "io/readers/readers.h"

void encode_route_message(buffer *b, route_message *rm) {
    write_to_buffer(b,rm, sizeof(route_message));
}

route_message* decode_route_message(buffer *b) {
    return (route_message *) read_from_buffer(b, sizeof(route_message));
}

void encode_route_udp_message(buffer *b, route_udp_message *u) {
    write_to_buffer(b,u, sizeof(route_udp_message));
    encode_list(b, u->way, encode_device_id);
    encode_char_array(b, u->msg);
}

route_udp_message* decode_route_udp_message(buffer *b) {
    route_udp_message *rum = (route_udp_message *) read_from_buffer(b, sizeof(route_udp_message));
    rum->way = decode_list(b, decode_uint64);
    rum->msg = decode_char_array(b);
    return rum;
}
