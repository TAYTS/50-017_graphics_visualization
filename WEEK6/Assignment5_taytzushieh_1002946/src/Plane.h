#ifndef PLANE_H
#define PLANE_H

#include "Object3D.h"
#include "vecmath.h"
#include <cmath>
using namespace std;

/// TODO: Implement Plane representing an infinite plane
class Plane : public Object3D {
 public:
  Plane() {}

  Plane(const Vector3f& normal, float d, Material* m) : Object3D(m) {
    this->normal = normal.normalized();
    this->d = -d;
  }

  ~Plane() {}

  // TODO
  virtual bool intersect(const Ray& r, Hit& h, float tmin) {
    const float normalDotRayOrigin = Vector3f::dot(this->normal, r.getOrigin());
    const float normalDotRayDirection = Vector3f::dot(this->normal, r.getDirection());
    const float t = (-this->d - normalDotRayOrigin) / normalDotRayDirection;

    if (t > tmin && t < h.getT()) {
      h.set(t, this->material, this->normal);
      return true;
    }

    return false;
  }

 protected:
  Vector3f normal;
  float d;
};
#endif  //PLANE_H
