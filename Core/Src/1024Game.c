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

int gameArr[] = { 0, 0, 0, 0, /**/0, 0, 0, 0, /**/0, 0, 0, 0, /**/0, 0, 0, 0 }; //главный
//int gameArr[] = { 512, 0, 512, 0, /**/0, 0, 0, 0, /**/0, 0, 0, 0, /**/0, 0, 0, 0 }; // тест победы
//int gameArr[] = { 32, 16, 4, 1, /**/16, 8, 1, 8, /**/8, 2, 8, 2, /**/2, 8, 2, 1 }; // тест поражения !!!!!!!!!! ОБЯЗАТЕЛЬНО ЗАКОММЕНТИТЬ (~185 строка) цикл спавна новых чисел в "r" !!!!!!!!!

int shiftArr[16];

int gameScore = 0;

uint8_t startBit = 0;
uint8_t winBit = 0;
uint8_t moveNumCount = 0;

uint8_t noUpMovement = 0;
uint8_t noDownMovement = 0;
uint8_t noLeftMovement = 0;
uint8_t noRightMovement = 0;

void shift(uint8_t i, uint8_t max);
uint8_t randomNum();
uint8_t choosingANumber();

void shiftMain(char mode) {

	if (startBit == 1) {
		if (mode == 'a') {
			memcpy(shiftArr, gameArr, sizeof(gameArr));
		} else if (mode == 'd') {
			for (int i = 0; i < 4; ++i) {
				shiftArr[i] = gameArr[3 - i];
				shiftArr[i + 4] = gameArr[7 - i];
				shiftArr[i + 8] = gameArr[11 - i];
				shiftArr[i + 12] = gameArr[15 - i];
			}
		} else if (mode == 'w') {
			for (int i = 0; i < 4; ++i) {
				shiftArr[i] = gameArr[i * 4];
				shiftArr[i + 4] = gameArr[i * 4 + 1];
				shiftArr[i + 8] = gameArr[i * 4 + 2];
				shiftArr[i + 12] = gameArr[i * 4 + 3];
			}
		} else if (mode == 's') {
			for (int i = 0; i < 4; ++i) {
				shiftArr[i] = gameArr[12 - i * 4];
				shiftArr[i + 4] = gameArr[13 - i * 4];
				shiftArr[i + 8] = gameArr[14 - i * 4];
				shiftArr[i + 12] = gameArr[15 - i * 4];
			}
		} else if (mode == 'r') {
			memset(gameArr, 0, sizeof(gameArr));
			PRINT_DATA(gameLogo);
			PRINT_DATA(gameControls);
			startBit = 1;
			winBit = 0;
			gameScore = 0;

			for (uint8_t i = 0; i < 2; ++i) {
				uint8_t a = 0;

				do {
					a = randomNum();
				} while (gameArr[a] != 0);

				gameArr[a] = choosingANumber();

			}

			drawGame(gameArr);
			return;
		}

		moveNumCount = 0;
		for (uint8_t i = 0; i < 13; i = i + 4) {
			if (shiftArr[i] != 0 || shiftArr[i + 1] != 0 || shiftArr[i + 2] != 0
					|| shiftArr[i + 3] != 0) {
				shift(i, i + 3);
			}
		}

		if (mode == 'a') {

			if (moveNumCount == 0) {
				noLeftMovement = 1;
			} else {
				noLeftMovement = 0;
			}

			memcpy(gameArr, shiftArr, sizeof(gameArr));
		} else if (mode == 'd') {
			if (moveNumCount == 0) {
				noRightMovement = 1;
			} else {
				noRightMovement = 0;
			}
			for (int i = 0; i < 4; ++i) {
				gameArr[3 - i] = shiftArr[i];
				gameArr[7 - i] = shiftArr[i + 4];
				gameArr[11 - i] = shiftArr[i + 8];
				gameArr[15 - i] = shiftArr[i + 12];
			}
		} else if (mode == 'w') {
			if (moveNumCount == 0) {
				noUpMovement = 1;
			} else {
				noUpMovement = 0;
			}
			for (int i = 0; i < 4; ++i) {
				gameArr[i * 4] = shiftArr[i];
				gameArr[i * 4 + 1] = shiftArr[i + 4];
				gameArr[i * 4 + 2] = shiftArr[i + 8];
				gameArr[i * 4 + 3] = shiftArr[i + 12];
			}
		} else if (mode == 's') {
			if (moveNumCount == 0) {
				noDownMovement = 1;
			} else {
				noDownMovement = 0;
			}
			for (int i = 0; i < 4; ++i) {
				gameArr[12 - i * 4] = shiftArr[i];
				gameArr[13 - i * 4] = shiftArr[i + 4];
				gameArr[14 - i * 4] = shiftArr[i + 8];
				gameArr[15 - i * 4] = shiftArr[i + 12];
			}
		}

		if (moveNumCount > 0) {
			uint8_t a = 0;

			do {
				a = randomNum();
			} while (gameArr[a] != 0);

			gameArr[a] = choosingANumber();
		}

		drawGame(gameArr);

		if (winBit == 1) {
			memset(gameArr, 0, sizeof(gameArr));
			startBit = 0;
			winBit = 0;
			gameScore = 0;
			PRINT_DATA(winLogo);
		}

		if (noUpMovement == 1 && noDownMovement == 1 && noLeftMovement == 1
				&& noRightMovement == 1) {
			memset(gameArr, 0, sizeof(gameArr));
			startBit = 0;
			gameScore = 0;
			PRINT_DATA(loseLogo);
		}

	} else {
		if (mode == 'r') {
			PRINT_DATA(gameLogo);
			PRINT_DATA(gameControls);
			startBit = 1;

			for (uint8_t i = 0; i < 2; ++i) { // !!!!!!!!!! ОБЯЗАТЕЛЬНО ЗАКОММЕНТИТЬ цикл для теста поражения
				uint8_t a = 0;

				do {
					a = randomNum();
				} while (gameArr[a] != 0);

				gameArr[a] = choosingANumber();

			}

			drawGame(gameArr);

		} else {
			PRINT_DATA(gameStartText);
		}
	}
}

