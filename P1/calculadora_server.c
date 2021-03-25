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

int *potencia_1_svc(power p,  struct svc_req *rqstp) {
    static int result;
    result = pow(p.base, p.exponente);

    return &result;
}

double *raizcuadrada_1_svc(double a, struct svc_req *rqstp) {
    static double result;
    if (a < 0)  result = -1.0; // Se establece que si se intenta hacer la raíz cuadrada de un número negativo se devuelve -1.0
    else        result = sqrt(a);

    return &result;
}


point *transladar_1_svc(point p, double x, double y, double z, struct svc_req *rqstp) {
    static point result;
    result.x = p.x + x;
    result.y = p.y + y;
    result.z = p.z + z;

    return &result;
}

point *escalar_1_svc(point p, double x, double y, double z, struct svc_req *rqstp) {
    static point result;
    result.x = p.x * x;
    result.y = p.y * y;
    result.z = p.z * z;

    return &result;
}


vect *sumarvectores_1_svc(vect v1, vect v2, struct svc_req *rqstp) {
    static vect result;
    if (v1.vect_len == v2.vect_len) {
        result.vect_len = v1.vect_len;
        result.vect_val = malloc(result.vect_len * sizeof(double));
        for (unsigned int i = 0; i < v1.vect_len; i++)
            result.vect_val[i] = v1.vect_val[i] + v2.vect_val[i];
    }
    else
        result.vect_len = 0;

    return &result;
}

vect *restarvectores_1_svc(vect v1, vect v2, struct svc_req *rqstp) {
    static vect result;
    if (v1.vect_len == v2.vect_len) {
        result.vect_len = v1.vect_len;
        result.vect_val = malloc(result.vect_len * sizeof(double));
        for (unsigned int i = 0; i < v1.vect_len; i++)
            result.vect_val[i] = v1.vect_val[i] - v2.vect_val[i];
    }
    else
        result.vect_len = 0;

    return &result;
}

vect *multiplicarvectores_1_svc(vect v1, vect v2, struct svc_req *rqstp) {
    static vect result;
    if (v1.vect_len == v2.vect_len) {
        result.vect_len = v1.vect_len;
        result.vect_val = malloc(result.vect_len * sizeof(double));
        for (unsigned int i = 0; i < v1.vect_len; i++)
            result.vect_val[i] = v1.vect_val[i] * v2.vect_val[i];
    }
    else
        result.vect_len = 0;

    return &result;
}

vect *dividirvectores_1_svc(vect v1, vect v2, struct svc_req *rqstp) {
    static vect result;
    if (v1.vect_len == v2.vect_len) {
        result.vect_len = v1.vect_len;
        result.vect_val = malloc(result.vect_len * sizeof(double));
        for (unsigned int i = 0; i < v1.vect_len; i++)
            result.vect_val[i] = v1.vect_val[i] / v2.vect_val[i];
    }
    else
        result.vect_len = 0;

    return &result;
}


matrix *sumarmatrices_1_svc(matrix m1, matrix m2, struct svc_req *rqstp) {
    static matrix result;
    if (m1.matrix_len == m2.matrix_len) {
        result.matrix_len = m1.matrix_len;
        result.matrix_val = malloc(result.matrix_len * sizeof(vect*));
        for (unsigned int i = 0; i < result.matrix_len; i++) {
            result.matrix_val[i].vect_len = m1.matrix_val[i].vect_len;
            result.matrix_val[i].vect_val = malloc(result.matrix_val[i].vect_len * sizeof(double));
            for (unsigned int j = 0; j < result.matrix_val[i].vect_len; j++) {
                result.matrix_val[i].vect_val[j] = m1.matrix_val[i].vect_val[j] + m2.matrix_val[i].vect_val[j];
            }
        }
    }
    else
        result.matrix_len = 0;

    return &result;
}

