#include "FireGeneration.h"
#include <GL/freeglut.h>
#include <stdlib.h>
#include "MathHelper.h"

void FireBox::CollisionDifference(FireBall *fb) {
	if (fb->position[2] + pixelSize + fb->velocity[2] < position[2] ||
		fb->position[2] > position[2] + size[2]) {
		fb->velocity[2] = 0;
		fb->temperature = 0;
	}

	if (fb->position[0] + pixelSize + fb->velocity[0] < position[0] ||
		fb->position[0] + fb->velocity[0] > position[0] + size[0]) {
		fb->velocity[0] = 0;
		fb->temperature = 0;
	}


}
void FireBox::CollisionDifference(FireBall* fb1, FireBall* fb2) {

}

void ValuesToArray(float xyz[], float x, float y, float z) {
	xyz[0] = x, xyz[1] = y, xyz[2] = z;
}

FireBox::FireBox(float posX, float posY, float posZ, float sizeX, float sizeY, float sizeZ, float pixelSize, float percentFullSet)
{
	percentFull = percentFullSet;
	ValuesToArray(position, posX, posY, posZ);
	ValuesToArray(size, sizeX, sizeY, sizeZ);
	FireBox::pixelSize = pixelSize;
	float newSize = (sizeX * floor(sizeY * percentFull) * sizeZ)/pixelSize;
	fire.resize(newSize);
	InitFireBallPosition(position, size);
}

void FireBox::ApplyForces(FireBall* fb)
{

	float minheightvec = position[1] + size[1] - (pixelSize * 3);
	if (fb->position[1] < position[1] + size[1]) {
		fb->velocity[1] += 0.03;
		for(int i = 0; i < 3; i+=2) fb->velocity[i] += normalizedFlipped(fb->velocity[i])*0.025;
		if (fb->velocity[1] <= 0) fb->temperature = (fb->velocity[1]*-1);
		CollisionDifference(fb);
	}
	if (fb->position[1] >= minheightvec) {
		if (fb->position[1] >= position[1] + size[1])
			fb->position[1] = position[1] + size[1];
		RandomizeVelocity(fb);
		fb->temperature = 1;
	}
}

bool FireBox::FireballTemperature(FireBall* fb)
{
	bool drawPixel = fb->temperature >= 0.15;
	if (drawPixel) {
		if (fb->temperature > 0.7)
			glColor3f(1, 1, 1);
		else if (fb->temperature > 0.35)
			glColor3f(fb->temperature, 0, 0);
		else
			glColor3f(0, 0, 0.5);
	}
	return drawPixel;
}

void FireBox::DrawFire()
{
	for (auto& fireball : fire) {
		ApplyForces(&fireball);
		for (int i = 0; i < 3; i++) fireball.position[i] += fireball.velocity[i];
		if (FireballTemperature(&fireball)) {
			glPushMatrix();
			glTranslatef(fireball.position[0], fireball.position[1], fireball.position[2]);
			float pixelSizeVal = (pixelSize * fireball.temperature);
			glutSolidCube((pixelSizeVal>0.5) ? pixelSizeVal : 0.5);
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


void FireBox::RandomizeVelocity(FireBall* fb)
{
	fb->velocity[1] = -(rand() % 6)/5.0;
	fb->velocity[0] = (double)moveToMiddle(fb->position[0], position[0], position[0]+size[0]) * (rand() % 5) / 5.0;
	fb->velocity[2] = (double)moveToMiddle(fb->position[2], position[2], position[2] + size[2]) * (rand() % 5) / 5.0;
}


void FireBox::setfireball(std::vector<FireBall>::iterator* it, float position[]) {
	if (*it == fire.end()) { printf("YEP"); return; }
	for (int i = 0; i < 3; i++) {
		(*it)->position[i] = position[i];
	}
	(*it)->temperature = 1;
	(*it)++;
}

void to3DArray(int indx, float maxX, float maxY, float position[]) {
	int x = 0, y = 0, z = 0;
	z = indx / (maxX * maxY);
	indx -= (z * maxX * maxY);
	y = indx / maxX;
	x = indx % (int)maxX;
	position[0] += ceil(x); position[1] += ceil(y); position[2] += ceil(z);
}

void FireBox::InitFireBallPosition(float position[], float size[])
{
	int i = 0;
	float positionAt[3] = { position[0], position[1], position[2] };
	float positionAt2[3] = { position[0], position[1], position[2] };
	for (auto& fireball : fire) {
		to3DArray(i, size[0], size[1] / percentFull, positionAt);
		fireball.position[0] = positionAt[0]; fireball.position[1] = positionAt[1]; fireball.position[2] = positionAt[2];
		for (int i = 0; i < 3; i++) positionAt[i] = positionAt2[i];
		i++;
	}
	/*std::vector<FireBall>::iterator it = fire.begin();
	for (int x = 0; x < size[0]; x += 1) {
		setfireball(&it, positionAt);
		for (int y = 0; y < (int) floor((double)size[1]*percentFull); y += 1) {
			positionAt[1] += (-pixelSize);
			setfireball(&it, positionAt);
			for (int z = 0; z < size[2]; z += 1) {
				positionAt[2] += pixelSize;
				setfireball(&it, positionAt);
			}
			positionAt[2] = position[2];
		}
		positionAt[1] = position[1];
		for (int z = 0; z < size[2]; z += 1) {
			positionAt[2] += pixelSize;
			setfireball(&it, positionAt);
		}
		positionAt[2] = position[2];
		positionAt[0] += pixelSize;
	}*/
}

void FireBoxHandler::addFireBox(FireBox fb)
{
	FireBoxes.push_back(fb);
}

void drawBox(float position[],float size[]) {
	glPushMatrix();
	glTranslatef(position[0]+size[0]/2, position[1], position[2]+size[2]/2);
	glutWireCube(size[0]);
	glPopMatrix();
}

void FireBoxHandler::DrawFireBox()
{
	for (auto& firebox : FireBoxes) {
		firebox.DrawFire();
		drawBox(firebox.position, firebox.size);
	}
}
