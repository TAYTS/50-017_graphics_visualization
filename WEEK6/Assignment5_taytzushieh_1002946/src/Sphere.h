#ifndef SPHERE_H
#define SPHERE_H

#include "Object3D.h"
#include "vecmath.h"
#include <cmath>

#include <iostream>
using namespace std;

/// TODO: Implement this class
class Sphere : public Object3D {
 public:
  Vector3f center;
  float radius;
  Sphere() {
    //unit ball at the center
    this->center = Vector3f(0, 0, 0);
    this->radius = 1.0;
  }

  Sphere(Vector3f center, float radius, Material* material) : Object3D(material) {
    this->center = center;
    this->radius = radius;
  }

  ~Sphere() {}

  // TODO
  virtual bool intersect(const Ray& r, Hit& h, float tmin) {
    Vector3f rayOriginToCircleCenter = r.getOrigin() - this->center;  // '-' operator will generate new instance of Vector3f

    // solve using quadratic equation
    // || o + td - c || - r = 0
    const float a = Vector3f::dot(r.getDirection(), r.getDirection());
    const float b = 2.0f * Vector3f::dot(r.getDirection(), rayOriginToCircleCenter);
    const float c = Vector3f::dot(rayOriginToCircleCenter, rayOriginToCircleCenter) - (this->radius * this->radius);

    bool hasIntersect = false;
    if (b * b >= 4 * a * c) {
      float temp = sqrt(b * b - 4 * a * c);
      float t1 = (-b + temp) / (2.0f * a);
      float t2 = (-b - temp) / (2.0f * a);

      if (t1 > tmin && t1 < h.getT()) {
        hasIntersect = true;
        updateHit(t1, r, h);
      }

      if (t2 > tmin && t2 < h.getT()) {
        hasIntersect = true;
        updateHit(t2, r, h);
      }
    }

    return hasIntersect;
  }

 private:
  // Used to update the Hit using the ray parameter,t, the surface normal vector of the intersection point
  // and the object material
  void updateHit(float rayParam, const Ray& r, Hit& h) {
    Vector3f pointOnSurface = r.pointAtParameter(rayParam);
    Vector3f pointNormal = (pointOnSurface - this->center).normalized();
    h.set(rayParam, this->material, pointNormal);
  }

 protected:
  // Vector3f center;
  // float radius;
};

#endif
