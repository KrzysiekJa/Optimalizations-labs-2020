//Do not edit the code below (unless you know what you are doing)

#include"solution.h"

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
	//y = NAN;
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
