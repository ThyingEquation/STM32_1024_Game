#include "1024Game.h"
#include "draw.h"

const uint8_t gameStartText[] =
		"=== Hi! This is a 1024 game. To start the game, send the 'r' character===\n\n";

const uint8_t gameLogo[] =
		"\n\n\n  __  ___ ___  _  _      _____          __  __ ______\n"
				" /_ |/ _ \\__ \\| || |    / ____|   /\\   |  \\/  |  ____|\n"
				"  | | | | | ) | || |_  | |  __   /  \\  | \\  / | |__\n"
				"  | | | | |/ /|__   _| | | |_ | / /\\ \\ | |\\/| |  __|\n"
				"  | | |_| / /_   | |   | |__| |/ ____ \\| |  | | |____\n"
				"  |_|\\___/____|  |_|    \\_____/_/    \\_\\_|  |_|______|\n\n\n";

const uint8_t winLogo[] = "\n\n\n__          _______ _   _ _\n"
		"\\ \\        / /_   _| \\ | | |\n"
		" \\ \\  /\\  / /  | | |  \\| | |\n"
		"  \\ \\/  \\/ /   | | | . ` | |\n"
		"   \\  /\\  /   _| |_| |\\  |_|\n"
		"    \\/  \\/   |_____|_| \\_(_)\n\n"
		"=== Start new game 'r' ===\n\n\n";

const uint8_t loseLogo[] = "\n\n\n _      ____   _____ ______ _\n"
		"| |    / __ \\ / ____|  ____| |\n"
		"| |   | |  | | (___ | |__  | |\n"
		"| |   | |  | |\\___ \\|  __| | |\n"
		"| |___| |__| |____) | |____|_|\n"
		"|______\\____/|_____/|______(_)\n\n"
		"=== Start new game 'r' ===\n\n\n";

const uint8_t gameControls[] =
		"=== Game controls (send next characters): start new game 'r'; left shift 'a'; right shift 'd'; top shift 'w'; down shift 's' ===\n\n";

int shiftArr[16];

void shiftArrProcessing(gameField_t *p);

void leftShift(gameField_t *p);
void rightShift(gameField_t *p);
void upShift(gameField_t *p);
void downShift(gameField_t *p);

void fullGameReload(gameField_t *p);

void shift(uint8_t i, uint8_t max, gameField_t *p);

uint8_t choosingANumber();

void shiftMain(char mode, gameField_t *p) {

	if (p->startBit == 1) {
		if (mode == 'a') {
			leftShift(p);
		} else if (mode == 'd') {
			rightShift(p);
		} else if (mode == 'w') {
			upShift(p);
		} else if (mode == 's') {
			downShift(p);
		} else if (mode == 'r') {
			fullGameReload(p);
			return;
		}

		if (p->moveNumCount > 0) { // Новое число
			uint8_t a = 0;

			do {
				a = rand() % 16;

			} while (p->gameArr[a] != 0);

			p->gameArr[a] = choosingANumber();
		}

		drawGame(p->gameArr, p->gameScore);

		if (p->winBit == 1) {
			memset(p->gameArr, 0, sizeof(p->gameArr));
			p->startBit = 0;
			p->winBit = 0;
			p->gameScore = 0;
			PRINT_DATA(winLogo);
		}

		if (p->noUpMovement == 1 && p->noDownMovement == 1
				&& p->noLeftMovement == 1 && p->noRightMovement == 1) {
			memset(p->gameArr, 0, sizeof(p->gameArr));
			p->startBit = 0;
			p->gameScore = 0;
			PRINT_DATA(loseLogo);
		}

	} else {
		if (mode == 'r') {
			fullGameReload(p);
		} else {
			PRINT_DATA(gameStartText);
		}
	}
}

// Функция обработки "сдвигового" массива
void shiftArrProcessing(gameField_t *p) {
	p->moveNumCount = 0;
	for (uint8_t i = 0; i < 13; i = i + 4) {
		if (shiftArr[i] != 0 || shiftArr[i + 1] != 0 || shiftArr[i + 2] != 0
				|| shiftArr[i + 3] != 0) {
			shift(i, i + 3, p);
		}
	}
}

void leftShift(gameField_t *p) {

	memcpy(shiftArr, p->gameArr, sizeof(p->gameArr));

	shiftArrProcessing(p);

	if (p->moveNumCount == 0) {
		p->noLeftMovement = 1;
	} else {
		p->noLeftMovement = 0;
	}

	memcpy(p->gameArr, shiftArr, sizeof(p->gameArr));
}

