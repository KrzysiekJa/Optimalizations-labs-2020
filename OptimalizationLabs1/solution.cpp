//Do not edit the code below (unless you know what you are doing)

#include <math.h>
#include "solution.h"
#include <fstream>

#define M_PI 3.14159265358979323846



int solution::f_calls = 0;
int solution::g_calls = 0;
int solution::H_calls = 0;
double solution::a = 0;

solution::solution(double L)
{
	x = matrix(L);
  g = matrix(2, 1);
  H = matrix(2, 2);
	//y = nullptr;
}

solution::solution(const matrix& A)
{
	x = A;
  g = matrix(2, 1);
  H = matrix(2, 2);
	//y = nullptr;
}

solution::solution(double* A, int n)
{
	x = matrix(A, n);
  g = matrix(new double[2]{ 0.,0. }, 2);
  H = matrix(2, 2);
	//y = nullptr;
}

void solution::clear_calls()
{
	f_calls = 0;
	g_calls = 0;
	H_calls = 0;
}

ostream& operator<<(ostream& S, const solution& A)
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
    
        y = -cos(0.1 * x(0, 0)) * exp(-pow(0.1 * x(0, 0) - 2 * M_PI, 2)) + 0.002 * pow(0.1 * x(0, 0), 2);

    #endif

    #if LAB_PART == 2
        matrix Y0(new double[3]{ 5,1,10 }, 3); //dVa, dVb, dTb
        matrix* Y = solve_ode(0, 1, 1000, Y0, x); //x=DA

        //szukamy max z Y[1][3]
        ofstream S("..//lag_sym.csv");
        double max = 0;
        for (int i = 0; i < 1000; i++) {
            S << Y[1](i, 0) << ", " << Y[1](i, 1) << ", " << Y[1](i, 2) << endl;
            if (max < Y[1](i, 2)) {
                max = Y[1](i, 2);
            }
        }
        S.close();
        y = abs(50 - max);

    #endif
    ++f_calls;
#endif
#if LAB_NO == 3
    #if LAB_PART == 1
        //y = pow(x(0), 2) + pow(x(1), 2);
        y = pow(x(0), 2) + pow(x(1), 2) - cos(2.5 * x(0) * M_PI) - cos(2.5 * x(1) * M_PI) + 2;
    
    #endif
    #if LAB_PART == 2
    
        double a_ref = M_PI, o_ref = 0;
        matrix Y0(2,1);
        
        matrix * Y = solve_ode(0, 0.1, 100, Y0,x); //x
        int * n = get_size(Y[1]);
        y(0) = 0;
        

        for(int i = 0; i < n[0]; ++i){
            y(0) = y(0) + 10 * pow(a_ref - Y[1](i,0), 2) + pow(o_ref - Y[1](i,1), 2) + pow(x(0) * (a_ref - Y[1](i,0)) + x(1) * (o_ref - Y[1](i,1)), 2);
        }
        y(0) = y(0) * 0.1;
        
    #endif
    ++f_calls;
