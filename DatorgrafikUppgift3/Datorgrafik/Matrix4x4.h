/*
 * Copyright (C) 2003 University of Skövde.
 */
/**
 *@brief The Matrix4x4 class represents 4 by 4 matrix.
 *@author Michael Andersson
 *@date 2004-02-04
*/

#ifndef INCLUDED_MATRIX4X4
#define INCLUDED_MATRIX4X4

#include "Matrix3x3.h"

template<typename T>
class Matrix4x4
{ 
public:
  /**
   *@brief This is the Matrix4x4 class default constructor.
  */
  Matrix4x4();

  /**
   *@brief This constructor enables a instance of Matrix4x4 to be initialized using the values pointed to by matrix.
   *@param matrix = A pointer to an array of 16 values of type T.
  */
  explicit Matrix4x4(T* matrix);

  /**
   *@brief This constructor enables a instance of Matrix4x4 to be initialize using 16 parameters.
   *@param m1-m16 = The values to initialize the matrix with.
  */
  Matrix4x4(T m1, T m5, T m9,  T m13, 
            T m2, T m6, T m10, T m14,
            T m3, T m7, T m11, T m15,
            T m4, T m8, T m12, T m16);

  /**
   *@brief This constructor enables a instance of Matrix4x4 to be initialize using a 3x3 matrix.
   *@param matrix = The values to initialize the upper left submatrix with.
  */
  explicit Matrix4x4(const Matrix3x3<T>& matrix);

  /**
   *@brief The data member function returns a pointer to the matrix data. The member function
   *can be used to pass the matrix to APIs such as OpenGL
   *@return A pointer to the matrix data.
  */
  inline const T* data() const;

   /**
   *@brief The data member function returns a pointer to the matrix data. The member function
   *can be used to pass the matrix to APIs such as OpenGL
   *@return A pointer to the matrix data.
  */
  inline T* data();
  
  /**
   *@brief The theTranspose member function returns the tranpose of the matrix.
   *@return The member function returns a new matrix that is the transpose of the matrix that 
   *recieved the message.
  */
  Matrix4x4 theTranspose() const;
  
  /**
   *@brief The transpose member function can be called in order to transpose the matrix.
   *@return The member function returns a reference to the transposed matrix. It's important to remember
   *that calling this member function will alter the original matrix.
  */
  Matrix4x4& transpose();
  
  /**
   *@brief The inverse member fuction returns the inverse of the matrix.
   *@return The member function returns a new matrix that is the inverse of the matrix that
   *recieved the message. If the matrix i a singular (not invertible) matrix the result is the identity matrix.
  */
  Matrix4x4 inverse() const;

  /**
   *@brief The invert member functi can be called in order to invert the matrix.
   *@return The member function returns a reference to the inverted matrix. It's important to remember
   *that calling this member function will alter the original matrix. If the matrix i a singular 
   *(not invertible) matrix the result is the identity matrix.
  */
  Matrix4x4& invert();

  /**
   *@brief The determinant member function computes the determinant of the matrix.
   *
   *If the determinante is not equal to zero the matrix is invertible.
   *@return The determinant of the matrix.
  */
  T determinant() const;
  
  /**
   *@brief The operator+ enables matrix-matrix addition.
   *@param matrix = the right hand side operand.
   *@return The result is a new matrix containing the sum of two matrices.
   */
  Matrix4x4 operator+(const Matrix4x4<T>& matrix) const;

  /**
   *@brief The operator- enables matrix-matrix subtraction.
   *@param matrix = the right hand side operand.
   *@return The result is a new matrix containing the difference between to matrices.
   */
  Matrix4x4 operator-(const Matrix4x4<T>& matrix) const;
  
  /**
   *@brief The operator+= enables matrix-matrix addition.
   *
   *The operator will add the matrix on the right hand side of the operator
   *to the one on the left hand side.
   *@param matrix = the right hand side operand.
   *@return The operator+= returns a reference to matrix containing the sum of the two matrices.
  */
  Matrix4x4<T>& operator+=(const Matrix4x4<T>& matrix);

