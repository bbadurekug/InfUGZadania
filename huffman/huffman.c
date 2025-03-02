#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

/*void openFile(FILE *file, int function){

    //0 - normal read
    //1 - normal write
    //2 - binary read
    //3 - binary write

    char fileDirectory[255];

    while(file == NULL){

        printf("Podaj sciezke pliku\n");
        scanf("%s", fileDirectory);

        switch(function){
        case 0:
            file = fopen(fileDirectory, "r");
            break;
        case 1:
            file = fopen(fileDirectory, "w");
            break;
        case 2:
            file = fopen(fileDirectory, "rb");
            break;
        case 3:
            file = fopen(fileDirectory, "wb");
            break;
        }

        if((function == 0 || function == 2) && file == NULL) printf("Plik nie istnieje, podaj sciezke jeszcze raz\n");

    }

}*/

typedef struct HeapNode{

    char label;
    int frequency;
    struct HeapNode *left, *right;

} HeapNode;

int findValue(char value, HeapNode* heap, int heapSize){

   int index = -1;

   for(int i = 0; i < heapSize; i++){

        if(heap[i].label == value){

            index = i;
            return index;

        }

   }

   return index;

}

void heapify(HeapNode *heap, int heapSize){

    for(int i = heapSize-1; i >= 0; i--){

        if(((i-1)/2) >= 0 && heap[i].frequency < heap[(i-1)/2].frequency){

            //printf("edge %d %d\n", i, (i-1)/2);

            HeapNode temp = heap[i];
            heap[i] = heap[(i-1)/2];
            heap[(i-1)/2] = temp;

            i = heapSize-1;

        }

    }

}

void generateTree(HeapNode **heap, int *heapSize){

    while(*heapSize > 1){

        HeapNode left = (*heap)[0];
        (*heap)[0] =(*heap)[*heapSize - 1];
        (*heapSize)--;
        (*heap) = realloc((*heap), sizeof(HeapNode) * (*heapSize));
        heapify((*heap), *heapSize);

        {
        /*printf("left node: (%c %d)\n", left.label, left.frequency);

        for(int i = 0; i < heapSize; i++){

            printf("(%c %d)\n", heap[i].label, heap[i].frequency);

        }
        printf("\n");*/
        }

        HeapNode right = (*heap)[0];
        (*heap)[0] = (*heap)[*heapSize - 1];
        (*heapSize)--;
        (*heap) = realloc((*heap), sizeof(HeapNode) * (*heapSize));
        heapify((*heap), *heapSize);

        {
        /*printf("left node: (%c %d)\n", left.label, left.frequency);

        for(int i = 0; i < heapSize; i++){

            printf("(%c %d)\n", heap[i].label, heap[i].frequency);

        }
        printf("\n");*/
        }

        HeapNode newNode;
        newNode.label = '\0';
        newNode.frequency = left.frequency + right.frequency;
        newNode.left = malloc(sizeof(HeapNode));
        *newNode.left = left;
        newNode.right = malloc(sizeof(HeapNode));
        *newNode.right = right;

        //printf("new node: (%c %d)\n", newNode.label, newNode.frequency);

        (*heapSize)++;
        (*heap) = realloc((*heap), sizeof(HeapNode) * (*heapSize));
        (*heap)[*heapSize - 1] = newNode;
        heapify((*heap), *heapSize);


        /*for(int i = 0; i < *heapSize; i++){

            printf("(%c %d)\n", (*heap)[i].label, (*heap)[i].frequency);

        }
        printf("\n");*/

    }

}

void generateCodes(HeapNode* root, char* code, int depth, char codes[256][256]){ //przepisac

    if(root == NULL) return;

    if(root->label != '\0'){ //To I zmienic na cos innego pozniej

        code[depth] = '\0';
        strcpy(codes[(char)root->label], code);
        printf("Character: %c, Huffman Code: %s\n", root->label, code);
        return;

    }

    //lewo w drzewie
    code[depth] = '0';
    generateCodes(root->left, code, depth + 1, codes);


    //prawo w drzwie
    code[depth] = '1';
    generateCodes(root->right, code, depth + 1, codes);

}