void shift(uint8_t i, uint8_t max) {
	if (shiftArr[i] == 0) {

		if (shiftArr[i + 1] != 0) {
			++moveNumCount;
			shiftArr[i] = shiftArr[i + 1];
			shiftArr[i + 1] = 0;
		}

		if (i + 2 <= max) {

			if (shiftArr[i + 2] != 0) {
				++moveNumCount;
				shiftArr[i + 1] = shiftArr[i + 2];
				shiftArr[i + 2] = 0;
			}

			if (i + 3 <= max) {

				if (shiftArr[i + 3] != 0) {
					++moveNumCount;
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

		shift(i, max);
	} else {

		if (i + 1 <= max && shiftArr[i + 1] != 0) {
			if (shiftArr[i] == shiftArr[i + 1]) {
				++moveNumCount;
				shiftArr[i] = shiftArr[i] + shiftArr[i + 1];
				gameScore += shiftArr[i];
				if (shiftArr[i] == 1024) {
					winBit = 1;
				}
				shiftArr[i + 1] = 0;
			}
		} else if (i + 2 <= max && shiftArr[i + 2] != 0) {
			if (shiftArr[i] == shiftArr[i + 2]) {
				++moveNumCount;
				shiftArr[i] = shiftArr[i] + shiftArr[i + 2];
				gameScore += shiftArr[i];
				if (shiftArr[i] == 1024) {
					winBit = 1;
				}
				shiftArr[i + 2] = 0;
			}
		} else if (i + 3 <= max && shiftArr[i + 3] != 0) {
			if (shiftArr[i] == shiftArr[i + 3]) {
				++moveNumCount;
				shiftArr[i] = shiftArr[i] + shiftArr[i + 3];
				gameScore += shiftArr[i];
				if (shiftArr[i] == 1024) {
					winBit = 1;
				}
				shiftArr[i + 3] = 0;
			}
		}

		if (i + 1 < max) {
			shift(i + 1, max);
		}
	}

	return;
}

uint8_t randomNum() {

	uint8_t randNum = getADCValue() % 100;

	if (randNum > 15) {
		randNum = randNum % 16;
	}

	return randNum;
}

uint8_t choosingANumber() {

	uint8_t chNum = getADCValue() % 100;

	if (chNum <= 89) {
		return 1;
	} else {
		return 2;
	}
}
