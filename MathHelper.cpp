#include <stdlib.h>

float subtractIfNotZero(float* velocity, float value) {
	if (*velocity > 0)
		*velocity -= value;

	return *velocity;
}
int positiveOrNegative() {
	return ((rand() % 2) < 1 ? -1 : 1);
}
int moveToMiddle(float valueToCompare, float border1, float border2) {
	if (valueToCompare < (border2+border1)/2) return 1;
	else return -1;
}
int normalizedFlipped(float value) {
	if (value < 0) return 1;
	else return -1;
}
int negativeOf(float value) {
	return (value < 0 ? -1 : 1);
}
bool inRange(float x, float a, float b) {
	return (x >= a && x <= b);
}
void subtractToMinZero(float* value, float subtract) {
	if (*value > 0) {
		float placeholder = *value - subtract;
		*value = (placeholder > 0) ? placeholder : 0;
	}
	else {
		float placeholder = *value + subtract;
		*value = (placeholder < 0) ? placeholder : 0;
	}
}