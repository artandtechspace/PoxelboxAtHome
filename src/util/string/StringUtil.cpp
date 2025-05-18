#include "StringUtil.h"

namespace StringUtil {

    // Returns the length of a given string
    int length(const char* str){
        if(str == nullptr) return 0;

        int idx=0;
        while(str[idx++] != '\0');

        return idx-1;
    }

}