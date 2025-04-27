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

    unsigned char key[8][8];

    FILE* keyFile = NULL;
    keyFile = fopen("key.txt", "r");

    if(keyFile == NULL){

        fprintf(stderr, "NO KEY!");
        return 1;

    }
	
    for(int i = 0; i < 8; i++){

        if(fscanf(keyFile, "%s", key[i]) == 0){

            fprintf(stderr, "KEY SHOULD BE 8x8 CHARACTERS");
            return 1;

        }

        for(int j = 0; j < 8; j++){

            if(key[i][j] == '\0'){

                fprintf(stderr, "KEY SHOULD BE 8x8 CHARACTERS");
                return 1;

            }

        }

    }

    fclose(keyFile);

    Header fileHeader;
    InfoHeader fileInfoHeader;

    FILE* plain = NULL;
    plain = fopen("plain.bmp", "rb");

    //if (plain != NULL) printf("B\n");

    fread(&fileHeader.signature, sizeof(short), 1, plain);
    fread(&fileHeader.fileSize, sizeof(int), 1, plain);
    fread(&fileHeader.reserved, sizeof(int), 1, plain);
    fread(&fileHeader.dataOffset, sizeof(int), 1, plain);

    //printf("Signature: %d\nFileSize: %d\nReserved: %d\nDataOffset: %d\n", fileHeader.signature, fileHeader.fileSize, fileHeader.reserved, fileHeader.dataOffset);

    fread(&fileInfoHeader.size, sizeof(int), 1, plain);
    fread(&fileInfoHeader.width, sizeof(int), 1, plain);
    fread(&fileInfoHeader.height, sizeof(int), 1, plain);
    fread(&fileInfoHeader.planes, sizeof(short), 1, plain);
    fread(&fileInfoHeader.bitCount, sizeof(short), 1, plain);
    fread(&fileInfoHeader.compression, sizeof(int), 1, plain);
    fread(&fileInfoHeader.imageSize, sizeof(int), 1, plain);
    fread(&fileInfoHeader.xPixelsPerM, sizeof(int), 1, plain);
    fread(&fileInfoHeader.yPixelsPerM, sizeof(int), 1, plain);
    fread(&fileInfoHeader.colorsUsed, sizeof(int), 1, plain);
    fread(&fileInfoHeader.colorsImportant, sizeof(int), 1, plain);

    //printf("Size: %d\nWidth: %d\nHeight: %d\nPlanes: %d\nBitCount: %d\nCompression: %d\nImageSize: %d\nXpixelsPerM: %d\nXpixelsPerM: %d\nColorsUsed: %d\nColorsImportant: %d\n", fileInfoHeader.size, fileInfoHeader.width, fileInfoHeader.height, fileInfoHeader.planes, fileInfoHeader.bitCount, fileInfoHeader.compression, fileInfoHeader.imageSize, fileInfoHeader.xPixelsPerM, fileInfoHeader.yPixelsPerM, fileInfoHeader.colorsUsed, fileInfoHeader.colorsImportant);

    ColorTable fileColorTable[2];

    fread(&fileColorTable[0].blue, sizeof(unsigned char), 1, plain);
    fread(&fileColorTable[0].green, sizeof(unsigned char), 1, plain);
    fread(&fileColorTable[0].red, sizeof(unsigned char), 1, plain);
    fread(&fileColorTable[0].reserved, sizeof(unsigned char), 1, plain);

    fread(&fileColorTable[1].blue, sizeof(unsigned char), 1, plain);
    fread(&fileColorTable[1].green, sizeof(unsigned char), 1, plain);
    fread(&fileColorTable[1].red, sizeof(unsigned char), 1, plain);
    fread(&fileColorTable[1].reserved, sizeof(unsigned char), 1, plain);

    //printf("Color1: %u %u %u %u\nColor2: %u %u %u %u\n", fileColorTable[0].blue, fileColorTable[0].green, fileColorTable[0].red, fileColorTable[0].reserved, fileColorTable[1].blue, fileColorTable[1].green, fileColorTable[1].red, fileColorTable[1].reserved);

    fseek(plain, fileHeader.dataOffset, SEEK_SET);

    int rowPadding = (4 - (fileInfoHeader.width / 8) % 4) % 4;
    unsigned char rowDataECB[fileInfoHeader.height][fileInfoHeader.width / 8 + rowPadding];
    unsigned char rowDataCBC[fileInfoHeader.height][fileInfoHeader.width / 8 + rowPadding];

    for(int i = 0; i < fileInfoHeader.height; i++){

        fread(rowDataECB[i], sizeof(unsigned char), fileInfoHeader.width / 8 + rowPadding, plain);

        for(int j = 0; j < fileInfoHeader.width / 8 + rowPadding; j++){

            rowDataCBC[i][j] = rowDataECB[i][j];

        }

    }

    FILE* copy = NULL;
    copy = fopen("ecb_crypto.bmp", "wb");

    fwrite(&fileHeader.signature, sizeof(short), 1, copy);
    fwrite(&fileHeader.fileSize, sizeof(int), 1, copy);
    fwrite(&fileHeader.reserved, sizeof(int), 1, copy);
    fwrite(&fileHeader.dataOffset, sizeof(int), 1, copy);

    fwrite(&fileInfoHeader.size, sizeof(int), 1, copy);
    fwrite(&fileInfoHeader.width, sizeof(int), 1, copy);
    fwrite(&fileInfoHeader.height, sizeof(int), 1, copy);
    fwrite(&fileInfoHeader.planes, sizeof(short), 1, copy);
    fwrite(&fileInfoHeader.bitCount, sizeof(short), 1, copy);
    fwrite(&fileInfoHeader.compression, sizeof(int), 1, copy);
    fwrite(&fileInfoHeader.imageSize, sizeof(int), 1, copy);
    fwrite(&fileInfoHeader.xPixelsPerM, sizeof(int), 1, copy);
    fwrite(&fileInfoHeader.yPixelsPerM, sizeof(int), 1, copy);
    fwrite(&fileInfoHeader.colorsUsed, sizeof(int), 1, copy);
    fwrite(&fileInfoHeader.colorsImportant, sizeof(int), 1, copy);

    fwrite(&fileColorTable[0].blue, sizeof(unsigned char), 1, copy);
    fwrite(&fileColorTable[0].green, sizeof(unsigned char), 1, copy);
    fwrite(&fileColorTable[0].red, sizeof(unsigned char), 1, copy);
    fwrite(&fileColorTable[0].reserved, sizeof(unsigned char), 1, copy);

    fwrite(&fileColorTable[1].blue, sizeof(unsigned char), 1, copy);
    fwrite(&fileColorTable[1].green, sizeof(unsigned char), 1, copy);
    fwrite(&fileColorTable[1].red, sizeof(unsigned char), 1, copy);
    fwrite(&fileColorTable[1].reserved, sizeof(unsigned char), 1, copy);

    fseek(copy, fileHeader.dataOffset, SEEK_SET);

    for(int k = 0; k < fileInfoHeader.height / 8; k++){

        for(int l = 0; l < fileInfoHeader.width / 8 + rowPadding; l++){

            for(int i = k * 8; i < k * 8 + 8; i++){

                for(int j = l; j < l + 1; j++){

                    rowDataECB[i][j] = rowDataECB[i][j] ^ key[i % 8][j % 8];

                }

            }

        }

    }

    for(int i = 0; i < fileInfoHeader.height; i++){

        fwrite(rowDataECB[i], sizeof(unsigned char), fileInfoHeader.width / 8 + rowPadding, copy);

    }

    FILE* copy1 = NULL;
    copy1 = fopen("cbc_crypto.bmp", "wb");

    fwrite(&fileHeader.signature, sizeof(short), 1, copy1);
    fwrite(&fileHeader.fileSize, sizeof(int), 1, copy1);
    fwrite(&fileHeader.reserved, sizeof(int), 1, copy1);
    fwrite(&fileHeader.dataOffset, sizeof(int), 1, copy1);

    fwrite(&fileInfoHeader.size, sizeof(int), 1, copy1);
    fwrite(&fileInfoHeader.width, sizeof(int), 1, copy1);
    fwrite(&fileInfoHeader.height, sizeof(int), 1, copy1);
    fwrite(&fileInfoHeader.planes, sizeof(short), 1, copy1);
    fwrite(&fileInfoHeader.bitCount, sizeof(short), 1, copy1);
    fwrite(&fileInfoHeader.compression, sizeof(int), 1, copy1);
    fwrite(&fileInfoHeader.imageSize, sizeof(int), 1, copy1);
    fwrite(&fileInfoHeader.xPixelsPerM, sizeof(int), 1, copy1);
    fwrite(&fileInfoHeader.yPixelsPerM, sizeof(int), 1, copy1);
    fwrite(&fileInfoHeader.colorsUsed, sizeof(int), 1, copy1);
    fwrite(&fileInfoHeader.colorsImportant, sizeof(int), 1, copy1);

    fwrite(&fileColorTable[0].blue, sizeof(unsigned char), 1, copy1);
    fwrite(&fileColorTable[0].green, sizeof(unsigned char), 1, copy1);
    fwrite(&fileColorTable[0].red, sizeof(unsigned char), 1, copy1);
    fwrite(&fileColorTable[0].reserved, sizeof(unsigned char), 1, copy1);

    fwrite(&fileColorTable[1].blue, sizeof(unsigned char), 1, copy1);
    fwrite(&fileColorTable[1].green, sizeof(unsigned char), 1, copy1);
    fwrite(&fileColorTable[1].red, sizeof(unsigned char), 1, copy1);
    fwrite(&fileColorTable[1].reserved, sizeof(unsigned char), 1, copy1);

    fseek(copy1, fileHeader.dataOffset, SEEK_SET);

    unsigned char lastBlock[8][8];
    int data_i = 0;
    int data_j = 0;

    for(int k = 0; k < fileInfoHeader.height / 8; k++){

        for(int l = 0; l < fileInfoHeader.width / 8 + rowPadding; l++){

            data_i = k * 8;
            data_j = l;

            for(int i = 0; i < 8; i++){

                for(int j = 0; j < 8; j++){

                    if(data_i + data_j != 0){

                        rowDataCBC[data_i][data_j] = (rowDataCBC[data_i][data_j] ^ lastBlock[i][j]);

                    }

                    rowDataCBC[data_i][data_j] = rowDataCBC[data_i][data_j] ^ key[i][j];

                    data_j++;

                }

                data_i++;

            }

            data_i = k * 8;
            data_j = l;

            for(int i = 0; i < 8; i++){

                for(int j = 0; j < 8; j++){

                    lastBlock[i][j] = rowDataCBC[data_i][data_j];

                    data_j++;

                }

                data_i++;

            }

        }

    }

    for(int i = 0; i < fileInfoHeader.height; i++){

        fwrite(rowDataCBC[i], sizeof(unsigned char), fileInfoHeader.width / 8 + rowPadding, copy1);

    }

    fclose(copy1);
    fclose(copy);
    fclose(plain);

    return 0;

}