#endif
#if LAB_NO == 4
            //zewnetrzna f kary
    #if LAB_PART == 1

        y = sin(M_PI * sqrt(pow(x(0)/ M_PI, 2) + pow(x(1)/ M_PI, 2)))/ (M_PI * sqrt(pow(x(0)/ M_PI, 2) + pow(x(1)/ M_PI, 2)));
       // y = pow(x(0), 2) + pow(x(1), 2);
    
        if(-x(0) + 1 > 0){
            y = y + O(0) * pow(-x(0) + 1,2);
        }
        if(-x(1) + 1 > 0){
            y = y + O(0) * pow(-x(1) + 1,2);
        }
        if(sqrt(pow(x(0),2) + pow(x(1),2)) - O(1) > 0){  // 0(1) = a
            y = y + O(0) * pow(sqrt(pow(x(0),2) + pow(x(1),2)) - O(1),2);
        }
        
    #endif
            //wewnetrzna f kary
    #if LAB_PART == 2

        y = sin(M_PI * sqrt(pow(x(0)/ M_PI, 2) + pow(x(1)/ M_PI, 2)))/ (M_PI * sqrt(pow(x(0)/ M_PI, 2) + pow(x(1)/ M_PI, 2)));
       // y = pow(x(0), 2) + pow(x(1), 2);

        if(-x(0) + 1 > 0){
            y = 1e10;
        }else{
            y = y - (O(0)/ (-x(0) + 1));
        }
        if(-x(1) + 1 > 0){
            y = 1e10;
        }else{
            y = y - (O(0) / (-x(1) + 1));
        }
        if(sqrt(pow(x(0),2) + pow(x(1),2)) - O(1) > 0){
            y = 1e10;
        }else{
            y = y - (O(0) / (sqrt(pow(x(0),2) + pow(x(1),2)) - O(1)));
        }
        
    #endif
            //problem rzeczywisty
    #if LAB_PART == 3

        matrix Y0(new double[4]{0, x(0), 100, 0}, 4);
        matrix *Y = solve_ode(0,0.01, 7, Y0, x(1));
        double x0, x50;
    
        for(int i = 0; i < get_size(Y[1])[0] - 1; ++i){
            if(Y[1](i,2) > 49.8 && Y[1](i,2) < 50.8){
                x50 = Y[1](i,0);
            }
            if(Y[1](i,2) > -0.2 && Y[1](i,2) < 0.2){
                x0 = Y[1](i,0);
            }
        }
        y = -x0;
    
    
        if(-x(0) - 10 > 0){
            y = y + O(0) * pow(-x(0) - 10,2);
        }
        if(-x(0) + 10 < 0){
            y = y + O(0) * pow(-x(0) + 10,2);
        }
        if(-x(1) - 20 > 0){
            y = y + O(0) * pow(-x(1) - 20,2);
        }
        if(-x(1) + 20 < 0){
            y = y + O(0) * pow(-x(1) + 20,2);
        }
        if(-x50 + 4 > 0){
            y = y + O(0) * pow(-x50 + 4,2);
        }
        if(-x50 + 6 < 0){
            y = y + O(0) * pow(-x50 + 6,2);
        }

    #endif
    ++f_calls;
#endif
#if LAB_NO == 5
    #if LAB_PART == 1
    
        int * n = get_size(O);
     
        if(n[1] == 1){
            y = pow(x(0) + 2*x(1) - 7, 2) + pow(2*x(0) + x(1) - 5, 2);
            ++f_calls;
        }else{
            solution tmp;
            tmp.x = O[0] + x * O[1];
            tmp.fit_fun();
            y = tmp.y;
        }
    
    #endif
    #if LAB_PART == 2
        
        int m   = 100;
        int * n = get_size(x);
        static matrix X(n[0], m), Y(1, m);
        
        if(solution::f_calls==0){
            ifstream S("XData.txt");
            if (S.good() == true){
                S >> X;
                S.close();
            }
            S.open("YData.txt");
            if (S.good() == true){
                S >> Y;
                S.close();
            }
        }
        
        double h;
        y = 0.0;
        for (int i = 0; i < m; ++i) {
            h = (trans(x) * X[i])(0);
            h = 1.0 / (1.0 + exp(-h));
            y = y - Y(0,i) * log(h) - (1 - Y(0,i)) * log(1 - h);
        }
        y(0) = y(0)/m;
        
        ++f_calls;
    
    #endif
#endif

