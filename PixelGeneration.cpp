#pragma once
#include <GL/freeglut.h>
#include <stdlib.h>
#include <algorithm>
#include "PixelGeneration.h"
/*
*Particle system developed by Jadon Steinmetz
*/


PixelGenerator::PixelGenerator(int posX, int posY, int posZ, int radiusX, int radiusY, int radiusZ, int pixelCount, int newShape) {
	position.x = posX; position.y = posY; position.z = posZ;
	radius.x = radiusX; radius.y = radiusY; radius.z = radiusZ;
	particles.resize(pixelCount);
	shape = newShape;
}

PixelGenerator::PixelGenerator(int positionArray[], int radiusArray[], int pixelCount, int newShape) {
	position.x = positionArray[0]; position.y = positionArray[1]; position.z = positionArray[2];
	radius.x = radiusArray[0]; radius.y = radiusArray[1]; radius.z = radiusArray[2];
	particles.resize(pixelCount);
	shape = newShape;
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

void PixelGenerator::setPixelCount(int pixelCount) {
	particles.resize(pixelCount);
}

//Method for drawing particle
void PixelGenerator::draw3DParticle(particleObj particleAt) {
	glPushMatrix();
	glTranslatef(particleAt.x, particleAt.y, particleAt.z);
	glRotatef(50.0 * particleAt.vy, 1, 1, 1);
	switch (shape) {
	case OBJ_SHAPE_CUBE:
		glutSolidCube(5);
		break;
	case OBJ_SHAPE_WIRECUBE:
		glutWireCube(5);
		break;
	case OBJ_SHAPE_TRIANGLE:
		glutSolidCone(1, 1, 3, 3);
		break;
	}
	glPopMatrix();
}

//Draws the particles and updates them accordingly
void PixelGenerator::drawParticles() {
	const int maxCreatedParticles = ceil(particles.size() * 0.1);
	int particlesCreated = 0;
	
	for (auto &particle : particles) {
		if (particlesCreated < maxCreatedParticles && particle.life<=0.0) {
			particle.life = (((double)(rand() % 75) + 25) / 100.0);
			particle.x = position.x + (radius.x != 0 ? rand() % (int)radius.x : 0);
			particle.y = position.y - (radius.y != 0 ? rand() % (int)radius.y : 0);
			particle.z = position.z + (radius.z != 0 ? rand() % (int)radius.z : 0);
				   
			particle.vx = (float)positiveOrNegative() * 2.0 * ((rand() % 7) + 1.5) / 5.0;
			particle.vy = (float)-2 * ((rand() % 10) + 3.5) / 6.5;
			particle.vz = (float)positiveOrNegative() * 2.0  * ((rand() % 5) + 0.5) / 4.5;
			particlesCreated++;
		}

		if (particle.life > 0.0) {
			float minVal = std::min(particle.vx, particle.vz);
			float lifespanByVelocity = minVal / (1 - (1 / minVal / 0.01));
			float pixelColor = (lifespanByVelocity > particle.life ? lifespanByVelocity : particle.life);
			glColor3f((pixelColor <= 1 ? pixelColor : 1), 0.0, 0.0);

			particle.x += subtractIfNotZero(&particle.vx, negativeOf(particle.vx) * 0.01);
			particle.y += (particle.vy += 0.05);
			particle.z += subtractIfNotZero(&particle.vz, negativeOf(particle.vz) * 0.01);
			particle.life -= 0.01;
			if (inRange(particle.vx, -.4, .4) || inRange(particle.vz, -.4, .4) || particle.y > position.y)
				particle.life = 0;
			draw3DParticle(particle);
		}
	}
}

void DrawPixelGenerators::addGenerator(PixelGenerator pg) {
	generators.push_back(pg);
}

void DrawPixelGenerators::drawGenerators() {
	for (auto &particle : generators) {
		particle.drawParticles();
	}
}