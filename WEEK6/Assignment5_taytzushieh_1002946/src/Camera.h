#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.h"
#include "vecmath.h"
#include <float.h>
#include <cmath>

class Camera {
 public:
  //generate rays for each screen-space coordinate
  virtual Ray generateRay(const Vector2f& point) = 0;

  virtual float getTMin() const = 0;
  virtual ~Camera() {}

 protected:
  Vector3f center;
  Vector3f direction;
  Vector3f up;
  Vector3f horizontal;
};

/// TODO: Implement Perspective camera
class PerspectiveCamera : public Camera {
 public:
  // TODO
  PerspectiveCamera(const Vector3f& center, const Vector3f& direction, const Vector3f& up, float angle) {
    w = Vector3f(direction).normalized();     // make a copy of the camera direction
    u = Vector3f::cross(w, up).normalized();  // camera right
    v = Vector3f::cross(u, w).normalized();   // camera up

    this->angle = angle;
    this->center = center;

    // transformation matrix from standard camera to extrinsic camera
    // pre-compute to speed up the generateRay process
    this->viewTransMat = Matrix4f(
        Vector4f(this->u, 0.0f),
        Vector4f(this->v, 0.0f),
        -Vector4f(this->w, 0.0f),
        Vector4f(this->center, 1.0f));
  }

  // TODO
  virtual Ray generateRay(const Vector2f& point) {
    float fieldOfViewAngle = tan(this->angle / 2.0f);
    Vector4f rayDirection = Vector4f(point.x() * fieldOfViewAngle, point.y() * fieldOfViewAngle, -1.0f, 0.0f);
    Vector3f transRayDir = (this->viewTransMat * rayDirection).xyz().normalized();
    return Ray(this->center, transRayDir);
  }

  virtual float getTMin() const {
    return 0.0f;
  }

 private:
  float angle;
  Vector3f w;
  Vector3f u;
  Vector3f v;
  Matrix4f viewTransMat;
};

#endif  //CAMERA_H
