/***********************************************************************
 *
 *  Ray Tracing
 *
 *  Assignment 5 of SUTD Course 50.017 (May-Aug Term, 2020)
 *
 *  24/06/2020
 *
 *  Note: TODO functions are in the following files:
 *    main.cpp
 *    camera.h
 *    Group.h
 *    Transform.h
 *    Sphere.h
 *    Plane.h
 *    Triangle.h
 *    Material.h
 *
 ***********************************************************************/

#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>

#include "SceneParser.h"
#include "Image.h"
#include "Camera.h"
#include <string.h>
#include "ProgramArgs.h"

using namespace std;

float clampedDepth(float depthInput, float depthMin, float depthMax);

#include "bitmap_image.hpp"

void renderImage(ProgramArgs* const args) {
  SceneParser sp = SceneParser(args->getInputFilename().data());
  Camera* camera = sp.getCamera();
  Group* group = sp.getGroup();
  Vector3f backgroundColor = sp.getBackgroundColor();
  Vector3f ambientLight = sp.getAmbientLight();
  int numLights = sp.getNumLights();

  // Generate image
  Image image(args->getImgWidth(), args->getImgHeight());
  image.SetAllPixels(backgroundColor);

  // Generate ray with reference: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays
  // Set image initial origin at the top left corner.
  // First normalize the pixel coord(x, y) to device coord[0:1] then normalize to screen coord [-1:1].
  float imgAspectRatio = (float)args->getImgWidth() / (float)(*args).getImgHeight();
  // point is normalized to [-1:1], the screen half height is from the camera center
  for (int px = 0; px < args->getImgWidth(); px++) {
    float nx = (2 * (px / (args->getImgWidth() - 1.0f)) - 1.0f) * imgAspectRatio;
    for (int py = 0; py < args->getImgHeight(); py++) {
      float ny = 2 * (py / (args->getImgHeight() - 1.0f)) - 1.0f;

      // Generate ray from the camera through the center of the image pixels
      Ray ray = (*camera).generateRay(Vector2f(nx, ny));

      // Create Hit instance which will be modified by the intersect method later
      Hit h = Hit();

      if (group->intersect(ray, h, camera->getTMin())) {
        Material* material = h.getMaterial();

        // Compute the ambient color/lighting
        Vector3f shadedColor = material->getDiffuseColor() * ambientLight;

        // Combine all the diffuse and specular lighting from different light sources
        for (int i = 0; i < numLights; i++) {
          Vector3f dirLight;
          Vector3f lightColor;
          float disToLight;
          Light* light = sp.getLight(i);
          light->getIllumination(ray.pointAtParameter(h.getT()), dirLight, lightColor, disToLight);
          shadedColor += material->Shade(ray, h, dirLight, lightColor);
        }

        image.SetPixel(px, py, shadedColor);
      }
    }
  }

  image.SaveImage(args->getOutputFilename().data());
}

int main(int argc, char* argv[]) {
  // Fill in your implementation here.

  // This loop loops over each of the input arguments.
  // argNum is initialized to 1 because the first
  // "argument" provided to the program is actually the
  // name of the executable (in our case, "a4").
  for (int argNum = 1; argNum < argc; ++argNum) {
    std::cout << "Argument " << argNum << " is: " << argv[argNum] << std::endl;
  }

  // TODO: First, parse the scene using SceneParser.
  // Then loop over each pixel in the image, shooting a ray
  // through that pixel and finding its intersection with
  // the scene.  Write the color at the intersection to that
  // pixel in your output image.
  ProgramArgs args = ProgramArgs::parse(argc, argv);  // parse the arguments and store in the ProgramArgs instance

  renderImage(&args);

  return 0;
}
