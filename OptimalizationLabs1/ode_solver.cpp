//Do not edit the code below (unless you know what you are doing)

#include "ode_solver.h"
#include <math.h>

matrix *solve_ode(double t0, double dt, double tend, const matrix &Y0, matrix P)
{
	int N = static_cast<int>(floor((tend - t0) / dt) + 1);
	if (N < 2)
		throw "The time interval is defined incorrectly";
	int *s = get_size(Y0);
	if (s[1] != 1)
		throw "Initial condition must be a vector";
	int n = s[0];
	delete[]s;
	matrix *S = new matrix[2]{ matrix(N), matrix(n,N) };
	S[0](0) = t0;
	for (int i = 0; i < n; ++i)
		S[1](i, 0) = Y0(i);
	matrix k1(n), k2(n), k3(n), k4(n);
	for (int i = 1; i < N; ++i)
	{
		S[0](i) = S[0](i - 1) + dt;
		k1 = dt*diff(S[0](i - 1), S[1][i - 1], P);
		k2 = dt*diff(S[0](i - 1) + 0.5*dt, S[1][i - 1] + 0.5*k1, P);
		k3 = dt*diff(S[0](i - 1) + 0.5*dt, S[1][i - 1] + 0.5*k2, P);
		k4 = dt*diff(S[0](i - 1) + dt, S[1][i - 1] + k3, P);
		for (int j = 0; j < n; ++j)
			S[1](j, i) = S[1](j, i - 1) + (k1(j) + 2 * k2(j) + 2 * k3(j) + k4(j)) / 6;
	}
	S[1] = trans(S[1]);
	return S;
}

//You can edit the following code

matrix diff(double t, const matrix &Y, matrix P)
{
#if LAB_NO == 1

	double m = 5, b = 1.5, k = 1, F = 0;

	matrix dY(Y);
	dY(0) = Y(1);
	dY(1) = (F - b*Y(1) - k*Y(0)) / m;

	return dY;
#else
	matrix dY;
	return dY;
#endif
}
