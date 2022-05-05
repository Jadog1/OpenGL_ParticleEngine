#ifndef PixelGeneration
#define PixelGeneration
#include <vector>

#define OBJ_SHAPE_CUBE 1
#define OBJ_SHAPE_WIRECUBE 2
#define OBJ_SHAPE_TRIANGLE 3
#define OBJ_SHAPE_SMOKE 4

struct coord3D {
	float x; float y; float z;
};
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

class PixelGenerator {
public:
	PixelGenerator(int position[], int radius[], int pixelCount, int shape=OBJ_SHAPE_CUBE);
	std::vector<particle> particles;
	coord3D position;
	coord3D radius;
	void drawParticles();
	void setPixelCount(int pixelCount);
private:
	void draw3DParticle(particle particleAt);
};

#endif