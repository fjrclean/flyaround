//vector_math.hpp
//Part of project game_engine/flyaround
//Should be generalised later for all game_engine components
//Provides useful functions for vector maths

#ifndef VECTOR_MATH_HPP
#define VECTOR_MATH_HPP

/********************************************************/

#include <cmath>

/********************************************************/

struct vector3d{
	double x;
	double y;
	double z;
};

/*********************************************************/

		/**
		*@brief
		*
		*/
class vecMath{
	
	public:
	double getMagnitude(struct vector3d *vec);
	struct vector3d getUnit(struct vector3d *vec);
	struct vector3d getNormal(struct vector3d *vec);
	struct vector3d getDotProduct(struct vector3d &, struct vector3d &);
};


/*********************************************************/

#endif
