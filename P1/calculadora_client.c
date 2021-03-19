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
    int *iresult;
    double *dresult;
    switch (operator) {
        case '+':
            iresult = sumar_1(a, b, clnt);
            break;
        case '-':
            iresult = restar_1(a, b, clnt);
            break;
        case 'x':
            iresult = multiplicar_1(a, b, clnt);
            break;
        case '/':
            iresult = dividir_1(a, b, clnt);
            break;
        case '^':
            iresult = potencia_1(a, b, clnt);
            break;
        case 'r':
            dresult = raizcuadrada_1(a, clnt);
            break;
    }


    // Impresión del resultado de la operación
    printf("Operación realizada:\n");
    if (operator != 'r')
        printf("%d %c %d = %d\n", a, operator, b, *iresult);
    else
        printf("sqrt(%.4f) = %.4f\n", (double)a, *dresult);



    #ifndef	DEBUG
        clnt_destroy (clnt);
    #endif	 /* DEBUG */
}


int main (int argc, char *argv[]) {
    // Comprobación del número de argumentos
    if (argc < 4) {
        printf("usage: %s server_host first_operand operator [second_operand]\n", argv[0]);
        exit(1);
    }

    char operator = argv[3][0]; // Asignación del operador
    // Comprobación de los operadores binarios
    if (argc == 5 && operator != '+' && operator != '-' && operator != 'x' && operator != '/' && operator != '^') {
        printf("usage: %s server_host first_operand operator [second_operand]\n", argv[0]);
        exit(1);
    }
    // Comprobación del operador unario
    if (argc == 4 && operator != 'r') {
        printf("usage: %s server_host first_operand operator [second_operand]\n", argv[0]);
        exit(1);
    }

    // Asignación del resto de argumentos
    char* host = argv[1]; // Asignación del host
    int a = atoi(argv[2]); // Primer operando
    int b;
    if (argc >= 5 )
        b = atoi(argv[4]); // Segundo operando

    // Función que selecciona la llamada remota
    // a procedimiento en acuerdo al operador introducido
    calculadoraprog_1(host, a, operator, b);

    exit (0);
}