   /**
   *@brief The operator-= enables matrix-matrix subtraction.
   *
   *The operator will subtract the matrix on the right hand side of the operator
   *from the one on the left hand side.
   *@param matrix = the right hand side operand.
   *@return The operator-= returns a reference to matrix containing the difference between the two matrices.
  */
  Matrix4x4<T>& operator-=(const Matrix4x4<T>& matrix);

   /**
   *@brief The operator*= enables matrix-matrix multiplication.
   *
   *The operator will multiply the matrix on the right hand side of the operator
   *with the one on the left hand side.
   *@param matrix = the right hand side operand.
   *return The operator*= returns a reference to the matrix containing the result from the multiplication.
  */
  Matrix4x4<T>& operator*=(const Matrix4x4<T>& matrix);
  
   /**
   *@brief Operator = makes it possible to assign a 3x3 matrix to a 4x4 matrix.
   *
   *The operator= will assign the 3x3 matrix to the upper left 3x3 matrix of the 4x4 matrix
   *@param matrix = the right hand side operand
   *return The operatorn= a reference to the assigned matrix.
  */
  const Matrix4x4<T>& operator=(const Matrix3x3<T>& matrix);

  /**
   *@brief The operator[] can be used in order to retrieve a specific matrix element.
   *
   *@param i = the index of the matrix element
   *return The operator[] returns a reference to the i'th matrix element.
  */
  inline T& operator[](unsigned int i);

   /**
   *@brief The operator[] can be used in order to retrieve a specific matrix element.
   *
   *@param i = the index of the matrix element
   *return The operator[] returns a reference to the i'th matrix element.
  */
  inline const T& operator[](unsigned int i) const;

  /**
   *@brief The assign member function can be used in order to set the entires of a matrix.
   *@param m1-m16 = The entry values of the matrix.
   *@return The member function returns a reference to the matrix.
   */
  Matrix4x4<T>& assign(T m1, T m5, T m9,  T m13, 
		    T m2, T m6, T m10, T m14,
		    T m3, T m7, T m11, T m15,
		    T m4, T m8, T m12, T m16);


  /**
   *@brief The static member identity contains the identity matrix.
  */
  static const Matrix4x4<T> identity;
  
 private:
  T m_matrix[16];
};

typedef Matrix4x4<float> Matrix4x4f;
typedef Matrix4x4<double> Matrix4x4d;

template <typename T>
const Matrix4x4<T> Matrix4x4<T>::identity;

template <typename T>
Matrix4x4<T> operator*(T factor, const Matrix4x4<T>& matrix)
{
  return Matrix4x4<T>(matrix[0]*factor, matrix[4]*factor, matrix[8]*factor, matrix[12]*factor, 
		      matrix[1]*factor, matrix[5]*factor, matrix[9]*factor, matrix[13]*factor, 
		      matrix[2]*factor, matrix[6]*factor, matrix[10]*factor, matrix[14]*factor, 
		      matrix[3]*factor, matrix[7]*factor, matrix[11]*factor, matrix[15]*factor);
}

template <typename T>
Matrix4x4<T> operator*(const Matrix4x4<T>& matrix, T factor)
{
  return factor*matrix;
}

