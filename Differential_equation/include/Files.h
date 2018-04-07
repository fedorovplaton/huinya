#pragma once

#include "Structures.h"


typedef struct Loader Loader;
typedef struct Saver Saver;

Loader *create_loader(const char *input);
Saver *create_saver(const char *output);

Vector *load_vector(Loader *loader);
Interval *load_interval(Loader *loader);
int reload_vector(Loader *loader, Vector *vector);
int reload_interval(Loader *loader, Interval *interval);

void save_vector(Saver *saver, const Vector *vector);
void save_interval(Saver *saver, const Interval *interval);

void delete_loader(Loader *loader);
void delete_saver(Saver *saver);
