#include "coap/coap.h"

// CoAP client response callback
void callback_response(CoapPacket &packet, IPAddress ip, int port);
Coap coap;

// CoAP client response callback
void callback_response(CoapPacket &packet, IPAddress ip, int port) {
    Serial.println("[Coap Response got]");

    char p[packet.payloadlen + 1];
    memcpy(p, packet.payload, packet.payloadlen);
    p[packet.payloadlen] = NULL;

    Serial.println(p);
}

void setup() {
    Serial.begin(9600);
    
    // client response callback.
    // this endpoint is single callback.
    Serial.println("Setup Response Callback");
    coap.response(callback_response);

    // start coap server/client
    coap.start();
}

void loop() {
    // send GET or PUT coap request to CoAP server.
    // To test, use libcoap, microcoap server...etc
    // int msgid = coap.put(IPAddress(10, 0, 0, 1), 5683, "light", "1");
    Serial.println("Send Request");
    int msgid = coap.get(IPAddress(XXX, XXX, XXX, XXX), 5683, "time");

    delay(1000);
    coap.loop();
}
