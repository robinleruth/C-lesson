#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"


int func(any_t i1, any_t i2){
    char *a = NULL;
    a = i2;
    printf("Elem is : %c\n", *a);
    return MAP_OK;
}


int main(){
    map_t m = hashmap_new();
    int a = 0;
    char c = 'c';
    any_t item = NULL;


    char *ptr = &c;

    a = hashmap_put(m, 5, (any_t)ptr);
    a = hashmap_put(m, 4, (any_t)ptr);
    a = hashmap_put(m, 5, (any_t)ptr);

    if(a != MAP_OK){
        printf("No\n");
    }else{
        printf("Ok\n");
    }

    a = hashmap_iterate(m, func, item);

    hashmap_free(m);
    return 0;
}
