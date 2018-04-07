#pragma once


typedef struct Vector Vector;
typedef struct Interval Interval;

Vector *create_vector(const float a
					, const float b
					, const float c
					, const float alpha
					, const float beta
					, const float x
					, const float y);

Interval *create_interval(const int steps
						, const float distance
						, const int points
						, const float h);

const float get_a(const Vector *vector);
const float get_b(const Vector *vector);
const float get_c(const Vector *vector);
const float get_alpha(const Vector *vector);
const float get_beta(const Vector *vector);
const float get_x(const Vector *vector);
const float get_y(const Vector *vector);

const int get_steps(const Interval *interval);
const float get_distance(const Interval *interval);
const int get_points(const Interval *interval);
const float get_h(const  Interval *interval);

void set_a(Vector *vector, const float a);
void set_b(Vector *vector, const float b);
void set_c(Vector *vector, const float c);
void set_alpha(Vector *vector, const float alpha);
void set_beta(Vector *vector, const float beta);
void set_x(Vector *vector, const float x);
void set_y(Vector *vector, const float y);

void set_steps(Interval *interval, const int steps);
void set_distance(Interval *interval, const float distance);
void set_points(Interval *interval, const int points);
void set_h(Interval *interval, const float h);

void delete_vector(Vector *vector);
void delete_interval(Interval *interval);
