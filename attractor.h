/** 
 * Generates `iters` number of points that the attractor
 * passes through and stores them in an array of `Point`s,
 * using the parameters specified.
 */
void generate(int iters, Point[iters], AttractorParams);

/** 
 * Makes a density matrix using the points generated with
 * `generate`.
 */
void makeHistogram(int n, Point[n], int w, int h, u_int8_t[h][w]);
