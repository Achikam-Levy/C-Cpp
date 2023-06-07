#include "Activation.h"
//
// Created by אחיקם לוי on 15/12/2022.
//

/**
 * relu function for matrices
 * @param d input matrix
 * @return new matrix changed by the relu function
 */
Matrix activation::relu(const Matrix &d)
{
  Matrix tmp( d.get_rows(), d.get_cols());
  for (int i = 0; i < d.get_rows(); ++i)
  {
    if (d._matrix[i] < 0)
    {
      tmp._matrix[i] = 0;
    }
    else
    {
      tmp._matrix[i] = d._matrix[i];
    }
  }
  return tmp;
}

/**
 * softmax function for matrices
 * @param d input matrix
 * @return new matrix changed by the softmax function
 */
Matrix activation::softmax(const Matrix &m){
  float k = 0;
  Matrix exp_mat(m.get_rows(), m.get_cols());
  for (int i = 0; i < m.get_rows(); ++i)
  {
    for (int j = 0; j < m.get_cols(); ++j)
    {
      k += exp (m._matrix[(i*m.get_cols())+j]);
      exp_mat._matrix[(i*m.get_cols())+j] = exp(m._matrix[(i*m.get_cols())+j]);
    }
  }
  exp_mat = exp_mat * (1/k);
  return exp_mat;
}