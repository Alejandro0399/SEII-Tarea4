# Tarea4
##Alejandro Gudiño Gallegos
##Eduardo Ethandrake Castillo Pulido

```
void segundero(void)
{
  g_segundos++;
  if(LIMITE_SEGUNDOS == g_segundos)
  {
    g_segundos = 0;
    minutero();
  }
  if(ALARMA_SEGUNDOS == g_segundos)
  {
    //generar una notificacion
    g_seg_flag = TRUE;
  }
  else
  {
    g_seg_flag = FALSE;
  }
}
```
```
void minutero(void)
{
  g_minutos++;
  if(LIMITE_MINUTOS == g_minutos)
  {
    g_minutos = 0;
    horas();
  }
  if(ALARMA_MINUTOS == g_minutos)
  {
    //generar una notificacion
    g_min_flag =TRUE;
  }
  else
  {
    g_min_flag = FALSE;
  }

}```
```
void horas(void)
{
  g_horas++;
  if(LIMITE_HORAS == g_horas)
  {
    g_horas = 0;
  }
  if(ALARMA_HORAS == g_horas)
  {
    //generar una notificacion
    g_hr_flag = TRUE;
  }
  else
  {
    g_hr_flag = FALSE;
  }

}```
```
void alarm(void)
{
  if(g_seg_flag && g_min_flag && g_hr_flag)
  {
    PRINTF("\r\nALARM\n");
  }
}```
```
void imprimir_hora(void)
{
  PRINTF("\e[1;1H\e[2J");
  if(g_horas < 10)
  {
	  PRINTF("\r0");
  }
  PRINTF("%d:",g_horas);
  if(g_minutos < 10)
  {
	  PRINTF("0");
  }
  PRINTF("%d:",g_minutos);
  if(g_segundos < 10)
  {
	  PRINTF("0");
  }
  PRINTF("%d",g_segundos);
}```
