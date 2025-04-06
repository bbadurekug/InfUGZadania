//Błażej Badurek

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define md5sumLength    47
#define sha1sumLength   55
#define sha224sumLength 71
#define sha256sumLength 79
#define sha384sumLength 111
#define sha512sumLength 143
#define b2sumLength     143

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

int main(){

    FILE *hash = NULL;
    hash = fopen("hash.txt", "r");

    if(hash != NULL){

        fclose(hash);
        system("rm hash.txt");
        system("touch hash.txt");

    }
    else{

        fclose(hash);
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

    printf("%s\n%s\n", md5sumPersonal, md5sumPersonal_);

    char sha1sumPersonal[sha1sumLength + 1];
    char sha1sumPersonal_[sha1sumLength + 1];

    fscanf(hash, "%s", sha1sumPersonal);
    fscanf(hash, "%s", sha1sumPersonal_);

    printf("%s\n%s\n", sha1sumPersonal, sha1sumPersonal_);

    char sha224sumPersonal[sha224sumLength + 1];
    char sha224sumPersonal_[sha224sumLength + 1];

    fscanf(hash, "%s", sha224sumPersonal);
    fscanf(hash, "%s", sha224sumPersonal_);

    printf("%s\n%s\n", sha224sumPersonal, sha224sumPersonal_);

    char sha256sumPersonal[sha256sumLength + 1];
    char sha256sumPersonal_[sha256sumLength + 1];

    fscanf(hash, "%s", sha256sumPersonal);
    fscanf(hash, "%s", sha256sumPersonal_);

    printf("%s\n%s\n", sha256sumPersonal, sha256sumPersonal_);

    char sha384sumPersonal[sha384sumLength + 1];
    char sha384sumPersonal_[sha384sumLength + 1];

    fscanf(hash, "%s", sha384sumPersonal);
    fscanf(hash, "%s", sha384sumPersonal_);

    printf("%s\n%s\n", sha384sumPersonal, sha384sumPersonal_);

    char sha1512umPersonal[sha512sumLength + 1];
    char sha1512umPersonal_[sha512sumLength + 1];

    fscanf(hash, "%s", sha1512umPersonal);
    fscanf(hash, "%s", sha1512umPersonal_);

    printf("%s\n%s\n", sha1512umPersonal, sha1512umPersonal_);

    char b2sumPersonal[b2sumLength + 1];
    char b2sumPersonal_[b2sumLength + 1];

    fscanf(hash, "%s", b2sumPersonal);
    fscanf(hash, "%s", b2sumPersonal_);

    printf("%s\n%s\n", b2sumPersonal, b2sumPersonal_);

    char hexPersonal;
    char hexPersonal_;

    for(int i = 0; i < md5sumLength; i++){

        hexPersonal = md5sumPersonal[i];
        hexPersonal_ = md5sumPersonal_[i];

    }

    fclose(hash);

    return 0;

}
