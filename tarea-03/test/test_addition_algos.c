#include "addition_algos.h"

#include <stdbool.h>
#include <stdio.h>

/*
Cortesía de nuestro querido maestro de Estructura de Datos:
Prof. Eduardo Acuña.

Macros para organizar pruebas.

Las pruebas se escriben con check(expresión, mensaje), una prueba
pasa cuando la expresión tiene valor verdadero y falla cuando tiene
valor falso, en cuyo caso se imprime el mensaje como error.

Las pruebas se agrupan en funciones de cero argumentos que regresan
un booleano, si alguna de las pruebas falla esta función debe
regresar falso, si todas pasan debe regresar verdadero.

Dentro de estas funciones, utiliza una etiqueta fail para
identificar el código que libera recursos (como la memoria) cuando
una prueba falla.
*/
#define run_test(test)                             \
    do {                                           \
        fprintf(stderr, "* Testing " #test "..."); \
        bool ok = test();                          \
        if (!ok)                                   \
            return -1;                             \
        fprintf(stderr, "ok\n");                   \
    } while (0)

#define check(expr, message)                             \
    if (!(expr)) {                                       \
        fprintf(stderr, "\nError (%s:%d) " message "\n", \
                __FILE__, __LINE__);                     \
        goto fail;                                       \
    }

int it_works() {
    int a = 2, b = 4;
    check(add(a, b) == 6, "add(2, 4) should be 6");
    return true;

fail:
    return false;
}

int main(void) {
    run_test(it_works);
    return 0;
}