#if LAB_NO == 6
    #if LAB_PART == 1
        int* n = get_size(O);

        if (n[1] == 1) {
            y = matrix(2, 1);
            y(0) = a * (pow(x(0) - 5, 2) + pow(x(1) - 5, 2));
            y(1) = 1 / a * (pow(x(0) + 5, 2) + pow(x(1) + 5, 2));
            ++f_calls;
        }
        else {
            solution temp;
            temp.x = O[0] + x * O[1];
            temp.fit_fun();
            y = O(0, 2) * temp.y(0) + (1 - O(0, 2)) * temp.y(1);
        }
    #endif
    #if LAB_PART == 2
        int* n = get_size(O);
        double f1min = 0.458797, f1max = 3.01327, f2min = 4.35446e-5 , f2max = 0.00188011;

        if (n[1] == 1) {
            y = matrix(3, 1);
            double ro = 7800, P = 1e3, E = 207e9;
            
            y(0) = ro * x(0) * M_PI * pow(x(1), 2) /4;
            y(1) = 64 * P * pow(x(0), 3) / (3 * E * M_PI * pow(x(1), 4));
            y(2) = 32 * P * x(0) / (M_PI * pow(x(1), 3));
            ++f_calls;
        } else {
            solution T;
            matrix yn(2, 1);
            
            T.x = O[0] + x * O[1];
            T.fit_fun();
            yn(0) = (T.y(0) - f1min) / (f1max - f1min);
            yn(1) = (T.y(1) - f2min) / (f2max - f2min);
             y = O(0, 2) * yn(0) + (1 - O(0, 2)) * yn(1);
            // y = O(0, 2) * T.y(0) + (1 - O(0, 2)) * T.y(1);
            
            if(T.y(1) > 0.005){
                y = y + 1e6 * pow(T.y(1) - 0.005, 2);
            }
            if(T.y(2) > 300e6){
                y = y + 1e6 * pow(T.y(2) - 300e6, 2);
            }
        }
        
       /* if(y(0) < f1min){
            f1min = y(0);
        }
        if(y(0) > f1max){
            f1max = y(0);
        }
        if(y(1) < f2min){
            f2min = y(1);
        }
        if(y(1) > f2max){
            f2max = y(1);
        }*/
        
    #endif
#endif
#if LAB_NO == 7
    #if LAB_PART == 1

        y = pow(x(0), 2) + pow(x(1), 2) - cos(2.5 * M_PI * x(0)) - cos(2.5 * M_PI * x(1)) + 2;

    #endif
    #if LAB_PART == 2

        int N = 1001;
        static matrix X(N, 2);
        
        if(solution::f_calls == 0){
            ifstream F("polozenia.txt");
            F >> X;
            F.close();
        }
   
        matrix Y0(4,1);
        matrix *Y = solve_ode(0, 0.1, 100, Y0, x);
        y(0) = 0.0;
        
        for(int i = 0; i < N; ++i){
            y = y + abs(X(i,0) - Y[1](i,0)) + abs(X(i,1) - Y[1](i,2));
        }
        y(0) = y(0) /(2. * N);

    #endif
        ++f_calls;
#endif
}

void solution::grad(matrix O)
{
#if LAB_NO == 5
    #if LAB_PART == 1
    //wektor 2 elem =df/dx1  i  df/dx2
    g(0) = 10 * x(0) + 8 * x(1) - 34;
    g(1) = 8 * x(0) + 10 * x(1) - 38;

    #endif
    #if LAB_PART == 2

        int m   = 100;
        int * n = get_size(x);
        double h;
        static matrix X(n[0], m), Y(1, m);

        if(solution::g_calls==0){
            ifstream S("XData.txt");
            if (S.good() == true){
                S >> X;
                S.close();
            }
            S.open("YData.txt");
            if (S.good() == true){
                S >> Y;
                S.close();
            }
        }

        g = matrix(n[0], 1);
        
        for (int j = 0; j < n[0]; ++j) {
            for (int i = 0; i < m; ++i) {
                h = (trans(x) * X[i])(0);
                h = 1.0 / (1.0 + exp(-h));
                g(j) = g(j) + X(j,i) * (h - Y(0,i));
            }
            g(j) = g(j)/m;
        }

    #endif
#endif
	
	++g_calls;
}

void solution::hess(matrix O)
{
#if LAB_NO == 5
 
    // macierz 2x2 df^2/dx1^2  df^2/dx1x2
    //             df^2/dx1x2  df^2/dx2^2
    H(0, 0) = 10;
    H(0, 1) = 8;
    H(1, 0) = 8;
    H(1, 1) = 10;
    
#endif

	++H_calls;
}
