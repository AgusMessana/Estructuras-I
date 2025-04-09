#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Ejercicio 1
/* int main(){
    int num1 = 2;
    char car1 = 'b';
    char pal1[] = "hola";

    int* dir_num1 = &num1;
    char* dir_car1 = &car1;

    printf("Direccion numero: %p\n", dir_num1);
    printf("Direccion caracter: %p\n", dir_car1);

    for(int i = 0; i < 5; i++){
        printf("Direccion de letra %c: %p\n", pal1[i], &pal1[i]);
    }

    return 0;
} */

//Ejercicio 2
void set_first(int numeros[]){
    numeros[0] = 0;
}

/* int main(){
    int numeros[5] = {2, 3, 10, 7, -3};
    printf("%s", "Arreglo original:\n");
    for(int i = 0; i < 5; i++){
        printf("El numero en la posicion %d es %d: \n", i, numeros[i]);
    }
    
    set_first(numeros);
    
    printf("%s", "\nArreglo modificado:\n");
    for(int j = 0; j < 5; j++){
        printf("El nuevo numero en la posicion %d es %d: \n", j, numeros[j]);
    }
    return 0;
} */

//Ejercicio 3
void set_in(int* num){
    if(*num != 0){
        *num = 1;
    }
}

/* int main(){
    int num;
    printf("Ingrese un numero entero: ");
    scanf ("%d", &num);
    printf("El numero ingresado es: %d\n", num);

    set_in(&num);
    printf("El nuevo numero es %d: \n", num);

    return 0;
} */

//Ejercicio 4
void swap(int* num1, int* num2){
    int copia = *num2;
    *num2 = *num1;
    *num1 = copia;
}

/* int main(){
    int num1, num2;
    printf("Ingrese dos numeros: ");
    scanf("%d %d", &num1, &num2);
    printf("num1 = %d, num2 = %d\n", num1, num2);

    swap(&num1, &num2);
    printf("num1 = %d, num2 = %d\n", num1, num2);

    return 0;
} */

//Ejercicio 5
// La función malloc() asigna bytes de tamaño y devuelve un puntero a la memoria asignada. La memoria no se inicializa.
// Si el tamaño es 0, mmaloc() retorna NULL o un valor de puntero único que puede pasar correctamente con free() posteriormente.

