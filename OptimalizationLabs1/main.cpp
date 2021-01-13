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
		cout << g.y << endl << endl;

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
		double c0 = 10.;
		double epsilon = 1e-5;
		int Nmax = 1e5;
		double a;

		random_device r;
		double temp_x1[100];
		double temp_x2[100];

		/*a = 4.;
		ofstream x4("..//x4.csv");
		for (int i = 0; i < 100; i++) {
			temp_x1[i] = (sqrt(a * a / 2) - 1) * r() / r.max() + 1;
			temp_x2[i] = (sqrt(a * a / 2) - 1) * r() / r.max() + 1;
			x4 << temp_x1[i] << " " << temp_x2[i] << endl;
		}
		x4.close();

		a = 4.4934;
		ofstream x449("..//x49.csv");
		for (int i = 0; i < 100; i++) {
			temp_x1[i] = (sqrt(a * a / 2) - 1) * r() / r.max() + 1;
			temp_x2[i] = (sqrt(a * a / 2) - 1) * r() / r.max() + 1;
			x449 << temp_x1[i] << " " << temp_x2[i] << endl;
		}
		x449.close();

		a = 5.;
		ofstream x5("..//x5.csv");
		for (int i = 0; i < 100; i++) {
			temp_x1[i] = (sqrt(a * a / 2) - 1) * r() / r.max() + 1;
			temp_x2[i] = (sqrt(a * a / 2) - 1) * r() / r.max() + 1;
			x5 << temp_x1[i] << " " << temp_x2[i] << endl;
		}
		x5.close();*/

#if LAB_PART ==1
		// double alfa = 1, beta = 0.5, gama = 2, delta = 0.5, s = 0.5;
		double dc = 1.5;

		fstream x4in;
		x4in.open("..//x4.csv", ios::in);
		if (x4in.good() == true)
		{
			for (int i = 0; i < 100; i++)
			{
				x4in >> temp_x1[i];
				x4in >> temp_x2[i];
			}
			x4in.close();
		}
		else {
			cout << "file error";
			system("pause");
		}

		a = 4.;
		ofstream pen_zew4("..//pen_zew4.csv");
		for (int i = 0; i < 100; i++) {
			solution::clear_calls();
			matrix O(a);
			matrix x0(new double[2]{ temp_x1[i], temp_x2[i] }, 2);
			solution X1 = pen(x0, c0, dc, epsilon, Nmax, O);
			pen_zew4 << temp_x1[i] << ";" << temp_x2[i] << ";" << X1.x(0) << ";" << X1.x(1) << ";" << X1.y << solution::f_calls << endl;
		}
		pen_zew4.close();

		/////

		fstream x49in;
		x49in.open("..//x49.csv", ios::in);
		if (x49in.good() == true)
		{
			for (int i = 0; i < 100; i++)
			{
				x49in >> temp_x1[i];
				x49in >> temp_x2[i];
			}
			x49in.close();
		}
		else {
			cout << "file error";
			system("pause");
		}

		a = 4.4934;
		ofstream pen_zew49("..//pen_zew49.csv");
		for (int i = 0; i < 100; i++) {
			solution::clear_calls();
			matrix O(a);
			matrix x0(new double[2]{ temp_x1[i], temp_x2[i] }, 2);
			solution X1 = pen(x0, c0, dc, epsilon, Nmax, O);
			pen_zew49 << temp_x1[i] << ";" << temp_x2[i] << ";" << X1.x(0) << ";" << X1.x(1) << ";" << X1.y << solution::f_calls << endl;
		}
		pen_zew49.close();

		/////////

		fstream x5in;
		x5in.open("..//x5.csv", ios::in);
		if (x5in.good() == true)
		{
			for (int i = 0; i < 100; i++)
			{
				x5in >> temp_x1[i];
				x5in >> temp_x2[i];
			}
			x5in.close();
		}
		else {
			cout << "file error";
			system("pause");
		}

		a = 5.;
		ofstream pen_zew5("..//pen_zew5.csv");
		for (int i = 0; i < 100; i++) {
			solution::clear_calls();
			matrix O(a);
			matrix x0(new double[2]{ temp_x1[i], temp_x2[i] }, 2);
			solution X1 = pen(x0, c0, dc, epsilon, Nmax, O);
			pen_zew5 << temp_x1[i] << ";" << temp_x2[i] << ";" << X1.x(0) << ";" << X1.x(1) << ";" << X1.y << solution::f_calls << endl;
		}
		pen_zew5.close();

