#include "./DrivingAnimation.h"
#include "../../poxelbox/Poxelbox.h"
#include <FastLED.h>
#include <Arduino.h>
#include "../../config/ConfigSystem.h"
#include "../../config/entrys/ByteEntry.h"
#include "../../config/MemoryOffsets.h"
#include "../../globalconfig/GlobalConfig.h"

namespace DrivingAnimation {
    ByteEntry* direction = ConfigSystem::mkByte(MEM_OFFSET_CFG_DRIVING_DIRECTION, "cfg/drv/dir", 0, 1);
    ByteEntry* turbo = ConfigSystem::mkByte(MEM_OFFSET_CFG_DRIVING_TURBO, "cfg/drv/turbo", 0, 1);
    ByteEntry* speed = ConfigSystem::mkByte(MEM_OFFSET_CFG_DRIVING_SPEED, "cfg/drv/speed", 20, 200);

    long nextFrameTime = 0;

    #define DISPLAY_WIDTH (BOX_SIZE_X * BOX_AMT_X)
    #define DISPLAY_HEIGHT BOX_SIZE_Y

    #define ARROW_VISUAL_LENGTH 5
    #define ARROW_VISUAL_HEIGHT 5
    #define TRAIL_EFFECT_LENGTH 10

    #define ARROW_SPACING (ARROW_VISUAL_LENGTH + TRAIL_EFFECT_LENGTH + 5) 
    #define NUM_ARROWS (DISPLAY_WIDTH / ARROW_SPACING + 2)

    int arrowTipX[NUM_ARROWS];

    const CHSV COLOR_BACKGROUND_HUE_BASE = CHSV(200, 220, 30);

    const CHSV COLOR_ARROW_FORWARD_BASE = CHSV(140, 255, 255);
    const CHSV COLOR_ARROW_BACKWARD_BASE = CHSV(170, 255, 255);
    const CRGB COLOR_ARROW_TURBO_BASE = CRGB::DeepPink;

    const uint8_t TRAIL_HUE_NORMAL = 150;
    const uint8_t TRAIL_HUE_TURBO = 25;
    const uint8_t TRAIL_SATURATION = 240;
    const uint8_t TRAIL_BRIGHTNESS_MAX = 220;
    const uint8_t TRAIL_BRIGHTNESS_MIN = 40;


    void drawPixel(int x, int y, CRGB color) {
        if (x >= 0 && x < DISPLAY_WIDTH && y >= 0 && y < DISPLAY_HEIGHT) {
            Poxelbox::leds[Poxelbox::getPBId(x, y)] = color;
        }
    }

    void drawArrowSymbol(int tipX, bool isForward, CRGB arrowColor, int arrowCenterY) {
        int y_offset_0 = arrowCenterY;
        int y_offset_1 = arrowCenterY - 1;
        int y_offset_2 = arrowCenterY + 1;
        int y_offset_3 = arrowCenterY - 2;
        int y_offset_4 = arrowCenterY + 2;

        y_offset_1 = constrain(y_offset_1, 0, DISPLAY_HEIGHT - 1);
        y_offset_2 = constrain(y_offset_2, 0, DISPLAY_HEIGHT - 1);
        y_offset_3 = constrain(y_offset_3, 0, DISPLAY_HEIGHT - 1);
        y_offset_4 = constrain(y_offset_4, 0, DISPLAY_HEIGHT - 1);


        if (isForward) {
            drawPixel(tipX, y_offset_0, arrowColor);
            drawPixel(tipX - 1, y_offset_1, arrowColor);
            drawPixel(tipX - 1, y_offset_2, arrowColor);
            drawPixel(tipX - 2, y_offset_0, arrowColor);
            drawPixel(tipX - 2, y_offset_3, arrowColor);
            drawPixel(tipX - 2, y_offset_4, arrowColor);
            drawPixel(tipX - 3, y_offset_0, arrowColor);
            drawPixel(tipX - 3, y_offset_1, arrowColor);
            drawPixel(tipX - 3, y_offset_2, arrowColor);
            drawPixel(tipX - 4, y_offset_0, arrowColor);
        } else {
            drawPixel(tipX, y_offset_0, arrowColor);
            drawPixel(tipX + 1, y_offset_1, arrowColor);
            drawPixel(tipX + 1, y_offset_2, arrowColor);
            drawPixel(tipX + 2, y_offset_0, arrowColor);
            drawPixel(tipX + 2, y_offset_3, arrowColor);
            drawPixel(tipX + 2, y_offset_4, arrowColor);
            drawPixel(tipX + 3, y_offset_0, arrowColor);
            drawPixel(tipX + 3, y_offset_1, arrowColor);
            drawPixel(tipX + 3, y_offset_2, arrowColor);
            drawPixel(tipX + 4, y_offset_0, arrowColor);
        }
    }