//Ejercicio 6
char* get_new_line(void){
    char* buffer = malloc(100*sizeof(char));

    if (buffer == NULL){
        printf("Error al asignar memoria\n");
        return NULL;
    }
    
    if(fgets(buffer, 100, stdin) == NULL){
        free(buffer);
        return NULL;
    }

    size_t len = strlen(buffer);
    if (buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    return buffer;
}

/* int main(){
    printf("Ingrese una linea de texto: ");
    char* linea = get_new_line();

    if(linea != NULL){
        printf("Linea ingresada: %s", linea);
        free(linea);
    }
    else{
        printf("Error al leer linea\n");
    }

    return 0;
} */

//Ejercicio 7
/* int main(){
    char* buffer = malloc(100*sizeof(char));
    if(buffer == NULL){
        printf("Error al guardar memoria\n");
        return 0;
    }
    free(buffer);
    free(buffer);

    return 0;
} */
//Si se hace un free doble, se detecta un error core dumped.

//Ejercicio 8
//a)
int area(int n){
    return n*n;
}

int apply(int(*func)(int), int x){
    return func(x);
}

/* int main(){
    int num;
    printf("Ingrese un numero entero positivo: ");
    scanf("%d", &num);

    int res = apply(&area, num);

    printf("El area del cuadrado es de %d\n", res);
    return 0;
} */

//b)
void apply_in(int(*func)(int), int* num){
    *num = func(*num);
}

/* int main(){
    int num;
    printf("Ingrese un numero entero positivo: ");
    scanf("%d", &num);

    printf("Valor actual de num: %d\n", num);
    apply_in(&area, &num);
    printf("Valor nuevo de num: %d\n", num);

    return 0;
} */

//c)
typedef void (*VisitorFunc)(int);

void imprimir(int x){
    printf("%d\n", x);
}
VisitorFunc func = imprimir;

void recorre(VisitorFunc func, int numeros[], int longi){
    for (int i = 0; i < longi; i++){
        func(numeros[i]);
    }
}

/* int main(){
    int longi = 5;
    int numeros[] = {3, 1, 5, -8, 10};
    
    recorre(imprimir, numeros, longi);

    return 0;
} */

//d)i)a)
int sucesor (int n){
    return n+1;
}

/* int main(){
    int num;
    printf("Ingrese un numero entero positivo: ");
    scanf("%d", &num);

    int res = apply(&sucesor, num);

    printf("El area del cuadrado es de %d\n", res);

    return 0;
} */

//d)i)b)
/* int main(){
    int num;
    printf("Ingrese un numero entero positivo: ");
    scanf("%d", &num);

    printf("Valor actual de num: %d\n", num);
    apply_in(&sucesor, &num);
    printf("Valor nuevo de num: %d\n", num);

    return 0;
} */

//d)ii)c)
//Es el ejemplo que usé. Imprime los valores del array.

//9)
/* int main(){
    int* punt;
    int x = 7, y = 5;
    punt = &x;
    *punt = 4;
    printf("%d %d", x, y);
    return 0;
} */

//Ejercicio 12
typedef struct{
    float x;
    float y;
} punto;

punto medio(punto punto1, punto punto2){
    punto punto_medio;

    punto_medio.x = (punto1.x + punto2.x)/2;
    punto_medio.y = (punto1.y + punto2.y)/2;

    return punto_medio;
}

/* int main(){
    punto p1 = {4, 5};
    punto p2 = {6, -2};

    punto p_medio = medio(p1, p2);
    printf("El punto medio entre p1 y p2 es x = %f, y = %f\n", p_medio.x, p_medio.y);

    return 0;
} */

//Ejercicio 13
//a)
typedef enum{
    OROS,
    COPAS,
    ESPADAS,
    BASTOS
} Palo;

typedef struct{
    int numero;
    Palo palo;
} Carta;

//b)
typedef struct{
    Carta baraja[48];
} Mazo;

//c)
void llenar(Mazo* naipes){
    int indice = 0;
    for(int palo = OROS; palo <= BASTOS; palo++){
        for(int numero = 1; numero <= 12; numero++){
            naipes -> baraja[indice].numero = numero;
            naipes -> baraja[indice].palo = (Palo)palo;
            indice ++;
        }
    }
}

//d)
Carta azar(Mazo* naipes){
    int aleatorio = rand() % 48;
    Carta carta = naipes->baraja[aleatorio];

    return carta;
}

//Ejercicio 14
//a)
typedef struct{
    char* nombre;
    char* numero;
    unsigned int edad;
} Contacto;

//b)
Contacto crear_contacto(){
    Contacto c;
    printf("Ingrese el nombre del contacto: \n");
    c.nombre = get_new_line();

    if (c.nombre == NULL) {
        printf("Error al obtener el nombre.\n");
        exit(1);
    }

    printf("Ingrese el numero de telefono: ");
    c.numero = get_new_line();

    if (c.numero == NULL) {
        printf("Error al obtener el numero.\n");
        free(c.nombre);
        exit(1);
    }

    printf("Ingrese la edad: ");
    scanf("%u", &c.edad);
    getchar();

    return c;
}

//c)
void actualizar_edad (Contacto* c){
    unsigned int nueva_edad;
    printf("Ingrese una edad: \n");
    scanf("%u", &nueva_edad);

    c->edad = nueva_edad;
    while (getchar() != '\n');
}

//d)
typedef struct{
    Contacto* lista;
    int cantidad;
} Agenda;

//e)
void Alta_contacto(Agenda* a){
    a -> lista = realloc(a -> lista, (a -> cantidad + 1)*sizeof(Contacto));
    if(a->lista == NULL){
        printf("Error al reasignar la memoria.\n");
        exit(1);
    }
    a->lista[a->cantidad] = crear_contacto();
    a->cantidad++;
}

//f)
void modificar_edad(Agenda* a){
    printf("Ingrese el nombre del contacto: \n");
    char* name = get_new_line();

    if(name == NULL){
        printf("Error al leer la edad.\n");
        return;
    }

    for(int i = 0; i < a->cantidad; i++){
        if(strcmp(a->lista[i].nombre, name) == 0){
            actualizar_edad(&a->lista[i]);
            free(name);
            return;
        }
    }

    printf("El contacto no está en la lista.\n");
    free(name);
}

//g)
void imprimir_contactos(Agenda* a){
    for(int i = 0; i < a->cantidad; i++){
        printf("Nombre:%s, telefono: %s, edad: %u\n", a->lista[i].nombre, a->lista[i].numero, a->lista[i].edad);
    }
}

//h)
double prom(Agenda* a){
    if(a->cantidad == 0){
        printf("No hay contactos en la agenda.\n");
        return 0.0;
    }

    int sum_edades = 0;
    for(int i = 0; i < a->cantidad; i++){
        sum_edades += a->lista[i].edad;
    }

    return (double)sum_edades/a->cantidad;
}

int main(){
    return 0;
}