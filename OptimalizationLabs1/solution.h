//Do not edit this file (unless you know what you are doing)

#ifndef SOLUTION_H
#define SOLUTION_H

#include"matrix.h"
#include"ode_solver.h"

class solution
{
	friend ostream &operator<<(ostream &, const solution &);
public:
	matrix x;
	matrix g;
	matrix H;
	matrix y;
	static int f_calls;
	static int g_calls;
	static int H_calls;
	static void clear_calls();
    solution(double = 0.0);
	solution(const matrix &);
	solution(double *, int);
	void fit_fun(matrix = 0.0);
	void grad(matrix = 0.0);
	void hess(matrix = 0.0);
	static double a;
};

#endif
