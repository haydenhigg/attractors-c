typedef struct {
	double a, b, c, d;
} AttractorParams;

typedef struct {
   double x, y;
} Point;

typedef struct {
	uint8_t r, g, b;
} Color;

AttractorParams newParams(double, double, double, double);