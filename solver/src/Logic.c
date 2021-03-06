#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <mpi.h>
#include "../include/Logic.h"

static const int QUANTITY_OF_HALF_TURN = 10;
#define EPS 0.000001
#define MAX_QUANTITY_OF_STEPS 10000000


double fi(double x, double y);
double psi(Vector *vector, double x, double y);
void set_next_point(Vector *vector, double x, double y, double *next_x, double *next_y, double h);
int pass_few_semicircle(double start_x, double start_y, Vector *vector, int quantity, double *rez_x, double *rez_y);
int find_cycles_in_sp_environs(Vector *vector, double x0, double y0, double to, unsigned int quantity_steps);

#define SWAP_DOUBLE(x,y) do { double t = x; (x) = y; (y) = t;  } while(0)
void swap(double *a, double *b)
{
	double c = *a;
	*a = *b;
	*b = c;
}

int get_direction(double from, double to)
{
	if (from < to)
	{
		return 1;
	}

	return from > to ? -1 : 0;
}

int test(int argc, char **argv)
{
	int q[8] = {0};
	int myrank, nprocs;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	printf("%d %d\n", myrank, nprocs);
	Vector *vector;
	for (int i = 0; i < nprocs; ++i) {
		if (myrank == i) {
			//vector = create_vector(-10.0 + 0.00001 * i, 2.7, 0.4, -437.5, 0.003);
			vector = create_vector(-10.5, 1.925 + 0.002 * i, 0.4, -437.5, 0.003);
			int quantity = find_cycles_in_sp_environs(vector, 0, 0, 10, 100);
			delete_vector(vector);
			q[i] = quantity;
		}
	}
	MPI_Finalize();
	printf("%d %d %d %d %d %d %d %d\n", q[0], q[1], q[2], q[3], q[4], q[5], q[6], q[7]);
	return q[0];
}

int find_cycles_in_region(Region *region, Saver *saver, int argc, char **argv)
{
	const double a_from = get_region_a_from(region);
	const double b_from = get_region_b_from(region);
	const double c_from = get_region_c_from(region);
	const double alpha_from = get_region_alpha_from(region);
	const double beta_from = get_region_beta_from(region);

	const double a_to = get_region_a_to(region);
	const double b_to = get_region_b_to(region);
	const double c_to = get_region_c_to(region);
	const double alpha_to = get_region_alpha_to(region);
	const double beta_to = get_region_beta_to(region);

	const double a_step = get_region_a_step(region);
	const double b_step = get_region_b_step(region);
	const double c_step = get_region_c_step(region);
	const double alpha_step = get_region_alpha_step(region);
	const double beta_step = get_region_beta_step(region);


	MPI_Init(&argc, &argv);
	for (double i = a_from; i <= a_to; i = i + a_step) {
		for (double j = b_from; j <= b_to; j = j + b_step) {
			for (double k = c_from; k <= c_to; k = k + c_step) {
				for (double l = alpha_from; l <= alpha_to; l = l + alpha_step) {
					for (double m = beta_from; m <= beta_to; m = m + beta_step) {
						Vector *vector = create_vector(i, j, k, l, m);
						int quantity = find_cycles_in_sp_environs(vector, 0, 0, 10, 20);
						if(quantity >= 3)
						{
							save_vector(saver, vector);
						}
						delete_vector(vector);
					}
				}
			}
		}
	}
	MPI_Finalize();
	return 0;
}

