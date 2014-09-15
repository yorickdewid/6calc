#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#define VERSION "v1.0"

/*
 * Print the usage / help text describing options
 */
void usage(char *argv[]){
    printf(
        "IPv6 calculator %s\n"
        "\n"
        "usage: %s [\033[3mprefix] [subnet]\033[0m\n",
    VERSION, argv[0]);
}

int main(int argc, char *argv[]){
    if(argc < 3)
        usage(argv);

	return 0;
}
