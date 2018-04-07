#include "../include/Files.h"
#include <stdlib.h>
#include <stdio.h>


typedef struct Loader
{
	FILE *input;
} Loader;

typedef struct Saver
{
	FILE *output;
} Saver;


Loader *create_loader(const char *input)
{
	Loader *loader = malloc(sizeof(Loader));

	loader->input = fopen(input, "r");

	return loader;
}

Saver *create_saver(const char *output)
{
	Saver *saver = malloc(sizeof(Saver));

	saver->output = fopen(output, "w");

	return saver;
}


int check_eof(Loader *loader)
{
	if (loader->input == NULL)
	{
		return -1;
	}

	if (feof(loader->input) != 0)
	{
		fclose(loader->input);
		loader->input = NULL;
		return -1;
	}

	return 0;
}

Vector *load_vector(Loader *loader)
{
	if (check_eof(loader) != 0)
	{
		return NULL;
	}

	float a = 0;
	float b = 0;
	float c = 0;
	float alpha = 0;
	float beta = 0;
	float x = 0;
	float y = 0;

	fscanf(loader->input
		, "%e%e%e%e%e%e%e"
		, &a
		, &b
		, &c
		, &alpha
		, &beta
		, &x
		, &y);

	return create_vector(a, b, c, alpha, beta, x, y);
}

Interval *load_interval(Loader *loader)
{
	if (check_eof(loader) != 0)
	{
		return NULL;
	}

	int steps = 0;
	float distance = 0;
	int points = 0;
	float h = 0;

	fscanf(loader->input
		, "%d%e%d%e"
		, &steps
		, &distance
		, &points
		, &h);

	return create_interval(steps, distance, points, h);
}

int reload_vector(Loader *loader, Vector *vector)
{
	if (check_eof(loader) != 0)
	{
		return -1;
	}

	float a = 0;
	float b = 0;
	float c = 0;
	float alpha = 0;
	float beta = 0;
	float x = 0;
	float y = 0;

	fscanf(loader->input
		, "%e%e%e%e%e%e%e"
		, &a
		, &b
		, &c
		, &alpha
		, &beta
		, &x
		, &y);

	set_a(vector, a);
	set_b(vector, b);
	set_c(vector, c);
	set_alpha(vector, alpha);
	set_beta(vector, beta);
	set_x(vector, x);
	set_y(vector, y);

	return 0;
}

int reload_interval(Loader *loader, Interval *interval)
{
	if (check_eof(loader) != 0)
	{
		return -1;
	}

	int steps = 0;
	float distance = 0;
	int points = 0;
	float h = 0;

	fscanf(loader->input
		, "%d%e%d%e"
		, &steps
		, &distance
		, &points
		, &h);

	set_steps(interval, steps);
	set_distance(interval, distance);
	set_points(interval, points);
	set_h(interval, h);

	return 0;
}


void save_vector(Saver *saver, const Vector *vector)
{
	fprintf(saver->output
		, "%e %e %e %e %e %e %e\n"
		, get_a(vector)
		, get_b(vector)
		, get_c(vector)
		, get_alpha(vector)
		, get_beta(vector)
		, get_x(vector)
		, get_y(vector));
}

void save_interval(Saver *saver, const Interval *interval)
{
	fprintf(saver->output
		, "%d %e %d %e\n"
		, get_steps(interval)
		, get_distance(interval)
		, get_points(interval)
		, get_h(interval));
}


void delete_loader(Loader *loader)
{
	if (loader->input != NULL)
	{
		fclose(loader->input);
	}

	free(loader);
}

void delete_saver(Saver *saver)
{
	fclose(saver->output);

	free(saver);
}
