#ifndef SRC_BACK_H_
#define SRC_BACK_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "s21_matrix.h"

typedef struct polygon_struct {
    int *name_vertexes;
	int sum_vertexes_in_facets;
} polygon_t;

typedef struct universe {
    int sum_vertexes;
	int sum_facets;
    int v;
    // int *array_3d;
    int *indexes_array;
    matrix_t matrix_3d;
    polygon_t *polygons;
} t_universe;

int loading(t_universe *data, char *file_name);
matrix_t moving(t_universe *data, double a, double b, double c);
matrix_t rotating(t_universe *data, double a, double b, double c);
matrix_t scaling(t_universe *data, double a, double b, double c);
void matrixToArray(t_universe *data, double *array_3d);

#endif  // SRC_BACK_H_