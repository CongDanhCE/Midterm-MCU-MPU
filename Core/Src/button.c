/*
 * button.c
 *
 *  Created on: Nov 5, 2022
 *      Author: ASUS
 */

#include "button.h"

int button1_flag = 0;
int button2_flag = 0;
int button3_flag = 0;

int KeyReg0[4] = { NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
int KeyReg1[4] = { NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
int KeyReg2[4] = { NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};

int TimerForKey1Press= 300;
int TimerForKey2Press= 300;
int TimerForKey3Press= 300;

int longPressedKey2_flag = 0;
int longPressedKey3_flag = 0;

// check button1
int isButton1Pressed(){
	if(button1_flag == 1){
		button1_flag = 0;
		return 1;
	}
	return 0;
}

// check button2
int isButton2Pressed(){
	if(button2_flag == 1){
		button2_flag = 0;
		return 1;
	}
	return 0;
}

// check button3
int isButton3Pressed(){
	if(button3_flag == 1){
		button3_flag = 0;
		return 1;
	}
	return 0;
}


void subKeyProcess1(){
	button1_flag = 1;
}

void subKeyProcess2(){
	button2_flag = 1;
}

void subKeyProcess3(){
	button3_flag = 1;
}

void getKeyInput(){
	//button 1
	KeyReg0[0] = KeyReg0[1];
	KeyReg0[1] = KeyReg0[2];
	KeyReg0[2] = HAL_GPIO_ReadPin(RESET_GPIO_Port, RESET_Pin);
	if( (KeyReg0[0] == KeyReg0[1]) && (KeyReg0[1] == KeyReg0[2])){
		if(KeyReg0[3] != KeyReg0[2]){
			KeyReg0[3] = KeyReg0[2];
			if(KeyReg0[2] == PRESSED_STATE){
				subKeyProcess1();
				TimerForKey1Press = 300;
			}
		}
		else{
			TimerForKey1Press--;
			if(TimerForKey1Press <= 0){
				KeyReg0[3] = NORMAL_STATE;
			}
		}
	}
	//button 2
	KeyReg1[0] = KeyReg1[1];
	KeyReg1[1] = KeyReg1[2];
	KeyReg1[2] = HAL_GPIO_ReadPin(INC_GPIO_Port, INC_Pin);
	if( (KeyReg1[0] == KeyReg1[1]) && (KeyReg1[1] == KeyReg1[2])){
		if(KeyReg1[3] != KeyReg1[2]){
			KeyReg1[3] = KeyReg1[2];
			if(KeyReg1[2] == PRESSED_STATE){
				subKeyProcess2();
				if(longPressedKey2_flag == 1){
					TimerForKey2Press = 100;
				}
				else{
					TimerForKey2Press = 300;
				}
			}
			else {
				// reset long press 3 flag && timer
				longPressedKey2_flag = 0;
				TimerForKey2Press = 300;
			}
		}
		else{
			TimerForKey2Press--;
			if(TimerForKey2Press <= 0){
				KeyReg1[3] = NORMAL_STATE;
				// set long press flag 2
				longPressedKey2_flag = 1;
			}
		}
	}
	//button 3
	KeyReg2[0] = KeyReg2[1];
	KeyReg2[1] = KeyReg2[2];
	KeyReg2[2] = HAL_GPIO_ReadPin(DEC_GPIO_Port, DEC_Pin);
	if( (KeyReg2[0] == KeyReg2[1]) && (KeyReg2[1] == KeyReg2[2])){
		if(KeyReg2[3] != KeyReg2[2]){
			KeyReg2[3] = KeyReg2[2];
			if(KeyReg2[2] == PRESSED_STATE){
				subKeyProcess3();
				if(longPressedKey3_flag == 1){
					TimerForKey3Press = 100;
				}
				else{
					TimerForKey3Press = 300;
				}
			}
			else{
				// reset long press 3 flag && timer
				longPressedKey3_flag = 0;
				TimerForKey3Press = 300;
			}
		}
		else{
			TimerForKey3Press--;
			if(TimerForKey3Press <= 0){
				KeyReg2[3] = NORMAL_STATE;
				// set long press flag 3
				longPressedKey3_flag = 1;
			}
		}
	}

}

