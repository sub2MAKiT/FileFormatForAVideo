#include "includes.h"
#include "fileHandling.h"

typedef struct __attribute__((packed)) testStruct {
    char first;
    unsigned long long second;
    double third;
    char fourth;
} test;

int main() {
    const char * name = "testing";

    test template;
    template.first = 10;
    template.second = 100;
    template.third = 1.42108215;
    template.fourth = 0;


    test first = template;
    test first0 = template;
    test first1 = template;
    test first2 = template;

    first0.third = 7.131265332;
    first1.fourth = 1;
    first2.second = 1000000000;

    test ** array = malloc(sizeof(test *)*4);
    array[0] = &first;
    array[1] = &first0;
    array[2] = &first1;
    array[3] = &first2;

    char * dataDesc = malloc(4); 

    dataDesc[0] = 1;
    dataDesc[1] = 3;
    dataDesc[2] = 5;
    dataDesc[3] = 1;

    fileWriting((MKTFile){(void**)array, 4, dataDesc, 4, name});

    MKTFile file = fileReading(name);

    printf("%d   %d   %f   %d\n",((test*)(file.data[0]))[0].first,((test*)(file.data[1]))[0].second,((test*)(file.data[2]))[0].third,((test*)(file.data[3]))[0].fourth);

    free(array);
    free(dataDesc);

    return 0;
}