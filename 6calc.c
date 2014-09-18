#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define VERSION "v0.2"

#define USAGE { \
    fprintf(stderr, \
        "IPv6 calculator %s\n\n" \
        "Usage: %s [address]\n", \
        VERSION, pgm); \
        exit(1); \
    }

/*
 * IPv6 address structure
 */
struct addr6 {
    unsigned char subnet;
    unsigned short oct[4];
};

/* Program name without prefix */
static const char *pgm;

/*
 * Convert hexadecimal to decimal
 */
int hex_dec(char *hex){
    int i, length, sum=0;
    for(length=0; hex[length]!='\0'; ++length);
        for(i=0; hex[i]!='\0'; ++i, --length){
            if(hex[i]>='0' && hex[i]<='9')
                sum+=(hex[i]-'0')*pow(16,length-1);
            if(hex[i]>='A' && hex[i]<='F')
                sum+=(hex[i]-55)*pow(16,length-1);
            if(hex[i]>='a' && hex[i]<='f')
                sum+=(hex[i]-87)*pow(16,length-1);
        }
    return sum;
}

/*
 * Check if string is numeric
 */
int isnumeric(char *str){
    while(*str){
        if(!isdigit(*str))
            return 0;
        str++;
    }
    return 1;
}

/*
 * Check if string is hexadecimal
 */
int ishex(char *str){
    while(*str){
        if(!isxdigit(*str))
            return 0;
        str++;
    }
    return 1;
}

int main(int argc, char *argv[]){
    char *pch;
    int i=0;
    struct addr6 ai;

    memset(&ai, 0, sizeof(struct addr6));

    pgm = strrchr(argv[0], '/');
    pgm = pgm == NULL ? argv[0] : pgm + 1;
    if(argc<2)
        USAGE;

    /* Check for subnet */
    pch = strchr(argv[1], '/');
    if(pch==NULL){
        fprintf(stderr, "No subnet is defined\n");
        return 1;
    }

    pch++;
    if(!isnumeric(pch)){
        fprintf(stderr, "Invalid subnet\n");
        return 0;
    }

    ai.subnet = atoi(pch);
    if(1>ai.subnet||ai.subnet>128){
        fprintf(stderr, "Invalid subnet\n");
        return 0;
    }

    /* Validate address */
    char *addr = argv[1];
    addr[pch-addr-1] = '\0';
    pch = strtok(addr,":");
    while(pch!=NULL){
        if(i>7){
            fprintf(stderr, "Address invalid\n");
            return 0;
        }
        if(!ishex(pch)){
            fprintf(stderr, "Address invalid\n");
            return 0;
        }
        pch[4] = '\0';
        ai.oct[i] = (short)hex_dec(pch);
        printf("%d : %d\n", i, ai.oct[i]);
        pch = strtok(NULL,":");
        i++;
    }

    return 0;
}