#endif
#if LAB_PART ==2
		double dc = 0.5;

		fstream x4in;
		x4in.open("..//x4.csv", ios::in);
		if (x4in.good() == true)
		{
			for (int i = 0; i < 100; i++)
			{
				x4in >> temp_x1[i];
				x4in >> temp_x2[i];
			}
			x4in.close();
		}
		else {
			cout << "file error";
			system("pause");
		}

		a = 4.;
		ofstream pen_wew4("..//pen_wew4.csv");
		for (int i = 0; i < 100; i++) {
			solution::clear_calls();
			matrix O(a);
			matrix x0(new double[2]{ temp_x1[i], temp_x2[i] }, 2);
			solution X1 = pen(x0, c0, dc, epsilon, Nmax, O);
			pen_wew4 << temp_x1[i] << ";" << temp_x2[i] << ";" << X1.x(0) << ";" << X1.x(1) << ";" << X1.y << solution::f_calls << endl;
		}
		pen_wew4.close();

		/////

		fstream x49in;
		x49in.open("..//x49.csv", ios::in);
		if (x49in.good() == true)
		{
			for (int i = 0; i < 100; i++)
			{
				x49in >> temp_x1[i];
				x49in >> temp_x2[i];
			}
			x49in.close();
		}
		else {
			cout << "file error";
			system("pause");
		}

		a = 4.4934;
		ofstream pen_wew49("..//pen_wew49.csv");
		for (int i = 0; i < 100; i++) {
			solution::clear_calls();
			matrix O(a);
			matrix x0(new double[2]{ temp_x1[i], temp_x2[i] }, 2);
			solution X1 = pen(x0, c0, dc, epsilon, Nmax, O);
			pen_wew49 << temp_x1[i] << ";" << temp_x2[i] << ";" << X1.x(0) << ";" << X1.x(1) << ";" << X1.y << solution::f_calls << endl;
		}
		pen_wew49.close();

		/////////

		fstream x5in;
		x5in.open("..//x5.csv", ios::in);
		if (x5in.good() == true)
		{
			for (int i = 0; i < 100; i++)
			{
				x5in >> temp_x1[i];
				x5in >> temp_x2[i];
			}
			x5in.close();
		}
		else {
			cout << "file error";
			system("pause");
		}

		a = 5.;
		ofstream pen_wew5("..//pen_wew5.csv");
		for (int i = 0; i < 100; i++) {
			solution::clear_calls();
			matrix O(a);
			matrix x0(new double[2]{ temp_x1[i], temp_x2[i] }, 2);
			solution X1 = pen(x0, c0, dc, epsilon, Nmax, O);
			pen_wew5 << temp_x1[i] << ";" << temp_x2[i] << ";" << X1.x(0) << ";" << X1.x(1) << ";" << X1.y << solution::f_calls << endl;
		}
		pen_wew5.close();

#endif
#if LAB_PART ==3

		double dc = 2., c = 1.0;

		solution::clear_calls();
		matrix O(new double[2]{ 1.,1. }, 2);
		matrix x0(new double[2]{ 2.0, 2.0 }, 2);
		solution simulation = pen(x0, c, dc, epsilon, Nmax, O);
		cout << simulation;
		matrix Y0(new double[] {0.0, 2.0, 100.0, 0.0}, 4);
		matrix* Y = solve_ode(0.0, 0.01, 7.0, Y0, 2.0);
		ofstream file("..//simulation.csv");
		file << Y[1];
		file.close();

