// implementation of ports API on the embedded platform
#define EMBEDDED
#include "ports.h"

int port_send(Port *port,void* data){
    return 0;
}
int port_recv(Port *port,void** data){
    return 0;
}
int port_peek(Port *port){
    return 0;
}
int port_probe(Port *port){
    return 0;
}
