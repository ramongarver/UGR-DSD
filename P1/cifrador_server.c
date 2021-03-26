#include "cifrador.h"

char **
cifrarfinal_1_svc(char *password,  struct svc_req *rqstp) {
    static char* result;

    for (unsigned int i = 0; password[i] != '\0'; i++)
        password[i] -= 32;

    result = password;

    return &result;
}

char **
descifrarfinal_1_svc(char *password,  struct svc_req *rqstp)
{
    static char* result;

    for (unsigned int i = 0; password[i] != '\0'; i++)
        password[i] += 32;

    result = password;

    return &result;
}
