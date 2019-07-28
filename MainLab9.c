//#include <stdio.h>
//#include <stdlib.h>
//#include "Lab9.h"
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>

int main(){
    char algo;
    setlocale(LC_ALL, "");
    algo = 160;
    if(algo == 'á'){
        int dato = 160;
        printf("%i",dato);
    }

    printf("%c",algo);

    return 0;
}