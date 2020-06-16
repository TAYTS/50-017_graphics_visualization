

#include "SkeletalModel.h"

using namespace std;

/*******************************************************************************/
/*****************************   Load .skel File ****************************/
/*******************************************************************************/

// TODO: Load the skeleton from file here, create hierarchy of joints
void SkeletalModel::loadSkeleton(const char *filename) {
  string filenameStr(filename);
  if (filenameStr.find(".skel") != string::npos) {
    ifstream fin(filenameStr, ios::in);
    if (!fin) {
      cerr << "Unable to open file." << endl;
      exit(1);
    }

    cout << "Loading model skeleton file: " << filenameStr << endl;

    string lineBuffer;
    while (getline(fin, lineBuffer)) {
      float x, y, z;
      int parentIdx;
      const char *skelJointData = lineBuffer.c_str();
      int match = sscanf(skelJointData, "%f %f %f %i", &x, &y, &z, &parentIdx);
      if (match != 4) {
        cout << "Failed to parse .skel file." << endl;
        exit(1);
      }

      // create new Joint instance
      Joint *joint = new Joint;

      // set joint transformation matrix relative to its parent joint
      Matrix4f joinTransMatrix = Matrix4f::identity();
      joinTransMatrix.setCol(3, Vector4f(x, y, z, 1));
      joint->transform = joinTransMatrix;

      // set the root joint if the parentIdx = -1
      if (parentIdx == -1) {
        // set the root joint for skeletal model
        m_rootJoint = joint;
      } else if (parentIdx >= 0) {
        // push the current joint instance to its parent children vector
        m_joints.at(parentIdx)->children.push_back(joint);
      } else {
        cerr << "Invalid parent joint index" << endl;
        exit(1);
      }

      // push the current joint instance to the skeletal model joints vector
      m_joints.push_back(joint);
    }

    // Close the file
    fin.close();
    cout << "Done loading .skel file" << endl;
    return;
  }

  cerr << "Invalid file" << endl;
  exit(1);
}

/*******************************************************************************/
/************************   Draw Joints and Skeleton ***********************/
/*******************************************************************************/

void SkeletalModel::draw(Matrix4f cameraMatrix, Matrix4f rotMatrix) {
  if (m_joints.size() == 0)
    return;

  // set the rotation centre at the root joint
  rotation_center_ = m_rootJoint->transform.getCol(3).xyz();

  // draw() gets called whenever a redraw is required
  // (after an update() occurs, when the camera moves, the window is resized,
  // etc)
  Matrix4f Trans_model =
      Matrix4f(1, 0, 0, rotation_center_.x(), 0, 1, 0, rotation_center_.y(), 0,
               0, 1, rotation_center_.z(), 0, 0, 0, 1);
  Matrix4f Trans_model_back =
      Matrix4f(1, 0, 0, -rotation_center_.x(), 0, 1, 0, -rotation_center_.y(),
               0, 0, 1, -rotation_center_.z(), 0, 0, 0, 1);
  m_matrixStack.clear();
  m_matrixStack.push(cameraMatrix);
  m_matrixStack.push(Trans_model);
  m_matrixStack.push(rotMatrix);
  m_matrixStack.push(Trans_model_back);

  setJointTransform(6, 120, 0, 0);
  drawJoints();
  drawSkeleton();
}

// TODO: draw joints of the skeleton
void SkeletalModel::drawJoints() {
  // Draw a sphere at each joint. You will need to add a recursive helper
  // function to traverse the joint hierarchy.
  //
  // We recommend using glutSolidSphere( 0.025f, 12, 12 )
  // to draw a sphere of reasonable size.
  //
  // You are *not* permitted to use the OpenGL matrix stack commands
  // (glPushMatrix, glPopMatrix, glMultMatrix).
  // You should use your MatrixStack class
  // and use glLoadMatrix() before your drawing call.
  drawJointsHelper(m_rootJoint);
}

void SkeletalModel::drawJointsHelper(Joint *jointNode) {
  // add the current joint transform matrix to the m_matrixStack
  m_matrixStack.push(jointNode->transform);

  // load the top of the m_matrixStack
  glLoadMatrixf(m_matrixStack.top());

  // draw the sphere
  glutSolidSphere(0.025f, 12, 12);

  // recursive call for each child joint
  for (Joint *j : jointNode->children) {
    drawJointsHelper(j);
  }

  // pop the current joint node transform matrix
  m_matrixStack.pop();
}

// TODO: draw bones of the skeleton
void SkeletalModel::drawSkeleton() {
  // Draw boxes between the joints. You will need to add a recursive helper
  // function to traverse the joint hierarchy.
  drawSkeletonHelper(m_rootJoint);
}

void SkeletalModel::drawSkeletonHelper(Joint *jointNode) {
  // add the current joint transform matrix to the m_matrixStack
  m_matrixStack.push(jointNode->transform);

  // translate in z direction matrix
  Matrix4f translateMatrix = Matrix4f::translation(Vector3f(0, 0, 0.5));

  for (Joint *j : jointNode->children) {
    Vector3f childVec = j->transform.getCol(3).xyz();

    Matrix4f scaleMatrix = Matrix4f::scaling(0.05, 0.05, childVec.abs());

    Vector3f z = childVec.normalized();
    Vector3f y = Vector3f::cross(z, Vector3f(0, 0, 1)).normalized();
    Vector3f x = Vector3f::cross(y, z).normalized();
    Matrix4f alignMatrix = Matrix4f(Vector4f(x, 0), Vector4f(y, 0),
                                    Vector4f(z, 0), Vector4f(0, 0, 0, 1));
    Matrix4f drawBoxTransMatrix = alignMatrix * scaleMatrix * translateMatrix;

    // push the drawBoxTransMatrix into the matrix stack
    m_matrixStack.push(drawBoxTransMatrix);

    // load the drawBoxTransMatrix
    glLoadMatrixf(m_matrixStack.top());

    // draw the skeleton box
    glutSolidCube(1.0f);

    // pop the drawBoxTransMatrix
    m_matrixStack.pop();

    // recursive draw the child joint
    drawSkeletonHelper(j);
  }

  // pop the current joint node transform matrix
  m_matrixStack.pop();
}

/*******************************************************************************/
/*********************   Set Joint Angles for Transform ********************/
/*******************************************************************************/

// TODO: Set the rotation part of the joint's transformation matrix based on
// the passed in Euler angles.
void SkeletalModel::setJointTransform(int jointIndex, float rX, float rY,
                                      float rZ) {
  Joint *joint = m_joints[jointIndex];
  Matrix3f rotateTransform =
      Matrix3f::rotateX(rX) * Matrix3f::rotateY(rY) * Matrix3f::rotateZ(rZ);
  joint->transform.setSubmatrix3x3(0, 0, rotateTransform);
}
