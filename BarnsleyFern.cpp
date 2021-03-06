#include "Console.h"

int mapRange(float inBegin, float inEnd, int outBegin, int outEnd, float value) {
	return outBegin + (outEnd - outBegin) * (value - inBegin) / (inEnd - inBegin);
}

int main() {
	Console console = Console(200, 200, 5);
	float x = .0f, y = .0f, prevX, prevY;

	// Forever
	for (;;) {

		// Remember the previous coordinates
		prevX = x; prevY = y;

		// Randomly perform one of the 4 transformations
		int portion, r = rand() % 10000;
		if      (r <  100) { x = 0; y *= .16f; }
		else if (r <  800) { x = prevX *  .2f  + prevY * -.26; y = prevX *  .23 + prevY * .22f + 1.6f; }
		else if (r < 1500) { x = prevX * -.15f + prevY *  .28; y = prevX *  .26 + prevY * .24f +  .44f; }
		else { x = prevX *  .85f + prevY *  .04; y = prevX * -.04 + prevY * .85f + 1.6f; }

		// Place a character at the current coordinates in the console
		console.setChar(
			mapRange(-2.182f, 2.6558f, 0, console.getWidth(),  x),
			mapRange(9.9983f,     .0f, 0, console.getHeight(), y),
			Console::Colors::WHITE,
			true // update this character now, don't wait to flush the whole buffer
		);

	}
	return 0;
}
