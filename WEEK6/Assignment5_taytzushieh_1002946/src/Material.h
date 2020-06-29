#ifndef MATERIAL_H
#define MATERIAL_H

#include <cassert>
#include "vecmath.h"

#include "Ray.h"
#include "Hit.h"
#include "texture.hpp"

/// TODO: Implement Shade function that uses diffuse and specular
class Material {
 public:
  Material(const Vector3f& d_color, const Vector3f& s_color = Vector3f::ZERO, float s = 0) : diffuseColor(d_color), specularColor(s_color), shininess(s) {
  }

  virtual ~Material() {
  }

  virtual Vector3f getDiffuseColor() const {
    return diffuseColor;
  }

  // TODO
  Vector3f Shade(const Ray& ray, const Hit& hit,
                 const Vector3f& dirToLight, const Vector3f& lightColor) {
    Vector3f shadeColor = Vector3f::ZERO;  // black color
    Vector3f surfaceNormal = hit.getNormal().normalized();

    float diffuseLightIntensity = Vector3f::dot(dirToLight, surfaceNormal);

    if (diffuseLightIntensity > 0) {
      shadeColor += this->diffuseColor * diffuseLightIntensity * lightColor;
    }

    Vector3f reflectedRayDir = 2 * surfaceNormal * Vector3f::dot(surfaceNormal, dirToLight) - dirToLight;
    // direction to camera is the opposite of the ray direction
    float specularLightIntensity = Vector3f::dot(reflectedRayDir, -ray.getDirection().normalized());

    if (diffuseLightIntensity > 0 && specularLightIntensity > 0) {
      shadeColor += this->specularColor * pow(specularLightIntensity, this->shininess) * lightColor;
    }
    return shadeColor;
  }

  void loadTexture(const char* filename) {
    t.load(filename);
  }

  Texture t;

 protected:
  Vector3f diffuseColor;
  Vector3f specularColor;
  float shininess;
};

#endif  // MATERIAL_H