/*void decodingTree(HeapNode* root, int depth, FILE *file){

    if(root == NULL) return;

    if(root->label != '\0'){ //To I zmienic na cos innego pozniej

        fwrite(&root->label, sizeof(char), 1, file);
        fwrite(&root->frequency, sizeof(char), 1, file);
        printf("Character: %c, Frequency: %d\n", root->label, root->frequency);
        return;

    }

    //lewo w drzewie
    decodingTree(root->left, depth + 1, file);


    //prawo w drzwie
    decodingTree(root->right, depth + 1, file);

}*/

void decodingTree(HeapNode* heap, int heapSize, FILE *file){

    for(int i = 0; i < heapSize; i++){

        fwrite(&heap[i].label, sizeof(char), 1, file);
        fwrite(&heap[i].frequency, sizeof(int), 1, file);

    }

}

int calcHowManyBits(HeapNode* heap, int heapSize, char codes[256][256]){

    int size = 0;

    for(int i = 0; i < heapSize; i++){

        size = size + (heap[i].frequency * strlen(codes[heap[i].label]));

        //printf("%d %d | %d || %d\n", heap[i].frequency, strlen(codes[heap[i].label]), (heap[i].frequency * strlen(codes[heap[i].label])), size);
    }

    return size;

}

int countBits(char codes[256][256], char fileDirectory[255]){

    FILE *file = NULL;

    while(file == NULL){

        file = fopen(fileDirectory, "r");

        if(file == NULL) printf("Plik nie istnieje\n");

    }

    char fileData = 0;
    char buffer = 0;
    char bits = 0;
    int bitsWrote = 0;

    while(fileData != EOF){

        fileData = fgetc(file);
        if(fileData == EOF) break;

        for(int i = 0; codes[(char)fileData][i] != '\0'; i++){

                if(bits == 8){

                    bits = 0;
                    buffer = 0;

                }

                if (codes[(char)fileData][i] == '1'){

                    buffer |= (1 << (7 - bits));

                }

                bits++;
                bitsWrote++;

        }

    }

    fclose(file);

    return bitsWrote;

}

