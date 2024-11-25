#include "draw.h"

char arrSprintf[10];
const uint8_t mainLine[] = "*****************************\n";
const uint8_t extraLine[] = "*      *      *      *      *\n";

extern int gameScore;

void drawGame(int arr[]) {
	int gameArrVal = 0;
	PRINT_DATA(mainLine);
	PRINT_DATA(extraLine);
	PRINT_DATA((uint8_t* )"* ");
	for (uint8_t i = 0; i < 16; i++) {
		gameArrVal = arr[i];

		if (gameArrVal > 1000) {
			sprintf(arrSprintf, "%d", gameArrVal);
			PRINT_DATA(arrSprintf);
			PRINT_DATA(" * ");
		} else {

			if (gameArrVal == 0) {
				PRINT_DATA("     * ");
			} else {
				sprintf(arrSprintf, " %d", gameArrVal);
				PRINT_DATA(arrSprintf);
				if (gameArrVal < 10) {
					PRINT_DATA("   * ");
				} else if (gameArrVal < 100) {
					PRINT_DATA("  * ");
				} else {
					PRINT_DATA(" * ");
				}
			}
		}

		if ((i + 1) % 4 == 0) {
			PRINT_DATA("\n");
			PRINT_DATA(extraLine);
			PRINT_DATA(mainLine);

			if (i != 15) {
				PRINT_DATA(extraLine);
				PRINT_DATA("* ");
			}
		}
	}
	PRINT_DATA("Score: ");
	sprintf(arrSprintf, "%d", gameScore);
	PRINT_DATA(arrSprintf);

}
