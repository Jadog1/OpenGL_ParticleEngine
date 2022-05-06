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
struct particleObj {
	float x; float y; float z;
	float vx; float vy; float vz;	//Vector for movement
	int rotate;
	float life;
};
float subtractIfNotZero(float* velocity, float value);
int positiveOrNegative();
int negativeOf(float value);
bool inRange(float x, float a, float b);

class PixelGenerator {
public:
	PixelGenerator(int posX, int posY, int posZ, int radiusX, int radiusY, int radiusZ, int pixelCount, int newShape = OBJ_SHAPE_CUBE);
	PixelGenerator(int positionArray[], int radiusArray[], int pixelCount, int newShape=OBJ_SHAPE_CUBE);
	coord3D position;
	coord3D radius;
	void drawParticles();
	void setPixelCount(int pixelCount);
private:
	int shape;
	std::vector<particleObj> particles;
	void draw3DParticle(particleObj particleAt);
};

class DrawPixelGenerators {
public:
	std::vector<PixelGenerator> generators;
	void addGenerator(PixelGenerator pg);
	void drawGenerators();
};

#endif