void rightShift(gameField_t *p) {

	for (int i = 0; i < 4; ++i) {
		shiftArr[i] = p->gameArr[3 - i];
		shiftArr[i + 4] = p->gameArr[7 - i];
		shiftArr[i + 8] = p->gameArr[11 - i];
		shiftArr[i + 12] = p->gameArr[15 - i];
	}

	shiftArrProcessing(p);

	if (p->moveNumCount == 0) {
		p->noRightMovement = 1;
	} else {
		p->noRightMovement = 0;
	}
	for (int i = 0; i < 4; ++i) {
		p->gameArr[3 - i] = shiftArr[i];
		p->gameArr[7 - i] = shiftArr[i + 4];
		p->gameArr[11 - i] = shiftArr[i + 8];
		p->gameArr[15 - i] = shiftArr[i + 12];
	}
}

void upShift(gameField_t *p) {
	for (int i = 0; i < 4; ++i) {
		shiftArr[i] = p->gameArr[i * 4];
		shiftArr[i + 4] = p->gameArr[i * 4 + 1];
		shiftArr[i + 8] = p->gameArr[i * 4 + 2];
		shiftArr[i + 12] = p->gameArr[i * 4 + 3];
	}

	shiftArrProcessing(p);

	if (p->moveNumCount == 0) {
		p->noUpMovement = 1;
	} else {
		p->noUpMovement = 0;
	}
	for (int i = 0; i < 4; ++i) {
		p->gameArr[i * 4] = shiftArr[i];
		p->gameArr[i * 4 + 1] = shiftArr[i + 4];
		p->gameArr[i * 4 + 2] = shiftArr[i + 8];
		p->gameArr[i * 4 + 3] = shiftArr[i + 12];
	}
}

void downShift(gameField_t *p) {
	for (int i = 0; i < 4; ++i) {
		shiftArr[i] = p->gameArr[12 - i * 4];
		shiftArr[i + 4] = p->gameArr[13 - i * 4];
		shiftArr[i + 8] = p->gameArr[14 - i * 4];
		shiftArr[i + 12] = p->gameArr[15 - i * 4];
	}

	shiftArrProcessing(p);

	if (p->moveNumCount == 0) {
		p->noDownMovement = 1;
	} else {
		p->noDownMovement = 0;
	}
	for (int i = 0; i < 4; ++i) {
		p->gameArr[12 - i * 4] = shiftArr[i];
		p->gameArr[13 - i * 4] = shiftArr[i + 4];
		p->gameArr[14 - i * 4] = shiftArr[i + 8];
		p->gameArr[15 - i * 4] = shiftArr[i + 12];
	}
}

void fullGameReload(gameField_t *p) {
	memset(p->gameArr, 0, sizeof(p->gameArr));
	PRINT_DATA(gameLogo);
	PRINT_DATA(gameControls);
	p->startBit = 1;
	p->winBit = 0;
	p->gameScore = 0;

	for (uint8_t i = 0; i < 2; ++i) {
		uint8_t a = 0;

		do {
			a = rand() % 16;
			;
		} while (p->gameArr[a] != 0);

		p->gameArr[a] = choosingANumber();

	}

	drawGame(p->gameArr, p->gameScore);
}

// Рекурсивная функция сдвига и сложения чисел в указанную сторону
void shift(uint8_t i, uint8_t max, gameField_t *p) {
	if (shiftArr[i] == 0) {
		if (shiftArr[i + 1] != 0) {
			p->moveNumCount++;
			shiftArr[i] = shiftArr[i + 1];
			shiftArr[i + 1] = 0;
		}
		if (i + 2 <= max) {
			if (shiftArr[i + 2] != 0) {
				p->moveNumCount++;
				shiftArr[i + 1] = shiftArr[i + 2];
				shiftArr[i + 2] = 0;
			}
			if (i + 3 <= max) {
				if (shiftArr[i + 3] != 0) {
					p->moveNumCount++;
					shiftArr[i + 2] = shiftArr[i + 3];
					shiftArr[i + 3] = 0;
				}
			} else {
				if (shiftArr[i + 1] == 0 && shiftArr[i + 2] == 0) {
					return;
				}
			}
		} else {
			if (shiftArr[i] == 0 && shiftArr[i + 1] == 0) {
				return;
			}
		}
		shift(i, max, p);
	} else {
		for (uint8_t j = 1; j <= 3; ++j) {
			if (i + j <= max && shiftArr[i + j] != 0) {
				if (shiftArr[i] == shiftArr[i + j]) {
					p->moveNumCount++;
					shiftArr[i] += shiftArr[i + j];
					p->gameScore += shiftArr[i];
					if (shiftArr[i] == p->difficulty) {
						p->winBit = 1;
					}
					shiftArr[i + j] = 0;
				}
				break;
			}
		}

		if (i + 1 < max) {
			shift(i + 1, max, p);
		}
	}
	return;
}

// Выбор числа 1 или 2 с вероятностью 90% и 10% соответственно
uint8_t choosingANumber() {

	uint8_t chNum = rand() % 100;

	if (chNum <= 89) {
		return 1;
	} else {
		return 2;
	}
}