#endif
#endif

#if LAB_NO == 5
#if LAB_PART == 1

		random_device r;
		double x1, x2;
		double epsilon = 1e-5;
		int Nmax = 10000;
		matrix O(2, 2);
		O(0, 0) = -10;
		O(0, 1) = 10;
		O(1, 0) = -10;
		O(1, 1) = 10;

		double temp_x1[100];
		double temp_x2[100];

		/*ofstream x100("..//x100.csv");
		for (int i = 0; i < 100; i++) {
			temp_x1[i] = 20.0 * r() / r.max() - 10;
			temp_x2[i] = 20.0 * r() / r.max() - 10;
			x100 << temp_x1[i] <<" " << temp_x2[i] << endl;
		}
		x100.close();

		ofstream x100_csv("..//x100_csv.csv");
		for (int i = 0; i < 100; i++) {
			x100_csv << temp_x1[i] << ";" << temp_x2[i] << endl;
		}
		x100_csv.close();
		system("pause");*/

		/*
		fstream x100in;
		x100in.open("..//x100.csv", ios::in);
		if (x100in.good() == true)
		{
			for (int i = 0; i < 100; i++)
			{
				x100in >> temp_x1[i];
				x100in >> temp_x2[i];
			}
			x100in.close();
		}
		else {
			cout << "file error";
			system("pause");
		}

		//spadek
		ofstream sd("..//SD.csv");
		for (int i = 0; i < 100; i++) {
			solution sd1;
			double d;
			matrix x0(new double[2]{ temp_x1[i], temp_x2[i] }, 2);

			solution::clear_calls();
			d = 0.05;
			sd1 = SD(x0, d, epsilon, Nmax, O);
			sd << sd1.x(0) << ";" << sd1.x(1) << ";" << sd1.y << solution::f_calls <<";"<< solution::g_calls <<endl;

			solution::clear_calls();
			d = 0.12;
			sd1 = SD(x0, d, epsilon, Nmax, O);
			sd << sd1.x(0) << ";" << sd1.x(1) << ";" << sd1.y << solution::f_calls << ";" << solution::g_calls << endl;

			solution::clear_calls();
			d = -1.;
			sd1 = SD(x0, d, epsilon, Nmax, O);
			sd << sd1.x(0) << ";" << sd1.x(1) << ";" << sd1.y << solution::f_calls << ";" << solution::g_calls << endl;
		}
		sd.close();

		//gradienty
		ofstream cg("..//CG.csv");
		for (int i = 0; i < 100; i++) {
			solution cg1;
			double d;
			matrix x0(new double[2]{ temp_x1[i], temp_x2[i] }, 2);

			solution::clear_calls();
			d = 0.05;
			cg1 = CG(x0, d, epsilon, Nmax, O);
			cg << cg1.x(0) << ";" << cg1.x(1) << ";" << cg1.y << solution::f_calls << ";" << solution::g_calls << endl;

			solution::clear_calls();
			d = 0.12;
			cg1 = CG(x0, d, epsilon, Nmax, O);
			cg << cg1.x(0) << ";" << cg1.x(1) << ";" << cg1.y << solution::f_calls << ";" << solution::g_calls << endl;

			solution::clear_calls();
			d = -1.;
			cg1 = CG(x0, d, epsilon, Nmax, O);
			cg << cg1.x(0) << ";" << cg1.x(1) << ";" << cg1.y << solution::f_calls << ";" << solution::g_calls << endl;
		}
		cg.close();

		//newton
		ofstream nt("..//Newton.csv");
		for (int i = 0; i < 100; i++) {
			solution nt1;
			double d;
			matrix x0(new double[2]{ temp_x1[i], temp_x2[i] }, 2);

			solution::clear_calls();
			d = 0.05;
			nt1 = Newton(x0, d, epsilon, Nmax, O);
			nt << nt1.x(0) << ";" << nt1.x(1) << ";" << nt1.y << solution::f_calls << ";" << solution::g_calls << ";" << solution::H_calls << endl;

			solution::clear_calls();
			d = 0.12;
			nt1 = Newton(x0, d, epsilon, Nmax, O);
			nt << nt1.x(0) << ";" << nt1.x(1) << ";" << nt1.y << solution::f_calls << ";" << solution::g_calls << ";" << solution::H_calls << endl;

			solution::clear_calls();
			d = -1.;
			nt1 = Newton(x0, d, epsilon, Nmax, O);
			nt << nt1.x(0) << ";" << nt1.x(1) << ";" << nt1.y << solution::f_calls << ";" << solution::g_calls << ";" << solution::H_calls << endl;
		}
		nt.close();
		*/

		matrix x0(new double[2]{ 2.55987, 6.28687 }, 2);
		double d;
		solution sd1;
		solution cg1;
		solution newton;

		d = 0.05;
		solution::clear_calls();
		sd1 = SD(x0, d, epsilon, Nmax, O);

		d = 0.12;
		solution::clear_calls();
		sd1 = SD(x0, d, epsilon, Nmax, O);

		d = -1;
		solution::clear_calls();
		sd1 = SD(x0, d, epsilon, Nmax, O);

		d = 0.05;
		solution::clear_calls();
		cg1 = CG(x0, d, epsilon, Nmax, O);

		d = 0.12;
		solution::clear_calls();
		cg1 = CG(x0, d, epsilon, Nmax, O);

		d = -1;
		solution::clear_calls();
		cg1 = CG(x0, d, epsilon, Nmax, O);

		d = 0.05;
		solution::clear_calls();
		newton = Newton(x0, d, epsilon, Nmax, O);

		d = 0.12;
		solution::clear_calls();
		newton = Newton(x0, d, epsilon, Nmax, O);

		d = -1;
		solution::clear_calls();
		newton = Newton(x0, d, epsilon, Nmax, O);