void codingFile(){

    FILE *file = NULL;

    //openFile(file, 0);

    char fileDirectory[255];

    while(file == NULL){

        printf("Podaj sciezke pliku\n");
        scanf("%s", fileDirectory);

        file = fopen(fileDirectory, "r");

        if(file == NULL) printf("Plik nie istnieje, podaj sciezke jeszcze raz\n");

    }

    HeapNode *heap;
    int heapSize = 1;

    heap = calloc(sizeof(HeapNode), heapSize);

    int fileData = 0;
    int index = -1;

    //fileData = fgetc(file);
    //printf("%c\n", (char)fileData);

    printf("\nReading file data\n");

    while(fileData != EOF){

        //moze scanf("%c") poprwai?

        fileData = fgetc(file);
        if(fileData == EOF) break;
        //printf("%c\n", (char)fileData);

        index = findValue(fileData, heap, heapSize);

        if(index == -1){

            if(heapSize > 1) heap = realloc(heap, sizeof(HeapNode) * (heapSize));
            heap[heapSize-1].label = fileData;
            heap[heapSize-1].frequency = 1;
            heapSize++;

        }
        else{

            heap[index].frequency++;

        }

        heapify(heap, heapSize-1);

    }

    for(int i = 0; i < heapSize - 1; i++){

        printf("(%c %d)\n", heap[i].label, heap[i].frequency);

    }

    heapSize--;

    int howManyCharacters = heapSize;

    //kopia kopca zeby pozniej obliczyc ile zajmie bitow

    HeapNode *helpHeap = malloc(sizeof(HeapNode) * heapSize);

    for(int i = 0; i < heapSize; i++){

        helpHeap[i].label = heap[i].label;
        helpHeap[i].frequency = heap[i].frequency;

    }

    printf("\nCreating huffman tree\n");

    generateTree(&heap, &heapSize);

    printf("\nGenerating codes\n");

    char codes[256][256];
    char code[256];

    generateCodes(&heap[0], code, 0, codes);

    fclose(file);

/////////////////////////////////////////////////////////////

    FILE *inputFile = NULL;

    while(inputFile == NULL){

        inputFile = fopen(fileDirectory, "r");

        if(inputFile == NULL) printf("Plik nie istnieje, podaj sciezke jeszcze raz\n");

    }

    char outputDirectory[255];

    snprintf(outputDirectory, sizeof(outputDirectory), "%s.bin", fileDirectory);

    FILE *outputFile = NULL;

    while(outputFile == NULL){

        outputFile = fopen(outputDirectory, "wb");

        if(outputFile == NULL) printf("Plik nie istnieje, podaj sciezke jeszcze raz\n");

    }

    fwrite(&howManyCharacters, sizeof(unsigned char), 1, outputFile);
    //printf("test  %c    test", howManyCharacters);
    decodingTree(helpHeap, howManyCharacters, outputFile);  //wpisuje heap do pliku

    int howManyBits = countBits(codes, fileDirectory);

    printf("how many bits %d\n", howManyBits);

    fwrite(&howManyBits, sizeof(int), 1, outputFile);
    //printf("   test   %d    test   ", howManyBits);

    fileData = 0;
    char buffer = 0;
    char bits = 0;

    while(fileData != EOF){

        fileData = fgetc(inputFile);
        if(fileData == EOF) break;

        for(int i = 0; codes[(char)fileData][i] != '\0'; i++){

                if(bits == 8){

                    fwrite(&buffer, sizeof(char), 1, outputFile);
                    bits = 0;
                    buffer = 0;

                }

                if (codes[(char)fileData][i] == '1'){

                    buffer |= (1 << (7 - bits));

                }

                bits++;

        }

        //fprintf(outputFile, "%s", codes[(char)fileData]); //this is just plain text

        printf("%s", codes[(char)fileData]);

    }

    if(bits > 0){
        fwrite(&buffer, sizeof(char), 1, outputFile);
        bits = 0;
    }

    fclose(inputFile);
    fclose(outputFile);
    free(heap);
    free(helpHeap);

}

