#ifndef PixelGeneration
#define PixelGeneration

struct particle {
	float x; float y; float z;
	float vx; float vy; float vz;	//Vector for movement
	int rotate;
	float life;
};
//Used to keep track of the particle system
struct particleSystem {
	int x; int y; int z;
	int radius[3];
};
void createParticleSystem(int x, int y, int z, int xr, int yr, int zr);
float subtractIfNotZero(float* velocity, float value);
int positiveOrNegative();
int negativeOf(float value);
bool inRange(float x, float a, float b);
void draw3DParticle(particle particleAt);
void drawParticles();

#endif