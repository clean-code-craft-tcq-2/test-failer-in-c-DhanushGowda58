#include <stdio.h>
#include <assert.h>
#include <string.h>

#define MAX_NO_OF_PRIMARYCOLORS  5
const char* majorColor[MAX_NO_OF_PRIMARYCOLORS] = {"White", "Red", "Black", "Yellow", "Violet"};
const char* minorColor[MAX_NO_OF_PRIMARYCOLORS] = {"Blue", "Orange", "Green", "Brown", "Slate"};
int CountofColorCodesPrinted= 0;

struct colorcode_s
{
    char majorColor[25];
    char minorColor[25];  
    char colorCode;
};

colorcode_s ColorCodeParserStub(int majorColorIndex, int minorColorIndex);
void printColourCodeManualInConsoleStub(int majorColorIndex, int minorColorIndex, colorcode_s colorcode);
int printColorMapStub(void (*printColourCodeManualInConsole_FnPtr)(int,int,colorcode_s ));
 
int printColorMap() {
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    int i = 0, j = 0;
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            printf("%d | %s | %s\n", i * 5 + j, majorColor[i], minorColor[i]);
        }
    }
    return i * j;
}

colorcode_s ColorCodeParserStub(int majorColorIndex, int minorColorIndex)
{
    colorcode_s colorcode;
    strcpy(colorcode.majorColor, majorColor[majorColorIndex]);
    strcpy(colorcode.minorColor, minorColor[minorColorIndex]);
    colorcode.colorCode = (MAX_NO_OF_PRIMARYCOLORS * majorColorIndex) + minorColorIndex + 1;
    return colorcode;   
}

/* Stub code to use in test enviroment, in production actual console interfaces can be called */
void printColourCodeManualInConsoleStub(int majorColorIndex, int minorColorIndex, colorcode_s colorcode)
{
    printf("%d | %s | %s\n", majorColorIndex * 5 + minorColorIndex, colorcode.majorColor, colorcode.minorColor);
    CountofColorCodesPrinted++;
}

int printColorMapStub(void (*printColourCodeManualInConsole_FnPtr)(int,int,colorcode_s ))
{
    colorcode_s colorcode;
    int majorColorIndex = 0; 
    int minorColorIndex = 0;

    for(majorColorIndex = 0; majorColorIndex < MAX_NO_OF_PRIMARYCOLORS; majorColorIndex++) 
    {
        for(minorColorIndex = 0; minorColorIndex < MAX_NO_OF_PRIMARYCOLORS; minorColorIndex++) 
        {
            colorcode = ColorCodeParserStub(majorColorIndex,minorColorIndex);
            printColourCodeManualInConsole_FnPtr(majorColorIndex,minorColorIndex,colorcode);
        }
    }

    return (minorColorIndex * majorColorIndex);
}


int main() {
    colorcode_s colorcode;
    int majorColorIndex = 0; 
    int minorColorIndex = 0;
    int CountofColorCodesPrinted_expected = 0;

    void (*printColourCodeManualInConsole_FnPtr)(int,int,colorcode_s) = printColourCodeManualInConsoleStub;
    /*Test ColorCodeParserStub */
    colorcode = ColorCodeParserStub(majorColorIndex,minorColorIndex);
    assert(colorcode.colorCode == (majorColorIndex * 5 + minorColorIndex));
    /*Test printColorMapStub */
    CountofColorCodesPrinted_expected = printColorMapStub(printColourCodeManualInConsole_FnPtr);
    assert(CountofColorCodesPrinted_expected == CountofColorCodesPrinted);
    CountofColorCodesPrinted = 0;
    printf("All is well (maybe!)\n");
    return 0;
}
