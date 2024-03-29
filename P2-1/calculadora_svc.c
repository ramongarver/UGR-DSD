/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "calculadora.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

static int *
_sumar_1 (sumar_1_argument *argp, struct svc_req *rqstp)
{
	return (sumar_1_svc(argp->a, argp->b, rqstp));
}

static int *
_restar_1 (restar_1_argument *argp, struct svc_req *rqstp)
{
	return (restar_1_svc(argp->a, argp->b, rqstp));
}

static int *
_multiplicar_1 (multiplicar_1_argument *argp, struct svc_req *rqstp)
{
	return (multiplicar_1_svc(argp->a, argp->b, rqstp));
}

static int *
_dividir_1 (dividir_1_argument *argp, struct svc_req *rqstp)
{
	return (dividir_1_svc(argp->a, argp->b, rqstp));
}

static int *
_potencia_1 (power  *argp, struct svc_req *rqstp)
{
	return (potencia_1_svc(*argp, rqstp));
}

static double *
_raizcuadrada_1 (double  *argp, struct svc_req *rqstp)
{
	return (raizcuadrada_1_svc(*argp, rqstp));
}

static point *
_transladar_1 (transladar_1_argument *argp, struct svc_req *rqstp)
{
	return (transladar_1_svc(argp->p, argp->x, argp->y, argp->z, rqstp));
}

static point *
_escalar_1 (escalar_1_argument *argp, struct svc_req *rqstp)
{
	return (escalar_1_svc(argp->p, argp->x, argp->y, argp->z, rqstp));
}

static vect *
_sumarvectores_1 (sumarvectores_1_argument *argp, struct svc_req *rqstp)
{
	return (sumarvectores_1_svc(argp->v1, argp->v2, rqstp));
}

static vect *
_restarvectores_1 (restarvectores_1_argument *argp, struct svc_req *rqstp)
{
	return (restarvectores_1_svc(argp->v1, argp->v2, rqstp));
}

static vect *
_multiplicarvectores_1 (multiplicarvectores_1_argument *argp, struct svc_req *rqstp)
{
	return (multiplicarvectores_1_svc(argp->v1, argp->v2, rqstp));
}

static vect *
_dividirvectores_1 (dividirvectores_1_argument *argp, struct svc_req *rqstp)
{
	return (dividirvectores_1_svc(argp->v1, argp->v2, rqstp));
}

static matrix *
_sumarmatrices_1 (sumarmatrices_1_argument *argp, struct svc_req *rqstp)
{
	return (sumarmatrices_1_svc(argp->m1, argp->m2, rqstp));
}

static matrix *
_restarmatrices_1 (restarmatrices_1_argument *argp, struct svc_req *rqstp)
{
	return (restarmatrices_1_svc(argp->m1, argp->m2, rqstp));
}

static matrix *
_multiplicarmatrices_1 (multiplicarmatrices_1_argument *argp, struct svc_req *rqstp)
{
	return (multiplicarmatrices_1_svc(argp->m1, argp->m2, rqstp));
}

static matrixv *
_sumarmatricesv_1 (sumarmatricesv_1_argument *argp, struct svc_req *rqstp)
{
	return (sumarmatricesv_1_svc(argp->m1, argp->m2, rqstp));
}

static matrixv *
_restarmatricesv_1 (restarmatricesv_1_argument *argp, struct svc_req *rqstp)
{
	return (restarmatricesv_1_svc(argp->m1, argp->m2, rqstp));
}

static matrixv *
_multiplicarmatricesv_1 (multiplicarmatricesv_1_argument *argp, struct svc_req *rqstp)
{
	return (multiplicarmatricesv_1_svc(argp->m1, argp->m2, rqstp));
}

static char **
_cifrar_1 (char * *argp, struct svc_req *rqstp)
{
	return (cifrar_1_svc(*argp, rqstp));
}

static char **
_descifrar_1 (char * *argp, struct svc_req *rqstp)
{
	return (descifrar_1_svc(*argp, rqstp));
}

static char **
_cifrarenservidorfinal_1 (char * *argp, char *host, struct svc_req *rqstp)
{
	return (cifrarenservidorfinal_1_svc(*argp, host, rqstp));
}

static char **
_descifrarenservidorfinal_1 (char * *argp, char *host, struct svc_req *rqstp)
{
	return (descifrarenservidorfinal_1_svc(*argp, host, rqstp));
}

