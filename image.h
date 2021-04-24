/** 
 * A custom hue function that take a scalar from 0-1 and
 * returns a `Color` that contains fields `r`, `g`, and `b`.
 */
Color getHue(double);

/** 
 * Converts the raw density matrix made by `makeHistogram`
 * into a 3D array, comparable to the input density matrix
 * but with each raw count scaled and replaced by a color
 * array ([r, g, b]).
 */
void makeColorMap(int w, int h, int[h][w], u_int8_t[h][w][3]);

/** 
 * Writes the 3D array made by `makeColorMap` to a file in
 * PPM format.
 */
int writeToPPMFile(int w, int h, u_int8_t[h][w][3], const char*);
