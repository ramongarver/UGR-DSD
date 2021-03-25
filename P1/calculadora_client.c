#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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


void generarMatrizv(matrixv m) {
    for (unsigned int i = 0; i < m.matrixv_len; i++)
        m.matrixv_val[i] = (double) (rand() % 10 + ((double) (1 + rand() % 9) / 10));
}

void printMatrizv(matrixv m, char* titulo) {
    printf("%s:\n", titulo);
    if (m.matrixv_len >= 0) {
        for (unsigned int i = 0; i < sqrt(m.matrixv_len); i++) {
            for (unsigned int j = 0; j < sqrt(m.matrixv_len)-1; j++) {
                printf("%.2f\t", m.matrixv_val[(int)sqrt(m.matrixv_len) * i + j]);
            }
            printf("%.2f\n", m.matrixv_val[(int)sqrt(m.matrixv_len) * i + (int)sqrt(m.matrixv_len)-1]);
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

    // Operaciones básicas
    // Selección de operación en función del operador
    power pow;
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
            pow.base = a; pow.exponente = b;
            iresult = potencia_1(pow, clnt);
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

    printf("\n");
    //-------------------------------------------------------------------------------------------//


    // Operaciones geométricas (transformaciones geométricas)
    point p;
    p.x = 1.0; p.y = 3.5; p.z = 2.2;
    point *ptransladado = transladar_1(p, 3.0, -3.5, 0.8, clnt);
    point *pescalado = escalar_1(p, 1.5, 0.75, 1.25, clnt);

    printf("Punto inicial:\n x=%.2f\ty=%.2f\tz=%.2f\n", p.x, p.y, p.z);
    printf("Punto transladado:\n x=%.2f\ty=%.2f\tz=%.2f\n", ptransladado->x, ptransladado->y, ptransladado->z);
    printf("Punto escalado:\n x=%.2f\ty=%.2f\tz=%.2f\n", pescalado->x, pescalado->y, pescalado->z);

    printf("\n");
    //-------------------------------------------------------------------------------------------//



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

    printf("\n");
    //-------------------------------------------------------------------------------------------//


    // Operaciones con matrices (matriz como array de punteros a vect) (matriz no cuadrada)
    matrix m1, m2;
    m1.matrix_len = 2; // Número de filas de la matriz 1
    m2.matrix_len = 2; // Número de filas de la matriz 2
        // Reservamos memoria para punteros a vect
    m1.matrix_val = malloc(m1.matrix_len * sizeof(vect*));
    m2.matrix_val = malloc(m2.matrix_len * sizeof(vect*));
        // Reservamos memoria para cada uno de los vect
    for (unsigned int i = 0; i < m1.matrix_len; i++) {
        m1.matrix_val[i].vect_len = 2; // Número de columnas de la matriz 1
        m1.matrix_val[i].vect_val = malloc(m1.matrix_val[i].vect_len * sizeof(double));
    }
    for (unsigned int i = 0; i < m2.matrix_len; i++) {
        m2.matrix_val[i].vect_len = 1; // Número de columnas de la matriz 2
        m2.matrix_val[i].vect_val = malloc(m2.matrix_val[i].vect_len * sizeof(double));
    }

    generarMatriz(m1);
    generarMatriz(m2);

    printMatriz(m1, "Matriz 1 (basada en punteros a vect)");
    printMatriz(m2, "Matriz 2 (basada en punteros a vect) (no cuadrada)");

    /* Para que estas funciones se puedan ejecutar correctamente
     * las matrices deben tener las mismas dimensiones
     * matrix *msuma, *mresta, *mmultiplicacion;
     *
     * msuma = sumarmatrices_1(m1, m2, clnt);
     * mresta = restarmatrices_1(m1, m2, clnt);
     * mmultiplicacion = multiplicarmatrices_1(m1, m2, clnt);
     *
     * printMatriz(*msuma, "Matriz suma (A+B)");
     * printMatriz(*mresta, "Matriz resta (A-B)");
     * printMatriz(*mmultiplicacion, "Matriz multiplicación (A*B)");
     */

    printf("\n");
    //-------------------------------------------------------------------------------------------//



    // Operaciones con matrices (matriz como array) (matriz cuadrada)
    matrixv mv1, mv2, *mvsuma, *mvresta, *mvmultiplicacion;
    mv1.matrixv_len = mv2.matrixv_len = 36; // Número de elementos de la matrix
        // Reservamos memoria para los elementos de la matriz
    mv1.matrixv_val = malloc(mv1.matrixv_len * sizeof(double));
    mv2.matrixv_val = malloc(mv2.matrixv_len * sizeof(double));

    generarMatrizv(mv1);
    generarMatrizv(mv2);

    mvsuma = sumarmatricesv_1(mv1, mv2, clnt);
    mvresta = restarmatricesv_1(mv1, mv2, clnt);
    mvmultiplicacion = multiplicarmatricesv_1(mv1, mv2, clnt);

    printMatrizv(mv1, "Matriz 1 (A)");
    printMatrizv(mv2, "Matriz 2 (B)");
    printMatrizv(*mvsuma, "Matriz suma (A+B)");
    printMatrizv(*mvresta, "Matriz resta (A-B)");
    printMatrizv(*mvmultiplicacion, "Matriz multiplicación (A*B)");

    printf("\n");
    //-------------------------------------------------------------------------------------------//



    // Cifrado y descifrado
    char *password = "abretesesamo";
    char **encryptedPassword;
    char **desencryptedPassword;

    printf("Contraseña sin cifrar: %s\n", password);
    encryptedPassword = cifrar_1(password, clnt);
    printf("Contraseña cifrada: %s\n", *encryptedPassword);
    desencryptedPassword = descifrar_1(*encryptedPassword, clnt);
    printf("Contraseña descifrada: %s\n", *desencryptedPassword);
    printf("\n");
    //-------------------------------------------------------------------------------------------//

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
