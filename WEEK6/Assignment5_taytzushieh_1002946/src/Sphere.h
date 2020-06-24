#ifndef SPHERE_H
#define SPHERE_H

#include "Object3D.h"
#include "vecmath.h"
#include <cmath>

#include <iostream>
using namespace std;


/// TODO: Implement this class  
class Sphere: public Object3D
{
public:
	Sphere(){ 
		//unit ball at the center
        this->center = Vector3f(0,0,0);
        this->radius = 1.0;
	}

	Sphere( Vector3f center , float radius , Material* material ):Object3D(material){
        this->center = center;
        this->radius = radius;
	}
	
	~Sphere(){}


    // TODO
	virtual bool intersect( const Ray& r , Hit& h , float tmin){

	}

protected:
    Vector3f center;
    float radius;
  
};


#endif
