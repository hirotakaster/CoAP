#include "coap/coap.h"

// CoAP server endpoint url callback
void callback_light(CoapPacket &packet, IPAddress ip, int port);

// CoAP client response callback
void callback_response(CoapPacket &packet, IPAddress ip, int port);

Coap coap;
bool LEDSTATE;

// CoAP server endpoint URL
void callback_light(CoapPacket &packet, IPAddress ip, int port) {
    Serial.println("[Light] ON/OFF");
    
    // send response
    char p[packet.payloadlen + 1];
    memcpy(p, packet.payload, packet.payloadlen);
    p[packet.payloadlen] = NULL;
    
    String message(p);

    if (message.equals("0"))
        LEDSTATE = false;
    else if(message.equals("1"))
        LEDSTATE = true;
        
    if (LEDSTATE) {
        coap.sendResponse(ip, port, packet.messageid, "1");
        RGB.color(255, 255, 255);
    } else { 
        coap.sendResponse(ip, port, packet.messageid, "0");
        RGB.color(0, 0, 0);
    }
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
    
    // LED Controll
    RGB.control(true);
    RGB.color(255, 255, 255);
    LEDSTATE = true;

    // add server url endpoints.
    // can add multiple endpoint urls.
    // exp) coap.server(callback_switch, "switch");
    //      coap.server(callback_env, "env/temp");
    //      coap.server(callback_env, "env/humidity");
    Serial.println("Setup Callback Light");
    coap.server(callback_light, "light");

    // client response callback.
    // this endpoint is single callback.
    Serial.println("Setup Response Callback");
    coap.response(callback_response);

    // start coap server/client
    coap.start();
}

void loop() {
    // send GET or PUT coap request to CoAP server.
    // To test, use microcoap server...etc
    // int msgid = coap.put(IPAddress(10, 0, 0, 1), 5683, "light", "1");
    Serial.println("Send Request");
    int msgid = coap.get(IPAddress(0, 0, 0, 0), 5683, "time");

    delay(1000);
    coap.loop();
}

/*
if you change LED, req/res test with coap-client(libcoap), run following.
coap-client -m get coap://(photon ip addr)/light
coap-client -e "1" -m put coap://(photon ip addr)/light
coap-client -e "0" -m put coap://(photon ip addr)/light
*/
