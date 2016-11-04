/*
 * Copyright (C) 2003 University of Skövde.
 */

#ifndef INCLUDED_QUATERNION
#define INCLUDED_QUATERNION

#include "Vector3.h"
#include "Vector4.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"

/**
 *@brief The Quaternion class represents a quaternion.
 *@author Michael Andersson
 *@date 2004-02-04
 */

template<typename T>
class Quaternion
{
public:
  /**
   *@brief This is the Quaternion class default constructor.
  */
  Quaternion();

  /**
	*@brief This constructor makes it possible to create a quaternion using a three dimensional vector and a scalar value.
	*@param img = The imaginary part of the quaternion.
    *@param real = The qutarnions real component.
*/
  Quaternion(const Vector3<T>& img, T real);

  /**
	*@brief This constructor makes it possible to create a quaternion using a four dimensional vector.
	*@param vector = The x,y,z components of the vector represents the imaginary part while the w component represents the real component.
*/
  explicit Quaternion(const Vector4<T>& vector);
  
  /**
	*@brief This constructor makes it possible to create a quaternion using four scalar values.
	*@param x = The x component of the imaginary vector.
    *@param y = The y component of the imaginary vector.
    *@param z = The z component of the imaginary vector.
    *@param w = The w represents the real component of the quaternion.
*/  
  Quaternion(T x, T y, T z, T w);
  
  /**
	*@brief This constructor makes it possible to create a quaternion using an angle and a rotation axis.
	*@param angle = The rotation angle expressed in radians.
    *@param axis = The rotation axis.
*/  
  Quaternion(T angle, const Vector3<T>& axis);

  /**
	*@brief This constructor makes it possible to create a quaternion using Euler angles.
	*@param head = The rotation around the y-axis expressed in radians.
    *@param pitch = The rotation around the x-axis expressed in radians.
    *@param roll = The rotation around the z-axis expressed in radians.
*/ 

  Quaternion(T head, T pitch, T roll);

  /**
	*@brief This constructor makes it possible to create a quaternion using a 3x3 matrix.
	*@param matrix = The matrix to initialize the quaternion with.
*/  
  explicit Quaternion(const Matrix3x3<T>& matrix);
  
    /**
	*@brief As the name implies the conjugate member function returns the conjugate of a quaternion.
    *@return The conjugate of the quaternion.
*/  
  inline Quaternion conjugate() const;

      /**
	*@brief As the name implies the norm member function returns the norm of a quaternion.
    *@return The norm of the quaternion.
*/   
  inline T norm() const;

    /**
	*@brief The normalize member function normalizes the quaternion.
    *@return A reference to the quaternion after normalization.
    */   
  inline Quaternion& normalize();
  
    /**
	*@brief The inverse member function computes the inverse of the quaternion.
    *@return The inverse of the quaternion.
    */   
  inline Quaternion inverse() const;
  
  /**
	*@brief The matrix member function can be used to retrieve the quaternion as a matrix.
    *@return The quaternion as a matrix.
    */   
  Matrix3x3<T> matrix() const;

  /**
	*@brief The matrix4x4 member function can be used to retrieve the quaternion as a 4x4 matrix.
    *@return The quaternion as a 4x4 matrix.
  */ 
  Matrix4x4<T> matrix4x4() const;
  
    /**
	*@brief The assingIdentity will convert the quaternion to an identity quaternion(0-vector, 1)
    */  
  void assignIdentity();
  
/**
	*@brief The axis member function can be used to retrieve the rotation axis used by a quaternion.
    *@return The rotation axis.
    */   
  Vector3<T> axis() const;

/**
	*@brief The angle member function can be used to retrieve the rotation angle.
    *@return The rotation angle.
    */  
  float angle() const;
  
  /**
	*@brief The img member function returns the imaginary component of the quaternion.
    *@return The imaginary component of the quaternion.
    */  
  inline Vector3<T>& img();

   /**
	*@brief The img member function returns the imaginary component of the quaternion.
    *@return The imaginary component of the quaternion.
    */  
  inline const Vector3<T>& img() const;
  
   /**
	*@brief The real member function returns the realcomponent of the quaternion.
    *@return The real component of the quaternion.
    */  
  inline T& real();

