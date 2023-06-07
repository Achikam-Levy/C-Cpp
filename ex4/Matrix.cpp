//
// Created by אחיקם לוי on 15/12/2022.
//
# include "Matrix.h"

using std::ostream;  using std::istream;  using std::endl;

/**
 * constructor with parameters
 * @param rows rows number
 * @param cols columns number
 */
Matrix::Matrix (int rows, int cols) : _cols(cols) , _rows(rows)
{
  if (rows < 1 || cols < 1)
  {
    throw std::domain_error ("the values must be grater then 0");
  }
  alloc_space (rows, cols);
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      _matrix[(i*_cols) + j] =  0;
    }
  }
}

/**
 * empty constructor
 */
Matrix::Matrix () : _cols(1) , _rows(1)
{
  alloc_space (_rows, _cols);
  _matrix[0] = 0;
}


/**
 * constructor with matrix parameter
 * @param m the matrix parameter
 */
Matrix::Matrix (const Matrix& m) : _cols(m.get_cols()) , _rows(m.get_rows())
{
  alloc_space (_rows, _cols);
  for (int i = 0; i < _rows; ++i)
  {
    for (int j = 0; j < _cols; ++j)
    {
      _matrix[(i*_cols) + j] = m._matrix[(i*_cols) + j];
    }
  }
}

/**
 *
 * @return number of rows
 */
int Matrix::get_rows()const{
  return _rows;
}

/**
 *
 * @return number of columns
 */
int Matrix::get_cols()const{
  return _cols;
}

/**
 * transpose the matrix
 * @return the same matrix transposed
 */
Matrix& Matrix::transpose()
{
  auto *new_matrix = new float[_cols * _rows];;
  for (int i = 0; i < _rows; ++i)
  {
    for (int j = 0; j < _cols; ++j)
    {
      new_matrix[(j*_rows) + i] = _matrix[(i*_cols) + j];
    }
  }
  std::swap (_rows, _cols);
  float *tmp = _matrix;
  _matrix = new_matrix;
  delete[] tmp;
  return *this;
}

/**
 * change a matrix to a vector by rows
 * @return the vectorize matrix
 */
Matrix& Matrix::vectorize()
{
  int k = _cols*_rows;
  _rows = k;
  _cols = 1;
  return *this;
}

/**
 * print the matrix
 */
void Matrix::plain_print() const{
  for (int i = 0; i < _rows; ++i)
  {
    for (int j = 0; j < _cols; ++j)
    {
      std::cout << _matrix[(i*_cols) + j] << " " ;
    }
    std::cout << "\n";
  }
}

/**
 * compute a dot product of two matrices
 * @param m a matrix
 * @return dot product of two matrices
 */
Matrix Matrix::dot(const Matrix &m) const{
  if( _cols != m.get_cols() || _rows != m.get_rows())
  {
    throw std::domain_error( "dot the matrices domain must much");
  }
  Matrix m_dot(_rows, _cols);
  for(int i = 0; i < _rows; ++i)
  {
    for (int j = 0; j < _cols; ++j)
    {
      m_dot(i,j) = _matrix[(i * _cols) + j] * m._matrix[(i * _cols) + j];
    }
  }
  return m_dot;
}

/**
 * compute the aum of all the matrix indexes
 * @return float k of the sum
 */
float Matrix::sum() const
{
  float k = 0;
  for (int i = 0; i < _rows*_cols; ++i)
  {
      k += _matrix[i];
  }
  return k;
}

/**
 *  compute the norm of the matrix
 * @return float k of the norm
 */
float Matrix::norm() const{
  double k = 0;
  for (int i = 0; i < _rows*_cols; ++i)
  {
    k += pow(_matrix[i], 2);
  }
  return float (sqrt (k));
}

/**
 * fined the index of the max val in the matrix
 * @return int c - the index
 */
int Matrix::argmax() const{
  double k = 0;
  int c = -1;
  for (int i = 0; i < _rows*_cols; ++i)
  {
    if(_matrix[i]> k)
    {
      k = _matrix[i];
      c = i;
    }
  }
  return  c;
}

/**
 * += for matrices
 * @param m parameter matrix
 * @return the same matrix changed
 */
Matrix& Matrix::operator+=(const Matrix &m){
  if(_cols != m.get_cols() || _rows != m.get_rows())
  {
    throw std::domain_error( "operator += of the matrices domain must much");
  }
  for (int i = 0; i < _rows*_cols; ++i)
  {
    _matrix[i] += m._matrix[i];
  }
  return *this;
}

/**
 * + for matrices
 * @param m parameter matrix
 * @return a new matrix of the sum
 */
Matrix Matrix::operator+(const Matrix &m) const{
  if(_cols != m.get_cols() || _rows != m.get_rows())
  {
    throw std::domain_error( "operator+ the matrices domain must much");
  }
  Matrix tmp(*this);
  for (int i = 0; i < _rows*_cols; ++i)
  {
    tmp._matrix[i] += m._matrix[i];
  }
  return tmp;
}

