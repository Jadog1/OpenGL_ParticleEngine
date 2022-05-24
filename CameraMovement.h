#pragma once

struct coord {
	float x; float y; float z;
};
struct player {
	struct coord worldCoord;
	struct coord rotatePos;
	float lookDirection[2];
	float unitCircleDegrees;
	int maxYRange;
	bool keypresses[256];
};
struct coordAndPrev {
	int x; int y; int z;
	int prevX; int prevY;
};
void setDefaults();
void keyup(unsigned char key, int useless, int useless2);
void keydown(unsigned char key, int useless, int useless2);
void cameraOrient();
void mouseMovement(int x, int y);