#include <math.h>
#include "calculadora.h"

int *sumar_1_svc(int a, int b,  struct svc_req *rqstp) {
	static int result;
    result = a + b;

	return &result;
}

int *restar_1_svc(int a, int b,  struct svc_req *rqstp) {
	static int result;
    result = a - b;

	return &result;
}

int *multiplicar_1_svc(int a, int b,  struct svc_req *rqstp) {
	static int result;
    result = a * b;

	return &result;
}

int *dividir_1_svc(int a, int b,  struct svc_req *rqstp) {
	static int result;
	if (b == 0) result = 0; // Se establece que si se divide por 0 el resultado es 0
    else        result = a / b;

	return &result;
}

int *potencia_1_svc(int a, int b,  struct svc_req *rqstp) {
    static int result;
    result = pow(a, b);

    return &result;
}

double *raizcuadrada_1_svc(double a, struct svc_req *rqstp) {
    static double result;
    if (a < 0)  result = -1.0; // Se establece que si se intenta hacer la raíz cuadrada de un número negativo se devuelve -1.0
    else        result = sqrt(a);

    return &result;
}