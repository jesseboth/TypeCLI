#include "include/params.h"
#include <stdio.h>

#define checkbit(val, bit) ((val & (1<<bit))>>bit)
#define setbit(val, bit) (val |= (1<<bit))

void help(){
    printf("TypeCLI: Typing speed test in the command line\n");
    printf("Useage: type <options>\n");
    printf("Options:\n");
    printf("\t--help     (-h): Display this message\n");
    printf("\t--debug    (-d): Print debug messages\n");
    printf("\t--filename (-f): Use a custom text file\n");
    printf("\t\tUsage - '-f <path to file>\n");
    printf("\t\tFormatting - each word on a newline\n");
}

static int strCompare(char *a, char *b){
    while(*a && *b){
        if(*a != *b){
            return 0;
        }
        a++;
        b++;
    }

    if(*a || *b){
        return 0;
    }

    return 1;
}

static int param(int set, int bit){
    static int p;

    if(set && bit > sizeof(int)){
        return -1;
    }

    if(set){
        setbit(p, bit);
    }

    return p;
}

static void storeStruct(int opt, char *arg){
    if(opt == PARAM_FILENAME){
        getParameters()->filename = arg;
    }
}

struct parameters *getParameters(){
    static struct parameters params;
    return &params;
}

int checkParam(int parameter){
    if(parameter > sizeof(int)){
        return -1;
    }

    return checkbit(param(0,0), parameter);
}

int findOption(char *opt){
    if(strCompare(opt, "-d") || strCompare(opt, "--debug")){
        return PARAM_DEBUG;
    }
    else if(strCompare(opt, "-f") || strCompare(opt, "--filename")){
        return PARAM_FILENAME;
    }
    else if(strCompare(opt, "-h") || strCompare(opt, "--help")){
        return PARAM_HELP;
    }

    return -1;
}

void parseParams(int argc, char **argv){
    int opt;
    for(int i = 0; i < argc; i++){
        if(argv[i][0] == '-'){
            opt = findOption(argv[i]);
            param(1, opt); 
            storeStruct(opt, argv[i+1]);
        }
    }
}