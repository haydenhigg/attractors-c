#include <stdlib.h>
#include <stdio.h>

#include "external.c"

#define ITERS 100000000
#define WIDTH 1200
#define HEIGHT 1200

static Point attractor[ITERS];
static int histogram[HEIGHT][WIDTH];
static u_int8_t colorMap[HEIGHT][WIDTH][3];

int main(int argc, char **argv) {
	// 2.01, 2.53, 1.61, -0.33
	// -2, -2, -1.2, 2
	// 0.56, -5.6, -1.9, 2
	
	AttractorParams params = newParams(2.01, 2.53, 1.61, -0.33);
	char *outfile = argc > 1 ? argv[1] : sprintf("%f_%f_%f_%f.ppm", params.a, params.b, params.c, params.d);

	generate(ITERS, attractor, params);
	makeHistogram(ITERS, attractor, WIDTH, HEIGHT, histogram);
	makeColorMap(WIDTH, HEIGHT, histogram, colorMap);

	return writeToPPMFile(WIDTH, HEIGHT, colorMap, outfile);
}
