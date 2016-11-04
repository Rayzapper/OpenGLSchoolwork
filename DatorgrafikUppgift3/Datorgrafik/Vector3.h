/*
 * Copyright (C) 2003 University of Skövde.
 */

/**
 *@brief The Vector3 class represents three dimensional vector.
 *@author Henrik Grimm and Michael Andersson
 *@date 2004-02-04
*/
#ifndef INCLUDED_VECTOR3
#define INCLUDED_VECTOR3

#include <cmath>


  /**
   *  \brief A 3-dimensional vector \f$ \bar{v} = (x,y,z) \f$. The type parameter \a T specifies
   *  the type of the three vector elements.
   */
template <typename T>
class Vector3 {
 public:
  Vector3();
  Vector3(T newX, T newY, T newZ);
  
  /**
   *  \brief Initializes this vector from an array of 3 values.
   *  \param  v  A pointer to an array of 3 values of some arbitrary type \a U, which
   *             must be convertible to type \a T.
   */
  template <typename U>
    explicit Vector3(const U* v)
    {
      x() = v[0];
      y() = v[1];
      z() = v[2];
    }
  
  /**
   *  \brief Initializes this vector with another vector.
   *  \param  v  The vector used to initialize this vector. The vector can be
   *             type-parameterized with an arbitrary type \a U, as long as \a U is
   *             convertible to type \a T.
   */
  template <typename U>
    explicit Vector3(const Vector3<U>& v)
    {
      x() = v.x();
      y() = v.y();
      z() = v.z();
    }
  
  void assign(T newX, T newY, T newZ);
  
  /**
   *  \brief Assigns this vector from an array of 3 values.
   *  \param  v  A pointer to an array of 3 values of some arbitrary type \a U, which
   *             must be implicitely convertible to type \a T.
   */
  template <typename U>
    void assign(const U* v)
    {
      x() = v[0];
      y() = v[1];
      z() = v[2];
    }
  
  /**
   *  \brief Assigns this vector from another vector.
   *  \param  v  The vector to assign to this vector. The vector can be
   *             type-parameterized with an arbitrary type \a U, as long as \a U is
   *             convertible to type \a T.
   */
  template <typename U>
    void assign(const Vector3<U>& v)
    {
      x() = v.x();
      y() = v.y();
      z() = v.z();
    }
  
  T& x();
  T& y();
  T& z();
  const T& x() const;
  const T& y() const;
  const T& z() const;
  
  T* data();
  const T* data() const;
  
  T& operator[](unsigned int i);
  const T& operator[](unsigned int i) const;
  
  void normalize();
  Vector3<T> getNormalized() const;
  
  Vector3<T> operator+() const;
  Vector3<T> operator-() const;
  void operator/=(const T s);
  void operator*=(const T s);
  void operator+=(const Vector3<T>& v);
  void operator-=(const Vector3<T>& v);
  
  T length() const;
  T lengthSquared() const;
  
  T dotProduct(const Vector3<T>& v) const;
  Vector3<T> crossProduct(const Vector3<T>& v) const;
  
 private:
  T m_vec[3];
};

template <typename T>
const Vector3<T> operator/(const Vector3<T>& v, T s);

template <typename T>
const Vector3<T> operator*(const Vector3<T>& v, T s);

template <typename T>
const Vector3<T> operator*(T s, const Vector3<T>& v);

template <typename T>
const Vector3<T> operator+(const Vector3<T>& v1, const Vector3<T>& v2);

template <typename T>
const Vector3<T> operator-(const Vector3<T>& v1, const Vector3<T>& v2);


typedef Vector3<float> Vector3f;
typedef Vector3<double> Vector3d;

// --------------------------------
// ------- Member functions -------
// --------------------------------

/**
 *  \brief Constructs a non-initialized vector.
 */
template <typename T>
inline 
Vector3<T>::Vector3()
{
  x() = static_cast<T>(0.0);
  y() = static_cast<T>(0.0);
  z() = static_cast<T>(0.0);
}

