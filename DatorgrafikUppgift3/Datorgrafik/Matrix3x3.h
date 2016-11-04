/*
 * Copyright (C) 2003 University of Skövde.
 */

#ifndef INCLUDED_MATRIX3X3
#define INCLUDED_MATRIX3X3

#include <cstring>

/**
 *\brief The Matrix3x3 class represents 3 by 3 matrix.
 *\author Michael Andersson
 *\date 2004-02-04
*/
template<typename T>
class Matrix3x3
{
 public:

	/**
	*\brief This is the Matrix3x3 class default constructor. The constructor will create an identity matrix
	*/
	Matrix3x3();

	/**
	*\brief This constructor enables a instance of Matrix3x3 to be initialized using the values pointed to by matrix.
	*\param matrix = A pointer to an array of 9 values of type T.
	*/
	Matrix3x3(T* matrix);

	/**
	*\brief This constructor enables a instance of Matrix3x3 to be initialize using 9 parameters.
	*\param m1-m9 = The values to initialize the matrix with.
	*/
	Matrix3x3(T m1, T m4, T m7,
			T m2, T m5, T m8,
			T m3, T m6, T m9);
	
	/**
	 *\brief The data member function returns a pointer to the matrix data. The member function
	*can be used to pass the matrix to APIs such as OpenGL
	*\return A pointer to the matrix data.
	*/
	T* data();
	
	/**
	*\brief The data member function returns a pointer to the matrix data. The member function
	*can be used to pass the matrix to APIs such as OpenGL
	 *\return A pointer to the matrix data.
	*/
	const T* data() const;
  
	/**
	*\brief The theTranspose member function returns the tranpose of the matrix.
	*\return The member function returns a new matrix that is the transpose of the matrix that 
	*recieved the message.
	*/
	Matrix3x3 theTranspose() const;
  
	/**
	*\brief The transpose member function can be called in order to transpose the matrix.
	*\return The member function returns a reference to the transposed matrix. It's important to remember
	*that calling this member function will alter the original matrix.
	*/
	Matrix3x3& transpose();
  
	/**
	*\brief The inverse member fuction returns the inverse of the matrix.
	*\return The member function returns a new matrix that is the inverse of the matrix that
	*recieved the message. If the matrix i a singular (not invertible) matrix the result is the identity matrix.
	*/
	Matrix3x3 inverse() const;
	
	/**
	*\brief The invert member functi can be called in order to invert the matrix.
	*\return The member function returns a reference to the inverted matrix. It's important to remember
	*that calling this member function will alter the original matrix. If the matrix i a singular 
	*(not invertible) matrix the result is the identity matrix.
	*/
	Matrix3x3& invert();

	/**
	*\brief The determinant member function computes the determinant of the matrix.
	*
	*If the determinante is not equal to zero the matrix is invertible.
	*\return The determinant of the matrix.
	*/
	T determinant() const;
  
	/**
	*\brief The operator+ enables matrix-matrix addition.
	*\param matrix = the right hand side operand.
	*\return The result is a new matrix containing the sum of two matrices.
	*/
	Matrix3x3 operator+(const Matrix3x3& matrix) const;
	
	/**
	*\brief The operator- enables matrix-matrix subtraction.
	*\param matrix = the right hand side operand.
	*\return The result is a new matrix containing the difference between to matrices.
	*/
	Matrix3x3 operator-(const Matrix3x3& matrix) const;

	/**
	*\brief The operator+= enables matrix-matrix addition.
	*
	*The operator will add the matrix on the right hand side of the operator
	*to the one on the left hand side.
	*\param matrix = the right hand side operand.
	*\return The operator+= returns a reference to matrix containing the sum of the two matrices.
	*/
	Matrix3x3<T>& operator+=(const Matrix3x3& matrix);
	
	/**
	*\brief The operator-= enables matrix-matrix subtraction.
	*
	*The operator will subtract the matrix on the right hand side of the operator
	*from the one on the left hand side.
	*\param matrix = the right hand side operand.
	*\return The operator-= returns a reference to matrix containing the difference between the two matrices.
	*/
	Matrix3x3<T>& operator-=(const Matrix3x3& matrix);
	
	/**
	*\brief The operator*= enables matrix-matrix multiplication.
	*
	*The operator will multiply the matrix on the right hand side of the operator
	*with the one on the left hand side.
	*\param matrix = the right hand side operand.
	*return The operator*= returns a reference to the matrix containing the result from the multiplication.
	*/
	Matrix3x3<T>& operator*=(const Matrix3x3& matrix);
  
