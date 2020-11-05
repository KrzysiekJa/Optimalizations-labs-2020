//Do not edit the code below (unless you know what you are doing)

#include <math.h>
#include "solution.h"
#include<fstream>

#define M_PI 3.14159265358979323846

int solution::f_calls = 0;
int solution::g_calls = 0;
int solution::H_calls = 0;

solution::solution(double L)
{
	x = matrix(L);
	//g = nullptr;
	//H = nullptr;
	//y = nullptr;
}

solution::solution(const matrix &A)
{
	x = A;
	//g = nullptr;
	//H = nullptr;
	//y = nullptr;
}

solution::solution(double *A, int n)
{
	x = matrix(A, n);
	//g = nullptr;
	//H = nullptr;
	//y = nullptr;
}

void solution::clear_calls()
{
	f_calls = 0;
	g_calls = 0;
	H_calls = 0;
}

ostream &operator<<(ostream &S, const solution &A)
{
	S << "x = " << A.x << endl;
	S << "y = " << A.y << endl;
	S << "f_calls = " << solution::f_calls << endl;
	S << "g_calls = " << solution::g_calls << endl;
	S << "H_calls = " << solution::H_calls << endl;
	return S;
}

//You can edit the following code

void solution::fit_fun(matrix O)
{
#if LAB_NO == 2
	#if LAB_PART == 1
    y = -cos(0.1* x(0,0)) * exp(-pow(0.1* x(0, 0) - 2*M_PI, 2))  +  0.002 * pow(0.1* x(0, 0),2);

	#endif

	#if LAB_PART == 2
	matrix Y0(new double[3]{ 5,1,10 }, 3); //dVa, dVb, dTb
	matrix* Y = solve_ode(0, 1, 1000, Y0, x); //x=DA

	//szukamy max z Y[1][3]
	ofstream S("..//lag_sym.csv");
	double max=0;
	for (int i = 0; i < 1000; i++) {
		S<< Y[1](i, 0) << ", " << Y[1](i, 1) << ", " << Y[1](i, 2) << endl;
		if (max < Y[1](i, 2)) {
			max = Y[1](i, 2);
		}
	}
	S.close();
	y = abs(50-max);
  
	#endif
#endif
	++f_calls;
}

void solution::grad(matrix O)
{
	//g = NAN;
	++g_calls;
}

void solution::hess(matrix O)
{
	//H = NAN;
	++H_calls;
}
