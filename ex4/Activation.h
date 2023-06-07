#include "Matrix.h"

#ifndef ACTIVATION_H
#define ACTIVATION_H

typedef  Matrix (activation_func)(const Matrix& m);

namespace activation
{
  activation_func relu;
  activation_func softmax;
};


#endif //ACTIVATION_H