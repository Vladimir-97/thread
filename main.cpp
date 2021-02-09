#include <iostream>
#include <omp.h>
#include <fstream>
#include <time.h>
#include <fstream>
#include "timetest.h"

using namespace std;

ifstream fin("in.txt");
ofstream fout("out.txt");

void draw() {
	fout << "|| Test number ";
	fout << "||  m   ";
	fout << "||  n   ";
	fout << "||  k   ";
	fout << "|| alg1 ";
	fout << "|| alg2(paral) ||";
	fout << "\n";
}

void Multiply(double* a, double* b, double* c, int m, int k, int n) {
	for (int i = 0; i < m; i++)
		for (int j = 0; j < k; j++)
		{
			double x = 0;
			for (int r = 0; r < n; r++)
				x = x + a[i * n + r] * b[r * k + j];
			c[i * k + j] = x;

		}
}

void Multiply_paral(double* a, double* b, double* c, int m, int k, int n)
{
	
	#pragma omp parallel for
	for (int i = 0; i < m; i++)
		for (int j = 0; j < k; j++)
		{
			double x = 0;
			for (int r = 0; r < n; r++)
				x = x + a[i * n + r] * b[r * k + j];
			c[i * k + j] = x;
			
		}
}

int main() {
	//A_m,n * B_n,k = Ñ_m,k
	srand(time(0));
	
	
	

	int var;
	int m, n, k;
	int dem = 10;
	
	draw();
	
	//fin >> m >> n >> k;
	
	
	for (int t = 0; t < 9; t++) {
		fout <<"||     " <<t + 1<<"       || ";
		
		m = dem;
		n = m;
		k = n;
		
		fout << m << "   || ";
		fout << n << "   || ";
		fout << k << "   || ";
		
		
		double *a = new double[m*n];
		double *b = new double[n*k];
		double *c = new double[m*k];

		for (int i = 0; i < m;i++) {
			for (int j = 0;j < n;j++) {
				//fin >> var;
				var = 1 + rand() % 10;
				a[n*i + j] = var;
			}
		}

		for (int i = 0; i < n;i++) {
			for (int j = 0;j < k;j++) {
				//fin >> var;
				var = 1 + rand() % 10;
				b[k*i + j] = var;
			}
		}

		startTest();
		
		Multiply(a, b, c, m, k, n);
		fout << stopTest();
		fout << "||";
		startTest();
		Multiply_paral(a, b, c, m, k, n);
		double perem;
		fout << stopTest();
		fout << "||";

		delete[] a;
		delete[] b;
		delete[] c;
		dem = dem * 2;
		fout << "\n";
	}
	

	return 0;
}