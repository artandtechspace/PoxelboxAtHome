#include "MqttHandler.h"
#include "../Secrets.h"
#include <WiFi.h>
#include <MqttClient.h>
#include "../config/ConfigSystem.h"
#include "../config/entrys/ByteEntry.h"

namespace MqttHandler
{
    // Base mqtt path to access all functionality of this device
    String basePath = "ats/smart/pb/";
    
    const char* ssid = WIFI_SSID;
    const char* pass = WIFI_PASS;
    const char broker[] = MQTT_BROKER;
    int port = MQTT_PORT;
    const char mqtt_user[] = MQTT_USER;
    const char mqtt_pass[] = MQTT_PASS;

    WiFiClient wifiClient;
    MqttClient mqttClient(wifiClient);

    IPAddress local_IP(10, 100, 16, 132);
    IPAddress gateway(10, 100, 16, 1);
    IPAddress subnet(255, 255, 255, 0);

    void maintainConnection(){
        if(WiFi.status() == WL_CONNECTED && mqttClient.connected()) return;

        Serial.println("[MqttHandler::maintainConnection]: (Re)connecting");
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }

        Serial.print("\tConnected with IP: ");
        Serial.println(WiFi.localIP());
        Serial.print("Connecting to the MQTT broker: ");
        Serial.print(broker);
        Serial.print(":");
        Serial.println(port);

        mqttClient.setUsernamePassword(mqtt_user, mqtt_pass);
        if (!mqttClient.connect(broker, port)) {

            Serial.print("MQTT connection failed! Error code = ");
            Serial.println(mqttClient.connectError());
            return;
        }

        Serial.println("Connection done. Registering topics:");

        // set the message receive callback
        mqttClient.onMessage(onMessage);

        // Subscribes the topics
        auto base = ConfigSystem::getFirstLLEntry();

        while(base != nullptr){
            String actualTopic = String(basePath)+String(base->getTopic());

            // Publishes the default
            mqttClient.beginMessage(actualTopic);
            base->writeMessage(&mqttClient);
            mqttClient.endMessage();

            // Subscribes the the topic
            mqttClient.subscribe(String(basePath)+String(base->getTopic()));
            Serial.print("\t[Topic::registered]");
            Serial.println(base->getTopic());
            base = base->next;
        }

        Serial.println("Topics registered.");
    }

    void setup()
    {
        Serial.print("[MqttHandler::setup]: Connecting to SSID: ");
        Serial.println(ssid);

        // Configure static IP
        if (!WiFi.config(local_IP, gateway, subnet))
            while(true) {
                Serial.println("STA Failed to configure");
                delay(1000);
            }

        WiFi.begin(ssid, pass);
    }

    void loop() {
        maintainConnection();
        mqttClient.poll();
    }

    void onMessage(int msgSize) {
        auto topic = mqttClient.messageTopic();

        if(!topic.startsWith(basePath)) return;
            topic = topic.substring(basePath.length());

        auto topicCStr = topic.c_str();

        auto base = ConfigSystem::getFirstLLEntry();

        while(1){
            if(base == nullptr) return;

            if(strcmp(base->getTopic(), topicCStr) == 0) break;

            base = base->next;
        }

        // Allocate memory for the message
        // +1 for the null terminator
        char* message = new char[msgSize + 1];
        if (message == nullptr) {
            Serial.println("Memory allocation failed!");
            return;
        }

        // Read the message into the char array
        int index = 0;
        while (mqttClient.available() && index < msgSize) {
            message[index++] = (char)mqttClient.read();
        }

        // Null-terminate the string
        message[index] = '\0';

        // Passes the message to the entry
        base->save(message);

        // Clean up (Free allocated memory)
        delete[] message;
    }
}