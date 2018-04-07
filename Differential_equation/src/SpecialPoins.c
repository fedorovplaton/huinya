#include "../include/SpecialPoints.h"
#include "../include/Structures.h"
#include <stdlib.h>
#include <math.h>

#define EPS 0.0000000005

typedef struct Point
{
    double x;
    double y;
} Point;

typedef struct SpecialPoint
{
    double x0;
    double y0;

    double x1;
    double y1;

    double x2;
    double y2;

    double x3;
    double y3;

    int numbers;
} SpecialPoint;

int three_solution(double x1, double x2, double x3, SpecialPoint *sPoint)
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

int two_solution(double x1, double x2, SpecialPoint *sPoint) {
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

int  solve_cubic_eqation(const double A, const double B, const double C, const double D, SpecialPoint *sPoint)
{
    const double p = C / A - (B * B) / (3 * A * A);
    const double q = 2 * B * B * B / (27 * A * A * A) - (B * C) / (3 * A * A) + D / A;
    const double Q1 = (p * p * p / 27) + (q * q / 4);

    if (fabs(Q1) < EPS)
    {
        const double alpha = cbrt(-q / 2);
        const double x1 = 2 * alpha - B / (3 * A);
        const double x2 = -alpha - B / (3 * A);

        return two_solution(x1, x2, sPoint);
    }
    else if (Q1 > 0)
    {
        const double alpha = cbrt(-q / 2 + sqrt(Q1));
        const double beta = cbrt(-q / 2 - sqrt(Q1));
        const double x = alpha + beta - B / (3 * A);

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
    else
    {
        const double r = sqrt(-p * p * p / 27);
        const double fi = acos(-q / (2 * p)) / 3;

        const double x1 = 2 * cbrt(r) * cos(fi) - B / (3 * A);
        const double x2 = 2 * cbrt(r) * cos(fi + 2 * M_PI / 3) - B / (3 * A);
        const double x3 = 2 * cbrt(r) * cos(fi + 4 * M_PI / 3) - B / (3 * A);

        return three_solution(x1, x2, x3, sPoint);
    }
}

int solve_square_eqation( const double A, const double B, const double C, SpecialPoint *sPoint)
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
        const double x2 = (-B - sqrt(Dis)) / (2 * A);

        return two_solution(x1, x2, sPoint);
    }
    else
    {
        return 1;
    }
}

int solve_linear_eqation( const double A, const double B, SpecialPoint *sPoint)
{
    const double x = -B / A;
    if (fabs(x - 1) > EPS && fabs(x) > EPS)
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

int num ( Vector *vector, SpecialPoint *sPoint)
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
        return solve_cubic_eqation(A1, B1, C1, D1, sPoint);
    }

    if (B1 != 0)
    {
        return solve_square_eqation(B1, C1, D1, sPoint);
    }

    if (C1 != 0)
    {
        return solve_linear_eqation(C1, D1, sPoint);
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

SpecialPoint *create_SpecialPoint(Vector *vector)
{
    SpecialPoint *sPoint = malloc(sizeof(SpecialPoint));

    set_x0(sPoint, 0);
    set_y0(sPoint, 0);

    set_numbers(sPoint, num(vector, sPoint));
    return sPoint;
}

const double get_x0(SpecialPoint *sPoint)
{
    return sPoint->x0;
}

const double get_x1(SpecialPoint *sPoint)
{
    return sPoint->x1;
}

const double get_x2(SpecialPoint *sPoint)
{
    return sPoint->x2;
}

const double get_x3(SpecialPoint *sPoint)
{
    return sPoint->x3;
}

const double get_y0(SpecialPoint *sPoint)
{
    return sPoint->y0;
}

const double get_y1(SpecialPoint *sPoint)
{
    return sPoint->y1;
}

const double get_y2(SpecialPoint *sPoint)
{
    return sPoint->y2;
}

const double get_y3(SpecialPoint *sPoint)
{
    return sPoint->y3;
}

const int  get_numbers(SpecialPoint *sPoint)
{
    return sPoint->numbers;
}

void set_x0(SpecialPoint *sPoint, double x0)
{
    sPoint->x0 = x0;
}

void set_x1(SpecialPoint *sPoint, double x1)
{
    sPoint->x1 = x1;
}

void set_x2(SpecialPoint *sPoint, double x2)
{
    sPoint->x2 = x2;
}

void set_x3(SpecialPoint *sPoint, double x3)
{
    sPoint->x3 = x3;
}

void set_y0(SpecialPoint *sPoint, double y0)
{
    sPoint->y0 = y0;
}

void set_y1(SpecialPoint *sPoint, double y1)
{
    sPoint->y1 = y1;
}

void set_y2(SpecialPoint *sPoint, double y2)
{
    sPoint->y2 = y2;
}

void set_y3(SpecialPoint *sPoint, double y3)
{
    sPoint->y3 = y3;
}

void set_numbers(SpecialPoint *sPoint, int numbers)
{
    sPoint->numbers = numbers;
}

