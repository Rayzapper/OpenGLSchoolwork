#ifndef INCLUDED_MATHUTILS
#define INCLUDED_MATHUTILS

#include "Vector3.h"
#include "Vector4.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "Quaternion.h"

 /**
   *@brief This operator* makes it possible to multiply a three dimensional vector by a 3x3 matrix.
   *@param matrix = The matrix to multiply with.
   *@param vector = The vector to multiply.
   *@return The result of the operator* is the result of the multiplication.
  */
template<typename T>
Vector3<T> operator*(const Matrix3x3<T>& matrix, const Vector3<T>& vector)
{
  return Vector3<T>(matrix[0]*vector.x()+matrix[3]*vector.y()+matrix[6]*vector.z(),
		    matrix[1]*vector.x()+matrix[4]*vector.y()+matrix[7]*vector.z(),
		    matrix[2]*vector.x()+matrix[5]*vector.y()+matrix[8]*vector.z());
}

/**
   *@brief This operator* makes it possible to multiply a four dimensional vector by a 4x4 matrix.
   *@param matrix = The matrix to multiply with.
   *@param vector = The vector to multiply.
   *@return The result of the operator* is the result of the multiplication.
  */
template<typename T>
Vector4<T> operator*(const Matrix4x4<T>& matrix, const Vector4<T>& vector)
{
  return Vector4<T>(matrix[0]*vector.x()+matrix[4]*vector.y()+matrix[8]*vector.z()+matrix[12]*vector.w(),
		    matrix[1]*vector.x()+matrix[5]*vector.y()+matrix[9]*vector.z()+matrix[13]*vector.w(),
		    matrix[2]*vector.x()+matrix[6]*vector.y()+matrix[10]*vector.z()+matrix[14]*vector.w(),
		    matrix[3]*vector.x()+matrix[7]*vector.y()+matrix[11]*vector.z()+matrix[15]*vector.w());
}

/**
   *@brief The createRotationMatrix3x3 function creates a 3x3 rotation matrix that will rotate an object
   *angle radius around the specified axis.
   *@param axis = The axis to rotate around.
   *@param angle = The rotation angle expressed in radians.
   *@return The rotation matrix.
  */
template<typename T>
Matrix3x3<T> createRotationMatrix3x3(const Vector3<T>& axis, T angle)
{
  float cosAngle = cos(angle);
  float sinAngle = sin(angle);
  
  return Matrix3x3<T>(cosAngle+(1-cosAngle)*axis.x()*axis.x(), (1-cosAngle)*axis.x()*axis.y()-axis.z()*sinAngle, (1-cosAngle)*axis.x()*axis.z()+axis.y()*sinAngle,
		      (1-cosAngle)*axis.x()*axis.y()+axis.z()*sinAngle, cosAngle+(1-cosAngle)*axis.y()*axis.y(), (1-cosAngle)*axis.y()*axis.z()-axis.x()*sinAngle,
		      (1-cosAngle)*axis.x()*axis.z()-axis.y()*sinAngle, (1-cosAngle)*axis.y()*axis.z()+axis.x()*sinAngle, cosAngle+(1-cosAngle)*axis.z()*axis.z());
}

/**
   *@brief The createRotationMatrix function creates a rotation matrix that will rotate an object
   *angle radius around the specified axis.
   *@param axis = The axis to rotate around.
   *@param angle = The rotation angle expressed in radians.
   *@return The rotation matrix.
  */
template<typename T>
Matrix4x4<T> createRotationMatrix(const Vector3<T>& axis, T angle)
{
  float cosAngle = cos(angle);
  float sinAngle = sin(angle);
  
  return Matrix4x4<T>(cosAngle+(1-cosAngle)*axis.x()*axis.x(), (1-cosAngle)*axis.x()*axis.y()-axis.z()*sinAngle, (1-cosAngle)*axis.x()*axis.z()+axis.y()*sinAngle, 0.0f,
		      (1-cosAngle)*axis.x()*axis.y()+axis.z()*sinAngle, cosAngle+(1-cosAngle)*axis.y()*axis.y(), (1-cosAngle)*axis.y()*axis.z()-axis.x()*sinAngle, 0.0f,
		      (1-cosAngle)*axis.x()*axis.z()-axis.y()*sinAngle, (1-cosAngle)*axis.y()*axis.z()+axis.x()*sinAngle, cosAngle+(1-cosAngle)*axis.z()*axis.z(), 0.0f,
 			  0.0f, 0.0f, 0.0f, 1.0f);	
}

