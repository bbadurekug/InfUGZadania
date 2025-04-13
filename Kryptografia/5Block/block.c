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

    char red;
    char green;
    char blue;
    char reserved;

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

    printf("Size: %d\nWidth: %d\nHeight: %d\nPlanes: %d\nBitCount: %d\nCompression: %d\nImageSize: %d\nXpixelsPerM: %d\nCyPixelsPerM: %d\nColorsUsed: %d\nColorsImportant: %d\n", fileInfoHeader.size, fileInfoHeader.width, fileInfoHeader.height, fileInfoHeader.planes, fileInfoHeader.bitCount, fileInfoHeader.compression, fileInfoHeader.imageSize, fileInfoHeader.xPixelsPerM, fileInfoHeader.yPixelsPerM, fileInfoHeader.colorsUsed, fileInfoHeader.colorsImportant);

    ColorTable fileColorTable[fileInfoHeader.width * fileInfoHeader.height];

    for(int i = 0; i < fileInfoHeader.width * fileInfoHeader.height; i++){

        fread(&fileColorTable[i].red, sizeof(char), 1, plain);
        fread(&fileColorTable[i].green, sizeof(char), 1, plain);
        fread(&fileColorTable[i].blue, sizeof(char), 1, plain);
        fread(&fileColorTable[i].reserved, sizeof(char), 1, plain);

    }

    //AM I READING THE PIXEL DATA WRONG? ASK CHAT

    for(int i = 0; i < 400; i++){

        fileColorTable[i].red = 0;
        fileColorTable[i].green = 0;
        fileColorTable[i].blue = 0;
        fileColorTable[i].reserved = 0;

    }

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

    for(int i = 0; i < fileInfoHeader.width * fileInfoHeader.height; i++){

        fwrite(&fileColorTable[i].red, sizeof(char), 1, copy);
        fwrite(&fileColorTable[i].green, sizeof(char), 1, copy);
        fwrite(&fileColorTable[i].blue, sizeof(char), 1, copy);
        fwrite(&fileColorTable[i].reserved, sizeof(char), 1, copy);

    }

    fclose(copy);
    fclose(plain);

    return 0;

}
