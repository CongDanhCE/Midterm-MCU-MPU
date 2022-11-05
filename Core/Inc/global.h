/*
 * global.h
 *
 *  Created on: Nov 5, 2022
 *      Author: ASUS
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"

#define INIT				0
#define RESET_PRESSED		1
#define INC_PRESSED			2
#define DEC_PRESSED			3
#define NOT_PRESSED			4

extern int counter;
extern int mode;

#endif /* INC_GLOBAL_H_ */
