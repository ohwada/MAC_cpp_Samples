/**
 * gnuplot sample
 * 2020-03-01 K.OHWADA
 */

// plot sin wave with CGnuplot
// reference : http://tips.hecomi.com/entry/20101209/1291888423

#include <vector>
#include <algorithm>
#include <cmath>
#include "gnuplot.h"

using namespace std;
using namespace gnuplot;

/**
 *  main
 */
int main(int argc, char **argv)
{

	vector<double> 	vec_x, vec_y;
	for (int i = 0; i < 628; i++){
		double x = i * 0.01;
		vec_x.push_back(x);
		double y = sin(x);
		vec_y.push_back(y);
	}

	CGnuplot gp;
	gp.SetTitle("CGnuplot: sin");
	gp.SetLabel("x", "sin(x)");
	gp.Plot(vec_x, vec_y);
	gp.DumpToPng("sin");

	__KEYWAIT__;

	return EXIT_SUCCESS;
}
