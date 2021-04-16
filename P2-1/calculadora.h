/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _CALCULADORA_H_RPCGEN
#define _CALCULADORA_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct power {
	int base;
	int exponente;
};
typedef struct power power;

struct point {
	double x;
	double y;
	double z;
};
typedef struct point point;

typedef struct {
	u_int vect_len;
	double *vect_val;
} vect;

typedef struct {
	u_int matrix_len;
	vect *matrix_val;
} matrix;

typedef struct {
	u_int matrixv_len;
	double *matrixv_val;
} matrixv;

typedef char *password;

struct sumar_1_argument {
	int a;
	int b;
};
typedef struct sumar_1_argument sumar_1_argument;

struct restar_1_argument {
	int a;
	int b;
};
typedef struct restar_1_argument restar_1_argument;

struct multiplicar_1_argument {
	int a;
	int b;
};
typedef struct multiplicar_1_argument multiplicar_1_argument;

struct dividir_1_argument {
	int a;
	int b;
};
typedef struct dividir_1_argument dividir_1_argument;

struct transladar_1_argument {
	point p;
	double x;
	double y;
	double z;
};
typedef struct transladar_1_argument transladar_1_argument;

struct escalar_1_argument {
	point p;
	double x;
	double y;
	double z;
};
typedef struct escalar_1_argument escalar_1_argument;

struct sumarvectores_1_argument {
	vect v1;
	vect v2;
};
typedef struct sumarvectores_1_argument sumarvectores_1_argument;

struct restarvectores_1_argument {
	vect v1;
	vect v2;
};
typedef struct restarvectores_1_argument restarvectores_1_argument;

struct multiplicarvectores_1_argument {
	vect v1;
	vect v2;
};
typedef struct multiplicarvectores_1_argument multiplicarvectores_1_argument;

struct dividirvectores_1_argument {
	vect v1;
	vect v2;
};
typedef struct dividirvectores_1_argument dividirvectores_1_argument;

struct sumarmatrices_1_argument {
	matrix m1;
	matrix m2;
};
typedef struct sumarmatrices_1_argument sumarmatrices_1_argument;

struct restarmatrices_1_argument {
	matrix m1;
	matrix m2;
};
typedef struct restarmatrices_1_argument restarmatrices_1_argument;

struct multiplicarmatrices_1_argument {
	matrix m1;
	matrix m2;
};
typedef struct multiplicarmatrices_1_argument multiplicarmatrices_1_argument;

struct sumarmatricesv_1_argument {
	matrixv m1;
	matrixv m2;
};
typedef struct sumarmatricesv_1_argument sumarmatricesv_1_argument;

struct restarmatricesv_1_argument {
	matrixv m1;
	matrixv m2;
};
typedef struct restarmatricesv_1_argument restarmatricesv_1_argument;

struct multiplicarmatricesv_1_argument {
	matrixv m1;
	matrixv m2;
};
typedef struct multiplicarmatricesv_1_argument multiplicarmatricesv_1_argument;

#define CALCULADORAPROG 0x20000000
#define CALCULADORAVER 1