   /**
	*@brief The real member function returns the realcomponent of the quaternion.
    *@return The real component of the quaternion.
    */  
  inline T real() const;

 private:
  Vector3<T> m_img; //The imaginary component
  T m_real; //The real component
};

typedef Quaternion<float> Quaternionf;
typedef Quaternion<double> Quaterniond;

template<typename T>
Quaternion<T> operator*(const Quaternion<T>& quat, T scalar)
{
  return Quaternion<T>(quat.img()*scalar, quat.real()*scalar);
}

template<typename T>
Quaternion<T> operator*(T scalar, const Quaternion<T>& quat)
{
  return Quaternion<T>(quat.img()*scalar, quat.real()*scalar);
}

template<typename T> 
Quaternion<T> operator*(const Quaternion<T>& left, const Quaternion<T>& right)
{
return Quaternion<T>(left.img().crossProduct(right.img())+left.img()*right.real()+right.img()*left.real(), left.real()*right.real()-left.img().dotProduct(right.img()));
}

template<typename T>
Quaternion<T> operator+(const Quaternion<T>& left, const Quaternion<T>& right)
{
  return Quaternion<T>(left.img()+right.img(), left.real()+right.real());
}

template<typename T>
Quaternion<T> operator-(const Quaternion<T>& left, const Quaternion<T>& right)
{
  return Quaternion<T>(left.img()-right.img(), left.real()-right.real());
}

template<typename T>
Quaternion<T>::Quaternion()
{
  m_img.assign(0.0, 0.0, 0.0);
  m_real = 1.0;
}

template<typename T>
Quaternion<T>::Quaternion(const Vector3<T>& img, T real)
{
  m_img = img;
  m_real = real;
}

template<typename T>
Quaternion<T>::Quaternion(const Vector4<T>& vector)
{
  m_img.assign(vector.x, vector.y, vector.z);
  m_real = vector.w;
}

template<typename T>
Quaternion<T>::Quaternion(T x, T y, T z, T w)
{
  m_img.assign(x, y, z);
  m_real = w;
}

template<typename T>
Quaternion<T>::Quaternion(T angle, const Vector3<T>& axis)
{
  m_img = axis*static_cast<T>(sin(angle*0.5));
  m_real = cos(angle*0.5);
}

template<typename T>
Quaternion<T>::Quaternion(T head, T pitch, T roll)
{
	const float cosHead = cos(head * 0.5f); //c1
	const float sinHead = sin(head * 0.5f); //s1
	const float cosRoll = cos(roll * 0.5f); //c2
	const float sinRoll = sin(roll * 0.5f); //s2
	const float cosPitch = cos(pitch * 0.5f); //c3
	const float sinPitch = sin(pitch * 0.5f); //s3

	const float cosHeadCosRoll = cosHead*cosRoll; //c1c2
	const float sinHeadSinRoll = sinHead*sinRoll; //s1s2
	m_real = cosHeadCosRoll * cosPitch - sinHeadSinRoll * sinPitch;
	m_img.x() = cosHeadCosRoll * sinPitch + sinHeadSinRoll * cosPitch;
	m_img.y() = sinHead * cosRoll * cosPitch + cosHead * sinRoll * sinPitch;
	m_img.z() = cosHead * sinRoll * cosPitch - sinHead * cosRoll * sinPitch;	
}

template<typename T>
Quaternion<T>::Quaternion(const Matrix3x3<T>& matrix)
{

	float tr, s, q[4];
	int i, j, k;
	int nxt[3] = {1, 2, 0};
	tr = matrix[0] + matrix[4] + matrix[8];
	
	if (tr > 0.0) {
		s = sqrt (tr + 1.0);
		m_real = s / 2;
		s = 0.5 / s;
		m_img.assign((matrix[5] - matrix[7]) * s, (matrix[6] - matrix[2]) * s, (matrix[1] - matrix[3]) *s);
	} else {
	
		i = 0;
		if (matrix[4] > matrix[0]) 
			i = 1;
		
		if (matrix[8] > matrix[i * 3 + i]) 
			i = 2;
		
		j = nxt[i];
		k = nxt[j];
		s = sqrt ((matrix[i * 3 + i] - (matrix[j * 3 + j] + matrix[k * 3 + k])) + 1.0);
		q[i] = s * 0.5;
		
		if (s != 0.0) 
			s = 0.5 / s;
		
		q[3] = (matrix[j * 3 + k] - matrix[k * 3 + j]) * s;
		q[j] = (matrix[i * 3 + j] + matrix[j * 3 + i]) * s;
		q[k] = (matrix[i * 3 + k] + matrix[k * 3 + i]) * s;
		m_img.assign(q[0], q[1], q[2]);
		m_real = q[3];
	}
}