void decodingFile(){

    FILE *inputFile = NULL;

    char fileDirectory[255];

    while(inputFile == NULL){

        printf("Podaj sciezke pliku .bin\n");
        scanf("%s", fileDirectory);

        inputFile = fopen(fileDirectory, "rb");

        if(inputFile == NULL) printf("Plik nie istnieje, podaj sciezke jeszcze raz\n");

    }

    unsigned char buffer, howManyCharacters; //buffer uzyty do wczytywania labeli

    int freqBuffer; //uzyty do wczytania ilosci

    int howManyBits;

    int labelFrequency = 0; //0 - label, 1 - frequency

    fread(&howManyCharacters, sizeof(howManyCharacters), 1, inputFile);

    printf("this many characters %d\n", howManyCharacters);

    HeapNode *heap = malloc(sizeof(HeapNode) * howManyCharacters);

    for(int i = 0; i < (howManyCharacters * 2); i++){


        if(!labelFrequency){

            fread(&buffer, sizeof(buffer), 1, inputFile);

            printf("%c ", (unsigned char) buffer);

            heap[i/2].label = buffer;

            labelFrequency = 1;

        }
        else if(labelFrequency){

            fread(&freqBuffer, sizeof(freqBuffer), 1, inputFile);

            printf("%d\n", freqBuffer);

            heap[(i-1)/2].frequency = freqBuffer;

            labelFrequency = 0;

        }

    }

    for(int i = 0; i < howManyCharacters; i++){

        printf("(%c %d)\n", heap[i].label, heap[i].frequency);

    }
    printf("\n");

    int heapSize = (int)howManyCharacters;

    HeapNode *helpHeap = malloc(sizeof(HeapNode) * heapSize);

    for(int i = 0; i < heapSize; i++){

        helpHeap[i].label = heap[i].label;
        helpHeap[i].frequency = heap[i].frequency;

    }

    generateTree(&heap, &heapSize);

    char codes[256][256];
    char code[256];

    char codeBytes = 1;
    char *codeBuffer = malloc(sizeof(char) * codeBytes);
    codeBuffer[0] = '\0';

    generateCodes(&heap[0], code, 0, codes);

    FILE *outputFile = NULL;

    char outputDirectory[255];

    snprintf(outputDirectory, sizeof(outputDirectory), "%s.txt", fileDirectory);

    while(outputFile == NULL){

        outputFile = fopen(outputDirectory, "w");

        if(outputFile == NULL) printf("Plik nie istnieje, podaj sciezke jeszcze raz\n");

    }

    fread(&howManyBits, sizeof(int), 1, inputFile);

    printf("how many bits %d\n", howManyBits);

    int found = 0;

    while(fread(&buffer, sizeof(buffer), 1, inputFile)){

         //printf("(bitsleft %d)", howManyBits);

         if(howManyBits >= 8){

            for(int i = 7; i >= 0; i--){

                //printf("%d", (buffer >> i) & 1);//po kolei printuje bity

                codeBuffer[codeBytes-1] = ((buffer >> i) & 1) + 48;
                codeBytes++;
                codeBuffer = realloc(codeBuffer, sizeof(char) * codeBytes);
                codeBuffer[codeBytes-1] = '\0';

                for(int i = 0; i < howManyCharacters; i++){

                //Sprawdza po kolei bity - zamienic w funkcje

                //printf("Comparing %s %s\n", codeBuffer, codes[helpHeap[i].label]);

                    if(strcmp(codeBuffer, codes[helpHeap[i].label]) == 0){

                        codeBytes = 1;
                        codeBuffer = realloc(codeBuffer, sizeof(char) * codeBytes);
                        codeBuffer[codeBytes-1] = '\0';
                        printf("%c", helpHeap[i].label);
                        fwrite(&helpHeap[i].label, sizeof(char), 1, outputFile);
                        found = 1;

                    }

                }

            }

            if(found){
                found = 0;
            }

            howManyBits -= 8;

        }
        else{

            for(int i = 7; i >= 8 - howManyBits; i--){

                //printf("%d", (buffer >> i) & 1);//po kolei printuje bity

                codeBuffer[codeBytes-1] = ((buffer >> i) & 1) + 48;
                codeBytes++;
                codeBuffer = realloc(codeBuffer, sizeof(char) * codeBytes);
                codeBuffer[codeBytes-1] = '\0';

                for(int i = 0; i < howManyCharacters; i++){

                    //Sprawdza po kolei bity - zamienic w funkcje

                    //printf("Comparing %s %s\n", codeBuffer, codes[helpHeap[i].label]);

                    if(strcmp(codeBuffer, codes[helpHeap[i].label]) == 0){

                        codeBytes = 1;
                        codeBuffer = realloc(codeBuffer, sizeof(char) * codeBytes);
                        codeBuffer[codeBytes-1] = '\0';
                        printf("%c", helpHeap[i].label);
                        fwrite(&helpHeap[i].label, sizeof(char), 1, outputFile);

                    }

                }

            }

        }

    }

    printf("\n");

    printf("%s", codeBuffer);

    fclose(inputFile);
    fclose(outputFile);
    free(heap);
    free(helpHeap);
    free(codeBuffer);

}

//1000101001010000000000111101110111110001101111
//100010110101000000000011110111011111000110111100111101110010111
//       x

int main(){

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int choice = 0;

    while(choice == 0){

        printf("Wybierz akcje:\n1 - kodowanie pliku\n2 - odkodowanie pliku\n");
        scanf("%d", &choice);

        switch(choice){

            case 1:
                codingFile();
                printf("Plik pomyslnie zakodowany");
                break;

            case 2:
                decodingFile();
                printf("Plik pomyslnie odkodowany");
                break;

            default:

                choice = 0;
                break;

        }

    }

    return 0;

}
