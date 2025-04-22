#include "includes.h"

typedef struct fileStruct {
    void ** data;
    indexType sizeOfData;
    char * dataDesc;
    indexType sizeOfDataDesc;
    const char * filename;
} MKTFile;



int fileWriting(MKTFile file);
MKTFile fileReading(const char * name);