#ifndef RELOJ_H_
#define RELOJ_H_

#include "fsl_pit.h"
#include "fsl_debug_console.h"
#include <stdio.h>

#define LIMITE_SEGUNDOS 60U
#define LIMITE_MINUTOS  60U
#define LIMITE_HORAS 24U

#define ALARMA_SEGUNDOS 10U
#define ALARMA_MINUTOS 00U
#define ALARMA_HORAS 13U

typedef enum {FALSE,TRUE} boolean_t;

void segundero(void);
void minutero(void);
void horas(void);
void alarm(void);
void imprimir_hora(void);

#endif
