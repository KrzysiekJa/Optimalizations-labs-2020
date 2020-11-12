#include "opt_alg.h"
#include<fstream>

#if LAB_NO>1
double *expansion(double x0, double d, double alfa, int Nmax, matrix O)
{
	double* p = new double[2];
	solution X0(x0), X1(x0 + d);
	X0.fit_fun();
	X1.fit_fun();

    
	if (X0.y == X1.y)
	{
		p[0] = x0;
		p[1] = x0 + d;
		return p;
	}
    
	if (X1.y > X0.y)
	{
		d *= -1;
		X1.x = x0 + d;
		X1.fit_fun();

		if (X1.y >= X0.y)
		{
			p[0] = x0 + d;
			p[1] = x0 - d;
			return p;
		}
	}
    
    solution X2;
	int i = 1;
	while (true)
	{
		X2.x = d * pow(alfa, i) + x0;
		X2.fit_fun();

        if (X2.y >= X1.y || solution::f_calls > Nmax)
			break;

		X0 = X1;
		X1 = X2;
		++i;
	}
    
    
    if(d > 0){
        p[0] = X0.x(0, 0);
        p[1] = X2.x(0, 0);
    }
    else{
        p[0] = X2.x(0, 0);
        p[1] = X0.x(0, 0);
    }

	return p;
}

solution fib(double a, double b, double epsilon, matrix O)
{
	ofstream plik("..//fib(-100,100).csv");
	int n = 100;
	double s =( b - a) / epsilon;
	int k_i;
	int *F = new int[n] {1, 1};
	for (int i = 2; i < n; ++i) {
		F[i] = F[i - 2] + F[i - 1];
		if (F[i] > s) {
			k_i = i;
			break;
		}
	}

	solution A(a ), B(b ), C(0.), D(0.);
	C.x = matrix(b-((double)F[k_i-1]/F[k_i])*(b-a));
	D.x = matrix(a+b)-C.x ;
	C.fit_fun();
	D.fit_fun();
	for (int i = 0; i <= k_i+1 - 3; ++i)
	{
		if (C.y < D.y) {
			B.x = D.x;
		}
		else {
			A.x = C.x;
		}
		C.x = B.x - ((double)F[k_i-i-2]/F[k_i-i-1])*(B.x-A.x) ;
		D.x = A.x+B.x-C.x ;
		C.fit_fun();
		D.fit_fun();
		plik << B.x - A.x<<endl;
	}
	plik.close();
	return C;
}

solution lag(double a, double b, double epsilon, double gamma, int Nmax, matrix O)
{
	solution A(a), B(b), C(0.), D(0.), dD(0.);

	ofstream plik("..//lag(-100,100).csv");
	plik << B.x - A.x << endl;

	C.x = (a + b) / 2;
	A.fit_fun();
	B.fit_fun();
	C.fit_fun();
	double l, m;
	while (true)
	{
		l = A.y(0) * (pow(B.x(0), 2) - pow(C.x(0), 2)) + B.y(0) * (pow(C.x(0), 2) - pow(A.x(0), 2)) + C.y(0) * (pow(A.x(0), 2) - pow(B.x(0), 2));
		m = A.y(0) * (B.x(0) - C.x(0)) + B.y(0) * (C.x(0) - A.x(0)) + C.y(0) * (A.x(0) - B.x(0));
		if (m <= 0)
		{
			C.x = NAN;
			C.y = NAN;
			return C;
		}
		D.x = (l / m) / 2;
		D.fit_fun();

		plik << D.x-A.x << endl;
		if (A.x < D.x && D.x < C.x)
		{
			if (D.y < C.y)
			{
				B = C;
				C = D;
			}
			else
				A = D;
		}
		else if (C.x < D.x && D.x < B.x)
		{
			if (D.y < C.y)
			{
				A = C;
				C = D;
			}
			else
				B = D;
		}
		else
		{
			C.x = NAN;
			C.y = NAN;
			return C;
		}
		
		if ((B.x - A.x < epsilon) || (abs(D.x(0, 0) - dD.x(0, 0)) <= gamma)) {
			plik.close();
			return C;
		}
		
		dD.x = D.x;
	}
}
#endif
#if LAB_NO>2
solution HJ(matrix x0, double s, double alfa, double epsilon, int Nmax, matrix O)
{
	solution XB, XB_old, X;
	XB.x = x0;
	XB.fit_fun();
	while (true)
	{
		X = HJ_trial(XB, s);
		if (X.y < XB.y)
		{
			while (true)
			{
				XB_old = XB;
				XB = X;
				X.x = 2 * XB.x - XB_old.x;
				X.fit_fun();
				X = HJ_trial(X, s);
				if (X.y >= XB.y)
					break;
				if (solution::f_calls > Nmax)
					return XB;
			}
		}
		else
			s *= alfa;
		if (s < epsilon || solution::f_calls > Nmax)
			return XB;
	}
}