matrix *restarmatrices_1_svc(matrix m1, matrix m2, struct svc_req *rqstp) {
    static matrix result;
    if (m1.matrix_len == m2.matrix_len) {
        result.matrix_len = m1.matrix_len;
        result.matrix_val = malloc(result.matrix_len * sizeof(vect*));
        for (unsigned int i = 0; i < result.matrix_len; i++) {
            result.matrix_val[i].vect_len = m1.matrix_val[i].vect_len;
            result.matrix_val[i].vect_val = malloc(result.matrix_val[i].vect_len * sizeof(double));
            for (unsigned int j = 0; j < result.matrix_val[i].vect_len; j++) {
                result.matrix_val[i].vect_val[j] = m1.matrix_val[i].vect_val[j] - m2.matrix_val[i].vect_val[j];
            }
        }
    }
    else
        result.matrix_len = 0;

    return &result;
}

matrix *multiplicarmatrices_1_svc(matrix m1, matrix m2, struct svc_req *rqstp) {
    static matrix result;
    if (m1.matrix_len == m2.matrix_len) {
        result.matrix_len = m1.matrix_len;
        result.matrix_val = malloc(result.matrix_len * sizeof(vect*));
        for (unsigned int i = 0; i < result.matrix_len; i++) {
            result.matrix_val[i].vect_len = m1.matrix_val[i].vect_len;
            result.matrix_val[i].vect_val = malloc(result.matrix_val[i].vect_len * sizeof(double));
            for (unsigned int j = 0; j < result.matrix_val[i].vect_len; j++) {
                result.matrix_val[i].vect_val[j] = 0.0;
                for (unsigned int k = 0; k < m1.matrix_len; k++)
                    result.matrix_val[i].vect_val[j] += m1.matrix_val[i].vect_val[k] * m2.matrix_val[k].vect_val[j];
            }
        }
    }
    else
        result.matrix_len = 0;

    return &result;
}


matrixv *sumarmatricesv_1_svc(matrixv m1, matrixv m2, struct svc_req *rqstp) {
    static matrixv result;
    if (m1.matrixv_len == m2.matrixv_len) {
        result.matrixv_len = m1.matrixv_len;
        result.matrixv_val = malloc(result.matrixv_len * sizeof(double));
        for (unsigned int i = 0; i < result.matrixv_len; i++)
            result.matrixv_val[i] = m1.matrixv_val[i] + m2.matrixv_val[i];
    }
    else
        result.matrixv_len = 0;

    return &result;
}


matrixv *restarmatricesv_1_svc(matrixv m1, matrixv m2, struct svc_req *rqstp) {
    static matrixv result;
    if (m1.matrixv_len == m2.matrixv_len) {
        result.matrixv_len = m1.matrixv_len;
        result.matrixv_val = malloc(result.matrixv_len * sizeof(double));
        for (unsigned int i = 0; i < result.matrixv_len; i++)
            result.matrixv_val[i] = m1.matrixv_val[i] - m2.matrixv_val[i];
    }
    else
        result.matrixv_len = 0;

    return &result;
}

matrixv *multiplicarmatricesv_1_svc(matrixv m1, matrixv m2, struct svc_req *rqstp) {
    static matrixv result;
    if (m1.matrixv_len == m2.matrixv_len) {
        result.matrixv_len = m1.matrixv_len;
        result.matrixv_val = malloc(result.matrixv_len * sizeof(double));
        for (unsigned int i = 0; i < sqrt(result.matrixv_len); i++)
            for (unsigned int j = 0; j < sqrt(result.matrixv_len); j++) {
                result.matrixv_val[(int)sqrt(result.matrixv_len) * i + j] = 0;
                for (unsigned int k = 0; k < sqrt(result.matrixv_len); k++)
                    result.matrixv_val[(int)sqrt(result.matrixv_len) * i + j] += m1.matrixv_val[(int)sqrt(result.matrixv_len) * i + k] * m2.matrixv_val[(int)sqrt(result.matrixv_len) * k + j];
            }
    }
    else
        result.matrixv_len = 0;

    return &result;
}


char **cifrar_1_svc(char *password, struct svc_req *rqstp) {
    static char* result;

    for (unsigned int i = 0; password[i] != '\0'; i++)
        password[i] -= 30;

    result = password;

    return &result;
};

char **descifrar_1_svc(char *password, struct svc_req *rqstp) {
    static char* result;

    for (unsigned int i = 0; password[i] != '\0'; i++)
        password[i] += 30;

    result = password;

    return &result;
};