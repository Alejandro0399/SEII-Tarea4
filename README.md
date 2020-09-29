# Tarea4
## Alejandro Gudiño Gallegos		Eduardo Ethandrake Castillo Pulido
## Funcionamiento General
El funcionamiento en general es el generar una interrupcion utilizando el PIT, esta interrupcion se genera a cada seegundo. En ese segundo se imprime la hora y se aumenta en uno el segundo, y en caso de ser necesario el minutero y horas. Tambien se llama a la funcion Alarma, la cual detecta si se encendieron las banderas para desplegar o no el mensaje de ALARM
## Control de Segundos
Esta fucnion se ejecuta cada segundo, aumentando uno cada vez que se llama. Esta funcion es llamada en el PIT_handler, lo cual quiere decir que cada que ocurre una interrupcion del PIT. Al aumentar el segundo se hace una comparacion para ver si el valor tiene que volver a 0 o no. Tambien se genera una bandera cuando los segundos son iguales a los propuestos en la alarma
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
## Control de Minutos
Esta funcion se llama cuando los segundos son 60, pues aumenta en uno el minuto. Tambien se hace el control para saber si se llega al limite de minutos. Cuando se llega al limite se llama a la funcion que suma uno a la hora. Tambien se activa la bandera cuando el minuto es igual al de la alarma.
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

}
```
## Control de Horas
Esta funcion aumenta en uno a la hora cada vez que el minutero es 60. Tambien se hace el control para poder generar la alarma activando una bandera, ademas de controlar cuando tiene que volver a 0.
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

}
```
## Activar Alarma
Esta funcion despliega el mensaje de alarma cuando las tres banderas estan activas. Estas banderas se activan en las funciones segundero, minutero y horas. Es importante recordar que para entrar a horas tiene que llegar al limite el minutero. De misma manera, el segundero tiene que llegar a 60 para que se ingrese a minutero.
```
void alarm(void)
{
  if(g_seg_flag && g_min_flag && g_hr_flag)
  {
    PRINTF("\r\nALARM\n");
  }
}
```
## Impresion de Hora
Esta funcion imprime la hora a cada segundo, agregando formato adecuado para poder desplegar de una manera apropiada la hora
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
}
```