solution HJ_trial(solution XB, double s, matrix O)
{
	int *n = get_size(XB.x);
	matrix D = ident_mat(n[0]);
	solution X;
	for (int i = 0; i < n[0]; ++i)
	{
		X.x = ? ;
		X.fit_fun();
		if (? )
			XB = ? ;
		else
		{
			X.x = ? ;
			X.fit_fun();
			if (? )
				XB = ? ;
		}
	}
	return XB;
}

solution Rosen(matrix x0, matrix s0, double alfa, double beta, double epsilon, int Nmax, matrix O)
{
	int* n = get_size(x0);
	matrix l(n[0], 1), p(n[0], 1), s(s0), D = ident_mat(n[0]);
	solution X, Xt;
	X.x = x0;
	X.fit_fun();
	while (true)
	{
		for (int i = 0; i < n[0]; ++i)
		{
			Xt.x = X.x + s(i) * D; 
			Xt.fit_fun();
			if (Xt.y < X.y)
			{
				X = Xt;
				l(i) += s(i);
				s(i) *= alfa;
			}
			else
			{
				p(i) += 1 ;
				s(i) *= -beta ;
			}
		}
		bool change = true;
		for (int i = 0; i < n[0]; ++i)
			if (p == 0 || l == 0)
			{
				change = false;
				break;
			}
		if (change)
		{
			matrix Q(n[0], n[0]), v(n[0], 1);
			for (int i = 0; i < n[0]; ++i)
				for (int j = 0; j <= i; ++j)
					Q(i, j) = l(i);
			Q = ? ;
			v = ? ;
			D = set_col(D, v, 0);
			for (int i = 1; i < n[0]; ++i)
			{
				matrix temp(n[0], 1);
				for (int j = 0; j < i; ++j)
					temp = ? ;
				v = ? ;
				D = set_col(D, v, i);
			}
			s = s0;
			l = 0;
			p = 0 ;
		}
		double max_s = abs(s(0));
		for (int i = 1; i < n[0]; ++i)
			if (max_s < abs(s(i)))
				max_s = abs(s(i));
		if (solution::f_calls > Nmax)
			return X;
	}
}
#endif
#if LAB_NO>3
solution pen(matrix x0, double c0, double dc, double epsilon, int Nmax, matrix O)
{
	double alfa = 1, beta = 0.5, gama = 2, delta = 0.5, s = 0.5;
	matrix A(new double[2]{ c0,O(0) }, 2);
	solution X, X1;
	X.x = ? ;
	while (true)
	{
		X1 = sym_NM(X.x, s, alfa, beta, gama, delta, epsilon, Nmax, A);
		if (? )
			return X1;
		A(0) *= ? ;
		X = ? ;
	}
}

