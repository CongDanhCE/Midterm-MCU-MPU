/*
 * fsm.c
 *
 *  Created on: Nov 5, 2022
 *      Author: ASUS
 */
#include "fsm.h"

void fsm_simple_buttons_run(){
	switch(mode){
	case INIT:
		if(counter > 9){
			counter = 0;
		}
		if(counter < 0){
			counter = 9;
		}
		// display
		display7SEG(counter);
		// reset press
		if(isButton1Pressed() == 1){
			mode = RESET_PRESSED;
			setTimer2(1000);
		}
		// inc press
		if(isButton2Pressed() == 1){
			mode = INC_PRESSED;
			setTimer2(1000);
		}
		// dec press
		if(isButton3Pressed() == 1){
			mode = DEC_PRESSED;
			setTimer2(1000);
		}
		// blinky led
		if(timer1_flag == 1){
			setTimer1(100);
			HAL_GPIO_TogglePin(Led_Red_GPIO_Port, Led_Red_Pin);
		}

		// 10s not press

		if(isButton1Pressed() == 0 && isButton2Pressed() == 0 && isButton3Pressed() == 0 ){
			if(timer2_flag == 1){
				setTimer2(500);
				if(counter == 0){
					mode = INIT;
				}
				else{
					mode = NOT_PRESSED;
				}
			}
		}
		else{
			setTimer2(1000);
		}
		break;
	case RESET_PRESSED:
		// reset : counter = 0
		counter = 0;
		mode = INIT;
		break;
	case INC_PRESSED:
		// inc : counter ++
		counter ++;
		mode = INIT;
		break;
	case DEC_PRESSED:
		// dec : counter --
		counter --;
		mode = INIT;
		break;
	case NOT_PRESSED:
		// counter --
		counter --;
		mode = INIT;
		break;
	default:
		break;
	}
}
