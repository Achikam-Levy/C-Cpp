#include <string>
#include <iostream>
#include <fstream>

# include <cmath>
using std::string;
using std::cout;
using std::cin;
using std::endl;
#ifndef MATRIX_H
#define MATRIX_H
#define MIN_DREW 0.1

class Matrix {
 private:
  int _cols;
  int _rows;
 public:
  float *_matrix;
  void alloc_space(int r, int c);

   /**
   * @struct Dims
   * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
   */
  struct dims {
      int rows, cols;
  };
  Matrix (int rows, int cols);
  Matrix ();
  Matrix (const Matrix &m);
  int get_rows() const;
  int get_cols()const;
  Matrix & transpose();
  Matrix & vectorize();
  void plain_print() const;
  Matrix dot(const Matrix &m) const;
  float sum() const;
  float norm() const;
  int argmax() const;
  Matrix& operator+=(const Matrix &m);
  Matrix& operator=(const Matrix &m);
  Matrix operator+(const Matrix &m) const;
  Matrix operator*(const Matrix &m) const;
  friend Matrix operator*( float c, Matrix &m);
  Matrix operator*(float c) const;
  float &operator()(int i, int j);
  float operator()(int i, int j)const;
  float &operator[]( int i) ;
  float operator[]( int i) const;
  friend std::ostream &operator<< (std::ostream &is, const Matrix &m);
  friend std::istream &operator>> (std::istream &is, Matrix &m);
  ~Matrix();
};



#endif //MATRIX_H
