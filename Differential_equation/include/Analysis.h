#pragma once


typedef struct Analyser Analyser;

Analyser *create_analyser(const float x, const float y);

void send_points(Analyser *analyser, const float x, const float y);
int receive_course(Analyser *analyser);

void delete_analyser(Analyser *analyser);
