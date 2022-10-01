
#define PARAM_DEBUG 0
#define PARAM_FILENAME 1
#define PARAM_HELP 2

struct parameters{
    char *filename;
};

void help();
void parseParams(int argc, char **argv);
int checkParam(int parameter);
struct parameters *getParameters();