template <typename T>
Matrix4x4<T> operator*(const Matrix4x4<T>& left, const Matrix4x4<T>& right)
{
  return Matrix4x4<T>(left[0]*right[0]+left[4]*right[1]+left[8]*right[2]+left[12]*right[3],
		      left[0]*right[4]+left[4]*right[5]+left[8]*right[6]+left[12]*right[7],
		      left[0]*right[8]+left[4]*right[9]+left[8]*right[10]+left[12]*right[11],
		      left[0]*right[12]+left[4]*right[13]+left[8]*right[14]+left[12]*right[15],
		      
		      left[1]*right[0]+left[5]*right[1]+left[9]*right[2]+left[13]*right[3],
		      left[1]*right[4]+left[5]*right[5]+left[9]*right[6]+left[13]*right[7],
		      left[1]*right[8]+left[5]*right[9]+left[9]*right[10]+left[13]*right[11],
		      left[1]*right[12]+left[5]*right[13]+left[9]*right[14]+left[13]*right[15],
		      
		      left[2]*right[0]+left[6]*right[1]+left[10]*right[2]+left[14]*right[3],
		      left[2]*right[4]+left[6]*right[5]+left[10]*right[6]+left[14]*right[7],
		      left[2]*right[8]+left[6]*right[9]+left[10]*right[10]+left[14]*right[11],
		      left[2]*right[12]+left[6]*right[13]+left[10]*right[14]+left[14]*right[15],

		      left[3]*right[0]+left[7]*right[1]+left[11]*right[2]+left[15]*right[3],
		      left[3]*right[4]+left[7]*right[5]+left[11]*right[6]+left[15]*right[7],
		      left[3]*right[8]+left[7]*right[9]+left[11]*right[10]+left[15]*right[11],
		      left[3]*right[12]+left[7]*right[13]+left[11]*right[14]+left[15]*right[15]);
  
}

template <typename T>
Matrix4x4<T>::Matrix4x4()
{
  memset(m_matrix, 0, 16*sizeof(T));
  m_matrix[0] = m_matrix[5] = m_matrix[10] = m_matrix[15] = 1.0f;
}

template <typename T>
Matrix4x4<T>::Matrix4x4(T* matrix)
{
  memcpy(m_matrix, matrix, 16*sizeof(T));
}

template <typename T>
Matrix4x4<T>::Matrix4x4(T m1, T m5, T m9,  T m13, 
	  T m2, T m6, T m10, T m14,
	  T m3, T m7, T m11, T m15,
	  T m4, T m8, T m12, T m16)
{
  m_matrix[0] = m1;
  m_matrix[1] = m2;
  m_matrix[2] = m3;
  m_matrix[3] = m4;
  m_matrix[4] = m5;
  m_matrix[5] = m6;
  m_matrix[6] = m7;
  m_matrix[7] = m8;
  m_matrix[8] = m9;
  m_matrix[9] = m10;
  m_matrix[10] = m11;
  m_matrix[11] = m12;
  m_matrix[12] = m13;
  m_matrix[13] = m14;
  m_matrix[14] = m15;
  m_matrix[15] = m16;
}

template <typename T>
Matrix4x4<T>::Matrix4x4(const Matrix3x3<T>& matrix)
{
    *this = matrix;
}

template <typename T>
inline const T* Matrix4x4<T>::data() const
{
  return m_matrix;
}

template <typename T>
inline T* Matrix4x4<T>::data()
{
  return m_matrix;
}

template <typename T>
Matrix4x4<T> Matrix4x4<T>::theTranspose() const
{
  return Matrix4x4<T>(m_matrix[0], m_matrix[1], m_matrix[2], m_matrix[3],
		      m_matrix[4], m_matrix[5], m_matrix[6], m_matrix[7], 
		      m_matrix[8], m_matrix[9], m_matrix[10], m_matrix[11], 
		      m_matrix[12], m_matrix[13], m_matrix[14], m_matrix[15]);
}

template <typename T>
Matrix4x4<T>& Matrix4x4<T>::transpose()
{
  T result[16];
  result[0] = m_matrix[0];
  result[1] = m_matrix[4];
  result[2] = m_matrix[8];
  result[3] = m_matrix[12];
  result[4] = m_matrix[1];
  result[5] = m_matrix[5];
  result[6] = m_matrix[9];
  result[7] = m_matrix[13];
  result[8] = m_matrix[2];
  result[9] = m_matrix[6];
  result[10] = m_matrix[10];
  result[11] = m_matrix[14];
  result[12] = m_matrix[3];
  result[13] = m_matrix[7];
  result[14] = m_matrix[11];
  result[15] = m_matrix[15];
  memcpy(m_matrix, result, 16*sizeof(T));
  return *this;
}

