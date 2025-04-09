#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Ejercicio 1
void bubble_sort(float arreglo[], int longitud) {
    for (int iter = 0 ; iter < longitud - 1 ; iter++) {
        for (int i = 0 ; i < longitud - iter - 1; i++) {
            if (arreglo[i] > arreglo[i + 1]) {
                float aux = arreglo[i];
                arreglo[i] = arreglo[i + 1];
                arreglo[i + 1] = aux;
            }
        }
    }
}

float mediana(float* arreglo, int longitud){
    float med;
    if((longitud % 2) != 0){
        med = arreglo[longitud / 2];
    }
    else{
        med = (arreglo[longitud/2] + arreglo[(longitud/2) - 1])/2;
    }
    return med;
}

//Ejercicio 2
//a)
int string_len(char* str){
    int cant = 0;
    while(str[cant] != '\0'){
        cant++;;
    }
    return cant;
}

//b)
void string_reverse(char* str){
    int str_len = string_len(str);
    char str_copy[str_len + 1];

    for(int i = 0; i < str_len; i++){
        str_copy[i] = str[i];
    }
    str_copy[str_len] = '\0';

    for(int j = 0; j < str_len; j++){
        str[j] = str_copy[str_len - j - 1];
    }
}

// c)