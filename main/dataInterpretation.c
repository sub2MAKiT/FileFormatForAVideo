#include "includes.h"

// TYPES
// 0 - terminate
// 1 - boolean (char)
// 2 - integer
// 3 - unsigned long long
// 4 - long long
// 5 - double
// 6 - string

indexType interpretStruct(char * structData, indexType structDataSize) {
    indexType sizeOfStruct = 0;
    char readingString = 0;
    for(indexType i = 0; i < structDataSize; i++) {
        if(structData[i] > 0 && structData[i] < 6)
            sizeOfStruct += structData[i] == 1 ? 1 : (structData[i] == 2 ? sizeof(int) : 8);
        if(structData[i] == 6)
            readingString = 1;
        if(!(structData[i]))
            readingString = 0;

        if(readingString)
            sizeOfStruct++;

    }
    return sizeOfStruct;
}

//1, 3, 5, 1