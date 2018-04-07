#pragma once

#include "Files.h"
typedef struct SpecialPoint SpecialPoint;

SpecialPoint *create_SpecialPoint(Vector *vector);

const double get_x0(SpecialPoint *sPoint);
const double get_x1(SpecialPoint *sPoint);
const double get_x2(SpecialPoint *sPoint);
const double get_x3(SpecialPoint *sPoint);
const double get_y0(SpecialPoint *sPoint);
const double get_y1(SpecialPoint *sPoint);
const double get_y2(SpecialPoint *sPoint);
const double get_y3(SpecialPoint *sPoint);
const int get_numbers(SpecialPoint *sPoint);

void set_x0(SpecialPoint *sPoint, double x0);
void set_x1(SpecialPoint *sPoint, double x1);
void set_x2(SpecialPoint *sPoint, double x2);
void set_x3(SpecialPoint *sPoint, double x3);
void set_y0(SpecialPoint *sPoint, double y0);
void set_y1(SpecialPoint *sPoint, double y1);
void set_y2(SpecialPoint *sPoint, double y2);
void set_y3(SpecialPoint *sPoint, double y3);
void set_numbers(SpecialPoint *sPoint, int numbers);

int solve_cubic_eqation(const double A, const double B, const double C, const double D, SpecialPoint *sPoint);
int solve_square_eqation( const double A, const double B, const double C, SpecialPoint *sPoint);
int solve_linear_eqation( const double A, const double B, SpecialPoint *sPoint);

