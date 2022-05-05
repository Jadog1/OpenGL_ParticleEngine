#include "CameraMovement.h"
#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>


struct coord eyePos;
struct coordAndPrev lookPos;
struct player playerData;
bool forceMouse = true;
//For testing
void setDefaults() {
	eyePos.x = 0; eyePos.y = 0; eyePos.z = 50;
	lookPos.x = 0; lookPos.y = 0; lookPos.z = 0; lookPos.prevX = 0; lookPos.prevY = 0;
	playerData.worldCoord.x = 0; playerData.worldCoord.y = 0; playerData.worldCoord.z = 20;
	playerData.lookDirection[0] = 0; playerData.lookDirection[1] = 1;
	playerData.unitCircleDegrees = 0;
	playerData.maxYRange = 40;
	playerData.rotatePos.x = 0; playerData.rotatePos.y = 0; playerData.rotatePos.z = 0;
}

float convertDegrees(float horizontal, float vertical) { return atan(vertical / horizontal) * 180 / 3.14159; }
float convertRadians(float degrees) { return degrees * 3.14159 / 180; }
void moveForward(float velocity) {
	float x = playerData.lookDirection[0] * velocity, z = playerData.lookDirection[1] * velocity;
	playerData.worldCoord.x += x;
	playerData.worldCoord.z += z;
}
void moveSideways(float velocity) {
	float x = sin(convertRadians(playerData.unitCircleDegrees+90)) * velocity, z = cos(convertRadians(playerData.unitCircleDegrees+90)) * velocity;
	playerData.worldCoord.x += x;
	playerData.worldCoord.z += z;
}
void rotateWorld(int degrees, int xrotation=0, int degrees2=0, int yrotation=0) {
	float angle = degrees2 * yrotation;
	bool CanLookX = true;

	if (degrees != 0) {
		if (playerData.rotatePos.y + degrees < playerData.maxYRange && playerData.rotatePos.y + degrees > -playerData.maxYRange) degrees = degrees;
		else if (playerData.rotatePos.y < playerData.maxYRange && degrees>0) degrees = playerData.maxYRange - playerData.rotatePos.y;
		else if (playerData.rotatePos.y > -playerData.maxYRange && degrees < 0) degrees = -(playerData.maxYRange + playerData.rotatePos.y);
		else CanLookX = false;

		if (CanLookX) playerData.rotatePos.y += degrees;
	}

	if (degrees2 != 0) playerData.rotatePos.x += degrees2;

	playerData.unitCircleDegrees -= angle;
	playerData.lookDirection[0] = sin(convertRadians(playerData.unitCircleDegrees));
	playerData.lookDirection[1] = cos(convertRadians(playerData.unitCircleDegrees));
}

void keydown(unsigned char key, int useless, int useless2) {
	playerData.keypresses[int(key)] = true;
	switch (key) {
	case '`':
		setDefaults();
		break;
	case 'p':
		forceMouse = !forceMouse;
		break;
	case 'Q':
		exit(0);
		break;
	}
}
void keyup(unsigned char key, int useless, int useless2) {
	playerData.keypresses[int(key)] = false;
}

void keyboardMovement() {

	if(playerData.keypresses[int('a')])
		moveSideways(5);
	if (playerData.keypresses[int('d')])
		moveSideways(-5);
	if (playerData.keypresses[int('w')])
		moveForward(5);
	if (playerData.keypresses[int('s')])
		moveForward(-5);
	if (playerData.keypresses[int('q')])
		playerData.worldCoord.y += 5;
	if (playerData.keypresses[int('e')])
		playerData.worldCoord.y -= 5;
}

void mouseMovement(int x, int y) {
	if (forceMouse) {
		rotateWorld(y-300, 1, x-300, 1);
		glutWarpPointer(300, 300);
	}
}

void cameraOrient() {
	//Move player
	keyboardMovement();
	//Rotate look position
	glRotatef(playerData.rotatePos.y, 1, 0, 0);
	glRotatef(playerData.rotatePos.x, 0, 1, 0);
	//Move user
	glTranslatef(playerData.worldCoord.x, playerData.worldCoord.y, playerData.worldCoord.z);
	gluLookAt(eyePos.x, eyePos.y, eyePos.z, lookPos.x, lookPos.y, lookPos.z, 0, -1, 0);
}