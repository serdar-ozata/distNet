//
// Created by serdar on 10/23/24.
//

#ifndef DISTNET_LOSS_H
#define DISTNET_LOSS_H


#include <stdio.h>
#include <math.h>
#include "../Matrix.h"
#include "mpi.h"

class Loss {
public:
    Matrix * labels;
    Loss(Matrix *labels);
    virtual Matrix *get_error_prime(Matrix *out) = 0;
    virtual void eval(Matrix* out) = 0;
    void checkDims(Matrix *out);
};


#endif //DISTNET_LOSS_H
