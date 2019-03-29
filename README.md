# CoAP client, server library for Spark Photon, Spark Core.
<a href="http://coap.technology/" target=_blank>CoAP</a> simple server, client library for Particle Photon, Core.

## Source Code
This lightweight library source code are only 2 files. simple-coap.cpp, simple-coap.h.

## Example
Some sample sketches for Spark Core and Photon included(firmware/examples/).

 - coaptest.ino : simple request/response sample.
 - coapserver.ino : server endpoint url callback sample.

## How to use
In this exmples need CoAP server libcoap or microcoap server for check the example program. There is setting the libcoap on Ubuntu Linux. But if there don't use CoAP server(request/reseponse), following setting don't be needed.

    git clone https://github.com/obgm/libcoap
    cd libcoap/
    ./autogen.sh
    ./configure --disable-examples
    gcc -o coap-server ./examples/coap-server.c -I./include/coap/ -I. -L.libs -lcoap-1 -DWITH_POSIX
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.libs
    ./coap-server
    # next start Photon or Core, check the request/response.

## Arduino compatible
This library is Arduino compatible. That's version is <a href="https://github.com/hirotakaster/CoAP/tree/arduino">here</a>.
