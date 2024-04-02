#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <math.h>
using namespace std;

double a = -2;
double b = 2;
double pi = 3.14159265;


double f(double x)
{
	double y = x * abs(x);
	return y;
}


void Table(double X[], double Y[], int n)
{
	cout << "Values:\n";
	X[0] = a;
	for (int i = 0; i <= n; i++) {
		X[i] = X[0] + i * (b - a) / n;
		Y[i] = f(X[i]);
		cout << X[i] << "  ";
		cout << Y[i] << endl;
	}
}


void Table1(double X[], double Y[], int n)
{
	X[0] = a;
	for (int i = 0; i <= n; i++) {
		X[i] = X[0] + i * (b - a) / n;
		Y[i] = f(X[i]);
	}
}


void Cheb(double X[], double Y[], int n)
{
	cout << "Chebyshov:\n";
	for (int i = 0; i <= n; i++) {
		X[i] = ((b - a) / 2)*cos((2 * i + 1)*pi / (2 * (n + 1)));
		Y[i] = f(X[i]);
		// cout << X[i] << "  ";
		// cout << Y[i] << endl;
	}
}


double Lagrange(double X[], double Y[], double t, int n)
{
	double res, p1, p2;
	res = 0;
	for (int i = 0; i <= n; i++) {
		p1 = 1;
		p2 = 1;
		for (int j = 0; j <= n; j++) {
			if (i != j) {
				p1 *= (t - X[j]);
				p2 *= (X[i] - X[j]);
			}
		}
		res += Y[i] * p1 / p2;
	}
	return res;
}


double Dif(double X[], double Y[], int k)
{
	double s = 0, m, d;
	for (int i = 0; i <= k; i++) {
		m = 1;
		for (int j = 0; j <= k; j++)
			if (i != j) m *= (X[i] - X[j]);
		d = Y[i] / m;
		s += d;
	}
	return s;
}


double Newton(double X[], double Y[], double t, int n)
{
	double res, p = 1;
	res = Y[0];
	for (int i = 0; i < n; i++) {
		p *= (t - X[i]);
		//res += p * Dif(X, Y, 0, i + 1, i + 1);
		res += p * Dif(X, Y, i + 1);
	}
	return res;
}


double Deviation(double X[], double Y[], double t, int n)
{
	double M, R = 0;
	int f;
	if (n == 1) {
		M = 2;
		f = 2;
		R = (M / f)*abs((t - X[0])*(t - X[1]));
	}
	if (n == 0) {
		M = 2 * abs(t);
		f = 1;
		R = (M / f)*abs(t - X[0]);
	}
	return R;
}


void main()
{
	int n;
	cout << "Enter the degree: ";
	cin >> n;
	double *X = new double[n + 1];
	double *Y = new double[n + 1];
	Table(X, Y, n);
	double t;
	cout << "Enter your parameter: ";
	cin >> t;
	cout << Lagrange(X, Y, t, n) << endl;
	cout << Newton(X, Y, t, n) << endl;*/
	ofstream fout("lagrange.txt", ios_base::out | ios_base::trunc);
	ofstream fnew("newton.txt", ios_base::out | ios_base::trunc);
	ofstream fdev("deviation.txt", ios_base::out | ios_base::trunc);
	ofstream fden("deviatn.txt", ios_base::out | ios_base::trunc);
	ofstream fdevp("deviatpr.txt", ios_base::out | ios_base::trunc);
	int k = n * 10;
	for (int i = 0; i <= k; i++) {
		t = X[0] + i * (b - a) / k;
		fout << t << " " << Lagrange(X, Y, t, n) << endl;
		fnew << t << " " << Newton(X, Y, t, n) << endl;
		fdev << t << " " << abs(f(t) - Lagrange(X, Y, t, n)) << endl;
		fden << t << " " << abs(f(t) - Newton(X, Y, t, n)) << endl;
		fdevp << t << " " << Deviation(X, Y, t, n) << endl;
	}
	fout.close();
	fdev.close();
	fnew.close();
	fden.close();
	Cheb(X, Y, n);
	cout << "Enter your parameter (Chebyshov): ";
	cin >> t;
	cout << Lagrange(X, Y, t, n) << endl;
	cout << Newton(X, Y, t, n) << endl;*/
	ofstream fch("lagrch.txt", ios_base::out | ios_base::trunc);
	ofstream fnch("newch.txt", ios_base::out | ios_base::trunc);
	ofstream fdevc("devch.txt", ios_base::out | ios_base::trunc);
	ofstream fdenc("devnch.txt", ios_base::out | ios_base::trunc);
	ofstream fdepc("deviatpch.txt", ios_base::out | ios_base::trunc);
	for (int i = 0; i <= k; i++) {
		t = a + i * (b - a) / k;
		fch << t << " " << Lagrange(X, Y, t, n) << endl;
		fnch << t << " " << Newton(X, Y, t, n) << endl;
		fdevc << t << " " << abs(f(t) - Lagrange(X, Y, t, n)) << endl;
		fdenc << t << " " << abs(f(t) - Newton(X, Y, t, n)) << endl;
		fdepc << t << " " << Deviation(X, Y, t, n) << endl;
	}
	fch.close();
	fdevc.close();
	fnch.close();
	fdenc.close();
	delete X;
	delete Y;
	ofstream fnlg("nlagrange.txt", ios_base::out | ios_base::trunc);
	ofstream fnlch("nlagrch.txt", ios_base::out | ios_base::trunc);
	ofstream fnnew("nnewton.txt", ios_base::out | ios_base::trunc);
	ofstream fnnch("nnewch.txt", ios_base::out | ios_base::trunc);
	double X1[100];
	double Y1[100];
	double X2[100];
	double Y2[100];
	double ml, mn, mlc, mnc, s;
	for (n = 0; n < 100; n++) {
		Table1(X1, Y1, n);
		Cheb(X2, Y2, n);
		k = n * 5;
		ml = 0;
		mn = 0;
		mlc = 0;
		mnc = 0;
		for (int i = 0; i <= k; i++) {
			t = a + i * (b - a) / k;
			s = abs(f(t) - Lagrange(X1, Y1, t, n));
			if (s > ml) ml = s;
			s = abs(f(t) - Newton(X1, Y1, t, n));
			if (s > mn) mn = s;
			s = abs(f(t) - Lagrange(X2, Y2, t, n));
			if (s > mlc) mlc = s;
			s = abs(f(t) - Newton(X2, Y2, t, n));
			if (s > mnc) mnc = s;
		}
		fnlg << n << " " << ml << endl;
		fnnew << n << " " << mn << endl;
		fnlch << n << " " << mlc << endl;
		fnnch << n << " " << mnc << endl;
	}
	fnlg.close();
	fnnew.close();
	fnlch.close();
	fnnch.close();
}
