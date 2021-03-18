#include "calculadora.h"

int *sumar_1_svc(int a, int b,  struct svc_req *rqstp) {
	static int  result;
    result = a + b;

	return &result;
}

int *restar_1_svc(int a, int b,  struct svc_req *rqstp) {
	static int  result;
    result = a - b;

	return &result;
}

int *multiplicar_1_svc(int a, int b,  struct svc_req *rqstp) {
	static int  result;
    result = a * b;

	return &result;
}

int *dividir_1_svc(int a, int b,  struct svc_req *rqstp) {
	static int  result;
	if (b == 0) result = 0; // Se establece que si se divide por 0 el resultado es 0
    else        result = a / b;

	return &result;
}
