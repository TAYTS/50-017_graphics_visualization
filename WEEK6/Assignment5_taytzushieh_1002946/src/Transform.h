#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "vecmath.h"
#include "Object3D.h"

/// TODO: implement this class
/// So that the intersect function first transforms the ray
class Transform : public Object3D {
 public:
  Transform() {}

  Transform(const Matrix4f& m, Object3D* obj) : o(obj) {
    this->m = m;
  }

  ~Transform() {
  }

  // TODO
  virtual bool intersect(const Ray& r, Hit& h, float tmin) {
    // reference: https://www.scratchapixel.com/lessons/3d-basic-rendering/transforming-objects-using-matrices
    Matrix4f matInv = this->m.inverse();
    Vector3f transRayOrigin = (matInv * Vector4f(r.getOrigin(), 1.0f)).xyz();
    Vector3f transRayDir = (matInv * Vector4f(r.getDirection(), 0.0f)).xyz();
    Ray transRay = Ray(transRayOrigin, transRayDir);

    if (o->intersect(transRay, h, tmin)) {
      Vector3f transNormal = (matInv.transposed() * Vector4f(h.getNormal(), 0.0f)).xyz().normalized();
      h.set(h.getT(), h.getMaterial(), transNormal);
      return true;
    }
    return false;
  }

 protected:
  Object3D* o;  //un-transformed object
  Matrix4f m;
};

#endif  //TRANSFORM_H