	/**
	*\brief The operator[] can be used in order to retrieve a specific matrix element.
	*
	*\param i = the index of the matrix element
	*return The operator[] returns a reference to the i'th matrix element.
	*/
	inline T& operator[](unsigned int i);
  
	/**
	*\brief The operator[] can be used in order to retrieve a specific matrix element.
	*
	*\param i = the index of the matrix element
	*return The operator[] returns a reference to the i'th matrix element.
	*/
	inline const T& operator[](unsigned int i) const;

	/**
	 *\brief The assign member function can be used in order to set the entires of a matrix.
	*\param m1-m19 = The entry values of the matrix.
	*\return The member function returns a reference to the matrix.
	*/
	Matrix3x3<T>& assign(T m1, T m4, T m7,   
						T m2, T m5, T m8,
						T m3, T m6, T m9);

	/**
	*\brief The static member identity contains the identity matrix.
	*/
	static const Matrix3x3<T> identity;
  
 private:
	T m_matrix[9];
};

typedef Matrix3x3<float> Matrix3x3f;
typedef Matrix3x3<double> Matrix3x3d;

/**
	*\brief The operator* makes it possible to multiply a 3x3 matrix by a scalar.
	*\param factor = The scalar to multiply the matrix with.
    *\param matrix = The matrix to multiply.
*/
template<typename T>
Matrix3x3<T> operator*(T factor, const Matrix3x3<T>& matrix);

/**
	*\brief The operator* makes it possible to multiply 3x3 matrices.
	*\param left = The left operand.
    *\param right = The right operand.
*/
template<typename T>
Matrix3x3<T> operator*(const Matrix3x3<T>& left, const Matrix3x3<T>& right);



template<typename T>
const Matrix3x3<T> Matrix3x3<T>::identity;

template<typename T>
Matrix3x3<T> operator*(T factor, const Matrix3x3<T>& matrix)
{
  return Matrix3x3<T>(matrix[0]*factor, matrix[3]*factor, matrix[6]*factor,
		      matrix[1]*factor, matrix[4]*factor, matrix[7]*factor,
		      matrix[2]*factor, matrix[5]*factor, matrix[8]*factor);
}

template<typename T>
Matrix3x3<T> operator*(const Matrix3x3<T>& matrix, T factor)
{
  return factor*matrix;
}

template<typename T>
Matrix3x3<T>::Matrix3x3()
{
  memset(m_matrix, 0, 9*sizeof(T));
  m_matrix[0] = 1.0;
  m_matrix[4] = 1.0;
  m_matrix[8] = 1.0;
}

template<typename T>
Matrix3x3<T>::Matrix3x3(T *matrix)
{
  memcpy(m_matrix, matrix, 9*sizeof(T));
}

template<typename T>
Matrix3x3<T>::Matrix3x3(T m1, T m4, T m7,
			T m2, T m5, T m8,
			T m3, T m6, T m9)
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

}

template<typename T>
T* Matrix3x3<T>::data()
{
  return m_matrix;
}

template<typename T>
const T* Matrix3x3<T>::data() const
{
  return m_matrix;
}

template<typename T>
Matrix3x3<T> Matrix3x3<T>::operator+(const Matrix3x3& mat) const
{
  return Matrix3x3<T>(m_matrix[0]+mat.m_matrix[0], m_matrix[3]+mat.m_matrix[3], m_matrix[6]+mat.m_matrix[6],
		      m_matrix[1]+mat.m_matrix[1], m_matrix[4]+mat.m_matrix[4], m_matrix[7]+mat.m_matrix[7],
		      m_matrix[2]+mat.m_matrix[2], m_matrix[5]+mat.m_matrix[5], m_matrix[8]+mat.m_matrix[8]);
 
    }

template<typename T>
Matrix3x3<T> Matrix3x3<T>::operator-(const Matrix3x3& mat) const
{
  return Matrix3x3<T>(m_matrix[0]-mat.m_matrix[0], m_matrix[3]-mat.m_matrix[3], m_matrix[6]-mat.m_matrix[6],
		      m_matrix[1]-mat.m_matrix[1], m_matrix[4]-mat.m_matrix[4], m_matrix[7]-mat.m_matrix[7],
		      m_matrix[2]-mat.m_matrix[2], m_matrix[5]-mat.m_matrix[5], m_matrix[8]-mat.m_matrix[8]);
}


