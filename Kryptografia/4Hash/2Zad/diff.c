//Błażej Badurek

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define md5sumLength    32
#define sha1sumLength   40
#define sha224sumLength 56
#define sha256sumLength 64
#define sha384sumLength 96
#define sha512sumLength 128
#define b2sumLength     128

void getHash(const char* type){

    char input[58 + strlen(type) + 1];

    sprintf(input, "cat hash-.pdf personal.txt | %s | awk '{print $1}' >> hash.txt", type);
    input[strlen(input)] = '\0';

    //printf("%s %ld\n", input, strlen(input));

    system(input);

    sprintf(input, "cat hash-.pdf personal_.txt | %s | awk '{print $1}' >> hash.txt", type);
    input[strlen(input)] = '\0';

    //printf("%s %ld\n", input, strlen(input));

    system(input);

}

void getDifference(const char* type, FILE* diffFile, int size, char personal[size + 1], char personal_[size + 1]){

    static char* hexCodes[] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};

    char hexPersonal[5];
    char hexPersonal_[5];

	fprintf(diffFile, "cat hash-.pdf personal.txt | md5sum\ncat hash-.pdf personal_.txt | %s\n%s\n%s\n", type, personal, personal_);

	int hits = 0;

    for(int i = 0; i < size; i++){

		if(personal[i] >= '0' && personal[i] <= '9'){

			strcpy(hexPersonal, hexCodes[personal[i] - '0']);

		}
		else if(personal[i] >= 'a' && personal[i] <= 'f'){

			strcpy(hexPersonal, hexCodes[personal[i] - 'a' + 10]);

		}

		if(personal_[i] >= '0' && personal_[i] <= '9'){

			strcpy(hexPersonal_, hexCodes[personal_[i] - '0']);

		}
		else if(personal_[i] >= 'a' && personal_[i] <= 'f'){

			strcpy(hexPersonal_, hexCodes[personal_[i] - 'a' + 10]);

		}

		hexPersonal[4] = '\0';
		hexPersonal_[4] = '\0';

		for(int j = 0; j < 4; j++){

			if(hexPersonal[j] != hexPersonal_[j]) hits++;

		}

    }

	float percentage = (float)(hits) / (size * 4) * 100;

	fprintf(diffFile, "Liczba rozniacych sie bitow: %d z %d, procentowo %.0f%%\n\n", hits, size * 4, percentage);

}

int main(){

    FILE *hash = NULL;
    hash = fopen("hash.txt", "r");

    if(hash != NULL){

        fclose(hash);
        system("rm hash.txt");
        system("touch hash.txt");

    }
    else{

        system("touch hash.txt");

    }

    getHash("md5sum");
    getHash("sha1sum");
    getHash("sha224sum");
    getHash("sha256sum");
    getHash("sha384sum");
    getHash("sha512sum");
    getHash("b2sum");

    hash = fopen("hash.txt", "r");

    char md5sumPersonal[md5sumLength + 1];
    char md5sumPersonal_[md5sumLength + 1];

    fscanf(hash, "%s", md5sumPersonal);
    fscanf(hash, "%s", md5sumPersonal_);

    char sha1sumPersonal[sha1sumLength + 1];
    char sha1sumPersonal_[sha1sumLength + 1];

    fscanf(hash, "%s", sha1sumPersonal);
    fscanf(hash, "%s", sha1sumPersonal_);

    char sha224sumPersonal[sha224sumLength + 1];
    char sha224sumPersonal_[sha224sumLength + 1];

    fscanf(hash, "%s", sha224sumPersonal);
    fscanf(hash, "%s", sha224sumPersonal_);

    char sha256sumPersonal[sha256sumLength + 1];
    char sha256sumPersonal_[sha256sumLength + 1];

    fscanf(hash, "%s", sha256sumPersonal);
    fscanf(hash, "%s", sha256sumPersonal_);

    char sha384sumPersonal[sha384sumLength + 1];
    char sha384sumPersonal_[sha384sumLength + 1];

    fscanf(hash, "%s", sha384sumPersonal);
    fscanf(hash, "%s", sha384sumPersonal_);

    char sha512sumPersonal[sha512sumLength + 1];
    char sha512sumPersonal_[sha512sumLength + 1];

    fscanf(hash, "%s", sha512sumPersonal);
    fscanf(hash, "%s", sha512sumPersonal_);

    char b2sumPersonal[b2sumLength + 1];
    char b2sumPersonal_[b2sumLength + 1];

    fscanf(hash, "%s", b2sumPersonal);
    fscanf(hash, "%s", b2sumPersonal_);

    FILE* diff = NULL;
	diff = fopen("diff.txt", "w");

	getDifference("md5sum", diff, md5sumLength, md5sumPersonal, md5sumPersonal_);
	getDifference("sha1sum", diff, sha1sumLength, sha1sumPersonal, sha1sumPersonal_);
	getDifference("sha224sum", diff, sha224sumLength, sha224sumPersonal, sha224sumPersonal_);
	getDifference("sha256sum", diff, sha256sumLength, sha256sumPersonal, sha256sumPersonal_);
	getDifference("sha384sum", diff, sha384sumLength, sha384sumPersonal, sha384sumPersonal_);
	getDifference("sha512sum", diff, sha512sumLength, sha512sumPersonal, sha512sumPersonal_);
	getDifference("b2sum", diff, b2sumLength, b2sumPersonal, b2sumPersonal_);

	fclose(hash);
    fclose(diff);

    return 0;

}
