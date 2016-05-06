//vector_math.cpp

/********************************************************/

#include "vector_math.hpp"

/********************************************************/

double vecMath::getMagnitude(struct vector3d *vec){
	double x,y,z;
	x = vec->x * vec->x;
	y = vec->y * vec->y;
	z = vec->z * vec->z;

	double mag = sqrt(x + y + z);
	return mag;
}

struct vector3d vecMath::getUnit(struct vector3d *vec){
	double mag = getMagnitude(vec);
	
	struct vector3d unitVector;
	unitVector.x = vec->x/mag;
	unitVector.y = vec->y/mag;
	unitVector.z = vec->z/mag;

	return unitVector;
}

struct vector3d getDotProduct(struct vector3d &, struct vector3d &){
	
}

/********************************************************/
