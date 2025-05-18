#include <Arduino.h>
#include "Letterfactory.h"
#include "../../Debug.h"

namespace Letterfactory {

    // Letter: !
    const Letter LETTER_EXCLAMATION_MARK = {{1,1,0,1},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    // Letter: +
    const Letter LETTER_PLUS = {{0,0,1,0},{0,1,1,1},{0,0,1,0},{0,0,0,0},{0,0,0,0}};
    // Letter: -
    const Letter LETTER_MINUS = {{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,0,0,0},{0,0,0,0}};
    /// Letter _
    const Letter LETTER_UNDERSCORE = {{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,0,0,0},{0,0,0,0}};

    // Letter: <Space>
    const Letter LETTER_SPACE = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};

    // Unknown letter
    const Letter LETTER_UNKNOWN = {{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}};

    // All alphabet letters
    const Letter ALPHABET_LETTERS[26] = {
        // Letter: A
        {{0,1,1,1},{1,0,1,0},{0,1,1,1},{0,0,0,0},{0,0,0,0}},
        // Letter: B
        {{1,1,1,1},{1,1,0,1},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
        // Letter: C
        {{0,1,1,0},{1,0,0,1},{1,0,0,1},{0,0,0,0},{0,0,0,0}},
        // Letter: D
        {{1,1,1,1},{1,0,0,1},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
        // Letter: E
        {{1,1,1,1},{1,1,0,1},{1,0,0,1},{0,0,0,0},{0,0,0,0}},
        // Letter: F
        {{1,1,1,1},{1,0,1,0},{1,0,0,0},{0,0,0,0},{0,0,0,0}},
        // Letter: G
        {{0,1,1,0},{1,0,0,1},{1,0,1,1},{0,0,0,0},{0,0,0,0}},
        // Letter: H
        {{1,1,1,1},{0,0,1,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}},
        // Letter: I
        {{1,0,0,1},{1,1,1,1},{1,0,0,1},{0,0,0,0},{0,0,0,0}},
        // Letter: J
        {{0,0,1,0},{0,0,0,1},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
        // Letter: K
        {{1,1,1,1},{0,0,1,0},{0,1,1,0},{1,0,0,1},{0,0,0,0}},
        // Letter: L
        {{1,1,1,1},{0,0,0,1},{0,0,0,1},{0,0,0,0},{0,0,0,0}},
        // Letter: M
        {{1,1,1,1},{0,1,0,0},{0,0,1,0},{0,1,0,0},{1,1,1,1}},
        // Letter: N
        {{1,1,1,1},{0,1,0,0},{0,0,1,0},{1,1,1,1},{0,0,0,0}},
        // Letter: O
        {{0,1,1,0},{1,0,0,1},{1,0,0,1},{0,1,1,0},{0,0,0,0}},
        // Letter: P
        {{1,1,1,1},{1,0,1,0},{0,1,0,0},{0,0,0,0},{0,0,0,0}},
        // Letter: Q
        {{0,1,1,0},{1,0,0,1},{1,0,1,1},{0,1,0,1},{0,0,0,0}},
        // Letter: R
        {{1,1,1,1},{1,0,1,0},{0,1,0,1},{0,0,0,0},{0,0,0,0}},
        // Letter: S
        {{0,1,0,1},{1,0,0,1},{1,0,1,0},{0,0,0,0},{0,0,0,0}},
        // Letter: T
        {{1,0,0,0},{1,1,1,1},{1,0,0,0},{0,0,0,0},{0,0,0,0}},
        // Letter: U
        {{1,1,1,0},{0,0,0,1},{0,0,0,1},{1,1,1,0},{0,0,0,0}},
        // Letter: V
        {{1,1,0,0},{0,0,1,0},{0,0,0,1},{0,0,1,0},{1,1,0,0}},
        // Letter: W
        {{1,1,1,0},{0,0,0,1},{0,1,1,0},{0,0,0,1},{1,1,1,0}},
        // Letter: X
        {{1,0,1,1},{0,1,0,0},{1,0,1,1},{0,0,0,0},{0,0,0,0}},
        // Letter: Y
        {{1,0,0,0},{0,1,0,0},{0,0,1,1},{0,1,0,0},{1,0,0,0}},
        // Letter: Z
        {{1,0,0,1},{1,0,1,1},{1,1,0,1},{1,0,0,1},{0,0,0,0}}
    };

    // All numerical letters
    const Letter DIGIT_LETTERS[10] = {
        // Number: 0
        {{1,1,1,1},{1,0,0,1},{1,1,1,1},{0,0,0,0},{0,0,0,0}},
        // Number: 1
        {{1,0,0,1},{1,1,1,1},{0,0,0,1},{0,0,0,0},{0,0,0,0}},
        // Number: 2
        {{1,0,1,1},{1,0,1,1},{1,1,0,1},{0,0,0,0},{0,0,0,0}},
        // Number: 3
        {{1,0,0,1},{1,0,1,1},{1,1,1,1},{0,0,0,0},{0,0,0,0}},
        // Number: 4
        {{1,1,1,0},{0,0,1,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}},
        // Number: 5
        {{1,1,0,1},{1,0,1,1},{1,0,1,1},{0,0,0,0},{0,0,0,0}},
        // Number: 6
        {{1,1,1,1},{1,0,1,1},{1,0,1,1},{0,0,0,0},{0,0,0,0}},
        // Number: 7
        {{1,0,0,1},{1,0,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
        // Number: 8
        {{1,1,1,1},{1,0,1,1},{1,1,1,1},{0,0,0,0},{0,0,0,0}},
        // Number: 9
        {{1,1,0,1},{1,1,0,1},{1,1,1,1},{0,0,0,0},{0,0,0,0}}
    };

    const Letter* getLetterFor(char c) {
        if(c >= 'A' && c <= 'Z')
            c+=('a'-'A');

        if(c >= 'a' && c <= 'z'){
            c-='a';

            return &ALPHABET_LETTERS[c];
        }

        if(c >= '0' && c <= '9'){
            c-='0';
            return &DIGIT_LETTERS[c];
        }

        switch(c){
            case '!': return &LETTER_EXCLAMATION_MARK;
            case '+': return &LETTER_PLUS;
            case '-': return &LETTER_MINUS;
            case '_': return &LETTER_UNDERSCORE;
            case ' ': return &LETTER_SPACE;
        }

        return &LETTER_UNKNOWN;
    }


    const int getLetterWidth(const Letter* letter){
        // Checks for the special case of <space>
        if((*letter) == LETTER_SPACE)
            return 2;

        // Iterates over each column
        for(int x=0;x<5;x++){

            // Checks if the column is empty (only 0's)
            int sum=0;
            for(int y=0;y<4;y++)
                sum+=(*letter)[x][y];
            if(sum == 0)
                return x;
        }

        return 5;
    }

    const int getWordLength(const char* word, int spaceBetweenLetters){
        int len = 0;
        int idx=0;
        while(word[idx] != '\0'){
            len += Letterfactory::getLetterWidth(Letterfactory::getLetterFor(word[idx])) + spaceBetweenLetters;
            ++idx;
        }

        if(idx != 0)
            len-=spaceBetweenLetters;

        return len;
    }

    bool pixelAt(const Letter* letter, int x, int y){
        return (*letter)[x][y];
    }

    #if DEBUG
    void debugLetter(const Letter* letter, void (*handle)(int,int,bool)){

        int letterWidth = getLetterWidth(letter);

        for(int x=0;x<letterWidth;x++){
            for(int y=0;y<4;y++)
                handle(x,y,(*letter)[letterWidth-x-1][y]);
        }
    }
    #endif

}
