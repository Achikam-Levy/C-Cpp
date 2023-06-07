//
// Created by אחיקם לוי on 15/12/2022.
//
#include "Dense.h"

/**
 * constructor of Dense class
 * @param weights initial weights - list of matrix
 * @param bias initial bias - list of matrix
 * @param activation_function initial the activation function
 */
Dense::Dense(const Matrix& weights, const Matrix& bias,
             activation_func *activ_function)
{
  _weights = weights;
  _bias = bias;
  _activationFunction = activ_function;
}

/**
 * return the weights filed
 * @return
 */
Matrix Dense::get_weights() const
{
  return _weights;
}

/**
 * return the bias filed
 * @return
 */
Matrix Dense::get_bias() const
{
  return _bias;
}

/**
 *
 * @return the activation function
 */
activation_func *Dense::get_activation()const
{
  return *_activationFunction;
}

/**
 * operate the activation function on a matrix
 * @param m parameter matrix
 * @return matrix after operated by the activation function
 */
Matrix Dense::operator()( Matrix &m)
{
  Matrix l = (_weights * m) + _bias;
  return _activationFunction(l);
}