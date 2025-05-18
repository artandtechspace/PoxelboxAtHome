#pragma once
#include "../../Debug.h"

namespace Letterfactory {
    // Holds the pixel map for each letter
    // X / Y pixel
    typedef bool Letter[5][4];

    /**
     * Takes in a character and returns a pointer to the letter that holds the correct representation
     * If no representation got found, this might return a nullptr
     */
    const Letter* getLetterFor(char c);

    /**
     * Takes in a letter and returns the x-size of it
     */
    const int getLetterWidth(const Letter* letter);

    /**
     * Returns the pixel width of a given word
     */
    const int getWordLength(const char* word, int spaceBetweenLetters);

    /**
     * Returns if the give at the given position is set
     */
    bool pixelAt(const Letter* letter, int x, int y);

    #if DEBUG
    /**
     * Only available for debugging purposes
     * Takes in a letter and a handler that takes in an x/y handle bool value
     * For each pixel of the letter the handler is then called
     */
    void debugLetter(const Letter* letter, void (*handle)(int,int,bool));
    #endif
}