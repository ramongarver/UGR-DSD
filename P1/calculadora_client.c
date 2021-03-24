#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "calculadora.h"

void generarVector(vect v) {
    for (unsigned int i = 0; i < v.vect_len; i++)
        v.vect_val[i] = (double) (rand() % 10 + ((double) (1 + rand() % 9) / 10));
}

void printVector(vect v, char* titulo) {
    printf("%s:\n", titulo);
    if (v.vect_len >= 0) {
        for (unsigned int i = 0; i < v.vect_len-1; i++)
            printf("%.2f ", v.vect_val[i]);
        printf("%.2f", v.vect_val[v.vect_len-1]);
    }
    printf("\n");
}

void generarMatriz(matrix m) {
    for (unsigned int i = 0; i < m.matrix_len; i++)
        for (unsigned int j = 0; j < m.matrix_val[i].vect_len; j++)
            m.matrix_val[i].vect_val[j] = (double) (rand() % 10 + ((double) (1 + rand() % 9) / 10));
}

void printMatriz(matrix m, char* titulo) {
    printf("%s:\n", titulo);
    if (m.matrix_len >= 0) {
        for (unsigned int i = 0; i < m.matrix_len; i++) {
            for (unsigned int j = 0; j < m.matrix_val[i].vect_len-1; j++)
                printf("%.2f\t", m.matrix_val[i].vect_val[j]);
            printf("%.2f\n", m.matrix_val[i].vect_val[m.matrix_val[i].vect_len-1]);
        }
    }
}

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


    // Operaciones geométricas
    point p;
    p.x = 1.0; p.y = 3.5; p.z = 2.2;
    point *ptransladado = transladar_1(p, 3.0, -3.5, 0.8, clnt);
    point *pescalado = escalar_1(p, 1.5, 0.75, 1.25, clnt);

    printf("Punto inicial:\n x=%.2f\ty=%.2f\tz=%.2f\n", p.x, p.y, p.z);
    printf("Punto transladado:\n x=%.2f\ty=%.2f\tz=%.2f\n", ptransladado->x, ptransladado->y, ptransladado->z);
    printf("Punto escalado:\n x=%.2f\ty=%.2f\tz=%.2f\n", pescalado->x, pescalado->y, pescalado->z);


    // Operaciones con vectores
    vect v1, v2, *vsuma, *vresta, *vmultiplicacion, *vdivision;
    v1.vect_len = v2.vect_len = 16;
    v1.vect_val = malloc(v1.vect_len * sizeof(double));
    v2.vect_val = malloc(v2.vect_len * sizeof(double));

    srand(time(NULL));
    generarVector(v1);
    generarVector(v2);

    vsuma = sumarvectores_1(v1, v2, clnt);
    vresta = restarvectores_1(v1, v2, clnt);
    vmultiplicacion = multiplicarvectores_1(v1, v2, clnt);
    vdivision = dividirvectores_1(v1, v2, clnt);

    printVector(v1, "Vector 1 (A)");
    printVector(v2, "Vector 2 (B)");
    printVector(*vsuma, "Vector suma (A+B)");
    printVector(*vresta, "Vector resta (A-B)");
    printVector(*vmultiplicacion, "Vector multiplicación (AxB)");
    printVector(*vdivision, "Vector división (A/B)");


    // Operaciones con matrices
    matrix m1, m2, *msuma, *mresta, *mmultiplicacion;
    m1.matrix_len = m2.matrix_len = 3;
        // Reservamos memoria para punteros a vect
    m1.matrix_val = malloc(m1.matrix_len * sizeof(vect*));
    m2.matrix_val = malloc(m2.matrix_len * sizeof(vect*));
        // Reservamos memoria para cada uno de los vect
    for (unsigned int i = 0; i < m1.matrix_len; i++) {
        m1.matrix_val[i].vect_len = m2.matrix_val[i].vect_len = 3;
        m1.matrix_val[i].vect_val = malloc(m1.matrix_val[i].vect_len * sizeof(double));
        m2.matrix_val[i].vect_val = malloc(m2.matrix_val[i].vect_len * sizeof(double));
    }

    generarMatriz(m1);
    generarMatriz(m2);

    // msuma = sumarmatrices_1(m1, m2, clnt);
    // mresta = restarmatrices_1(m1, m2, clnt);
    // mmultiplicacion = multiplicarmatrices_1(m1, m2, clnt);

    printMatriz(m1, "Matriz 1 (A)");
    printMatriz(m2, "Matriz 2 (B)");
    // printMatriz(*msuma, "Matriz suma (A+B)");
    // printMatriz(*mresta, "Matriz resta (A-B)");
    // printMatriz(*mmultiplicacion, "Matriz multiplicación (A*B)");


    // Cifrado y descifrado
    char *password = "abretesesamo";
    char **encryptedPassword;
    char **desencryptedPassword;

    printf("Contraseña sin cifrar: %s\n", password);
    encryptedPassword = cifrar_1(password, clnt);
    printf("Contraseña cifrada: %s\n", *encryptedPassword);
    desencryptedPassword = descifrar_1(*encryptedPassword, clnt);
    printf("Contraseña descifrada: %s\n", *desencryptedPassword);

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
