#include <3ds.h>
#include <stdio.h>

int main(int argc, char **argv) {

	//initalize services
	gfxInitDefault();
	cfguInit();

	// Init console for text output
	consoleInit(GFX_TOP, NULL);

	printf("- Touch Screen Accuracy / Functionality -");
	print("\nPress START to quit")
	u8 language = 0;
	Result res;

	// Read the language field from the config savegame.
	res = CFGU_GetSystemLanguage(&language);

	// Print return value and language code
	printf("       Result: 0x%x\n", (int)res);
	printf("Language code: %d", (int)language);

	// Main loop
	while (aptMainLoop())
	{
		hidScanInput();

		touchPosition touch;
		hidTouchRead(&touch);
		printf("\x1b[1;0HX coordinate: %i       ",touch.px);
		printf("\x1b[2;0HY coordinate: %i       ",touch.py);

		u32 kHeld = hidKeysHeld();
		if (kHeld & KEY_TOUCH)
			printf("\x1b[3;0HIs Active: TRUE ");
		else
			printf("\x1b[3;0HIs Active: FALSE");

		u32 kDown = hidKeysDown();
		if (kDown & KEY_START) break;

		gfxFlushBuffers();
		gfxSwapBuffers();

		//Wait for VBlank
		gspWaitForVBlank();
	}

	gfxExit();
	return 0;
}