template <typename T>
Matrix4x4<T> Matrix4x4<T>::inverse() const
{
  T det;
  det = determinant();
  
  if(det > -0.0005f && det < 0.0005f)
    return Matrix4x4<T>::identity;
  else{
    T invDet = 1.0f/det;
    Matrix3x3<T> subMatrix;
    T result[16];
    
    subMatrix.assign(m_matrix[5], m_matrix[9], m_matrix[13],
		  m_matrix[6], m_matrix[10], m_matrix[14],
		  m_matrix[7], m_matrix[11], m_matrix[15]);
    
    result[0] = subMatrix.determinant()*invDet;
    
    subMatrix.assign(m_matrix[1], m_matrix[9], m_matrix[13],
		  m_matrix[2], m_matrix[10], m_matrix[14],
		  m_matrix[3], m_matrix[11], m_matrix[15]);
    
    result[1] = -subMatrix.determinant()*invDet;
    
    subMatrix.assign(m_matrix[1], m_matrix[5], m_matrix[13],
		  m_matrix[2], m_matrix[6], m_matrix[14],
		  m_matrix[3], m_matrix[7], m_matrix[15]);
    
    result[2] = subMatrix.determinant()*invDet;
    
    subMatrix.assign(m_matrix[1], m_matrix[5], m_matrix[9],
		  m_matrix[2], m_matrix[6], m_matrix[10],
		  m_matrix[3], m_matrix[7], m_matrix[11]);
    
    result[3] = -subMatrix.determinant()*invDet;
    
    subMatrix.assign(m_matrix[4], m_matrix[8], m_matrix[12],
		  m_matrix[6], m_matrix[10], m_matrix[14],
		  m_matrix[7], m_matrix[11], m_matrix[15]);
    
    result[4] = -subMatrix.determinant()*invDet;
    
    subMatrix.assign(m_matrix[0], m_matrix[8], m_matrix[12],
		  m_matrix[2], m_matrix[10], m_matrix[14],
		  m_matrix[3], m_matrix[11], m_matrix[15]);
    
    result[5] = subMatrix.determinant()*invDet;
    
    subMatrix.assign(m_matrix[0], m_matrix[4], m_matrix[12],
		  m_matrix[2], m_matrix[6], m_matrix[14],
		  m_matrix[3], m_matrix[7], m_matrix[15]);
    
    result[6] = -subMatrix.determinant()*invDet;
    
    subMatrix.assign(m_matrix[0], m_matrix[4], m_matrix[8],
		  m_matrix[2], m_matrix[6], m_matrix[10],
		  m_matrix[3], m_matrix[7], m_matrix[11]);
    
    result[7] = subMatrix.determinant()*invDet;
    
    subMatrix.assign(m_matrix[4], m_matrix[8], m_matrix[12],
		  m_matrix[5], m_matrix[9], m_matrix[13],
		  m_matrix[7], m_matrix[11], m_matrix[15]);
    
    result[8] = subMatrix.determinant()*invDet;
    
    subMatrix.assign(m_matrix[0], m_matrix[8], m_matrix[12],
		  m_matrix[1], m_matrix[9], m_matrix[13],
		  m_matrix[3], m_matrix[11], m_matrix[15]);
    
    result[9] = -subMatrix.determinant()*invDet;
    
    subMatrix.assign(m_matrix[0], m_matrix[4], m_matrix[12],
		  m_matrix[1], m_matrix[5], m_matrix[13],
		  m_matrix[3], m_matrix[7], m_matrix[15]);
    
    result[10] = subMatrix.determinant()*invDet;
    
    subMatrix.assign(m_matrix[0], m_matrix[4], m_matrix[8],
		  m_matrix[1], m_matrix[5], m_matrix[9],
		  m_matrix[3], m_matrix[7], m_matrix[11]);
    
    result[11] = -subMatrix.determinant()*invDet;
    
    subMatrix.assign(m_matrix[4], m_matrix[8], m_matrix[12],
		  m_matrix[5], m_matrix[9], m_matrix[13],
		  m_matrix[6], m_matrix[10], m_matrix[14]);
    
    result[12] = -subMatrix.determinant()*invDet;
    
    subMatrix.assign(m_matrix[0], m_matrix[8], m_matrix[12],
		  m_matrix[1], m_matrix[9], m_matrix[13],
		  m_matrix[2], m_matrix[10], m_matrix[14]);
    
    result[13] = subMatrix.determinant()*invDet;
    
    subMatrix.assign(m_matrix[0], m_matrix[4], m_matrix[12],
		  m_matrix[1], m_matrix[5], m_matrix[13],
		  m_matrix[2], m_matrix[6], m_matrix[14]);
    
    result[14] = -subMatrix.determinant()*invDet;
    
    subMatrix.assign(m_matrix[0], m_matrix[4], m_matrix[8],
		  m_matrix[1], m_matrix[5], m_matrix[9],
		  m_matrix[2], m_matrix[6], m_matrix[10]);
    
    result[15] = subMatrix.determinant()*invDet;
    
    return Matrix4x4<T>(result);
  }
}

