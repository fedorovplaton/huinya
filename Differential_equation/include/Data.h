#pragma once


typedef struct tVector Vector;
typedef struct tInterval Interval;

Vector *create_vector(double a, double b, double c, double alpha, double beta, double x0, double y0);
Interval *create_interval(int quantity_of_points, double h, int quantity_of_jumps, double distance_jump);

void delete_vector(Vector *vector);
void delete_interval(Interval *interval);

double get_a( const Vector *vector);
double get_b( const Vector *vector);
double get_c( const Vector *vector);
double get_alpha( const Vector *vector);
double get_beta( const Vector *vector);
double get_x0( const Vector *vector);
double get_y0( const Vector *vector);

int get_quantity_of_points(const Interval *interval);
double get_h(const  Interval *interval);
int get_quantity_of_jumps(const Interval *interval);
double get_distance_jump(const Interval *interval);

void set_a(Vector *vector, double a);
void set_b(Vector *vector, double b);
void set_c(Vector *vector, double c);
void set_alpha(Vector *vector, double alpha);
void set_beta(Vector *vector, double beta);
void set_x0(Vector *vector, double x0);
void set_y0(Vector *vector, double y0);

int set_quantity_of_points(Interval *interval, int quantity);
void set_h(Interval *interval, double h);
void set_quantity_of_jumps(Interval *interval, int quantity_of_jumps);
void set_distance_jump(Interval *interval, double distance_jump);