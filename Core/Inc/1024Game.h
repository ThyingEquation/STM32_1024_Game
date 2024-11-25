#ifndef INC_1024GAME_H_
#define INC_1024GAME_H_

#include "main.h"

typedef struct {
	int gameArr[16];

	int gameScore;

	uint8_t startBit;
	uint8_t winBit;
	uint8_t moveNumCount;

	uint8_t noUpMovement;
	uint8_t noDownMovement;
	uint8_t noLeftMovement;
	uint8_t noRightMovement;
} gameField;

void shiftMain(char mode, gameField *p);

#endif /* INC_1024GAME_H_ */
