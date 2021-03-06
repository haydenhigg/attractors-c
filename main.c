#include <stdlib.h>

#include "external.c"

#define ITERS	50000000
#define WIDTH	4000
#define HEIGHT	4000
#define OUTFILE	"out.ppm"

static Point attractor[ITERS];
static u_int8_t histogram[HEIGHT][WIDTH];
static u_int8_t colorMap[HEIGHT][WIDTH][3];

int main(void) {
	// 2.01, 2.53, 1.61, -0.33
	// -2, -2, -1.2, 2
	// 0.56, -5.6, -1.9, 2
	
	AttractorParams params = newParams(2.01, 2.53, 1.61, -0.33);

	generate(ITERS, attractor, params);
	makeHistogram(ITERS, attractor, WIDTH, HEIGHT, histogram);
	makeColorMap(WIDTH, HEIGHT, histogram, colorMap);

	return writeToPPMFile(WIDTH, HEIGHT, colorMap, OUTFILE);
}
