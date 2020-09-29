#include "reloj.h"


void segundero(void)
{
  static uint8_t segundos = 0;
  segundos++;
  if(alarma_seg == segundos)
  {
    //generar una notificacion
  }
  if(LIMITE_SEGUNDOS == segundos)
  {
    segundos = 0;
    minutero();
  }
}

void minutero(void)
{
  static uint8_t minutos = 0;
  if(alarma_min == minutos)
  {
    //generar una notificacion
  }
  if(LIMITE_MINUTOS == minutos)
  {
    minutos = 0;
    horas();
  }
}

void horas(void)
{
  static uint8_t hora = 0;
  if(alarma_hr == hora)
  {
    //generar una notificacion
  }
  if(LIMITE_HORAS == hora)
  {
    hora = 0;
  }
}
