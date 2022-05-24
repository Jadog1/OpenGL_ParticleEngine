#include "FireGeneration.h"
#include <GL/freeglut.h>
#include <stdlib.h>

void ValuesToArray(float xyz[], float x, float y, float z) {
	xyz[0] = x, xyz[1] = y, xyz[2] = z;
}

FireBox::FireBox(float posX, float posY, float posZ, float sizeX, float sizeY, float sizeZ, float pixelSize)
{
	ValuesToArray(position, posX, posY, posZ);
	ValuesToArray(size, sizeX, sizeY, sizeZ);
	FireBox::pixelSize = pixelSize;
	fire.resize((sizeX * sizeY * sizeZ) / pixelSize);
	InitFireBallPosition(position, size);
}

void FireBox::DrawFire()
{
	for (auto& fireball : fire) {
		glPushMatrix();
		glTranslatef(fireball.position[0], fireball.position[1], fireball.position[2]);
		glutSolidSphere(pixelSize, 1, 1);
		glPopMatrix();
	}
}

bool FireBox::Collision(FireBall one, FireBall two)
{
	return false;
}

void FireBox::setfireball(std::vector<FireBall>::iterator *it, float position[3]) {
	if (*it == fire.end()) { printf("Hit end"); return; }
	for (int i = 0; i < 3; i++) {
		(*it)->position[i] = position[i];
	}
	(*it)++;
}

void FireBox::InitFireBallPosition(float position[3], float size[3])
{
	float positionAt[3] = { position[0], position[1], position[2] };
	std::vector<FireBall>::iterator it = fire.begin();
	for (int x = 0; x < size[0]; x += pixelSize) {
		setfireball(&it, positionAt);
		for (int y = 0; y < size[1]; y += pixelSize) {
			setfireball(&it, positionAt);
			for (int z = 0; z < size[2]; z += pixelSize) {
				setfireball(&it, positionAt);
				positionAt[2] += pixelSize;
			}
			positionAt[1] -= pixelSize;
		}
		positionAt[0] += pixelSize;
	}

}

void FireBoxHandler::addFireBox(FireBox fb)
{
	FireBoxes.push_back(fb);
}

void FireBoxHandler::DrawFireBox()
{
	for (auto& firebox : FireBoxes) {
		firebox.DrawFire();
	}
}
