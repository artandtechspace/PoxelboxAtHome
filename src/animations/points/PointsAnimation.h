#pragma once

namespace PointsAnimation {

    typedef struct {
        // Decay-percentage value
        float perc;
        // Position
        int x;
        int y;

        // HUE-Color value (0-255)
        int clr;
    } Point;

    // Internal function to reset a point
    void resetPoint(Point* pt);

    void setup();

    void loop();

}