//(x0, y0) -- singular point
int find_cycles_in_sp_environs(Vector*vector, double x0, double y0, double to, unsigned int quantity_steps)
{
	assert(quantity_steps);
	double step = fabs((to - x0)) / quantity_steps;
	double coshi_x = x0;
	double coshi_y = y0;
	double last_x, last_y = coshi_y;
	double next_x, next_y;
	int last_direction = 1, new_direction;
	int quantity = 0;
	int myrank;
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	printf("******%d******\n", myrank);
	unsigned int i;
	for (i = 0; i < quantity_steps; ++i) {
		coshi_x += step;
		last_x = coshi_x;
			if (pass_few_semicircle(last_x, last_y, vector, QUANTITY_OF_HALF_TURN, &next_x, &next_y)) {
			return -1; // ...
		}
		printf("%lf %lf || %lf %lf\n", last_x, last_y, next_x, next_y);
		new_direction = get_direction(last_x, next_x);
		if (last_direction != new_direction) {
			//printf("%.10lf %.10lf %d %d\n", last_x, next_x, last_direction, new_direction);
			double right_x = coshi_x, left_x = coshi_x - step;
			while (right_x - left_x > EPS) {
				printf("***%lf %lf\n", left_x, right_x);
				double new_x = left_x + (right_x - left_x) / 2;
				double x, y;
				pass_few_semicircle(new_x, y0, vector, QUANTITY_OF_HALF_TURN, &x, &y);
				if (get_direction(new_x, x) == last_direction/*???*/) {
					left_x = new_x;
				}
				else {
					right_x = new_x;
				}
			}
			printf("%.10lf %.10lf %d %d\n", left_x, right_x, last_direction, new_direction);
			++quantity;
			last_direction = new_direction;
		}
	}
	/*
	for (int i = 0; i < quantity_steps; ++i) {
		coshi_x += step;
		last_x = coshi_x;
		if (pass_few_semicircle(last_x, last_y, vector, QUANTITY_OF_HALF_TURN, &next_x, &next_y)) {
			return -1; // ...
		}
		//printf("%lf %lf || %lf %lf\n", last_x, last_y, next_x, next_y);
		new_direction = get_direction(last_x, next_x);
		if (last_direction != new_direction) {
			if (step < EPS) {
				printf("%.10lf %.10lf %d %d\n", last_x, next_x, last_direction, new_direction);
				++quantity;
			}
			else {
				double last_coshi = coshi_x - step; // * 1.1;
				quantity += find_cycles_in_sp_environs(vector, last_coshi, coshi_y, next_x, 100);
			}
			last_direction = new_direction;
		}
	}
	*/
	return quantity;
}

// TODO: пофиксить
int pass_few_semicircle(double start_x, double start_y, Vector *vector, int quantity, double *rez_x, double *rez_y)
{
	const double h = 0.000001;
	double y0 = start_y;
	double last_x = start_x;
	double last_y = start_y;
	double next_x = 0;
	double next_y = 0;
	int counter = -1;

	int quantitySteps = 0;
	while (counter < quantity && quantitySteps < MAX_QUANTITY_OF_STEPS) {
		quantitySteps++;
		set_next_point(vector, last_x, last_y, &next_x, &next_y, h);
		if ( (last_y >= y0 && next_y < y0) || (last_y <= y0 && next_y > y0) ) { //parentheses ???
			counter++;
		}
		last_x = next_x;
		last_y = next_y;
		if (quantitySteps == MAX_QUANTITY_OF_STEPS) {
			return 1;
		}
	}
	//printf("%lf %lf\n", next_x, next_y);
	*rez_x = next_x;
	*rez_y = next_y;
	return 0;
}


double fi(const double x, const double y)
{
	return x * x + x * y + y;
}

double psi(Vector *vector, const double x, const double y)
{
	const double a = get_a(vector);
	const double b = get_b(vector);
	const double c = get_c(vector);
	const double alpha = get_alpha(vector);
	const double beta = get_beta(vector);

	return a * x * x + b * x * y + c * y * y + alpha * x + beta * y;
}

void set_next_point(Vector *vector, double x, double y, double *next_x, double *next_y, const double h)
{
	const double k11 = h * fi(x, y);
	const double k21 = h * psi(vector, x, y);

	const double k12 = h * fi(x + k11 / 2, y + k21 / 2);
	const double k22 = h * psi(vector, x + k11 / 2, y + k21 / 2);

	const double k13 = h * fi(x + k12 / 2, y + k22 / 2);
	const double k23 = h * psi(vector, x + k12 / 2, y + k22 / 2);

	const double k14 = h * fi(x + k13, y + k23);
	const double k24 = h * psi(vector, x + k13, y + k23);

	*next_x = x + (k11 + k12 + k13 + k14) / 6;
	*next_y = y + (k21 + k22 + k23 + k24) / 6;
}

int FindCentre(double start_x, double start_y, Vector *vector, double *rez_x, double *rez_y)
{
	const double error = 0.01;
	double last_x = start_x;
	double last_y = start_y;
	double next_x;
	double next_y;

	do {
		if (pass_few_semicircle(last_x, last_y, vector, 1, &next_x, &next_y)) {
			return 1;
		}

		if (last_x < next_x) {
			next_x -= (next_x - last_x) / 2;
		}
		else if (last_x > next_x) {
			SWAP_DOUBLE(last_x, next_x);
			SWAP_DOUBLE(last_y, next_y);
		}

	}
	while (next_x - start_x > error);
	*rez_x = next_x;
	*rez_y = next_y;
	return 0;
}