#if defined(__STDC__) || defined(__cplusplus)
#define sumar 1
extern  int * sumar_1(int , int , CLIENT *);
extern  int * sumar_1_svc(int , int , struct svc_req *);
#define restar 2
extern  int * restar_1(int , int , CLIENT *);
extern  int * restar_1_svc(int , int , struct svc_req *);
#define multiplicar 3
extern  int * multiplicar_1(int , int , CLIENT *);
extern  int * multiplicar_1_svc(int , int , struct svc_req *);
#define dividir 4
extern  int * dividir_1(int , int , CLIENT *);
extern  int * dividir_1_svc(int , int , struct svc_req *);
#define potencia 5
extern  int * potencia_1(power , CLIENT *);
extern  int * potencia_1_svc(power , struct svc_req *);
#define raizcuadrada 6
extern  double * raizcuadrada_1(double , CLIENT *);
extern  double * raizcuadrada_1_svc(double , struct svc_req *);
#define transladar 7
extern  point * transladar_1(point , double , double , double , CLIENT *);
extern  point * transladar_1_svc(point , double , double , double , struct svc_req *);
#define escalar 8
extern  point * escalar_1(point , double , double , double , CLIENT *);
extern  point * escalar_1_svc(point , double , double , double , struct svc_req *);
#define sumarvectores 9
extern  vect * sumarvectores_1(vect , vect , CLIENT *);
extern  vect * sumarvectores_1_svc(vect , vect , struct svc_req *);
#define restarvectores 10
extern  vect * restarvectores_1(vect , vect , CLIENT *);
extern  vect * restarvectores_1_svc(vect , vect , struct svc_req *);
#define multiplicarvectores 11
extern  vect * multiplicarvectores_1(vect , vect , CLIENT *);
extern  vect * multiplicarvectores_1_svc(vect , vect , struct svc_req *);
#define dividirvectores 12
extern  vect * dividirvectores_1(vect , vect , CLIENT *);
extern  vect * dividirvectores_1_svc(vect , vect , struct svc_req *);
#define sumarmatrices 13
extern  matrix * sumarmatrices_1(matrix , matrix , CLIENT *);
extern  matrix * sumarmatrices_1_svc(matrix , matrix , struct svc_req *);
#define restarmatrices 14
extern  matrix * restarmatrices_1(matrix , matrix , CLIENT *);
extern  matrix * restarmatrices_1_svc(matrix , matrix , struct svc_req *);
#define multiplicarmatrices 15
extern  matrix * multiplicarmatrices_1(matrix , matrix , CLIENT *);
extern  matrix * multiplicarmatrices_1_svc(matrix , matrix , struct svc_req *);
#define sumarmatricesv 16
extern  matrixv * sumarmatricesv_1(matrixv , matrixv , CLIENT *);
extern  matrixv * sumarmatricesv_1_svc(matrixv , matrixv , struct svc_req *);
#define restarmatricesv 17
extern  matrixv * restarmatricesv_1(matrixv , matrixv , CLIENT *);
extern  matrixv * restarmatricesv_1_svc(matrixv , matrixv , struct svc_req *);
#define multiplicarmatricesv 18
extern  matrixv * multiplicarmatricesv_1(matrixv , matrixv , CLIENT *);
extern  matrixv * multiplicarmatricesv_1_svc(matrixv , matrixv , struct svc_req *);
#define cifrar 21
extern  char ** cifrar_1(char *, CLIENT *);
extern  char ** cifrar_1_svc(char *, struct svc_req *);
#define descifrar 22
extern  char ** descifrar_1(char *, CLIENT *);
extern  char ** descifrar_1_svc(char *, struct svc_req *);
#define cifrarenservidorfinal 23
extern  char ** cifrarenservidorfinal_1(char *, char *, CLIENT *);
extern  char ** cifrarenservidorfinal_1_svc(char *, char *, struct svc_req *);
#define descifrarenservidorfinal 24
extern  char ** descifrarenservidorfinal_1(char *, char *, CLIENT *);
extern  char ** descifrarenservidorfinal_1_svc(char *, char *, struct svc_req *);
extern int calculadoraprog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define sumar 1
extern  int * sumar_1();
extern  int * sumar_1_svc();
#define restar 2
extern  int * restar_1();
extern  int * restar_1_svc();
#define multiplicar 3
extern  int * multiplicar_1();
extern  int * multiplicar_1_svc();
#define dividir 4
extern  int * dividir_1();
extern  int * dividir_1_svc();
#define potencia 5
extern  int * potencia_1();
extern  int * potencia_1_svc();
#define raizcuadrada 6
extern  double * raizcuadrada_1();
extern  double * raizcuadrada_1_svc();
#define transladar 7
extern  point * transladar_1();
extern  point * transladar_1_svc();
#define escalar 8
extern  point * escalar_1();
extern  point * escalar_1_svc();
#define sumarvectores 9
extern  vect * sumarvectores_1();
extern  vect * sumarvectores_1_svc();
#define restarvectores 10
extern  vect * restarvectores_1();
extern  vect * restarvectores_1_svc();
#define multiplicarvectores 11
extern  vect * multiplicarvectores_1();
extern  vect * multiplicarvectores_1_svc();
#define dividirvectores 12
extern  vect * dividirvectores_1();
extern  vect * dividirvectores_1_svc();
#define sumarmatrices 13
extern  matrix * sumarmatrices_1();
extern  matrix * sumarmatrices_1_svc();
#define restarmatrices 14
extern  matrix * restarmatrices_1();
extern  matrix * restarmatrices_1_svc();
#define multiplicarmatrices 15
extern  matrix * multiplicarmatrices_1();
extern  matrix * multiplicarmatrices_1_svc();
#define sumarmatricesv 16
extern  matrixv * sumarmatricesv_1();
extern  matrixv * sumarmatricesv_1_svc();
#define restarmatricesv 17
extern  matrixv * restarmatricesv_1();
extern  matrixv * restarmatricesv_1_svc();
#define multiplicarmatricesv 18
extern  matrixv * multiplicarmatricesv_1();
extern  matrixv * multiplicarmatricesv_1_svc();
#define cifrar 21
extern  char ** cifrar_1();
extern  char ** cifrar_1_svc();
#define descifrar 22
extern  char ** descifrar_1();
extern  char ** descifrar_1_svc();
#define cifrarenservidorfinal 23
extern  char ** cifrarenservidorfinal_1();
extern  char ** cifrarenservidorfinal_1_svc();
#define descifrarenservidorfinal 24
extern  char ** descifrarenservidorfinal_1();
extern  char ** descifrarenservidorfinal_1_svc();
extern int calculadoraprog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_power (XDR *, power*);
extern  bool_t xdr_point (XDR *, point*);
extern  bool_t xdr_vect (XDR *, vect*);
extern  bool_t xdr_matrix (XDR *, matrix*);
extern  bool_t xdr_matrixv (XDR *, matrixv*);
extern  bool_t xdr_password (XDR *, password*);
extern  bool_t xdr_sumar_1_argument (XDR *, sumar_1_argument*);
extern  bool_t xdr_restar_1_argument (XDR *, restar_1_argument*);
extern  bool_t xdr_multiplicar_1_argument (XDR *, multiplicar_1_argument*);
extern  bool_t xdr_dividir_1_argument (XDR *, dividir_1_argument*);
extern  bool_t xdr_transladar_1_argument (XDR *, transladar_1_argument*);
extern  bool_t xdr_escalar_1_argument (XDR *, escalar_1_argument*);
extern  bool_t xdr_sumarvectores_1_argument (XDR *, sumarvectores_1_argument*);
extern  bool_t xdr_restarvectores_1_argument (XDR *, restarvectores_1_argument*);
extern  bool_t xdr_multiplicarvectores_1_argument (XDR *, multiplicarvectores_1_argument*);
extern  bool_t xdr_dividirvectores_1_argument (XDR *, dividirvectores_1_argument*);
extern  bool_t xdr_sumarmatrices_1_argument (XDR *, sumarmatrices_1_argument*);
extern  bool_t xdr_restarmatrices_1_argument (XDR *, restarmatrices_1_argument*);
extern  bool_t xdr_multiplicarmatrices_1_argument (XDR *, multiplicarmatrices_1_argument*);
extern  bool_t xdr_sumarmatricesv_1_argument (XDR *, sumarmatricesv_1_argument*);
extern  bool_t xdr_restarmatricesv_1_argument (XDR *, restarmatricesv_1_argument*);
extern  bool_t xdr_multiplicarmatricesv_1_argument (XDR *, multiplicarmatricesv_1_argument*);

#else /* K&R C */
extern bool_t xdr_power ();
extern bool_t xdr_point ();
extern bool_t xdr_vect ();
extern bool_t xdr_matrix ();
extern bool_t xdr_matrixv ();
extern bool_t xdr_password ();
extern bool_t xdr_sumar_1_argument ();
extern bool_t xdr_restar_1_argument ();
extern bool_t xdr_multiplicar_1_argument ();
extern bool_t xdr_dividir_1_argument ();
extern bool_t xdr_transladar_1_argument ();
extern bool_t xdr_escalar_1_argument ();
extern bool_t xdr_sumarvectores_1_argument ();
extern bool_t xdr_restarvectores_1_argument ();
extern bool_t xdr_multiplicarvectores_1_argument ();
extern bool_t xdr_dividirvectores_1_argument ();
extern bool_t xdr_sumarmatrices_1_argument ();
extern bool_t xdr_restarmatrices_1_argument ();
extern bool_t xdr_multiplicarmatrices_1_argument ();
extern bool_t xdr_sumarmatricesv_1_argument ();
extern bool_t xdr_restarmatricesv_1_argument ();
extern bool_t xdr_multiplicarmatricesv_1_argument ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_CALCULADORA_H_RPCGEN */