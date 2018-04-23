#include "../include/SingularPoints.h"
#include <math.h>
#include "stdio.h"

#define EPS 0.0000000001

int three_solution(double x1, double x2, double x3, SingularPoints *sPoint)
{
	int i = 1;
	if (fabs(x1 + 1) > EPS && fabs(x1) > EPS)
	{
		set_x1(sPoint, x1);
		set_y1(sPoint, -(x1 * x1) / (x1 + 1));
		i++;

		if (fabs(x2 + 1) > EPS && fabs(x2) > EPS)
		{
			set_x2(sPoint, x2);
			set_y2(sPoint, -(x2 * x2) / (x2 + 1));
			i++;

			if (fabs(x3 + 1) > EPS && fabs(x3) > EPS)
			{
				set_x3(sPoint, x3);
				set_y3(sPoint, -(x3 * x3) / (x3 + 1));
				i++;
			}

		}
		else if (fabs(x3 + 1) > EPS && fabs(x3) > EPS)
		{
			set_x2(sPoint, x3);
			set_y2(sPoint, -(x3 * x3) / (x3 + 1));
			i++;
		}
	}
	else if (fabs(x2 + 1) > EPS && fabs(x2) > EPS)
	{
		set_x1(sPoint, x2);
		set_y1(sPoint, -(x2 * x2) / (x2 + 1));
		i++;

		if (fabs(x3 + 1) > EPS && fabs(x3) > EPS)
		{
			set_x2(sPoint, x3);
			set_y2(sPoint, -(x3 * x3) / (x3 + 1));
			i++;
		}
	}
	else if (fabs(x3 + 1) > EPS && fabs(x3) > EPS)
	{
		set_x1(sPoint, x3);
		set_y1(sPoint, -(x3 * x3) / (x3 + 1));
		i++;
	}

	return i;
}

int two_solution(double x1, double x2, SingularPoints *sPoint) {
	int i = 1;
	if (fabs(x1 + 1) > EPS && fabs(x1) > EPS)
	{
		set_x1(sPoint, x1);
		set_y1(sPoint, -(x1 * x1) / (x1 + 1));
		i++;

		if (fabs(x2 + 1) > EPS && fabs(x2) > EPS)
		{
			set_x2(sPoint, x2);
			set_y2(sPoint, -(x2 * x2) / (x2 + 1));
			i++;
		}
	} else if (fabs(x2 + 1) > EPS && fabs(x2) > EPS)
	{
		set_x1(sPoint, x2);
		set_y1(sPoint, -(x2 * x2) / (x2 + 1));
		i++;
	}

	return i;
}

int  solve_cubic_equation(const double A, const double B, const double C, const double D, SingularPoints *sPoint)
{
	const double a = B / A;
	const double b = C / A;
	const double c = D / A;
	const double v = B / (3.0 * A);

	const double Q = (a * a -3.0 * b) / 9.0;
	//q=(a*a-3.*b)/9.;
	const double R = (a * (2.0 * a * a - 9.0* b ) + 27.0 * c) / 54.0;
	//r=(a*(2.*a*a-9.*b)+27.*c)/54.
	const double S = Q * Q * Q - R * R;
	if (S <= 0)
	{
		printf("\n S: %lf R: %lf ,  %lf %lf %lf %lf \n", S, R, A, B, C, D);
		double _A;
		double _B;

		if(R == 0.0)
			_A = 0.0;
		else {
			if (R > 0)
				_A = -1.0 * cbrt(fabs(R) + sqrt(-1.0 * S));
			else
				_A = cbrt(fabs(R) + sqrt(-1.0 * S));
		}
		if(_A == 0.0)
			_B = 0.0;
		else
			_B = Q/_A;

		const double x1 = (_A + _B) - (a / 3.0);
		if(_A == _B)
		{
			const  double x2 = -1.0 * _A - (a/3.0);
			if(x1 == x2) {
				if (fabs(x1 + 1) > EPS && fabs(x1) > EPS) {
					set_x1(sPoint, x1);
					set_y1(sPoint, -(x1 * x1) / (x1 + 1));
					//printf("%lf %lf %lf %lf 2 \n", A, B, C,  D);
					printf("esk2");
					return 2;
				}
				else {
					printf("esk1");
					return 1;
				}
			}
			printf(" x1 = %lf, x2 = %lf ", x1, x2);
			return two_solution(x1, x2, sPoint);
		}
		else
		{
			if (fabs(x1 + 1) > EPS && fabs(x1) > EPS) {
				set_x1(sPoint, x1);
				set_y1(sPoint, -(x1 * x1) / (x1 + 1));
				//printf("%lf %lf %lf %lf 2 \n", A, B, C, D);
				return 2;
			}
			else
				printf("esk3");
				return 1;
		}
	}
	else
	{
		const double fi = acos(R / (Q * sqrt(Q)));
		const double rad = -2. * sqrt(Q);

		const double x1 = rad*cos(fi / 3.0) - v;
		const double x2 = rad*cos((fi + 2*M_PI) / 3.0) - v;
		const double x3 = rad*cos((fi - 2*M_PI) / 3.0) - v;

		//printf("%lf %lf %lf %lf three \n", A, B, C, D);
		return three_solution(x1, x2, x3, sPoint);
	}
}

int solve_square_equation( const double A, const double B, const double C, SingularPoints *sPoint)
{
	const double Dis = B * B - 4 * A * C;
	if (fabs(Dis) < EPS)
	{
		const double x = -B / (2 * A);
		if (fabs(x + 1) > EPS && fabs(x) > EPS)
		{
			set_x1(sPoint, x);
			set_y1(sPoint, -(x * x) / (x + 1));

			return 2;
		}
		else
		{
			return 1;
		}
	}
	if (Dis > 0)
	{
		const double x1 = (-B + sqrt(Dis)) / (2 * A);
		const double x2 = ( -B - sqrt(Dis)) / (2 * A);

		return two_solution(x1, x2, sPoint);
	}
	else
	{
		return 1;
	}
}

int solve_linear_equation( const double A, const double B, SingularPoints *sPoint)
{
	const double x = -B / A;
	if (fabs(x + 1) > EPS && fabs(x) > EPS)
	{
		set_x1(sPoint, x);
		set_x1(sPoint, -(x * x) / (x + 1));
		return 2;
	}
	else
	{
		return 1;
	}
}

int num ( Vector *vector, SingularPoints *sPoint)
{
	const double a = get_a(vector);
	const double b = get_b(vector);
	const double c = get_c(vector);
	const double alpha = get_alpha(vector);
	const double beta = get_beta(vector);

	const double A1 = a - b + c;
	const double B1 = 2 * a - b + alpha - beta;
	const double C1 = a - beta + 2 * alpha;
	const double D1 = alpha;

	if (A1 != 0)
	{
		return solve_cubic_equation(A1, B1, C1, D1, sPoint);
	}

	if (B1 != 0)
	{
		return solve_square_equation(B1, C1, D1, sPoint);
	}

	if (C1 != 0)
	{
		return solve_linear_equation(C1, D1, sPoint);
	}
	if (D1 != 0)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}