template <typename T>
Matrix4x4<T>& Matrix4x4<T>::invert()
{
  T det;
  det = determinant();
  
  if(det > -0.0005f && det < 0.0005f){
    //Is this really correct?
    memcpy(m_matrix, identity.data(), 16*sizeof(T));
    return *this;
  }
  else{
    float invDet = 1.0f/det;
    T result[16];
    Matrix3x3<T> subMatrix;
  
    subMatrix.assign(m_matrix[5], m_matrix[9], m_matrix[13],
		  m_matrix[6], m_matrix[10], m_matrix[14],
		  m_matrix[7], m_matrix[11], m_matrix[15]);
    
    result[0] = subMatrix.determinant()*invDet;
    
    subMatrix.assign(m_matrix[1], m_matrix[9], m_matrix[13],
		  m_matrix[2], m_matrix[10], m_matrix[14],
		  m_matrix[3], m_matrix[11], m_matrix[15]);
    
    result[1] = -subMatrix.determinant()*invDet;
    
    subMatrix.assign(m_matrix[1], m_matrix[5], m_matrix[13],
		  m_matrix[2], m_matrix[6], m_matrix[14],
		  m_matrix[3], m_matrix[7], m_matrix[15]);
    
    result[2] = subMatrix.determinant()*invDet;
    
    subMatrix.assign(m_matrix[1], m_matrix[5], m_matrix[9],
		  m_matrix[2], m_matrix[6], m_matrix[10],
		  m_matrix[3], m_matrix[7], m_matrix[11]);
    
    result[3] = -subMatrix.determinant()*invDet;
    
    subMatrix.assign(m_matrix[4], m_matrix[8], m_matrix[12],
		  m_matrix[6], m_matrix[10], m_matrix[14],
		  m_matrix[7], m_matrix[11], m_matrix[15]);
    
    result[4] = -subMatrix.determinant()*invDet;
    
    subMatrix.assign(m_matrix[0], m_matrix[8], m_matrix[12],
		  m_matrix[2], m_matrix[10], m_matrix[14],
		  m_matrix[3], m_matrix[11], m_matrix[15]);
    
    result[5] = subMatrix.determinant()*invDet;
    
    subMatrix.assign(m_matrix[0], m_matrix[4], m_matrix[12],
		  m_matrix[2], m_matrix[6], m_matrix[14],
		  m_matrix[3], m_matrix[7], m_matrix[15]);
    
    result[6] = -subMatrix.determinant()*invDet;
    
    subMatrix.assign(m_matrix[0], m_matrix[4], m_matrix[8],
		  m_matrix[2], m_matrix[6], m_matrix[10],
		  m_matrix[3], m_matrix[7], m_matrix[11]);
    
    result[7] = subMatrix.determinant()*invDet;
    
    subMatrix.assign(m_matrix[4], m_matrix[8], m_matrix[12],
		  m_matrix[5], m_matrix[9], m_matrix[13],
		  m_matrix[7], m_matrix[11], m_matrix[15]);
    
    result[8] = subMatrix.determinant()*invDet;
    
    subMatrix.assign(m_matrix[0], m_matrix[8], m_matrix[12],
		  m_matrix[1], m_matrix[9], m_matrix[13],
		  m_matrix[3], m_matrix[11], m_matrix[15]);
    
    result[9] = -subMatrix.determinant()*invDet;
    
    subMatrix.assign(m_matrix[0], m_matrix[4], m_matrix[12],
		  m_matrix[1], m_matrix[5], m_matrix[13],
		  m_matrix[3], m_matrix[7], m_matrix[15]);
    
    result[10] = subMatrix.determinant()*invDet;
    
    subMatrix.assign(m_matrix[0], m_matrix[4], m_matrix[8],
		  m_matrix[1], m_matrix[5], m_matrix[9],
		  m_matrix[3], m_matrix[7], m_matrix[11]);
    
    result[11] = -subMatrix.determinant()*invDet;
    
    subMatrix.assign(m_matrix[4], m_matrix[8], m_matrix[12],
		  m_matrix[5], m_matrix[9], m_matrix[13],
		  m_matrix[6], m_matrix[10], m_matrix[14]);
    
    result[12] = -subMatrix.determinant()*invDet;
    
    subMatrix.assign(m_matrix[0], m_matrix[8], m_matrix[12],
		  m_matrix[1], m_matrix[9], m_matrix[13],
		  m_matrix[2], m_matrix[10], m_matrix[14]);
    
    result[13] = subMatrix.determinant()*invDet;
    
    subMatrix.assign(m_matrix[0], m_matrix[4], m_matrix[12],
		  m_matrix[1], m_matrix[5], m_matrix[13],
		  m_matrix[2], m_matrix[6], m_matrix[14]);
    
    result[14] = -subMatrix.determinant()*invDet;
    
    subMatrix.assign(m_matrix[0], m_matrix[4], m_matrix[8],
		  m_matrix[1], m_matrix[5], m_matrix[9],
		  m_matrix[2], m_matrix[6], m_matrix[10]);
    
    result[15] = subMatrix.determinant()*invDet;
    
    memcpy(m_matrix, result, 16*sizeof(T));
    return *this;
  }
}

