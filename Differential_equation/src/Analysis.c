#include "../include/Analysis.h"
#include <stdlib.h>


typedef struct Analyser
{
	float x;
	float y;

	float prev_tangent_x;
	float prev_tangent_y;

	float next_tangent_x;
	float next_tangent_y;

	int clockwise;
	int counterclockwise;

	int flag;
} Analyser;


Analyser *create_analyser(const float x, const float y)
{
	Analyser *analyser = malloc(sizeof(Analyser));

	analyser->x = x;
	analyser->y = y;

	analyser->prev_tangent_x = 0;
	analyser->prev_tangent_y = 0;

	analyser->next_tangent_x = 0;
	analyser->next_tangent_y = 0;

	analyser->clockwise = 0;
	analyser->counterclockwise = 0;

	analyser->flag = 0;

	return analyser;
}


int quarter_number(const float x, const float y)
{
	if ((x >= 0) && (y >= 0))
	{
		return 1;
	}

	if ((x < 0) && (y >= 0))
	{
		return 2;
	}

	if ((x < 0) && (y < 0))
	{
		return 3;
	}

	return 4;
}

void update_statistics(Analyser *analyser)
{
	const float prev_x = analyser->prev_tangent_x;
	const float prev_y = analyser->prev_tangent_y;
	const float next_x = analyser->next_tangent_x;
	const float next_y = analyser->next_tangent_y;

	const int prev = quarter_number(prev_x, prev_y);
	const int next = quarter_number(next_x, next_y);

	if ((next - prev == -1) || (next - prev == 3))
	{
		analyser->clockwise++;
	}

	if ((next - prev == 1) || (next - prev == -3))
	{
		analyser->counterclockwise++;
	}
}

void send_points(Analyser *analyser, const float x, const float y)
{
	switch (analyser->flag)
	{
		case 0:
		{
			analyser->prev_tangent_x = x - analyser->x;
			analyser->prev_tangent_y = y - analyser->y;

			analyser->x = x;
			analyser->y = y;

			analyser->flag++;
			break;
		}
		case 1:
		{
			analyser->next_tangent_x = x - analyser->x;
			analyser->next_tangent_y = y - analyser->y;

			analyser->x = x;
			analyser->y = y;

			analyser->flag++;
			update_statistics(analyser);
			break;
		}
		default:
		{
			analyser->prev_tangent_x = analyser->next_tangent_x;
			analyser->prev_tangent_y = analyser->next_tangent_y;

			analyser->next_tangent_x = x - analyser->x;
			analyser->next_tangent_y = y - analyser->y;

			analyser->x = x;
			analyser->y = y;

			update_statistics(analyser);
			break;
		}
	}
}

int receive_course(Analyser *analyser)
{
	if (analyser->clockwise > analyser->counterclockwise)
	{
		return 1;
	}

	if (analyser->clockwise < analyser->counterclockwise)
	{
		return -1;
	}

	return 0;
}


void delete_analyser(Analyser *analyser)
{
	free(analyser);
}