template<typename T>
Matrix3x3<T> operator*(const Matrix3x3<T>& left,  const Matrix3x3<T>& right)
{
  return Matrix3x3<T>(left[0]*right[0]+left[3]*right[1]+left[6]*right[2], left[0]*right[3]+left[3]*right[4]+left[6]*right[5], left[0]*right[6]+left[3]*right[7]+left[6]*right[8],
		   left[1]*right[0]+left[4]*right[1]+left[7]*right[2], left[1]*right[3]+left[4]*right[4]+left[7]*right[5], left[1]*right[6]+left[4]*right[7]+left[7]*right[8],
		   left[2]*right[0]+left[5]*right[1]+left[8]*right[2], left[2]*right[3]+left[5]*right[4]+left[8]*right[5], left[2]*right[6]+left[5]*right[7]+left[8]*right[8]);
}



template<typename T>
Matrix3x3<T> Matrix3x3<T>::inverse() const
{
  T invDet;
  T det = determinant();
  if(det > -0.0005 && det < 0.0005)
    return Matrix3x3::identity;
  else{
    invDet = 1.0/det;
    return Matrix3x3<T>((m_matrix[4]*m_matrix[8]-m_matrix[7]*m_matrix[5])*invDet, -(m_matrix[3]*m_matrix[8]-m_matrix[5]*m_matrix[6])*invDet,  (m_matrix[3]*m_matrix[7]-m_matrix[4]*m_matrix[6])*invDet,
		     -(m_matrix[1]*m_matrix[8]-m_matrix[7]*m_matrix[2])*invDet, (m_matrix[0]*m_matrix[8]-m_matrix[2]*m_matrix[6])*invDet, -(m_matrix[0]*m_matrix[7]-m_matrix[1]*m_matrix[6])*invDet,
		     (m_matrix[1]*m_matrix[5]-m_matrix[2]*m_matrix[4])*invDet, -(m_matrix[0]*m_matrix[5]-m_matrix[2]*m_matrix[3])*invDet, (m_matrix[0]*m_matrix[4]-m_matrix[3]*m_matrix[1])*invDet);
  }
}

template<typename T>
Matrix3x3<T>& Matrix3x3<T>::invert()
{
  T det = determinant();
  if(det > -0.0005 && det < 0.0005)
    //Is this really correct?
    memcpy(m_matrix, identity.data(), 9*sizeof(T));
  else{
     T result[9];
     T invDet;
     invDet = 1.0f/det;
     result[0] = (m_matrix[4]*m_matrix[8]-m_matrix[7]*m_matrix[5])*invDet;
     result[1] = -(m_matrix[1]*m_matrix[8]-m_matrix[7]*m_matrix[2])*invDet;
     result[2] = (m_matrix[1]*m_matrix[5]-m_matrix[2]*m_matrix[4])*invDet;
     result[3] = -(m_matrix[3]*m_matrix[8]-m_matrix[5]*m_matrix[6])*invDet;
     result[4] = (m_matrix[0]*m_matrix[8]-m_matrix[2]*m_matrix[6])*invDet;
     result[5] = -(m_matrix[0]*m_matrix[5]-m_matrix[2]*m_matrix[3])*invDet;
     result[6] = (m_matrix[3]*m_matrix[7]-m_matrix[4]*m_matrix[6])*invDet;
     result[7] = -(m_matrix[0]*m_matrix[7]-m_matrix[1]*m_matrix[6])*invDet;
     result[8] = (m_matrix[0]*m_matrix[4]-m_matrix[3]*m_matrix[1])*invDet;
     memcpy(m_matrix, result, 9*sizeof(T));
  }
  return *this;
}

template<typename T>
T Matrix3x3<T>::determinant() const
{
  return m_matrix[0]*(m_matrix[4]*m_matrix[8]-m_matrix[5]*m_matrix[7])-
    m_matrix[3]*(m_matrix[1]*m_matrix[8]-m_matrix[2]*m_matrix[7])+
    m_matrix[6]*(m_matrix[1]*m_matrix[5]-m_matrix[2]*m_matrix[4]);
}

template<typename T>
Matrix3x3<T> Matrix3x3<T>::theTranspose() const
{
  return Matrix3x3<T>(m_matrix[0], m_matrix[1], m_matrix[2],
		      m_matrix[3], m_matrix[4], m_matrix[5],
		      m_matrix[6], m_matrix[7], m_matrix[8]);
}

