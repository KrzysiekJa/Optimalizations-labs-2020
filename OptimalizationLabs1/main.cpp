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

    #endif // LAB_NO == 1

	}
	catch (char * EX_INFO)
	{
		cout << EX_INFO << endl;
	}
	//system("pause");
	return 0;
}
