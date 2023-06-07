#include "MlpNetwork.h"

//
// Created by אחיקם לוי on 15/12/2022.
//

/**
 * initial the biases and the weights
 * @param weights array of matrix
 * @param biases array of matrix
 */
MlpNetwork::MlpNetwork(const Matrix *weights, const Matrix *biases){
  _weights[0] = weights[0];
  _weights[1] = weights[1];
  _weights[2] = weights[2];
  _weights[3] = weights[3];
  _bias[0] = biases[0];
  _bias[1] = biases[1];
  _bias[2] = biases[2];
  _bias[3] = biases[3];
}

/**
 * run the process of the whole program
 * @param m matrix the input of the first layer
 * @return number object that found
 */
digit MlpNetwork::operator()(const Matrix &m)
{
  digit number;
  number.probability = 0;
  Matrix r_0 (m);
  r_0.vectorize();
  Matrix r_1  = Dense (_weights[0], _bias[0], activation::relu)(r_0);
  Matrix r_2  = Dense (_weights[1], _bias[1], activation::relu)(r_1);
  Matrix r_3  = Dense (_weights[2], _bias[2], activation::relu)(r_2);
  Matrix r_4  = Dense (_weights[3], _bias[3], activation::softmax)(r_3);
  for (int i = 0; i < r_4.get_rows(); ++i)
  {
    for (int j = 0; j < r_4.get_cols (); ++j)
    {
      if (r_4._matrix[(i*r_4.get_cols()) + j] > 0)
      {
        if (r_4._matrix[(i*r_4.get_cols()) + j] > number.probability)
        {
          number.value = i;
          number.probability = r_4._matrix[(i*r_4.get_cols()) + j];
        }
      }
    }
  }
  return number;
}