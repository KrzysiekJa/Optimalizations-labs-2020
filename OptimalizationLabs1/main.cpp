#include<iostream>
#include<random>
#include<chrono>
#include<fstream>
#include"opt_alg.h"
#include"ode_solver.h"

using namespace std;

int main()
{
	try
	{
		cout << "LAB NUMBER " << LAB_NO << endl;
		cout << "LAB PART " << LAB_PART << endl << endl;

#if LAB_NO == 1

		double t0 = 0.0, dt = 0.1, tend = 50;
		matrix Y0 = matrix(new double[2]{ 1, 0 }, 2);

		matrix* Y = solve_ode(t0, dt, tend, Y0);

		ofstream S("..//tout.csv");
		S << Y[0];
		S.close();

		S.open("..//yout.csv");
		S << Y[1];
		S.close();

#endif
#if LAB_NO == 2
		double x0 = -10., d = 2., epsilon, gamma, alfa;
		int Nmax = 100;;
		random_device r;

		epsilon = 0.00001;
		gamma = 0.0000001;
		alfa = 20;      //dowolna wartosc > 1
#if LAB_PART == 1

		ofstream E("..//expansion.csv");
		ofstream F("..//fibonacci.csv");
		ofstream L("..//lagrange.csv");

		double temp_0[100];
		double temp_1[100];

		for (int i = 0; i < 100; i++) {
			solution::clear_calls();
			x0 = 200.0 * r() / r.max() - 100;
			double* p = expansion(x0, d, alfa, Nmax);
			E << x0 << "," << p[0] << "," << p[1] << "," << solution::f_calls << endl;
			temp_0[i] = p[0];
			temp_1[i] = p[1];
		}
		E.close();

		for (int i = 0; i < 100; i++) {
			solution::clear_calls();
			solution x_fib = fib(temp_0[i], temp_1[i], epsilon);
			F << x_fib.x << x_fib.y << solution::f_calls << endl;
		}
		F.close();

		for (int i = 0; i < 100; i++) {
			solution::clear_calls();
			solution x_lag = lag(temp_0[i], temp_1[i], epsilon, gamma, Nmax);
			L << x_lag.x << x_lag.y << solution::f_calls << endl;
		}
		L.close();

		//pojedyncze obliczenie dla (-100,100)
		solution::clear_calls();
		solution x_fib = fib(-100, 100, epsilon);
		cout << x_fib << endl;

		solution::clear_calls();
		solution x_lag = lag(-100, 100, epsilon, gamma, Nmax);
		cout << x_lag << endl;

#endif
#if LAB_PART == 2
		/*
		cout << "Fibonacci" << endl;
		solution::clear_calls();
		solution x_fib = fib(0.001, 0.01, epsilon);

		cout << "Lagrange" << endl;
		solution::clear_calls();
		solution x_lag = lag(0.001, 0.01, epsilon,gamma,Nmax);

		cout << x_fib << endl;
		cout << x_lag << endl;
		 */

		 //solution x_fib = fib(0.00241337, 0.00241337, epsilon);
		solution x_lag = lag(0.00241337, 0.00241337, epsilon, gamma, Nmax);

#endif
#endif

#if LAB_NO ==3
#if LAB_PART ==1
		random_device r;
		double x1, x2, s, epsilon, alfa_HJ, alfa_Ros, Nmax, beta;
		alfa_HJ = 0.2;
		alfa_Ros = 2;
		epsilon = 0.001;
		beta = 0.0001;
		Nmax = 1000;
		s = 0.001; //s2 = 0.005, s3 = 0.01

		solution X1, X2;

		double temp_0[100];
		double temp_1[100];

		/*ofstream output_HJ("..//HJ.csv");
		for (int i = 0; i < 100; i++) {
			solution::clear_calls();
			x1 = 2. * r() / r.max() - 1;
			x2 = 2. * r() / r.max() - 1;
			temp_0[i] = x1;
			temp_1[i] = x2;

			matrix x0(new double[2]{ x1, x2 }, 2);
			X1 = HJ(x0, s, alfa_HJ, epsilon, Nmax);
			output_HJ <<x1<<";"<<x2<<";"<< X1.x(0) << ";" << X1.x(1) << ";" << X1.y << solution::f_calls << endl;
		}
		output_HJ.close();

		ofstream output_Ros("..//Ros.csv");
		for (int i = 0; i < 100; i++) {
			solution::clear_calls();

			matrix x0(new double[2]{ temp_0[i], temp_1[i] }, 2);
			matrix s0(new double[2]{ s,s }, 2);
			X2 = Rosen(x0, s0, alfa_Ros, beta, epsilon, Nmax);
			output_Ros << temp_0[i] << ";" << temp_1[i] << ";" << X2.x(0) << ";" << X2.x(1) << ";" << X2.y << solution::f_calls << endl;
		}
		output_Ros.close();*/

		//matrix x0(new double[2]{-0.187375, -0.369641}, 2);
		//X1 = HJ(x0, s, alfa_HJ, epsilon, Nmax);
		////cout << X1 << endl;

		//matrix s0(new double[2]{ s,s }, 2);
		//X2 = Rosen(x0, s0, alfa_Ros, beta, epsilon, Nmax);
		////cout << X2 << endl;
#endif
#if LAB_PART == 2
		random_device r;
		double x1, x2, s, epsilon, alfa_HJ, alfa_Ros, Nmax, beta;
		alfa_HJ = 0.2;
		alfa_Ros = 2;
		epsilon = 0.001;
		beta = 0.0001;
		Nmax = 1000;
		s = 0.1; //s2 = 0.005, s3 = 0.01

		matrix x0(new double[2]{ 1, 1 }, 2);
		solution g(x0);
		g.fit_fun();
		cout << g.y << endl<<endl;

		solution::clear_calls();
		solution solHJ = HJ(x0, s, alfa_HJ, epsilon, Nmax);
		cout << solHJ << endl;

		solution::clear_calls();
		matrix s0(new double[2]{ s,s }, 2);
		solution solRos = Rosen(x0, s0, alfa_Ros, beta, epsilon, Nmax);
		cout << solRos << endl;

#endif
#endif
#if LAB_NO ==4
		double c0 = 5.;
		double epsilon = 1e-5;
		int Nmax = 1e5;
		double a = 5;

		random_device r;
		double temp_x1[100];
		double temp_x2[100];
		for (int i = 0; i < 100; i++) {
			temp_x1[i] = (sqrt(a * a / 2) - 1) * r() / r.max() + 1;
			temp_x2[i] = (sqrt(a * a / 2) - 1) * r() / r.max() + 1;
		}

#if LAB_PART ==1
       // double alfa = 1, beta = 0.5, gama = 2, delta = 0.5, s = 0.5;
		double dc = 1.5;
	
		for (int i = 0; i < 100; i++) {
			solution::clear_calls();
			matrix O(a);
			matrix x0(new double[2]{ temp_x1[i], temp_x2[i] }, 2);
			solution X = pen(x0, c0, dc, epsilon, Nmax, O);
			cout << X << endl;
		}

  //      matrix O(a);
  //      matrix x0(new double[2]{ 3, 2 }, 2);
  //     // solution X = sym_NM(x0, s, alfa, beta, gama, delta, epsilon, Nmax, O);
		//solution X = pen(x0, c0, dc, epsilon, Nmax, O);
  //      cout << X << endl;
#endif
#if LAB_PART ==2
		double dc = 0.5;
       
		for (int i = 0; i < 100; i++) {
			solution::clear_calls();
			matrix O(a);
			matrix x0(new double[2]{ temp_x1[i], temp_x2[i] }, 2);
			solution X = pen(x0, c0, dc, epsilon, Nmax, O);
			cout << X << endl;
		}
        
       /* matrix O();
        matrix x0(new double[2]{ 3, 2 }, 2);
        solution X = pen(x0, c0, dc, epsilon, Nmax, O);
        cout << X << endl;*/
        
#endif
#if LAB_PART ==3
        
        
#endif
#endif
	}
	catch (char* EX_INFO)
	{
		cout << EX_INFO << endl;
	}
	//system("pause");
	return 0;
}