template <typename T>
T Matrix4x4<T>::determinant() const
{
  Matrix3x3<T> subMatrix;
  T det, result = 0.0;

  subMatrix.assign(m_matrix[5], m_matrix[9], m_matrix[13],
		m_matrix[6], m_matrix[10], m_matrix[14],
		m_matrix[7], m_matrix[11], m_matrix[15]);

  det = subMatrix.determinant();
  result += m_matrix[0]*det;

  subMatrix.assign(m_matrix[1], m_matrix[9], m_matrix[13],
		m_matrix[2], m_matrix[10], m_matrix[14],
		m_matrix[3], m_matrix[11], m_matrix[15]);
  
  det = subMatrix.determinant();
  result += -m_matrix[4]*det;

  subMatrix.assign(m_matrix[1], m_matrix[5], m_matrix[13],
		m_matrix[2], m_matrix[6], m_matrix[14],
		m_matrix[3], m_matrix[7], m_matrix[15]);

  det = subMatrix.determinant();
  result += m_matrix[8]*det;
  
  subMatrix.assign(m_matrix[1], m_matrix[5], m_matrix[9],
		m_matrix[2], m_matrix[6], m_matrix[10],
		m_matrix[3], m_matrix[7], m_matrix[11]);
  
  det = subMatrix.determinant();
  result += -m_matrix[12]*det;
  return result;
}

template<typename T>
Matrix4x4<T> Matrix4x4<T>::operator+(const Matrix4x4<T>& matrix) const
{
  return Matrix4x4<T>(m_matrix[0]+matrix[0], m_matrix[4]+matrix[4], m_matrix[8]+matrix[8], m_matrix[12]+matrix[12],
		      m_matrix[1]+matrix[1], m_matrix[5]+matrix[5], m_matrix[9]+matrix[9], m_matrix[13]+matrix[13],
		      m_matrix[2]+matrix[2], m_matrix[6]+matrix[6], m_matrix[10]+matrix[10], m_matrix[14]+matrix[14],
		      m_matrix[3]+matrix[3], m_matrix[7]+matrix[7], m_matrix[11]+matrix[11], m_matrix[15]+matrix[15]);
		      
}