solution sym_NM(matrix x0, double s, double alfa, double beta, double gama, double delta, double epsilon, int Nmax, matrix O)
{
	int *n = get_size(x0);
	matrix D = ident_mat(n[0]);
	int N = n[0] + 1;
	solution *S = new solution[N];
	S[0].x = ? ;
	S[0].fit_fun(O);
	for (int i = 1; i < N; ++i)
	{
		S[i].x = ? ;
		S[i].fit_fun(O);
	}
	solution p_o, p_e, p_z;
	matrix p_sr;
	int i_min, i_max;
	while (true)
	{
		i_min = i_max = 0;
		for (int i = 1; i < N; ++i)
		{
			if (? )
				i_min = i;
			if (? )
				i_max = i;
		}
		p_sr = matrix(n[0], 1);
		for (int i = 0; i < N; ++i)
			if (i != i_max)
				p_sr = ? ;
		p_sr = ? ;
		p_o.x = ? ;
		p_o.fit_fun(O);
		if (? )
			S[i_max] = ? ;
		else if (? )
		{
			p_e.x = ? ;
			p_e.fit_fun(O);
			if (? )
				S[i_max] = ? ;
			else
				S[i_max] = ? ;
		}
		else
		{
			p_z.x = ? ;
			p_z.fit_fun(O);
			if (? )
				S[i_max] = ? ;
			else
			{
				for (int i = 0; i < N; ++i)
					if (i != i_min)
					{
						S[i].x = ? ;
						S[i].fit_fun(O);
					}
			}
		}
		double max_s = norm(S[0].x - S[i_min].x);
		for (int i = 1; i < N; ++i)
			if (max_s < norm(S[i].x - S[i_min].x))
				max_s = norm(S[i].x - S[i_min].x);
		if (? )
			return S[i_min];
	}
}
#endif
#if LAB_NO>4
solution SD(matrix x0, double h0, double epsilon, int Nmax, matrix O)
{
	int *n = get_size(x0);
	solution X, X1;
	X.x = x0;
	matrix d(n[0], 1), P(n[0], 2), limits = O;
	solution h;
	double b;
	while (true)
	{
		X.grad();
		d = ? ;
		P = set_col(P, X.x, 0);
		P = set_col(P, d, 1);
		if (h0 < 0)
		{
			b = compute_b(? , ? , limits);
			h = golden(? , ? , epsilon, Nmax, P);
			X1.x = ? ;
		}
		else
			X1.x = ? ;
		if (? ||
			? ||
			? );
		{
			X1.fit_fun();
			return X1;
		}
		X = ? ;
	}
}

solution CG(matrix x0, double h0, double epsilon, int Nmax, matrix O)
{
	int *n = get_size(x0);
	solution X, X1;
	X.x = x0;
	matrix d(n[0], 1), P(n[0], 2), limits = O;
	solution h;
	double b, beta;
	X.grad();
	d = ? ;
	while (true)
	{
		P = set_col(P, X.x, 0);
		P = set_col(P, d, 1);
		if (h0 < 0)
		{
			b = compute_b(? , ? , limits);
			h = golden(? , ? , epsilon, Nmax, P);
			X1.x = ? ;
		}
		else
			X1.x = ? ;
		if (? ||
			? ||
			? )
		{
			X1.fit_fun();
			return X1;
		}
		X1.grad();
		beta = ? ;
		d = ? ;
		X = ? ;
	}
}

solution Newton(matrix x0, double h0, double epsilon, int Nmax, matrix O)
{
	int *n = get_size(x0);
	solution X, X1;
	X.x = x0;
	matrix d(n[0], 1), P(n[0], 2), limits = O;
	solution h;
	double b;
	while (true)
	{
		X.grad();
		X.hess();
		d = ? ;
		P = set_col(P, X.x, 0);
		P = set_col(P, d, 1);
		if (h0 < 0)
		{
			b = compute_b(? , ? , limits);
			h = golden(? , ? , epsilon, Nmax, P);
			X1.x = ? ;
		}
		else
			X1.x = ? ;
		if (? ||
			? ||
			? ||
			? )
		{
			X1.fit_fun();
			return X1;
		}
		X = ? ;
	}
}

solution golden(double a, double b, double epsilon, int Nmax, matrix O)
{
	double alfa = ? ;
	solution A, B, C, D;
	A.x = ? ;
	B.x = ? ;
	C.x = ? ;
	C.fit_fun(O);
	D.x = ? ;
	D.fit_fun(O);
	while (true)
	{
		if (? )
		{
			B = ? ;
			D = ? ;
			C.x = ? ;
			C.fit_fun(O);
		}
		else
		{
			A = ? ;
			C = ? ;
			D.x = ? ;
			D.fit_fun(O);
		}
		if (? )
		{
			A.x = (A.x + B.x) / 2.0;
			A.fit_fun(O);
			return A;
		}
	}
}