    void setup() {
        bool isForward = (direction->get() == 0);
        for (int i = 0; i < NUM_ARROWS; ++i) {
            if (isForward) {
                arrowTipX[i] = -ARROW_VISUAL_LENGTH - (i * ARROW_SPACING);
            } else {
                arrowTipX[i] = DISPLAY_WIDTH + ARROW_VISUAL_LENGTH -1 + (i * ARROW_SPACING);
            }
        }
        nextFrameTime = 0;
    }

    void loop() {
        if (millis() < nextFrameTime) {
            return;
        }
        nextFrameTime = millis() + speed->get();

        bool isForwardGlobal = (direction->get() == 0);
        bool isTurboActive = (turbo->get() == 1);
        uint8_t currentGlobalBrightness = GlobalConfig::globalBrightness->get();

        uint8_t bg_hue_offset = (millis() / 60) % 30;
        for (int x = 0; x < DISPLAY_WIDTH; x++) {
            CHSV bgColor = COLOR_BACKGROUND_HUE_BASE;
            bgColor.hue += ((x * 2 + bg_hue_offset) % 20) - 10;
            bgColor.v = map(currentGlobalBrightness, 0, 255, 0, COLOR_BACKGROUND_HUE_BASE.val);
            for (int y = 0; y < DISPLAY_HEIGHT; y++) {
                drawPixel(x, y, bgColor);
            }
        }

        int arrowCenterY = DISPLAY_HEIGHT / 2;

        for (int i = 0; i < NUM_ARROWS; ++i) {
            if (isForwardGlobal) {
                arrowTipX[i]++;
                if (arrowTipX[i] - ARROW_VISUAL_LENGTH >= DISPLAY_WIDTH) {
                    arrowTipX[i] -= NUM_ARROWS * ARROW_SPACING;
                }
            } else { // Backward
                arrowTipX[i]--;
                if (arrowTipX[i] + ARROW_VISUAL_LENGTH < 0) {
                     arrowTipX[i] += NUM_ARROWS * ARROW_SPACING;
                }
            }
        }

        for (int i = 0; i < NUM_ARROWS; ++i) {
            int currentTipX = arrowTipX[i];

            CRGB arrowDrawColor;
            uint8_t trailEffectHue;

            if (isTurboActive) {
                arrowDrawColor = COLOR_ARROW_TURBO_BASE;
                trailEffectHue = TRAIL_HUE_TURBO;
            } else {
                arrowDrawColor = isForwardGlobal ? COLOR_ARROW_FORWARD_BASE : COLOR_ARROW_BACKWARD_BASE;
                trailEffectHue = TRAIL_HUE_NORMAL;
            }
            arrowDrawColor.nscale8_video(currentGlobalBrightness);

            int trailStartVisualOffset = isForwardGlobal ? -(ARROW_VISUAL_LENGTH -1) : (ARROW_VISUAL_LENGTH -1);

            for (int j = 0; j < TRAIL_EFFECT_LENGTH; ++j) {
                int trailPixelX;
                if (isForwardGlobal) {
                    trailPixelX = currentTipX + trailStartVisualOffset - j;
                } else {
                    trailPixelX = currentTipX + trailStartVisualOffset + j;
                }

                uint8_t brightness = map(j, 0, TRAIL_EFFECT_LENGTH - 1, TRAIL_BRIGHTNESS_MAX, TRAIL_BRIGHTNESS_MIN);
                
                CHSV trailPixelColorHSV = CHSV(trailEffectHue, TRAIL_SATURATION, brightness);
                CRGB trailPixelColorRGB = trailPixelColorHSV;
                trailPixelColorRGB.nscale8_video(currentGlobalBrightness);

                drawPixel(trailPixelX, arrowCenterY, trailPixelColorRGB);
                if (DISPLAY_HEIGHT >= 3) {
                   drawPixel(trailPixelX, constrain(arrowCenterY - 1, 0, DISPLAY_HEIGHT -1), trailPixelColorRGB);
                   drawPixel(trailPixelX, constrain(arrowCenterY + 1, 0, DISPLAY_HEIGHT -1), trailPixelColorRGB);
                }
                 if (DISPLAY_HEIGHT >= 5 && ARROW_VISUAL_HEIGHT >=5) {
                    drawPixel(trailPixelX, constrain(arrowCenterY - 2, 0, DISPLAY_HEIGHT -1), trailPixelColorRGB);
                    drawPixel(trailPixelX, constrain(arrowCenterY + 2, 0, DISPLAY_HEIGHT -1), trailPixelColorRGB);
                }
            }

            drawArrowSymbol(currentTipX, isForwardGlobal, arrowDrawColor, arrowCenterY);
        }

        FastLED.show();
    }
}