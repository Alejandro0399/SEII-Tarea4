/*
 * PIT.c
 *
 *  Created on: Feb 22, 2020
 *      Author: eduar
 */

#include "PIT.h"

uint8_t interrupt_flag = 0x00;//Se usa para registrar las interrupciones, cada bit es una bandera correspondiente a un PIT
uint8_t interrupt_flag_2 = 0x00;
uint32_t dummyRead = 0;

static void(*pit_0_callback)(void) = 0;
static void(*pit_1_callback)(void) = 0;
static void(*pit_2_callback)(void) = 0;
static void(*pit_3_callback)(void) = 0;


void PIT_callback_init(PIT_timer_t pit_timer, void (*handler)(void))
{
	switch(pit_timer)
	{
		case PIT_0:
			pit_0_callback = handler;
			break;
		case PIT_1:
			pit_1_callback = handler;
			break;
		case PIT_2:
			pit_2_callback = handler;
			break;
		case PIT_3:
			pit_3_callback = handler;
			break;
	}
}

void PIT_stop(PIT_timer_t pit_timer)
{
	PIT->CHANNEL[pit_timer].TCTRL = 0;
}

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function configure the PIT to generate a delay base on the system clock.
 	 It is important to note that this strictly is not device driver since everything is
 	 contained in a single function,  in general you have to avoid this practices, this only
 	 for the propose of the homework

 	 \param[in]  pit_timer channel to be used.
	 \param[in]  system_clock system clock use in the K64 (defult = 21e6).
	 \param[in]  delay the amount of time the delay the microcontroller
 	 \return void
 */
void PIT_delay(PIT_timer_t pit_timer, My_float_pit_t system_clock , My_float_pit_t delay)
{

	My_float_pit_t pit_clk = system_clock/2;
	uint32_t load_val = (uint32_t)(delay*pit_clk);
	//load timer value
	PIT->CHANNEL[pit_timer].LDVAL = load_val;
	PIT_enable_interrupt(pit_timer);
	//enable timer
	PIT->CHANNEL[pit_timer].TCTRL |= PIT_TCTRL_TEN_MASK;
}

/********************************************************************************************/
/*!
 	 \brief	 This function enable the clock signal of the pit

 	 \param[in]  void.
 	 \return void
 */
void PIT_clock_gating(void)
{
	//se necesitan cambiar los magic numbers por macros del Mk64F.h
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
}

/********************************************************************************************/
/*!
 	 \brief	It return the status of the interrupt flag. This flag is a variable created by the programmer.
 	 It is not the flag related with bit TIF in PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK, this flag must be clear in the ISR of the PIT

 	 \param[in]  void.
 	 \return uint8_t flag status
 */
uint8_t PIT_get_interrupt_flag_status(void)
{
	return interrupt_flag;
}

uint8_t PIT_get_interrupt_flag_status_2(void)
{
	return interrupt_flag_2;
}
/********************************************************************************************/
/*!
 	 \brief	Clears the interrupt flag created by the programmer.
 	 It is not the flag related with bit TIF in PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK, this flag must be clear in the ISR of the PIT

 	 \param[in]  void.
 	 \return uint8_t flag status
 */
void PIT_clear_interrupt_flag(void)
{
	interrupt_flag = 0x00;
}

void PIT_clear_interrupt_flag_2(void)
{
	interrupt_flag_2 = 0x00;
}
/********************************************************************************************/
/*!
 	 \brief	It enables the PIT

 	 \param[in]  void.
 	 \return void.
 */
void PIT_enable(void)
{
	PIT->MCR &= ~PIT_MCR_MDIS_MASK; //0x2u
	PIT->MCR |= PIT_MCR_FRZ_MASK;
}

/********************************************************************************************/
/*!
 	 \brief	It enable the interrupt capabilities of the PIT

 	 \param[in]  pit that will be used.
 	 \return void.
 */
void PIT_enable_interrupt(PIT_timer_t pit)
{
	//clear flag first
	PIT->CHANNEL[pit].TFLG  |= PIT_TFLG_TIF_MASK; //1u
	//enables PIT_0 interrupt
	PIT->CHANNEL[pit].TCTRL |= PIT_TCTRL_TIE_MASK; //2u

}

/********************************************************************************************/
/*!
 	 \brief	It activates when an interruption happens. It clears the flag, then enables the interrupt flag
 	 and the reads the TCTRL of the PIT0

 	 \param[in]  void
 	 \return void.
 */
void PIT0_IRQHandler(void)
{
	PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
	interrupt_flag |= 0x01;
	dummyRead = PIT->CHANNEL[0].TCTRL;
	//LLAMAR AL CALLBACK
	if(pit_0_callback)
	{
		pit_0_callback();
		PIT_clear_interrupt_flag();
	}
}

/********************************************************************************************/
/*!
 	 \brief	It activates when an interruption happens. It clears the flag, then enables the interrupt flag
 	 and the reads the TCTRL of the PIT1

 	 \param[in]  void
 	 \return void.
 */
void PIT1_IRQHandler(void)
{
	PIT->CHANNEL[1].TFLG |= PIT_TFLG_TIF_MASK;
	interrupt_flag |= 0x02;
	dummyRead = PIT->CHANNEL[1].TCTRL;
	if(pit_1_callback)
	{
		pit_1_callback();
		PIT_clear_interrupt_flag();
	}
}

/********************************************************************************************/
/*!
 	 \brief	It activates when an interruption happens. It clears the flag, then enables the interrupt flag
 	 and the reads the TCTRL of the PIT2

 	 \param[in]  void
 	 \return void.
 */
void PIT2_IRQHandler(void)
{
	PIT->CHANNEL[2].TFLG |= PIT_TFLG_TIF_MASK;
	interrupt_flag_2 |= 0x04;
	dummyRead = PIT->CHANNEL[2].TCTRL;
	if(pit_2_callback)
	{
		pit_2_callback();
		PIT_clear_interrupt_flag();
	}
}

/********************************************************************************************/
/*!
 	 \brief	It activates when an interruption happens. It clears the flag, then enables the interrupt flag
 	 and the reads the TCTRL of the PIT3

 	 \param[in]  void
 	 \return void.
 */
void PIT3_IRQHandler(void)
{
	PIT->CHANNEL[3].TFLG |= PIT_TFLG_TIF_MASK;
	interrupt_flag |= 0x08;
	dummyRead = PIT->CHANNEL[3].TCTRL;
}