template<typename T>
inline Quaternion<T> Quaternion<T>::conjugate() const
{
  return Quaternion<T>(-m_img, m_real);
}

template<typename T>
inline T Quaternion<T>::norm() const
{
  return m_img.x()*m_img.x()+m_img.y()*m_img.y()+m_img.z()*m_img.z()+m_real*m_real;
}

template<typename T>
inline Quaternion<T>& Quaternion<T>::normalize()
{
  T invMagnitude = 1/sqrt(m_img.x()*m_img.x()+m_img.y()*m_img.y()+m_img.z()*m_img.z()+m_real*m_real);
  m_img *= invMagnitude;
  m_real *= invMagnitude;
  return *this;
}

template<typename T>
inline Quaternion<T> Quaternion<T>::inverse() const
{
  return (1/norm())*conjugate();
}

template<typename T>
void Quaternion<T>::assignIdentity()
{
  m_img.assign(0.0, 0.0, 0.0);
  m_real = 1.0;
}

template<typename T>
Matrix3x3<T> Quaternion<T>::matrix() const
{
  T matrix[9];
  float s, x, y, z, w;
  s = 2.0f/norm();
  x = m_img.x();
  y = m_img.y();
  z = m_img.z();
  w = m_real;
  
  matrix[0] = 1-s*(y*y+z*z);
  matrix[1] = s*(x*y+w*z);
  matrix[2] = s*(x*z-w*y);
  
  matrix[3] = s*(x*y-w*z);
  matrix[4] = 1.0f-s*(x*x+z*z);
  matrix[5] = s*(y*z+w*x);
  
  matrix[6] = s*(x*z+w*y);
  matrix[7] = s*(y*z-w*x);
  matrix[8] = 1.0f-s*(x*x+y*y);

  return Matrix3x3<T>(matrix);
}

template<typename T>
Matrix4x4<T> Quaternion<T>::matrix4x4() const
{
  T matrix[16];
  memset(matrix, 0, sizeof(T) * 16);
  float s, x, y, z, w;
  s = 2.0f/norm();
  x = m_img.x();
  y = m_img.y();
  z = m_img.z();
  w = m_real;
  
  matrix[0] = 1-s*(y*y+z*z);
  matrix[1] = s*(x*y+w*z);
  matrix[2] = s*(x*z-w*y);
  
  matrix[4] = s*(x*y-w*z);
  matrix[5] = 1.0f-s*(x*x+z*z);
  matrix[6] = s*(y*z+w*x);
  
  matrix[8] = s*(x*z+w*y);
  matrix[9] = s*(y*z-w*x);
  matrix[10] = 1.0f-s*(x*x+y*y);

  matrix[15] = 1;

  return Matrix4x4<T>(matrix);
}

template<typename T>
Vector3<T> Quaternion<T>::axis() const
{
  Quaternion<T> q = *this;
  q.normalize();
  
  double sinAngle = sqrt(1-m_real*m_real);
  if(fabs(sinAngle) < 0.00005)
    sinAngle = 1.0;
  return Vector3<T>(m_img.x()/sinAngle, m_img.y()/sinAngle, m_img.z()/sinAngle);
}

template<typename T>
float Quaternion<T>::angle() const
{
  return acos(m_real)*2;
}

template<typename T>
inline Vector3<T>& Quaternion<T>::img()
{
  return m_img;
}

template<typename T>
inline const Vector3<T>& Quaternion<T>::img() const
{
  return m_img;
}

template<typename T>
inline T& Quaternion<T>::real()
{
  return m_real;
}

template<typename T>
inline T Quaternion<T>::real() const
{
  return m_real;
}

#endif
