//
// Created by serdar on 10/23/24.
//

#include <math.h>
#include <stdio.h>
#include "Loss.h"

void Loss::checkDims(Matrix *out) {
    if (out->m != labels->m || out->n != labels->n) {
        printf("Error: dimensions of output and labels do not match\n");
        exit(1);
    }
}

Loss::Loss(Matrix *labels) {
    this->labels = labels;
}
