#include "draw.h"

void drawGame(int arr[], int gameScore) {

	char arrSprintf[32];

	PRINT_DATA(
			"*****************************\n*      *      *      *      *\n* ");
	for (uint8_t i = 0; i < 16; i++) {
		if (arr[i] > 1000) {
			sprintf(arrSprintf, "%d * ", arr[i]);
			PRINT_DATA(arrSprintf);
		} else {
			if (arr[i] == 0) {
				PRINT_DATA("     * ");
			} else {
				if (arr[i] < 10) {
					sprintf(arrSprintf, " %d   * ", arr[i]);
				} else if (arr[i] < 100) {
					sprintf(arrSprintf, " %d  * ", arr[i]);
				} else {
					sprintf(arrSprintf, " %d * ", arr[i]);
				}
				PRINT_DATA(arrSprintf);
			}
		}
		if ((i + 1) % 4 == 0) {
			PRINT_DATA(
					"\n*      *      *      *      *\n*****************************\n");
			if (i != 15) {
				PRINT_DATA("*      *      *      *      *\n* ");
			}
		}
	}
	sprintf(arrSprintf, "## Total score: %d ##\n\n\n", gameScore);
	PRINT_DATA(arrSprintf);
}
