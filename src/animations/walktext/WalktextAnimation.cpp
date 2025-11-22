#include <Arduino.h>
#include "WalktextAnimation.h"
#include "../../config/ConfigSystem.h"
#include "../../config/entrys/StringEntry.h"
#include "../../config/MemoryOffsets.h"
#include "../../util/string/StringUtil.h"
#include "../../util/letterfactory/Letterfactory.h"
#include "../../globalconfig/GlobalConfig.h"
#include <FastLED.h>
#include "../../poxelbox/Poxelbox.h"

// Defines the amount of empty pixels that are between letters
#define PIXEL_BETWEEN_LETTERS 1

namespace WaltktextAnimation {

    StringEntry* text = ConfigSystem::mkString(
        MEM_OFFSET_CFG_TEXT_START, MEM_OFFSET_CFG_TEXT_END,
        "cfg/text/txt",
        &setup
    );

    auto textHue = ConfigSystem::mkByte(MEM_OFFSET_CFG_TEXT_HUE_TEXT,"cfg/text/huetxt");
    auto textSat = ConfigSystem::mkByte(MEM_OFFSET_CFG_TEXT_SATURATION_TEXT,"cfg/text/sattxt");
    auto backgroundHue = ConfigSystem::mkByte(MEM_OFFSET_CFG_TEXT_HUE_BG,"cfg/text/huebg");
    auto backgroundSat = ConfigSystem::mkByte(MEM_OFFSET_CFG_TEXT_SATURATION_BG,"cfg/text/satbg");
    auto slow = ConfigSystem::mkByte(MEM_OFFSET_CFG_TEXT_SLOW,"cfg/text/slow");

    /**
     * Prints the next frame and returns if the word has finished running after the frame
     */
    bool nextFrame(int offset){
        // Gets the length of available space
        const int screenLen = WIDTH;

        // Gets the word
        const char* word = text->get();

        // Length of the word
        const int wordLen = StringUtil::length(word);
        const int wordWidth = Letterfactory::getWordLength(word, PIXEL_BETWEEN_LETTERS);

        // Creates the colors
        auto clrBack = CHSV(backgroundHue->get(), backgroundSat->get(), GlobalConfig::globalBrightness->get());
        auto clrText = CHSV(textHue->get(), textSat->get(), GlobalConfig::globalBrightness->get());

        if(backgroundHue->get() == 0)
            clrBack = CHSV(0,0,0);

        if(textHue->get() == 0)
            clrText = CHSV(0,0,0);

        // Fills the stripe
        for(int i=0;i<LED_AMT;i++)
            Poxelbox::setPixel(i, clrBack);

        // Start position of the word to render
        const int startPos = screenLen - offset;

        // Pixel used to 
        int currentPixel = 0;

        for(int wIdx=0;wIdx<wordLen;wIdx++){
            // Gets the letter and width that the letter takes up
            auto letter = Letterfactory::getLetterFor(word[wIdx]);
            auto letterLen = Letterfactory::getLetterWidth(letter);

            // Optimisation:
            if(startPos + currentPixel > screenLen) break;

            // Iterates over each x/y pixel of the letter
            for(int x=0;x<letterLen;x++){
                int pixelXPos = startPos + currentPixel;
                // Advances the global overall x position pixel
                ++currentPixel;

                if(pixelXPos < 0) continue;
                if(pixelXPos >= screenLen) break;
                for(int y=0;y<4;y++){
                    // Calculates the id
                    if(!(*letter)[x][y]) continue;

                    // Sets the color
                    Poxelbox::setPixel(pixelXPos, 4-1-y, clrText);
                }

            }

            // Inserts a space after each letter
            currentPixel++;
        }

        // Sends the data
        FastLED.show();

        // Checks if the text is done and has fully been displayed
        return screenLen - offset + wordWidth <= 0;
    }

    int offset=0;

    void setup(){
        offset=0;
    }
    
    void loop() {
        static long next = 0;
        if(millis() < next) return;
        next = millis() + slow->get()*10;

        if(nextFrame(offset++))
            offset = 0;
    }

}