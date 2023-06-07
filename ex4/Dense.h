#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"

class Dense{
 private:
  Matrix _weights;
  Matrix _bias;
  activation_func *_activationFunction;
 public:
  Dense(const Matrix& weights, const Matrix& bias,
        activation_func *activ_function);
  Matrix get_weights() const;
  Matrix get_bias() const;
  activation_func * get_activation() const;
  Matrix operator()( Matrix &m) ;
};

#endif //DENSE_H
