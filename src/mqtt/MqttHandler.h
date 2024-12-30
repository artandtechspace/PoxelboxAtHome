#pragma once

namespace MqttHandler {
    
    // Setup fires once when the mc boots up
    void setup();
    // Loop is the maintainment method
    void loop();

    // Event: When a new message is retreived from the mqtt broker
    void onMessage(int msgSize);
}