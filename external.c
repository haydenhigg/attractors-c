#include <stdlib.h>
#include <stdio.h>

#include <stdint.h>
#include <limits.h>
#include <float.h>

#include <math.h>

#include "data.h"
#include "attractor.h"
#include "image.h"

/**** DATA ****/
AttractorParams newParams(double a, double b, double c, double d) {
	AttractorParams ret;

	ret.a = a;
	ret.b = b;
	ret.c = c;
	ret.d = d;

	return ret;
}

/**** ATTRACTOR ****/
void generate(int iters, Point attractor[iters], AttractorParams params) {
	attractor[0].x = 0;
	attractor[0].y = 0;

	Point p = attractor[0];
	
	for (int n = 1; n < iters; n++) {
		attractor[n].x = sin(params.a * p.y) - cos(params.b * p.x); // x_n+1 = sin(a * y_n) - cos(b * x_n)
		attractor[n].y = sin(params.c * p.x) - cos(params.d * p.y); // y_n+1 = sin(c * x_n) - cos(d * y_n)

		p = attractor[n];
	}
}

void makeHistogram(int n, Point attractor[n], int w, int h, u_int8_t histogram[h][w]) {
	//-- find top left and bottom right --//
	Point min = {.x = __DBL_MAX__, .y = __DBL_MAX__};
	Point max = {.x = __DBL_MIN__, .y = __DBL_MIN__};

	for (int i = 0; i < n; i++) {
		if (attractor[i].x < min.x)
			min.x = attractor[i].x;
		else if (attractor[i].x > max.x)
			max.x = attractor[i].x;

		if (attractor[i].y < min.y)
			min.y = attractor[i].y;
		else if (attractor[i].y > max.y)
			max.y = attractor[i].y;
	}

	//-- initialize all histogram counts to 0 --//
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			histogram[i][j] = 0;

	//-- so that the math is easier when scaling --//
	double widthScaling = w / (max.x - min.x);
	double heightScaling = h / (max.y - min.y);

	double offsetX = min.x * widthScaling;
	double offsetY = min.y * heightScaling;

	//-- re-adjusts all points in `attractor` to  --//
	//-- fill a box with width `w` and height `h` --//
	//-- and writes the values in that box to the --//
	//-- matrix `histogram`                       --//
	int x, y;

	for (int i = 0; i < n; i++) {
		x = attractor[i].x * widthScaling - offsetX;
		y = attractor[i].y * heightScaling - offsetY;

		histogram[y][x] = fmin(histogram[y][x] + 1, UINT8_MAX);
	}
}

/**** IMAGE ****/
Color getHue(double density) {
	Color ret;

	// 	vvvvvvv change this vvvvvvv //
	ret.r = fmax(255 - density * 4, 0);
	ret.g = fmax(255 - density * 8, 0);
	ret.b = fmax(255 - density * 20, 0);
	// 	^^^^^^^^^^^^^^^^^^^^^^^^^^^ //

	return ret;
}

void makeColorMap(int w, int h, u_int8_t histogram[h][w], u_int8_t colorMap[h][w][3]) {
	u_int8_t min = UINT8_MAX;
	u_int8_t max = 0;

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (histogram[i][j] < min && histogram[i][j] > 0)
				min = histogram[i][j];
			else if (histogram[i][j] > max)
				max = histogram[i][j];
		}
	}

	double scaling = 255. / (max - min);
	double offset = min * scaling;

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (histogram[i][j] == 0) { // blank
				colorMap[i][j][0] = 255;
				colorMap[i][j][1] = 255;
				colorMap[i][j][2] = 255;
			} else {                    // passed through at least once
				Color hue = getHue(histogram[i][j] * scaling - offset);

				colorMap[i][j][0] = hue.r;
				colorMap[i][j][1] = hue.g;
				colorMap[i][j][2] = hue.b;
			}
		}
	}
}

int writeToPPMFile(int w, int h, u_int8_t colorMap[h][w][3], const char *fileName) {
	FILE *file = fopen(fileName, "wb");
	if (!file) return 1;

	//-- write header to PPM file; P6 = 8-bit non-ASCII file --//
	fprintf(file, "P6 %d %d %d\n", w, h, 255);

	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			fwrite(colorMap[i][j], 1, 3, file);

	fclose(file);

	return 0;
}
