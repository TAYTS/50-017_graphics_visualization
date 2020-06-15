#ifndef SKELETALMODEL_H
#define SKELETALMODEL_H

#ifdef WIN32
#include <windows.h>
#endif

#ifndef M_PI
#define M_PI 3.14159265358979f
#endif

#include <cstdlib>
#ifdef WIN32
#include <glut.h>
#else
#include <GLUT/glut.h>
#endif
#include "vecmath.h"
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

#include "Joint.h"
#include "MatrixStack.h"
#include "tuple.h"

class SkeletalModel {
public:
  // Part 1: Implement method to load a skeleton.
  // This method should compute m_rootJoint and populate m_joints.
  void loadSkeleton(const char *filename);

  // Part 2: Draw the skeleton.
  void draw(Matrix4f cameraMatrix, Matrix4f rotMatrix);

  // 2.1. Implement this method with a recursive helper to draw a sphere at each
  // joint.
  void drawJoints();
  void drawJointsHelper(Joint *);

  // 2.2. Implement this method a recursive helper to draw a box between
  // each pair of joints
  void drawSkeleton();
  void drawSkeletonHelper(Joint *);

  // Part 3: Implement this method to handle changes to your skeleton given
  // changes of joints angles
  void setJointTransform(int jointIndex, float rX, float rY, float rZ);

  double globalAngle_;
  Vector3f globalAxis_;

private:
  // pointer to the root joint
  Joint *m_rootJoint;
  // the list of joints.
  std::vector<Joint *> m_joints;
  Vector3f rotation_center_;

  MatrixStack m_matrixStack;
};

#endif
