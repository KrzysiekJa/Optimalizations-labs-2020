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
		matrix Y0 = matrix(new double[2]{1, 0}, 2);

		matrix *Y = solve_ode(t0, dt, tend, Y0);

		ofstream S("..//tout.csv");
		S << Y[0];
		S.close();

		S.open("..//yout.csv");
		S << Y[1];
		S.close();
    
    #endif
    #if LAB_NO == 2
		double x0, d, epsilon,gamma, alfa;
		int Nmax;
		random_device r;
		
		d = 2;
		epsilon = 0.01;
		gamma = 0.0001;
		alfa = 2;      //dowolna wartosc >1
		Nmax = 1000;

		/*double* p = expansion(-10., 1.9, 2., 100);
		cout << p[0] << endl;
		cout << p[1] << endl;*/

		solution::clear_calls();
		solution x_fib = fib(-5., 2., epsilon);
		cout << x_fib << endl;

		solution::clear_calls();
		solution x_lag = lag(-5., 2., epsilon, gamma, Nmax);
		cout << x_lag << endl;

		/*ofstream E("..//expansion.csv");
		ofstream F("..//fibonacci.csv");
		ofstream L("..//lagrange.csv");

		for (int i = 0; i < 100; i++) {

			x0 = 200.0 * r() / r.max() - 100;
			double *p = expansion(x0, d, alfa, Nmax);
			E << x0 << "," << p[0] << "," << p[1] << "," << solution::f_calls << endl;

			solution::clear_calls();
			solution x_fib = fib(p[0], p[1], epsilon);
			F << x_fib.x << "," << x_fib.y << "," << solution::f_calls << endl;

			solution::clear_calls();
			solution x_lag = lag(p[0], p[1], epsilon, gamma, Nmax);
			L << x_lag.x << "," << x_lag.y << "," << solution::f_calls << endl;

			E.close();
			F.close();
			L.close();
		}*/

		////pojedyncze obliczenie dla (-100,100)
		//solution::clear_calls();
		//solution x_fib = fib(-100, 100, epsilon);
		//cout << x_fib << endl;

		//solution::clear_calls();
		//solution x_lag = lag(-100, 100, epsilon, gamma, Nmax);
		//cout << x_lag << endl;
	#endif
		#if LAB_PART == 2
		//fib i lagrange od 0.0001 do 0.01
    #endif

	}
	catch (char * EX_INFO)
	{
		cout << EX_INFO << endl;
	}
	//system("pause");
	return 0;
}
