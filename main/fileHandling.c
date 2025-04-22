#include "includes.h"
#include "fileHandling.h"
#include "dataInterpretation.h"

// data - array of structs
// sizeOfData - amount of structs in our array
// dataDesc - description of the struct
// sizeOfDataDesc - size of data description

int fileWriting(MKTFile file) {
    // the void ** is a bit overengineered but... should be fine
    FILE* fptr = fopen(file.filename, "ab");

    ERROR_CHECK_HERE(fptr == NULL)

    indexType sizeOfStruct = interpretStruct(file.dataDesc, file.sizeOfDataDesc);

    // size of the struct descriptor
    fwrite(&file.sizeOfDataDesc, 1, sizeof(indexType), fptr);

    // the struct descriptor
    fwrite(file.dataDesc, 1, file.sizeOfDataDesc, fptr);

    // amount of structs
    fwrite(&file.sizeOfData, 1, sizeof(indexType), fptr);

    // size of the struct descriptor
    for(indexType i = 0; i < file.sizeOfData; i++)
        fwrite(file.data[i], 1, sizeOfStruct, fptr);

    fclose(fptr);

    return 0;
}

MKTFile fileReading(const char * name) {

    FILE* fptr = fopen(name, "rb");

    ERROR_CHECK_HERE(fptr == NULL)

    char *list;
    fseek(fptr, 0L, SEEK_END);
    unsigned long sizeOfFile = ftell(fptr);
    rewind(fptr);
    list = malloc(sizeOfFile);
    sizeOfFile = fread( list,1, sizeOfFile, fptr );
    fclose( fptr );

    printf("%d\n",*((unsigned long long*)list));
    MKTFile fileData;

    fileData.sizeOfDataDesc = *((unsigned long long*)(list));
    fileData.dataDesc = malloc(fileData.sizeOfDataDesc);
    memcpy(fileData.dataDesc,list+8,fileData.sizeOfDataDesc);
    fileData.sizeOfData = *((unsigned long long*)(list+8+fileData.sizeOfDataDesc));
    fileData.data = malloc(sizeof(void*) * fileData.sizeOfData);
    indexType sizeOfStruct = interpretStruct(fileData.dataDesc, fileData.sizeOfDataDesc);
    for(indexType i = 0; i < fileData.sizeOfData; i++){
        fileData.data[i] = malloc(sizeOfStruct);
        memcpy(fileData.data[i],list+8+fileData.sizeOfDataDesc+8+sizeOfStruct*i,sizeOfStruct);
    }
    return fileData;
}