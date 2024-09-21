#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include <stdbool.h>
#include "handlers.h"
#include "error_codes.h"

int main(int argc, char* argv[]) {

	if(argc < 2){
        return 1;
    }

    char *firstArg = argv[1];
    bool nFlag = false;
    char a;
    char *resPath['NULL'];

    if (firstArg[0] == '-' || firstArg[0] == '/'){
        if(firstArg[1] == 'n'){
            nFlag = true;
            a = firstArg[2];
            *resPath = argv[3] ; 
        }else{
            nFlag = false;
            a = firstArg[1];
        }
        switch (a)
        {
        case 'd':
            HandlerOptD(argv[2], nFlag, *resPath);
            break;
        case 'i':
            HandlerOptI(argv[2], nFlag, *resPath);
            break;
        case 's':
            HandlerOptS(argv[2], nFlag, *resPath);
            break;
        case 'a':
            HandlerOptA(argv[2], nFlag, *resPath);
            break;
        default:
            printf("ERROR");
            break;
        }
    }else{
        return 1;
    }

}