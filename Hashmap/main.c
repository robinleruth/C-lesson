#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"



int main(){
    map_t m = hashmap_new();
    int a = 0;
    char c = 'c';
    char *ptr = &c;
    a = hashmap_put(m, 5, (any_t)ptr);
    if(a != MAP_OK){
        printf("No");
    }else{
        printf("Ok");
    }
    return 0;
}
