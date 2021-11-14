#include <stdlib.h>
#include <stdio.h>
#include <gint/gint.h>
#include <gint/display.h>
#include <gint/keyboard.h>
#include <gint/keycodes.h>
#include <gint/timer.h>

char* buffer;
bool keyWasPressed = false;
int lastKeyPressed = 0;
int rectX = (128 / 2) - 8;
int rectY = (64 / 2) - 8;
int rectVelX = 1;
int rectVelY = 1;

int tick() {
	rectX += rectVelX;
	rectY += rectVelY;

	if (rectX <= 0) {
		rectVelX = 1;
	}

	if (rectX >= 128 - 16) {
		rectVelX = -1;
	}

	if (rectY <= 0) {
		rectVelY = 1;
	}

	if (rectY >= 64 - 16) {
		rectVelY = -1;
	}

	return TIMER_CONTINUE;
}

void main(void) {
	buffer = malloc(16);

	int timer = timer_configure(TIMER_ETMU, 4e4, GINT_CALL(tick)); // No need to be precise

	timer_start(timer);

	while (true) {
		dclear(C_WHITE);

		dtext(0, 0, C_BLACK, "Hello, world!");
		dtext(0, 8, C_BLACK, "An add-in made by");
		dtext(0, 16, C_BLACK, "James Livesey");
		
		if (keyWasPressed) {
			sprintf(buffer, "Key pressed: %d", lastKeyPressed);
		} else {
			sprintf(buffer, "No keys pressed");
		}

		dtext(0, 64 - 8, C_BLACK, buffer);

		drect(rectX, rectY, rectX + 15, rectY + 15, C_INVERT);

		dupdate();

		key_event_t keyEvent = pollevent();

		if (keyEvent.type == KEYEV_DOWN) {
			keyWasPressed = true;
			lastKeyPressed = keyEvent.key;

			if (lastKeyPressed == KEY_MENU) {
				gint_osmenu();
			}
		}
	}
}