/**
 *  \brief Constructs an initialized vector.
 *  \param  newX  The vector's first element.
 *  \param  newY  The vector's second element.
 *  \param  newZ  The vector's third element.
 */
template <typename T>
inline 
Vector3<T>::Vector3(T newX, T newY, T newZ)
{
  x() = newX;
  y() = newY;
  z() = newZ;
}

/**
 *  \brief Assigns new values to the vectors elements.
 *  \param  newX  The new value for the vector's first element.
 *  \param  newY  The new value for the vector's second element.
 *  \param  newZ  The new value for the vector's third element.
 */
template <typename T>
inline 
void Vector3<T>::assign(T newX, T newY, T newZ)
{
  x() = newX;
  y() = newY;
  z() = newZ;
}	

/**
 *  \brief Returns a reference to the vector's first element.
 *  \return The vector's first element.
 *
 *  For a vector \a v, \a v.x() is equivalent to \a v[0].
 */
template <typename T>
inline
T& Vector3<T>::x()
{
  return m_vec[0];
}

/**
 *  \brief Returns a reference to the vector's second element.
 *  \return The vector's second element.
 *
 *  For a vector \a v, \a v.y() is equivalent to \a v[1].
 */
template <typename T>
inline
T& Vector3<T>::y()
{
  return m_vec[1];
}

/**
 *  \brief Returns a reference to the vector's third element.
 *  \return The vector's third element.
 *
 *  For a vector \a v, \a v.z() is equivalent to \a v[2].
 */
template <typename T>
inline T& Vector3<T>::z()
{
  return m_vec[2];
}

/**
 *  \brief Returns a constant reference to the vector's first element.
 *  \return The vector's first element.
 *
 *  For a vector \a v, \a v.x() is equivalent to \a v[0].
 */
template <typename T>
inline const T& Vector3<T>::x() const
{
  return m_vec[0];
}

/**
 *  \brief Returns a constant reference to the vector's second element.
 *  \return The vector's second element.
 *
 *  For a vector \a v, \a v.y() is equivalent to \a v[1].
 */
template <typename T>
inline const T& Vector3<T>::y() const
{
  return m_vec[1];
}

/**
 *  \brief Returns a constant reference to the vector's third element.
 *  \return The vector's third element.
 *
 *  For a vector \a v, \a v.z() is equivalent to \a v[2].
 */
template <typename T>
inline const T& Vector3<T>::z() const
{
  return m_vec[2];
}

/**
 *  \brief Returns a pointer to the vector's array of elements.
 *  \return A pointer to the vector's array of elements.
 */
template <typename T>
inline T* Vector3<T>::data()
{
  return m_vec;
}

/**
 *  \brief Returns a constant pointer to the vector's array of elements.
 *  \return A constant pointer to the vector's array of elements.
 */
template <typename T>
inline const T* Vector3<T>::data() const
{
  return m_vec;
}

/**
 *  \brief Normalizes the vector.
 *  \pre At least one of the vector's elements must be non-zero (i.e. the length of
 *       the vector must be larger than 0).
 *
 *  The normal of a vector \f$ \bar{v} \f$ is a vector \f$ \bar{n} \f$ with the same
 *  direction as \f$ \bar{v} \f$, but with a length of 1. The normal can be calculated
 *  as \f$ \bar{n} = \frac {\bar{v}} {\left| \bar{v} \right|} \f$.
 */
template <typename T>
inline void Vector3<T>::normalize()
{
  (*this) /= length();
}

/**
 *  \brief Returns a normalization of this vector.
 *  \pre At least one of the vector's elements must be non-zero (i.e. the length of
 *       the vector must be larger than 0).
 *
 *  The normal of a vector \f$ \bar{v} \f$ is a vector \f$ \bar{n} \f$ with the same
 *  direction as \f$ \bar{v} \f$, but with a length of 1. The normal can be calculated
 *  as \f$ \bar{n} = \frac {\bar{v}} {\left| \bar{v} \right|} \f$.
 */
template <typename T>
inline Vector3<T> Vector3<T>::getNormalized() const
{
  return (*this / length());
}

