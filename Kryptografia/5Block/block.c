//Błażej Badurek

#include<stdio.h>
#include<stdlib.h>

typedef struct header{

    short signature;
    int fileSize;
    int reserved;
    int dataOffset;

} Header;

typedef struct infoHeader {

    int size;
    int width;
    int height;
    short planes;
    short bitCount;
    int compression;
    int imageSize;
    int xPixelsPerM;
    int yPixelsPerM;
    int colorsUsed;
    int colorsImportant;

} InfoHeader;

typedef struct colorTable {

    unsigned char blue;
    unsigned char green;
    unsigned char red;
    unsigned char reserved;

} ColorTable;

int main(){

    Header fileHeader;
    InfoHeader fileInfoHeader;

    FILE* plain = NULL;
    plain = fopen("plain.bmp", "rb");

    //if (plain != NULL) printf("B\n");

    fread(&fileHeader.signature, sizeof(char), 2, plain);
    fread(&fileHeader.fileSize, sizeof(char), 4, plain);
    fread(&fileHeader.reserved, sizeof(char), 4, plain);
    fread(&fileHeader.dataOffset, sizeof(char), 4, plain);

    printf("Signature: %d\nFileSize: %d\nReserved: %d\nDataOffset: %d\n", fileHeader.signature, fileHeader.fileSize, fileHeader.reserved, fileHeader.dataOffset);

    fread(&fileInfoHeader.size, sizeof(char), 4, plain);
    fread(&fileInfoHeader.width, sizeof(char), 4, plain);
    fread(&fileInfoHeader.height, sizeof(char), 4, plain);
    fread(&fileInfoHeader.planes, sizeof(char), 2, plain);
    fread(&fileInfoHeader.bitCount, sizeof(char), 2, plain);
    fread(&fileInfoHeader.compression, sizeof(char), 4, plain);
    fread(&fileInfoHeader.imageSize, sizeof(char), 4, plain);
    fread(&fileInfoHeader.xPixelsPerM, sizeof(char), 4, plain);
    fread(&fileInfoHeader.yPixelsPerM, sizeof(char), 4, plain);
    fread(&fileInfoHeader.colorsUsed, sizeof(char), 4, plain);
    fread(&fileInfoHeader.colorsImportant, sizeof(char), 4, plain);

    printf("Size: %d\nWidth: %d\nHeight: %d\nPlanes: %d\nBitCount: %d\nCompression: %d\nImageSize: %d\nXpixelsPerM: %d\nXpixelsPerM: %d\nColorsUsed: %d\nColorsImportant: %d\n", fileInfoHeader.size, fileInfoHeader.width, fileInfoHeader.height, fileInfoHeader.planes, fileInfoHeader.bitCount, fileInfoHeader.compression, fileInfoHeader.imageSize, fileInfoHeader.xPixelsPerM, fileInfoHeader.yPixelsPerM, fileInfoHeader.colorsUsed, fileInfoHeader.colorsImportant);

    ColorTable fileColorTable[2];

    fread(&fileColorTable[0].blue, sizeof(unsigned char), 1, plain);
    fread(&fileColorTable[0].green, sizeof(unsigned char), 1, plain);
    fread(&fileColorTable[0].red, sizeof(unsigned char), 1, plain);
    fread(&fileColorTable[0].reserved, sizeof(unsigned char), 1, plain);

    fread(&fileColorTable[1].blue, sizeof(unsigned char), 1, plain);
    fread(&fileColorTable[1].green, sizeof(unsigned char), 1, plain);
    fread(&fileColorTable[1].red, sizeof(unsigned char), 1, plain);
    fread(&fileColorTable[1].reserved, sizeof(unsigned char), 1, plain);

    printf("Color1: %u %u %u %u\nColor2: %u %u %u %u\n", fileColorTable[0].blue, fileColorTable[0].green, fileColorTable[0].red, fileColorTable[0].reserved, fileColorTable[1].blue, fileColorTable[1].green, fileColorTable[1].red, fileColorTable[1].reserved);

    fseek(plain, fileHeader.dataOffset, SEEK_SET);

    FILE* copy = NULL;
    copy = fopen("copy.bmp", "wb");

    fwrite(&fileHeader.signature, sizeof(char), 2, copy);
    fwrite(&fileHeader.fileSize, sizeof(char), 4, copy);
    fwrite(&fileHeader.reserved, sizeof(char), 4, copy);
    fwrite(&fileHeader.dataOffset, sizeof(char), 4, copy);

    fwrite(&fileInfoHeader.size, sizeof(char), 4, copy);
    fwrite(&fileInfoHeader.width, sizeof(char), 4, copy);
    fwrite(&fileInfoHeader.height, sizeof(char), 4, copy);
    fwrite(&fileInfoHeader.planes, sizeof(char), 2, copy);
    fwrite(&fileInfoHeader.bitCount, sizeof(char), 2, copy);
    fwrite(&fileInfoHeader.compression, sizeof(char), 4, copy);
    fwrite(&fileInfoHeader.imageSize, sizeof(char), 4, copy);
    fwrite(&fileInfoHeader.xPixelsPerM, sizeof(char), 4, copy);
    fwrite(&fileInfoHeader.yPixelsPerM, sizeof(char), 4, copy);
    fwrite(&fileInfoHeader.colorsUsed, sizeof(char), 4, copy);
    fwrite(&fileInfoHeader.colorsImportant, sizeof(char), 4, copy);

    fwrite(&fileColorTable[0].blue, sizeof(unsigned char), 1, copy);
    fwrite(&fileColorTable[0].green, sizeof(unsigned char), 1, copy);
    fwrite(&fileColorTable[0].red, sizeof(unsigned char), 1, copy);
    fwrite(&fileColorTable[0].reserved, sizeof(unsigned char), 1, copy);

    fwrite(&fileColorTable[1].blue, sizeof(unsigned char), 1, copy);
    fwrite(&fileColorTable[1].green, sizeof(unsigned char), 1, copy);
    fwrite(&fileColorTable[1].red, sizeof(unsigned char), 1, copy);
    fwrite(&fileColorTable[1].reserved, sizeof(unsigned char), 1, copy);

    unsigned char input;

    for(int i = 0; i < (fileInfoHeader.width * fileInfoHeader.height); i++){

        fread(&input, sizeof(unsigned char), 1, plain);
        printf("%u ", input);
        fwrite(&input, sizeof(unsigned char), 1, copy);

    }

    fclose(copy);
    fclose(plain);

    return 0;

}