static void
calculadoraprog_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		sumar_1_argument sumar_1_arg;
		restar_1_argument restar_1_arg;
		multiplicar_1_argument multiplicar_1_arg;
		dividir_1_argument dividir_1_arg;
		power potencia_1_arg;
		double raizcuadrada_1_arg;
		transladar_1_argument transladar_1_arg;
		escalar_1_argument escalar_1_arg;
		sumarvectores_1_argument sumarvectores_1_arg;
		restarvectores_1_argument restarvectores_1_arg;
		multiplicarvectores_1_argument multiplicarvectores_1_arg;
		dividirvectores_1_argument dividirvectores_1_arg;
		sumarmatrices_1_argument sumarmatrices_1_arg;
		restarmatrices_1_argument restarmatrices_1_arg;
		multiplicarmatrices_1_argument multiplicarmatrices_1_arg;
		sumarmatricesv_1_argument sumarmatricesv_1_arg;
		restarmatricesv_1_argument restarmatricesv_1_arg;
		multiplicarmatricesv_1_argument multiplicarmatricesv_1_arg;
		char *cifrar_1_arg;
		char *descifrar_1_arg;
		char *cifrarenservidorfinal_1_arg;
		char *descifrarenservidorfinal_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case sumar:
		_xdr_argument = (xdrproc_t) xdr_sumar_1_argument;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) _sumar_1;
		break;

	case restar:
		_xdr_argument = (xdrproc_t) xdr_restar_1_argument;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) _restar_1;
		break;

	case multiplicar:
		_xdr_argument = (xdrproc_t) xdr_multiplicar_1_argument;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) _multiplicar_1;
		break;

	case dividir:
		_xdr_argument = (xdrproc_t) xdr_dividir_1_argument;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) _dividir_1;
		break;

	case potencia:
		_xdr_argument = (xdrproc_t) xdr_power;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) _potencia_1;
		break;

	case raizcuadrada:
		_xdr_argument = (xdrproc_t) xdr_double;
		_xdr_result = (xdrproc_t) xdr_double;
		local = (char *(*)(char *, struct svc_req *)) _raizcuadrada_1;
		break;

	case transladar:
		_xdr_argument = (xdrproc_t) xdr_transladar_1_argument;
		_xdr_result = (xdrproc_t) xdr_point;
		local = (char *(*)(char *, struct svc_req *)) _transladar_1;
		break;

	case escalar:
		_xdr_argument = (xdrproc_t) xdr_escalar_1_argument;
		_xdr_result = (xdrproc_t) xdr_point;
		local = (char *(*)(char *, struct svc_req *)) _escalar_1;
		break;

	case sumarvectores:
		_xdr_argument = (xdrproc_t) xdr_sumarvectores_1_argument;
		_xdr_result = (xdrproc_t) xdr_vect;
		local = (char *(*)(char *, struct svc_req *)) _sumarvectores_1;
		break;

	case restarvectores:
		_xdr_argument = (xdrproc_t) xdr_restarvectores_1_argument;
		_xdr_result = (xdrproc_t) xdr_vect;
		local = (char *(*)(char *, struct svc_req *)) _restarvectores_1;
		break;

	case multiplicarvectores:
		_xdr_argument = (xdrproc_t) xdr_multiplicarvectores_1_argument;
		_xdr_result = (xdrproc_t) xdr_vect;
		local = (char *(*)(char *, struct svc_req *)) _multiplicarvectores_1;
		break;

	case dividirvectores:
		_xdr_argument = (xdrproc_t) xdr_dividirvectores_1_argument;
		_xdr_result = (xdrproc_t) xdr_vect;
		local = (char *(*)(char *, struct svc_req *)) _dividirvectores_1;
		break;

	case sumarmatrices:
		_xdr_argument = (xdrproc_t) xdr_sumarmatrices_1_argument;
		_xdr_result = (xdrproc_t) xdr_matrix;
		local = (char *(*)(char *, struct svc_req *)) _sumarmatrices_1;
		break;

	case restarmatrices:
		_xdr_argument = (xdrproc_t) xdr_restarmatrices_1_argument;
		_xdr_result = (xdrproc_t) xdr_matrix;
		local = (char *(*)(char *, struct svc_req *)) _restarmatrices_1;
		break;

	case multiplicarmatrices:
		_xdr_argument = (xdrproc_t) xdr_multiplicarmatrices_1_argument;
		_xdr_result = (xdrproc_t) xdr_matrix;
		local = (char *(*)(char *, struct svc_req *)) _multiplicarmatrices_1;
		break;

	case sumarmatricesv:
		_xdr_argument = (xdrproc_t) xdr_sumarmatricesv_1_argument;
		_xdr_result = (xdrproc_t) xdr_matrixv;
		local = (char *(*)(char *, struct svc_req *)) _sumarmatricesv_1;
		break;

	case restarmatricesv:
		_xdr_argument = (xdrproc_t) xdr_restarmatricesv_1_argument;
		_xdr_result = (xdrproc_t) xdr_matrixv;
		local = (char *(*)(char *, struct svc_req *)) _restarmatricesv_1;
		break;

	case multiplicarmatricesv:
		_xdr_argument = (xdrproc_t) xdr_multiplicarmatricesv_1_argument;
		_xdr_result = (xdrproc_t) xdr_matrixv;
		local = (char *(*)(char *, struct svc_req *)) _multiplicarmatricesv_1;
		break;

	case cifrar:
		_xdr_argument = (xdrproc_t) xdr_wrapstring;
		_xdr_result = (xdrproc_t) xdr_wrapstring;
		local = (char *(*)(char *, struct svc_req *)) _cifrar_1;
		break;

	case descifrar:
		_xdr_argument = (xdrproc_t) xdr_wrapstring;
		_xdr_result = (xdrproc_t) xdr_wrapstring;
		local = (char *(*)(char *, struct svc_req *)) _descifrar_1;
		break;

	case cifrarenservidorfinal:
		_xdr_argument = (xdrproc_t) xdr_wrapstring;
		_xdr_result = (xdrproc_t) xdr_wrapstring;
		local = (char *(*)(char *, struct svc_req *)) _cifrarenservidorfinal_1;
		break;

	case descifrarenservidorfinal:
		_xdr_argument = (xdrproc_t) xdr_wrapstring;
		_xdr_result = (xdrproc_t) xdr_wrapstring;
		local = (char *(*)(char *, struct svc_req *)) _descifrarenservidorfinal_1;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

int
main (int argc, char **argv)
{
	register SVCXPRT *transp;

	pmap_unset (CALCULADORAPROG, CALCULADORAVER);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, CALCULADORAPROG, CALCULADORAVER, calculadoraprog_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (CALCULADORAPROG, CALCULADORAVER, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, CALCULADORAPROG, CALCULADORAVER, calculadoraprog_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (CALCULADORAPROG, CALCULADORAVER, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}