/**
 *  \brief Returns a reference to the vector's \a i:th element.
 *  \param  i  The index of the element to return where 0 means the vector's
 *             first element. Must not be smaller than 0 or larger than 2.
 *  \return A reference to the vector's element.
 */
template <typename T>
inline T& Vector3<T>::operator[](unsigned int i)
{
  return m_vec[i];
}

/**
 *  \brief Returns a constant reference to the vector's \a i:th element.
 *  \param  i  The index of the element to return where 0 means the vector's
 *             first element. Must not be smaller than 0 or larger than 2.
 *  \return A constant reference to the vector's element.
 */
template <typename T>
inline const T& Vector3<T>::operator[](unsigned int i) const
{
  return m_vec[i];
}

/**
 *  \brief Returns the length of this vector.
 *
 *  Given a vector \f$ \bar{v} = (x,y,z) \f$, its length \f$ \left| \bar{v} \right| \f$ is defined as
 *  \f$ \left| \bar{v} \right| = \sqrt{x^2 + y^2 + z^2} \f$.
 */
template <typename T>
inline T Vector3<T>::length() const
{
  return sqrt(lengthSquared());
}

/**
 *  \brief Returns the square of the length of the vector.
 *
 *  For a vector \a v, \a v.lengthSquared() gives the same result as 
 * \a v.length() * \a v.length() (ignoring rounding errors), but is 
 * usually more efficient.
 */
template <typename T>
inline T Vector3<T>::lengthSquared() const
{
  return (x()*x() + y()*y() + z()*z());
}

/**
 *  \brief Returns a copy of this vector.
 *  \return A copy of this vector.
 */
template <typename T>
inline Vector3<T> Vector3<T>::operator+() const
{
  return (*this);
}

/**
 *  \brief Returns the opposite of this vector.
 *  \return The opposite of this vector.
 *
 *  For a vector \f$ \bar{v} = (x, y, z) \f$, the opposite \f$ -\bar{v} \f$ is a vector
 *  with the same length as \f$ v \f$ but pointing in the opposite direction. It is
 *  calculated as \f$ -v = (-x, -y, -z) \f$.
 */
template <typename T>
inline Vector3<T> Vector3<T>::operator-() const
{
  return Vector3<T>(-x(), -y(), -z());
}

/**
 *  \brief Divides this vector with a scalar value.
 *  \param  s  The scalar value (must be non-zero).
 */
template <typename T>
inline void Vector3<T>::operator/=(T s)
{
  x() /= s;
  y() /= s;
  z() /= s;
}

/**
 *  \brief Multiplies this vector with a scalar value.
 *  \param  s  The scalar value.
 */
template <typename T>
inline void Vector3<T>::operator*=(T s)
{
  x() *= s;
  y() *= s;
  z() *= s;
}

/**
 *  \brief Adds another vector to this vector.
 *  \param  v  The vector to add to this vector.
 */
template <typename T>
inline void Vector3<T>::operator+=(const Vector3<T>& v)
{
  x() += v.x();
  y() += v.y();
  z() += v.z();
}

/**
 *  \brief Subtracts another vector from this vector.
 *  \param  v  The vector to subtract from this vector.
 */
template <typename T>
inline void Vector3<T>::operator-=(const Vector3<T>& v)
{
  x() -= v.x();
  y() -= v.y();
  z() -= v.z();
}

/**
 *  \brief Calculates the dot product of this and another vector.
 *  \param  v  The second vector.
 *  \return The dot product of the two vectors.
 *
 *  Given two vectors, \f$ \bar{u} \f$ and \f$ \bar{v} \f$, the dot product \f$ \bar{u} \cdot \bar{v} \f$ is defined as
 *  \f$ \bar{u} \cdot \bar{v} = \left| \bar{u} \right| \left| \bar{v} \right| \cos \gamma \f$ where
 *  \f$ \gamma \f$ is the angle between \f$ \bar{u} \f$ and \f$ \bar{v} \f$. 
 * 
 *  Given the components of the two vectors, \f$ \bar{u} = (u_1,u_2,u_3) \f$ and \f$ \bar{v} = (v_1,v_2,v_3) \f$,
 *  the dot product is \f$ \bar{u} \cdot \bar{v} = (u_1 v_1, u_2 v_2, u_3 v_3) \f$.
 */
