#pragma once
#include <vector>



class FireBall {
public:
	float position[3];
	float velocity[3];
	float temperature;
};

class FireBox {
public:
	float position[3];
	float size[3];
	float pixelSize;
	FireBox(float posX, float posY, float posZ, float sizeX, float sizeY, float sizeZ, float pixelSize=1.0, float percentFullSet=1);
	void DrawFire();
private:
	std::vector<FireBall> fire;
	float percentFull;
	bool Collision(FireBall one, FireBall two);
	void InitFireBallPosition(float position[], float size[]);
	void setfireball(std::vector<FireBall>::iterator *it, float position[]);
	void ApplyForces(FireBall *fb);
	void RandomizeVelocity(FireBall* fb);
	bool FireballTemperature(FireBall* fb);
};

class FireBoxHandler {
public:
	std::vector<FireBox> FireBoxes;
	void addFireBox(FireBox fb);
	void DrawFireBox();
};