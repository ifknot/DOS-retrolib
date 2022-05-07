/*****************************************************************//**
 * \file   vector2D.h
 * \brief  2D vector type encapsulates vector operations 
 * 
 * \author ifkno
 * \date   September 2021
 *********************************************************************/
//#pragma once

#ifndef VECTOR2D_H
#define VECTOR2D_H

namespace jst {
	
	
	template<typename T>
	struct vector2D {

		T x;
		T y;

		vector2D() : x(0), y(0) {}

		vector2D(T x, T y) : x(x), y(y) {}

		inline T magnitude_squared() {
			return x * x + y * y;
		}

		inline void reverse() {
			x = -x;
			y = -y;
		}

		/**
		 * perpendicular is simply a vector at right angles to the original vector and same magnitude
		 * exchanges the x and y members and negates one of them 
		 * i.e. a rotation through a quarter turn.
		 */
		inline vector2D perpendicular() {
			return vector2D(-y, x)
		}

		/**
		 * dot product or scalar product an (of many) inner product
		 * sum of magnitude products
		 * The dot product gives a nice method for determining if two vectors are 
		 * perpendicular (aka orthogonal) and it will give another method for determining 
		 * when two vectors are parallel.
		 * Collision detection for polygon vertex on one body to a polygon face on
		 * another body 
		 */
		inline T dot(vector2D u) {
			return x * u.x + y * u.y;
		}

		/**
		* perpendicular dot product (n.b. the cross product is not defined in 2D space)
		* It has a number of useful properties: It is a Number with value v1v2 sin ?, 
		* v1 and v2 are the vector lengths and ? is the angle between the vectors, 
		* and is the area of the parallelogram with the vectors as two sides, 
		* and so twice the area of the triangle formed by the two vectors.
		* 
		* It is closely related to the dot product which has value v1v2 cos ?. 
		* Together they form a complex number which if normalised can be used as 
		* the rotation between the vector directions. 
		* And as already noted they can be passed to atan2 to accurately get the 
		* signed angle between the vectors on a f.p. co-processor
		*
		* The perp dot product is the two-dimensional equivalent of the cross product 
		* in three dimensions, although in many ways it is more useful as it more 
		* immediately relates to the dot product and rotations. 
		*/
		inline T perp_dot(vector2D u) {
			return perpendicular().dot(u);

		}

		inline vector2D& operator+=(vector2D& u) {
			x += u.x;
			y += u.y;
			return *this;
		}

		inline vector2D& operator-=(vector2D& u) {
			x -= u.x;
			y -= u.y;
			return *this;
		}

		inline vector2D& operator*=(T scale) {
			x *= scale;
			y *= scale;
			return *this;
		}

		inline vector2D& operator/=(T scale) {
			x /= scale;
			y /= scale;
			return *this;
		}

		// conjugate of this
		inline vector2D operator-() {
			return vector2D(-x, -y);
		}
		
	};

}

#endif // VECTOR2D_H