template <typename T>
inline T Vector3<T>::dotProduct(const Vector3<T>& v) const
{
  return x() * v.x() + y() * v.y() + z() * v.z();
}

/**
 *  \brief Calculates the cross product of this and another vector.
 *  \param  v  The second vector.
 *  \return The cross product of the two vectors.
 *
 *  For two non-parallel vectors \f$ \bar{u} \f$ and \f$ \bar{v} \f$ whose lengths are greater
 *  than zero, the cross product \f$ \bar{u} \times \bar{v} \f$ is defined as:
 *  - \f$ \left| \bar{u} \times \bar{v} \right| = \left| \bar{u} \right| \left| \bar{v} \right| \sin \gamma \f$ where \f$ \gamma \f$ is the angle between \f$ \bar{u} \f$ and \f$ \bar{v} \f$.
 *  - \f$ \bar{u} \times \bar{v} \f$ is perpendicular to both \f$ \bar{u} \f$ and \f$ \bar{v} \f$.
 *  - \f$ \bar{u} \f$, \f$ \bar{v} \f$, \f$ \bar{u} \times \bar{v} \f$ is a right hand system.
 *
 *  If \f$ \bar{u} \f$ or \f$ \bar{v} \f$ have a length of zero or if \f$ \bar{u} \f$ and \f$ \bar{v} \f$ are parallel,
 *  then \f$ \bar{u} \times \bar{v} \f$ is equal to the zero vector \f$ (0, 0, 0) \f$.
 */
template <typename T>
inline Vector3<T> Vector3<T>::crossProduct(const Vector3<T>& v) const
{
  return Vector3<T>(y() * v.z() - z() * v.y(), 
		    z() * v.x() - x() * v.z(), 
		    x() * v.y() - y() * v.x());
}




// --------------------------------
// ------- Global functions -------
// --------------------------------

/**
 *  \brief Returns the result of diving a vector with a scalar value.
 *  \param  v  The vector.
 *  \param  s  The scalar value (must be non-zero).
 *  \return The result of dividing the vector with the scalar value.
 */
template <typename T>
inline const Vector3<T> operator/(const Vector3<T>& v, T s)
{
  return Vector3<T>(v.x() / s, v.y() / s, v.z() / s);
}

/**
 *  \brief Returns the result of multiplying a vector with a scalar value.
 *  \param  v  The vector.
 *  \param  s  The scalar value.
 *  \return The result of multiplying the vector with the scalar value.
 */
template <typename T>
inline const Vector3<T> operator*(const Vector3<T>& v, T s)
{
  return Vector3<T>(v.x() * s, v.y() * s, v.z() * s);
}

/**
 *  \brief Returns the result of multiplying a scalar value with a vector.
 *  \param  s  The scalar value.
 *  \param  v  The vector.
 *  \return The result of multiplying the scalar value with the vector.
 */
template <typename T>
inline const Vector3<T> operator*(T s, const Vector3<T>& v)
{
  return Vector3<T>(v.x() * s, v.y() * s, v.z() * s);
}

/**
 *  \brief Calculates the sum of two vectors.
 *  \param  v1  The first vector.
 *  \param  v2  The second vector.
 *  \return The sum of the two vectors.
 */
template <typename T>
inline const Vector3<T> operator+(const Vector3<T>& v1, const Vector3<T>& v2)
{
  return Vector3<T>(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
}

/**
 *  \brief Returns the result of subtracting two vectors.
 *  \param  v1  The first vector.
 *  \param  v2  The second vector.
 *  \return The result of subtracting the two vectors.
 */
template <typename T>
inline const Vector3<T> operator-(const Vector3<T>& v1, const Vector3<T>& v2)
{
  return Vector3<T>(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z());
}

#endif // VECTOR3_H