/**
   *@brief The createRotationMatrix function creates a rotation matrix using euler angles.
   *@param head = The rotation in radians around the y axis.	
   *@param pitch = The rotation in radians around the x axis.
   *@param roll = The rotation in radians around the z axis.	
   *@return The rotation matrix.
  */
template<typename T>
Matrix4x4<T> createRotationMatrix(T head, T pitch, T roll)
{
    T a = cos(pitch);
    T b = sin(pitch);
    T c = cos(head);
    T d = sin(head);
    T e = cos(roll);
    T f = sin(roll);
    
    T ad = a * d;
    T bd = b * d;

    return Matrix4x4<T>(c * e, -c * f, d, 0,
                        bd * e + a * f, -bd * f + a * e, -b * c, 0,
                        -ad * e + b * f, ad * f + b * e, a * c, 0,
                        0, 0, 0, 1);
}


/**
   *@brief The createTranslationMatrix function creates a translation matrix.
   *@param x = The translation along the x axis.
   *@param y = The translation along the y axis.
   *@param z = The translation along the z axis.
   *@return The translation matrix.
  */
template<typename T>
Matrix4x4<T> createTranslationMatrix(T x, T y, T z)
{
	return Matrix4x4<T>(1, 0, 0, x,
                        0, 1, 0, y,
                        0, 0, 1, z,
                        0, 0, 0, 1);
					
}

/**
   *@brief The createScaleMatrix function creates a scale matrix.
   *@param x = The x scale factor
   *@param y = The y scale factor
   *@param z = The z scale factor
   *@return The translation matrix.
  */
template<typename T>
Matrix4x4<T> createScaleMatrix(T x, T y, T z)
{
	return Matrix4x4<T>(x, 0, 0, 0,
                        0, y, 0, 0,
                        0, 0, z, 0,
                        0, 0, 0, 1);
					
}

/**
   *@brief The interpolate function can be used to perform linear interpolation between matrices.
   *@param start = The start matrix.
   *@param finish = The end matrix.
   *@param t = A interpolation value (0 = start, 1 = end).
   *@return The intermediate matrix.
  */
template<typename T>
Matrix3x3<T> interpolate(const Matrix3x3<T>& start, const Matrix3x3<T>& finish, float t)
{
  Matrix3x3<T> matrix = start.theTranspose()*finish;
  Quaternion<T> quat(start.theTranspose()*finish);
  return buildRotationMatrix(quat.axis(), quat.angle()*t);
}

/**
   *@brief Performs a componentvise multiplication of two vectors
   *@param start = The left hand side operand.
   *@param finish = The right hand side operand.
   *@return The result of the componentvise multiplication of the operands.
*/
template<typename T>
Vector3<T> operator*(const Vector3<T>& left, const Vector3<T>& right)
{
	return Vector3<T>(left.x() * right.x(), left.y() * right.y(), left.z() * right.z());
}

/**
   *@brief Performs a componentvise multiplication of two vectors
   *@param left = The left hand side operand.
   *@param right = The right hand side operand.
   *@return The result of the componentvise multiplication of the operands.
*/
template<typename T>
Vector4<T> operator*(const Vector4<T>& left, const Vector4<T>& right)
{
	return Vector4<T>(left.x() * right.x(), left.y() * right.y(), left.z() * right.z(), left.w() * right.w());
}

/**
   *@brief Normalizes the normal of a plane
   *@param plane = The four factors of the plane equation
*/
template<typename T>
void normalizePlane(Vector4<T>& plane)
{
	float magnitude = sqrt(plane.x() * plane.x() + plane.y() * plane.y() + plane.z() * plane.z());
	plane.x() /= magnitude;
	plane.y() /= magnitude;
	plane.z() /= magnitude;
	plane.w() /= magnitude;
}

#endif
