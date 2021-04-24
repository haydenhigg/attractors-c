#include <stdlib.h>

#include "external.c"

const int ITERS = 100000000;
const int WIDTH = 1200;
const int HEIGHT = 1200;

static Point attractor[ITERS];
static int histogram[HEIGHT][WIDTH];
static uint8_t colorMap[HEIGHT][WIDTH][3];

int main(int argc, char **argv) {
	// 2.01, 2.53, 1.61, -0.33
	// -2, -2, -1.2, 2
	// 0.56, -5.6, -1.9, 2

	generate(ITERS, attractor, newParams(2.01, 2.53, 1.61, -0.33));
	makeHistogram(ITERS, attractor, WIDTH, HEIGHT, histogram);
	makeColorMap(WIDTH, HEIGHT, histogram, colorMap);

	return writeToPPMFile(WIDTH, HEIGHT, colorMap, argc > 1 ? argv[1] : "out.ppm");
}