template<typename T>
Matrix3x3<T>& Matrix3x3<T>::transpose()
{
  T result[9];
  result[0] = m_matrix[0];
  result[1] = m_matrix[3];
  result[2] = m_matrix[6];
  result[3] = m_matrix[1];
  result[4] = m_matrix[4];
  result[5] = m_matrix[7];
  result[6] = m_matrix[2];
  result[7] = m_matrix[5];
  result[8] = m_matrix[8];
  memcpy(m_matrix, result, 9*sizeof(T));
  return *this;
}

template<typename T>
Matrix3x3<T>& Matrix3x3<T>::operator+=(const Matrix3x3& matrix)
{
  m_matrix[0] += matrix.m_matrix[0];
  m_matrix[1] += matrix.m_matrix[1];
  m_matrix[2] += matrix.m_matrix[2];
  m_matrix[3] += matrix.m_matrix[3];
  m_matrix[4] += matrix.m_matrix[4];
  m_matrix[5] += matrix.m_matrix[5];
  m_matrix[6] += matrix.m_matrix[6];
  m_matrix[7] += matrix.m_matrix[7];
  m_matrix[8] += matrix.m_matrix[8];
  return *this;
}

template<typename T>
Matrix3x3<T>& Matrix3x3<T>::operator-=(const Matrix3x3& matrix)
{
  m_matrix[0] -= matrix.m_matrix[0];
  m_matrix[1] -= matrix.m_matrix[1];
  m_matrix[2] -= matrix.m_matrix[2];
  m_matrix[3] -= matrix.m_matrix[3];
  m_matrix[4] -= matrix.m_matrix[4];
  m_matrix[5] -= matrix.m_matrix[5];
  m_matrix[6] -= matrix.m_matrix[6];
  m_matrix[7] -= matrix.m_matrix[7];
  m_matrix[8] -= matrix.m_matrix[8]; 
  return *this;
}

template<typename T>
Matrix3x3<T>& Matrix3x3<T>::operator*=(const Matrix3x3& matrix)
{
  T result[9];
  result[0] = m_matrix[0]*matrix.m_matrix[0]+m_matrix[3]*matrix.m_matrix[1]+m_matrix[6]*matrix.m_matrix[2];
  result[1] = m_matrix[1]*matrix.m_matrix[0]+m_matrix[4]*matrix.m_matrix[1]+m_matrix[7]*matrix.m_matrix[2];
  result[2] = m_matrix[2]*matrix.m_matrix[0]+m_matrix[5]*matrix.m_matrix[1]+m_matrix[8]*matrix.m_matrix[2];

  result[3] = m_matrix[0]*matrix.m_matrix[3]+m_matrix[3]*matrix.m_matrix[4]+m_matrix[6]*matrix.m_matrix[5];
  result[4] = m_matrix[1]*matrix.m_matrix[3]+m_matrix[4]*matrix.m_matrix[4]+m_matrix[7]*matrix.m_matrix[5];
  result[5] = m_matrix[2]*matrix.m_matrix[3]+m_matrix[5]*matrix.m_matrix[4]+m_matrix[8]*matrix.m_matrix[5];

  result[6] = m_matrix[0]*matrix.m_matrix[6]+m_matrix[3]*matrix.m_matrix[7]+m_matrix[6]*matrix.m_matrix[8];
  result[7] = m_matrix[1]*matrix.m_matrix[6]+m_matrix[4]*matrix.m_matrix[7]+m_matrix[7]*matrix.m_matrix[8];
  result[8] = m_matrix[2]*matrix.m_matrix[6]+m_matrix[5]*matrix.m_matrix[7]+m_matrix[8]*matrix.m_matrix[8];
  memcpy(m_matrix, result, 9*sizeof(T));
  return *this;
}

template<typename T>
inline T& Matrix3x3<T>::operator[](unsigned int i)
{
  return m_matrix[i];
}

template<typename T>
inline const T& Matrix3x3<T>::operator[](unsigned int i) const
{
  return m_matrix[i];
}


template<typename T>
Matrix3x3<T>& Matrix3x3<T>::assign(T m1, T m4, T m7,   
				T m2, T m5, T m8,
				T m3, T m6, T m9)
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
  return *this;
}
		   


#endif
