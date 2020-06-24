#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "vecmath.h"
#include "Object3D.h"


/// TODO: implement this class
/// So that the intersect function first transforms the ray
class Transform: public Object3D
{
public: 
  Transform(){}

  Transform( const Matrix4f& m, Object3D* obj ):o(obj){
     this->m = m;
  }

  ~Transform(){
  }

  // TODO
  virtual bool intersect( const Ray& r , Hit& h , float tmin){
       
  }

 protected:
   Object3D* o; //un-transformed object
    Matrix4f m;
};

#endif //TRANSFORM_H
