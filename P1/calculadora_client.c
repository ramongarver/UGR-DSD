#include <stdio.h>
#include <stdlib.h>
#include "calculadora.h"


void calculadoraprog_1(char *host, int a, char operator, int b) {
    CLIENT *clnt;
    #ifndef	DEBUG
        clnt = clnt_create (host, CALCULADORAPROG, CALCULADORAVER, "udp");
        if (clnt == NULL) {
            clnt_pcreateerror (host);
            exit (1);
        }
    #endif	/* DEBUG */

    // Selección de operación en función del operador
    int *result;
    switch (operator) {
        case '+':
            result = sumar_1(a, b, clnt);
            break;
        case '-':
            result = restar_1(a, b, clnt);
            break;
        case 'x':
            result = multiplicar_1(a, b, clnt);
            break;
        case '/':
            result = dividir_1(a, b, clnt);
            break;
    }

    // Impresión del resultado de la operación
    printf("%d %c %d = %d\n", a, operator, b, *result);

    #ifndef	DEBUG
        clnt_destroy (clnt);
    #endif	 /* DEBUG */
}


int main (int argc, char *argv[]) {
    // Comprobación del número de argumentos
    if (argc < 5) {
        printf("usage: %s server_host first_operand operator second_operand\n", argv[0]);
        exit(1);
    }

    // Comprobación del operador
    char operator = argv[3][0]; // Asignación del operador
    if (operator != '+' && operator != '-' && operator != 'x' && operator != '/') {
        printf("usage: %s server_host first_operand operator second_operand\n", argv[0]);
        exit(1);
    }

    // Asignación del resto de argumentos
    char* host = argv[1]; // Asignación del host
    int a = atoi(argv[2]); // Primer operando
    int b = atoi(argv[4]); // Segundo operando

    // Función que selecciona el procedimiento remoto
    // a llamar en función del operador introducido
    calculadoraprog_1(host, a, operator, b);

    exit (0);
}
