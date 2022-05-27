#include "FireGeneration.h"
#include <GL/freeglut.h>
#include <stdlib.h>

void ValuesToArray(float xyz[], float x, float y, float z) {
	xyz[0] = x, xyz[1] = y, xyz[2] = z;
}

FireBox::FireBox(float posX, float posY, float posZ, float sizeX, float sizeY, float sizeZ, float pixelSize, float percentFullSet)
{
	percentFull = percentFullSet;
	ValuesToArray(position, posX, posY, posZ);
	ValuesToArray(size, sizeX, sizeY, sizeZ);
	FireBox::pixelSize = pixelSize;
	fire.resize((sizeX * (sizeY*percentFull) * sizeZ) / pixelSize);
	InitFireBallPosition(position, size);
}

void FireBox::DrawFire()
{
	for (auto& fireball : fire) {
		ApplyForces(&fireball);
		if (FireballTemperature(&fireball)) {
			glPushMatrix();
			glTranslatef(fireball.position[0], fireball.position[1], fireball.position[2]);
			glutSolidCube(pixelSize);
			glPopMatrix();
		}
	}
}

bool FireBox::Collision(FireBall fb1, FireBall fb2)
{
	return !(
		fb1.position[2] + pixelSize < fb2.position[2] ||
		fb1.position[2] > fb2.position[2] + pixelSize ||
		fb1.position[1] + pixelSize < fb2.position[1] ||
		fb1.position[1] > fb2.position[1] + pixelSize ||
		fb1.position[0] + pixelSize < fb2.position[0] ||
		fb1.position[0] > fb2.position[0] + pixelSize
		);
}

void FireBox::setfireball(std::vector<FireBall>::iterator *it, float position[]) {
	if (*it == fire.end()) { 
		printf("overflow");  return; }
	for (int i = 0; i < 3; i++) {
		(*it)->position[i] = position[i];
	}
	(*it)++;
}

void FireBox::ApplyForces(FireBall *fb)
{

	
	if (fb->position[1] < position[1] + size[1]) {
		fb->velocity[1] += 0.1;
		fb->temperature -= 0.01;
	}
	float minheightvec = position[1] + size[1] - (pixelSize * 3);
	if (fb->position[1] >= minheightvec && fb->position[1] <= position[1] + size[1]) {
		RandomizeVelocity(fb);
		fb->temperature = 1;
	}

	for (int i = 0; i < 3; i++) fb->position[i] += fb->velocity[i];
}

void FireBox::RandomizeVelocity(FireBall* fb)
{
	fb->velocity[1] = -(rand() % 4);
}

bool FireBox::FireballTemperature(FireBall* fb)
{
	bool drawPixel = true;//fb->temperature >= 0.3;
	if (drawPixel) {
		if (fb->temperature > 0.8)
			glColor3f(1, 1, 1);
		else if (fb->temperature > 0.5)
			glColor3f(fb->temperature, 0, 0);
		else
			glColor3f(0, 0, 0.5);
	}
	return drawPixel;
}

void FireBox::InitFireBallPosition(float position[], float size[])
{
	float positionAt[3] = { position[0], position[1], position[2] };
	std::vector<FireBall>::iterator it = fire.begin();
	for (int x = 0; x < size[0]; x += pixelSize) {
		for (int y = 0; y < size[1]*percentFull; y += pixelSize) {
			for (int z = 0; z < size[2]; z += pixelSize) {
				//RandomizeVelocity(&(*it));
				it->temperature = 1;
				setfireball(&it, positionAt);
				positionAt[2] += pixelSize;
			}
			positionAt[2] = position[2];
			positionAt[1] += (-pixelSize);
		}
		positionAt[1] = position[1];
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