#endif
#if LAB_PART == 2
		double epsilon = 1e-7;
		int Nmax = 10000;
		/*matrix O(2, 2);
		O(0, 0) = 25;
		O(0, 1) = 100;
		O(1, 0) = 25;
		O(1, 1) = 100;
		*/

		matrix x0(new double[3]{ 0., 0., 0. }, 3);

		solution::clear_calls();
		solution cg = CG(x0, 0.01, epsilon, Nmax);
		cout << cg << endl;

		solution::clear_calls();
		solution cg2 = CG(x0, 0.001, epsilon, Nmax);
		cout << cg2 << endl;

		solution::clear_calls();
		solution cg3 = CG(x0, 0.0001, epsilon, Nmax);
		cout << cg3 << endl;

#endif
#endif
#if LAB_NO == 6
		matrix x0(2, 1);
		double epsilon = 0.00001;
		int Nmax = 100000;
		matrix O(2, 3);
		O(0, 0) = -10.0;
		O(0, 1) = 10.0;
		O(1, 0) = -10.0;
		O(1, 1) = 10.0;
		O(0, 2) = 0.5;

		random_device R;
		/*int a[3] = { 1, 10, 100 };
		ofstream plik("Powell.csv");

		for (int i = 0; i < 100; i++) {
			x0(0) = 20.0 * R() / R.max() - 10.0;
			x0(1) = 20.0 * R() / R.max() - 10.0;
			plik << x0(0) << "," << x0(1) << ",";

			for (int j = 0; j < 3; j++) {*/
			//solution::a = a[j];
		solution p = Powell(x0, epsilon, Nmax, O);
		cout << p;
		/*plik << p.x(0) << "," << p.x(1) << "," << p.y(0)
			<< "," << p.y(1) << "," << solution::f_calls << ",";
		solution::clear_calls();
	}
	plik << endl;*/
	//O(0, 2) += 0.01;
	

#endif
	}
	catch (char* EX_INFO)
	{
		cout << EX_INFO << endl;
	}
	//system("pause");
	return 0;
}
