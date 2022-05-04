#pragma once
#include <GL/freeglut.h>
#include <stdlib.h>
#include <algorithm>
#include "PixelGeneration.h"
/*
*Particle system developed by Jadon Steinmetz
*/

#define MAXPARTICLES 150


struct particle particleSys[MAXPARTICLES];


struct particleSystem p;
void createParticleSystem(int x, int y, int z, int xr, int yr, int zr) {
	p.x = x;
	p.y = y;
	p.z = z;
	p.radius[0] = xr;
	p.radius[1] = yr;
	p.radius[2] = zr;
}

float subtractIfNotZero(float* velocity, float value) {
	if (*velocity > 0)
		*velocity -= value;

	return *velocity;
}
int positiveOrNegative() {
	return ((rand() % 2) < 1 ? -1 : 1);
}
int negativeOf(float value) {
	return (value < 0 ? -1 : 1);
}
bool inRange(float x, float a, float b) {
	return (x >= a && x <= b);
}

//Method for drawing particle
void draw3DParticle(particle particleAt) {
	glPushMatrix();
	glTranslatef(particleAt.x, particleAt.y, particleAt.z);
	glRotatef(50.0 * particleAt.vy, 1, 1, 1);
	glutSolidCube(5);
	glPopMatrix();
}

//Draws the particles and updates them accordingly
void drawParticles() {
	const int maxCreatedParticles = ceil(MAXPARTICLES * 0.1);
	int particlesCreated = 0;
	
	for (int i = 0; i < MAXPARTICLES; i++) {
		if (particlesCreated < maxCreatedParticles && particleSys[i].life<=0.0) {
			particleSys[i].life = (((double)(rand() % 75) + 25) / 100.0);
			particleSys[i].x = p.x + (p.radius[0] != 0 ? rand() % p.radius[0] : 0);
			particleSys[i].y = p.y - (p.radius[1] != 0 ? rand() % p.radius[1] : 0);
			particleSys[i].z = p.z + (p.radius[2] != 0 ? rand() % p.radius[2] : 0);

			particleSys[i].vx = (float)positiveOrNegative() * 2.0 * ((rand() % 7) + 1.5) / 5.0;
			particleSys[i].vy = (float)-2 * ((rand() % 10) + 3.5) / 6.5;
			particleSys[i].vz = (float)positiveOrNegative() * 2.0  * ((rand() % 5) + 0.5) / 4.5;
			particlesCreated++;
		}

		if (particleSys[i].life > 0.0) {
			float minVal = std::min(particleSys[i].vx, particleSys[i].vz);
			float lifespanByVelocity = minVal / (1 - (1 / minVal / 0.01));
			float pixelColor = (lifespanByVelocity > particleSys[i].life ? lifespanByVelocity : particleSys[i].life);
			glColor3f((pixelColor <= 1 ? pixelColor : 1), 0.0, 0.0);

			particleSys[i].x += subtractIfNotZero(&particleSys[i].vx, negativeOf(particleSys[i].vx) * 0.01);
			particleSys[i].y += (particleSys[i].vy += 0.05);
			particleSys[i].z += subtractIfNotZero(&particleSys[i].vz, negativeOf(particleSys[i].vz) * 0.01);
			particleSys[i].life -= 0.01;
			if (inRange(particleSys[i].vx, -.4, .4) || inRange(particleSys[i].vz, -.4, .4) || particleSys[i].y > p.y)
				particleSys[i].life = 0;
			draw3DParticle(particleSys[i]);
		}
	}
}