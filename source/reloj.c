#include "reloj.h"

uint8_t g_segundos = 0;
uint8_t g_minutos = 0;
uint8_t g_horas = 0;

boolean_t g_seg_flag = FALSE;
boolean_t g_min_flag = FALSE;
boolean_t g_hr_flag = FALSE;

void segundero(void)
{
  g_segundos++;
  if(ALARMA_SEGUNDOS == g_segundos)
  {
    //generar una notificacion
    g_seg_flag = TRUE;
  }
  else
  {
    g_seg_flag = FALSE;
  }
  if(LIMITE_SEGUNDOS == g_segundos)
  {
    g_segundos = 0;
    minutero();
  }
}

void minutero(void)
{
  if(ALARMA_MINUTOS == g_minutos)
  {
    //generar una notificacion
    g_min_flag =TRUE;
  }
  else
  {
    g_min_flag = FALSE;
  }
  if(LIMITE_MINUTOS == g_minutos)
  {
    g_minutos = 0;
    horas();
  }
}

void horas(void)
{
  if(ALARMA_HORAS == g_horas)
  {
    //generar una notificacion
    g_hr_flag = TRUE;
  }
  else
  {
    g_hr_flag = FALSE;
  }
  if(LIMITE_HORAS == g_horas)
  {
    g_horas = 0;
  }
}

void alarm(void)
{
  if(g_seg_flag && g_min_flag && g_hr_flag)
  {
    PRINTF("DESPIERTAAAAAAAAAA \n");
  }
}

void imprimir_hora(void)
{
  PRITNF("%d:%d:%d\n",g_horas,g_minutos,g_segundos);
}