template<typename T>
Matrix4x4<T> Matrix4x4<T>::operator-(const Matrix4x4<T>& matrix) const
{
  return Matrix4x4<T>(m_matrix[0]-matrix[0], m_matrix[4]-matrix[4], m_matrix[8]-matrix[8], m_matrix[12]-matrix[12],
		      m_matrix[1]-matrix[1], m_matrix[5]-matrix[5], m_matrix[9]-matrix[9], m_matrix[13]-matrix[13],
		      m_matrix[2]-matrix[2], m_matrix[6]-matrix[6], m_matrix[10]-matrix[10], m_matrix[14]-matrix[14],
		      m_matrix[3]-matrix[3], m_matrix[7]-matrix[7], m_matrix[11]-matrix[11], m_matrix[15]-matrix[15]);
}

template <typename T>
Matrix4x4<T>& Matrix4x4<T>::operator+=(const Matrix4x4<T>& matrix)
{
  m_matrix[0] += matrix[0];
  m_matrix[1] += matrix[1];
  m_matrix[2] += matrix[2];
  m_matrix[3] += matrix[3];
  m_matrix[4] += matrix[4];
  m_matrix[5] += matrix[5];
  m_matrix[6] += matrix[6];
  m_matrix[7] += matrix[7];
  m_matrix[8] += matrix[8];
  m_matrix[9] += matrix[9];
  m_matrix[10] += matrix[10];
  m_matrix[11] += matrix[11];
  m_matrix[12] += matrix[12];
  m_matrix[13] += matrix[13];
  m_matrix[14] += matrix[14];
  m_matrix[15] += matrix[15];
  return *this;
}

template <typename T>
Matrix4x4<T>& Matrix4x4<T>::operator-=(const Matrix4x4<T>& matrix)
{
  m_matrix[0] -= matrix[0];
  m_matrix[1] -= matrix[1];
  m_matrix[2] -= matrix[2];
  m_matrix[3] -= matrix[3];
  m_matrix[4] -= matrix[4];
  m_matrix[5] -= matrix[5];
  m_matrix[6] -= matrix[6];
  m_matrix[7] -= matrix[7];
  m_matrix[8] -= matrix[8];
  m_matrix[9] -= matrix[9];
  m_matrix[10] -= matrix[10];
  m_matrix[11] -= matrix[11];
  m_matrix[12] -= matrix[12];
  m_matrix[13] -= matrix[13];
  m_matrix[14] -= matrix[14];
  m_matrix[15] -= matrix[15];
  return *this;
}