/**
 * = for matrices
 * @param m parameter matrix
 * @return the same matrix changed to the parameter matrix
 */
Matrix& Matrix::operator=(const Matrix &m)
{
  if (this == &m)
  {
    return *this;
  }
  if (_rows != m.get_rows() || _cols != m.get_cols())
  {
    delete[] _matrix;
    _rows = m.get_rows();
    _cols = m.get_cols();
    alloc_space (_rows, _cols);
  }
  for (int i = 0; i < _rows*_cols; ++i)
  {
    _matrix[i] = m._matrix[i];
  }
  return *this;
}

/**
 * * for matrices
 * @param m parameter matrix
 * @return a new matrix of the matrices product
 */
Matrix Matrix::operator*(const Matrix &m)const
{
  if(_cols != m.get_rows())
  {
    throw std::domain_error( "operator* the matrices domain must much");
  }
  Matrix tmp(_rows, m.get_cols());

  for(int i = 0; i < _rows; ++i)
  {
    for (int j = 0; j < m._cols; ++j)
    {
      for (int k = 0; k < _cols; ++k)
      {
        tmp._matrix[(i*tmp._cols) + j] += _matrix[(i*_cols) + k] *
                                          m._matrix[(k*m._cols) + j];
      }
    }
  }
  return tmp;
}

/**
 * scalar mult with scalar parameter
 * @param c scalar
 * @return a new matrix of the matrix*c product
 */
Matrix Matrix::operator*(float c)const
{
  Matrix tmp(*this);
  for (int i = 0; i < _rows*_cols; ++i)
  {
    tmp._matrix[i] *= c;
  }
  return tmp;
}

/**
 * scalar mult scalar and matrix parameter
 * @param c scalar
 * @param m matrix
 * @return a new matrix of the matrix*c product
 */
Matrix operator*(float c,Matrix &m)
{
  Matrix tmp(m);
  for (int i = 0; i < m.get_rows()*m.get_cols(); ++i)
  {
    tmp._matrix[i] *= c;
  }
  return tmp;
}

/**
 * recives two numbers
 * @param i index rows
 * @param j index cols
 * @return the value in the given location
 */
float Matrix::operator()(int i, int j)const
{
  if (j < 0 || j >= _cols || i < 0 || i >= _rows)
  {
    throw std::out_of_range ( "index is out of range");
  }
  return _matrix[(i*_cols)+j];
}

/**
 * same as above but not const
 */
float &Matrix::operator()(int i, int j)
{if (j < 0 || j >= _cols || i < 0 || i >= _rows)
  {
    throw std::out_of_range ( "index is out of range");
  }
  return _matrix[(i*_cols)+j];
}

/**
 * recives one number
 * @param i the location index
 * @return the value in the given location
 */
float &Matrix::operator[]( int i)
{
  if ( i < 0 || i > (_rows*_cols))
    {
      throw std::out_of_range ( "index is out of range");
    }
  return _matrix[i];
}

/**
 * same as above but const
 */
float Matrix::operator[]( int i) const
{
  if ( i < 0 || i > _rows*_cols)
  {
    throw std::out_of_range ( "index is out of range");
  }
  return _matrix[i];
}

/**
 * print the number that recognized by the main function
 * @param os istream object
 * @param m matrix
 * @return os
 */
std::ostream &operator<< (ostream &os, const Matrix &m){
  for (int i = 0; i < m.get_rows(); ++i)
  {
    for (int j = 0; j < m.get_cols(); ++j)
    {
      if (m(i, j) > MIN_DREW)
      {
        std::cout << "**" ;
      }
      else
      {
        std::cout << "  " ;
      }
    }
    std::cout << "\n" ;
  }
  return os;
}

/**
 * load a binary image into a matrix
 * @param is istream object
 * @param m matrix to load
 * @return is
 */
std::istream &operator >> (std::istream &is, Matrix &m){
  if (is.fail ())
  {
    throw std::runtime_error ("the file not opened");
  }
  is.seekg (0, std::ios_base::end);
  unsigned long long int last = is.tellg ();
  is.seekg (0, std::ios_base::beg);
  if (last != m.get_cols () * m.get_rows () * sizeof(float))
  {
    throw std::runtime_error ("size of the matrix not mach to the image");
  }
  for (int i = 0; i < m.get_rows()*m.get_cols(); ++i)
  {
      is.read ((char *) &m._matrix[i], sizeof (float));
  }
  return is;
}

/**
 * destructor
 */
Matrix::~Matrix()
{
  delete[] _matrix;
}

/**
 * allocate space for new matrix
 * @param rows rows number
 * @param cols columns number
 */
void Matrix::alloc_space(int rows, int cols)
{
  _matrix = new float[rows * cols];
}
