#ifndef RELOJ_H_
#define RELOJ_H_

#include "fsl_pit.h"
#include <stdio.h>
#define LIMITE_SEGUNDOS 60U
#define LIMITE_MINUTOS  60U
#define LIMITE_HORAS 24U

void segundero(void);
void minutero(void);
void horas(void);
void alarm(void);
void imprimir_hora(void);

#endif