template <typename T>
Matrix4x4<T>& Matrix4x4<T>::operator*=(const Matrix4x4<T>& matrix)
{
  T result[16];
  result[0] = m_matrix[0]*matrix[0]+m_matrix[4]*matrix[1]+m_matrix[8]*matrix[2]+m_matrix[12]*matrix[3];
  result[1] = m_matrix[1]*matrix[0]+m_matrix[5]*matrix[1]+m_matrix[9]*matrix[2]+m_matrix[13]*matrix[3];
  result[2] = m_matrix[2]*matrix[0]+m_matrix[6]*matrix[1]+m_matrix[10]*matrix[2]+m_matrix[14]*matrix[3];
  result[3] = m_matrix[3]*matrix[0]+m_matrix[7]*matrix[1]+m_matrix[11]*matrix[2]+m_matrix[15]*matrix[3];

  result[4] = m_matrix[0]*matrix[4]+m_matrix[4]*matrix[5]+m_matrix[8]*matrix[6]+m_matrix[12]*matrix[7];
  result[5] = m_matrix[1]*matrix[4]+m_matrix[5]*matrix[5]+m_matrix[9]*matrix[6]+m_matrix[13]*matrix[7];
  result[6] = m_matrix[2]*matrix[4]+m_matrix[6]*matrix[5]+m_matrix[10]*matrix[6]+m_matrix[14]*matrix[7];
  result[7] = m_matrix[3]*matrix[4]+m_matrix[7]*matrix[5]+m_matrix[11]*matrix[6]+m_matrix[15]*matrix[7];

  result[8] = m_matrix[0]*matrix[8]+m_matrix[4]*matrix[9]+m_matrix[8]*matrix[10]+m_matrix[12]*matrix[11];
  result[9] = m_matrix[1]*matrix[8]+m_matrix[5]*matrix[9]+m_matrix[9]*matrix[10]+m_matrix[13]*matrix[11];
  result[10] = m_matrix[2]*matrix[8]+m_matrix[6]*matrix[9]+m_matrix[10]*matrix[10]+m_matrix[14]*matrix[11];
  result[11] = m_matrix[3]*matrix[8]+m_matrix[7]*matrix[9]+m_matrix[11]*matrix[10]+m_matrix[15]*matrix[11];

  result[12] = m_matrix[0]*matrix[12]+m_matrix[4]*matrix[13]+m_matrix[8]*matrix[14]+m_matrix[12]*matrix[15];
  result[13] = m_matrix[1]*matrix[12]+m_matrix[5]*matrix[13]+m_matrix[9]*matrix[14]+m_matrix[13]*matrix[15];
  result[14] = m_matrix[2]*matrix[12]+m_matrix[6]*matrix[13]+m_matrix[10]*matrix[14]+m_matrix[14]*matrix[15];
  result[15] = m_matrix[3]*matrix[12]+m_matrix[7]*matrix[13]+m_matrix[11]*matrix[14]+m_matrix[15]*matrix[15];
  memcpy(m_matrix, result, 16*sizeof(T));
  return *this;
}

template<typename T>
const Matrix4x4<T>& Matrix4x4<T>::operator=(const Matrix3x3<T>& matrix)
{
    m_matrix[0] = matrix[0];
    m_matrix[1] = matrix[1];
    m_matrix[2] = matrix[2];
    m_matrix[3] = static_cast<T>(0);
    
    m_matrix[4] = matrix[3];
    m_matrix[5] = matrix[4];
    m_matrix[6] = matrix[5];
    m_matrix[7] = static_cast<T>(0);
    
    m_matrix[8] = matrix[6];
    m_matrix[9] = matrix[7];
    m_matrix[10] = matrix[8];
    m_matrix[11] = static_cast<T>(0);
    
    m_matrix[12] = static_cast<T>(0);
    m_matrix[13] = static_cast<T>(0);
    m_matrix[14] = static_cast<T>(0);
    m_matrix[15] = static_cast<T>(1);
    return *this;
}

template <typename T>
inline T& Matrix4x4<T>::operator[](unsigned int i)
{
  return m_matrix[i];
}

template <typename T>
inline const T& Matrix4x4<T>::operator[](unsigned int i) const
{
  return m_matrix[i];
}


template <typename T>
Matrix4x4<T>& Matrix4x4<T>::assign(T m1, T m5, T m9,  T m13, 
				T m2, T m6, T m10, T m14,
				T m3, T m7, T m11, T m15,
				T m4, T m8, T m12, T m16)
{
  m_matrix[0] = m1;
  m_matrix[1] = m2;
  m_matrix[2] = m3;
  m_matrix[3] = m4;
  m_matrix[4] = m5;
  m_matrix[5] = m6;
  m_matrix[6] = m7;
  m_matrix[7] = m8;
  m_matrix[8] = m9;
  m_matrix[9] = m10;
  m_matrix[10] = m11;
  m_matrix[11] = m12;
  m_matrix[12] = m13;
  m_matrix[13] = m14;
  m_matrix[14] = m15;
  m_matrix[15] = m16;
  return *this;
}

#endif
