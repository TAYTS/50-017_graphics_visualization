#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object3D.h"
#include "vecmath.h"
#include <cmath>
#include <iostream>

using namespace std;

/// TODO: implement this class
class Triangle : public Object3D {
 public:
  Triangle();

  ///@param a b c are three vertex positions of the triangle
  Triangle(const Vector3f& a, const Vector3f& b, const Vector3f& c, Material* m) : Object3D(m) {
    this->a = a;
    this->b = b;
    this->c = c;
    hasTex = false;
  }

  // TODO
  virtual bool intersect(const Ray& ray, Hit& hit, float tmin) {
    Vector3f constCol = this->a - ray.getOrigin();
    Vector3f betaCol = this->a - this->b;
    Vector3f gammaCol = this->a - this->c;
    Vector3f tCol = ray.getDirection();

    float coefDet = Matrix3f(betaCol, gammaCol, tCol).determinant();
    float betaDet = Matrix3f(constCol, gammaCol, tCol).determinant();
    float gammaDet = Matrix3f(betaCol, constCol, tCol).determinant();
    float tDet = Matrix3f(betaCol, gammaCol, constCol).determinant();

    float beta = betaDet / coefDet;
    float gamma = gammaDet / coefDet;
    float t = tDet / coefDet;

    if (t > tmin && t < hit.getT() && beta + gamma <= 1.0f && beta >= 0.0f && gamma >= 0.0f) {
      float alpha = 1.0f - beta - gamma;
      Vector3f normal = alpha * normals[0] + beta * normals[1] + gamma * normals[2];
      hit.set(t, this->material, normal.normalized());

      return true;
    }

    return false;
  }

  bool hasTex;
  Vector3f normals[3];
  Vector2f texCoords[3];

 protected:
  Vector3f a;
  Vector3f b;
  Vector3f c;
};

#endif  //TRIANGLE_H
