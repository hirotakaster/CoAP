#include "coap.h"

// CoAP server endpoint url callback
void callback_light(CoapPacket &packet, IPAddress ip, int port);
void callback_switch(CoapPacket &packet, IPAddress ip, int port);

// CoAP client response callback
void callback_response(CoapPacket &packet, IPAddress ip, int port);


Coap coap;

// CoAP server endpoint URL
void callback_light(CoapPacket &packet, IPAddress ip, int port) {
    Serial.println("[Light]");
    
    // send response
    coap.sendResponse(ip, port, packet.messageid, (uint8_t *)"1", 1);
}

void callback_switch(CoapPacket &packet, IPAddress ip, int port) {
    Serial.println("[Switch]");
    
    // send response
    coap.sendResponse(ip, port, packet.messageid, (uint8_t *)"CLOSE", 5);
}


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

    // add server url endpoints
    coap.server(callback_light, "light");
    coap.server(callback_switch, "switch");

    // client response callback
    coap.response(callback_response);

    // start coap server/client
    coap.start();
}

void loop() {
    // send GET or PUT coap request to CoAP server.
    // int msgid = coap.put(IPAddress(xxx, xxx, xxx, xxx), 5683, "light", "1", 1);
    int msgid = coap.get(IPAddress(xxx, xxx, xxx, xxx), 5683, "light");
    delay(1000);
    coap.loop();
}