double compute_b(matrix x, matrix d, matrix limits)
{
	int *n = get_size(x);
	double b = 1e9, bi;
	for (int i = 0; i < n[0]; ++i)
	{
		if (d(i) == 0)
			bi = ? ;
		else if (d(i) > 0)
			bi = ? ;
		else
			bi = ? ;
			if (? )
				b = bi;
	}
	return b;
}
#endif
#if LAB_NO>5
solution Powell(matrix x0, double epsilon, int Nmax, matrix O)
{
	int *n = get_size(x0);
	matrix D = ident_mat(n[0]), A(n[0], 3), limits(n[0], 2);
	limits = set_col(limits, O[0], 0);
	limits = set_col(limits, O[1], 1);
	A(0, 2) = O(0, 2);
	solution X, P, h;
	X.x = x0;
	double *ab;
	while (true)
	{
		P = ?;
		for (int i = 0; i < ? ; ++i)
		{
			A = set_col(A, P.x, 0);
			A = set_col(A, D[i], 1);
			ab = compute_ab(? , ? , limits);
			h = golden(? , ? , epsilon, Nmax, A);
			P.x = ? ;
		}
		if (? )
		{
			P.fit_fun();
			return P;
		}
		for (int i = 0; i < n[0] - 1; ++i)
			D = ? ;
		D = ? ;
		A = set_col(A, P.x, 0);
		A = set_col(A, D[n[0] - 1], 1);
		ab = compute_ab(? , ? , limits);
		h = golden(? , ? , epsilon, Nmax, A);
		X.x = ? ;
	}
}

double *compute_ab(matrix x, matrix d, matrix limits)
{
	int *n = get_size(x);
	double *ab = new double[2]{ -1e9,1e9 };
	double ai, bi;
	for (int i = 0; i < n[0]; ++i)
	{
		if (d(i) == 0)
		{
			ai = ? ;
			bi = ? ;
		}
		else if (d(i) > 0)
		{
			ai = ? ;
			bi = ? ;
		}
		else
		{
			ai = ? ;
			bi = ? ;
		}
		if (? )
			ab[0] = ai;
		if (? )
			ab[1] = bi;
	}
	return ab;
}
#endif
#if LAB_NO>6
solution EA(int N, matrix limits, double epsilon, int Nmax, matrix O)
{
	int mi = 20, lambda = 40;
	solution *P = new solution[mi + lambda];
	solution *Pm = new solution[mi];
	random_device rd;
	default_random_engine gen;
	gen.seed(static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count()));
	normal_distribution<double> distr(0.0, 1.0);
	matrix IFF(mi, 1), temp(N, 2);
	double r, s, s_IFF;
	double tau = ? , tau1 = ? ;
	int j_min;
	for (int i = 0; i < ? ; ++i)
	{
		P[i].x = matrix(N, 2);
		for (int j = 0; j < N; ++j)
		{
			P[i].x(j, 0) = ? ;
			P[i].x(j, 1) = ? ;
		}
		P[i].fit_fun();
		if (P[i].y < epsilon)
			return P[i];
	}
	while (true)
	{
		s_IFF = 0;
		for (int i = 0; i < ? ; ++i)
		{
			IFF(i) = 1 / P[i].y(0);
			s_IFF += IFF(i);
		}
		for (int i = 0; i < ? ; ++i)
		{
			r = ? ;
			s = 0;
			for (int j = 0; j < ? ; ++j)
			{
				s += ? ;
				if (? )
				{
					P[mi + i] = ? ;
					break;
				}
			}
		}
		for (int i = 0; i < ? ; ++i)
		{
			r = distr(gen);
			for (int j = 0; j < N; ++j)
			{
				P[mi + i].x(j, 1) *= ? ;
				P[mi + i].x(j, 0) += ? ;
			}
		}
		for (int i = 0; i < ? ; i += 2)
		{
			r = ? ;
			temp = P[mi + i].x;
			P[mi + i].x = ? ;
			P[mi + i + 1].x = ? ;
		}
		for (int i = 0; i < ? ; ++i)
		{
			P[mi + i].fit_fun();
			if (P[mi + i].y < epsilon)
				return P[mi + i];
		}
		for (int i = 0; i < ? ; ++i)
		{
			j_min = 0;
			for (int j = 1; j < ? ; ++j)
				if (P[j_min].y>P[j].y)
					j_min = j;
			Pm[i] = P[j_min];
			P[j_min].y = 1e10;
		}
		for (int i = 0; i < ? ; ++i)
			P[i] = Pm[i];
		if (? )
			return P[0];
	}
}
#endif
