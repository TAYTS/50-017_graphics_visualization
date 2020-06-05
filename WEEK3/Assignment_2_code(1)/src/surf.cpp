#include "surf.h"

using namespace std;

namespace {

// We're only implenting swept surfaces where the profile curve is
// flat on the xy-plane.  This is a check function.
static bool checkFlat(const Curve &profile) {
  for (unsigned i = 0; i < profile.size(); i++)
    if (profile[i].V[2] != 0.0 || profile[i].T[2] != 0.0 ||
        profile[i].N[2] != 0.0)
      return false;

  return true;
}
} // namespace

Matrix3f getRotationalMatrix(float angle) {
  Matrix3f rotMat(cos(angle), 0, sin(angle), 0, 1, 0, -1 * sin(angle), 0,
                  cos(angle));
  return rotMat;
}

// TODO: Create surface of revolution from a profile curve
Surface makeSurfRev(const Curve &profile, unsigned steps) {
  Surface surface;

  if (!checkFlat(profile)) {
    cerr << "Profile is not flat on the xy-plane." << endl;
    exit(0);
  }

  Curve surfaceVertices;
  Matrix4f rotateTransform;

  unsigned profileSize = profile.size();

  for (unsigned step = 0; step < steps; step++) {
    float rotateRad = 2 * M_PI * step / steps;
    Matrix3f rotateMatrix = getRotationalMatrix(rotateRad);
    Matrix3f invTransp = rotateMatrix.inverse().transposed();

    // push the surface vertices of each rotation step
    for (unsigned i = 0; i < profileSize; i++) {
      // rotate the profile curve vertex
      surface.VV.push_back(rotateMatrix * profile.at(i).V);

      // get the reverse normal vector of each profile curve vertex for the
      // lighting calculations to work properly (pointing away from surface)
      Vector3f newVN = profile.at(i).N;
      newVN.negate();

      // rotate the normal vector
      surface.VN.push_back((invTransp * newVN));

      // calculate the faces using all the vertices except the last vertex
      if (i < profileSize) {
        /*
         *   * - *      1 - 3      3
         *   | / |  =>  | /      / |
         *   * - *      2      1 - 2
         */
        // current "step" profile curve vertex
        unsigned curVtxIdx = step * profileSize + i;
        // next corresponding "step" profile curve vertex
        unsigned nextVtxIdx = (curVtxIdx + profileSize) % (profileSize * steps);

        // first triangle face
        surface.VF.push_back(Tup3u(curVtxIdx, curVtxIdx + 1, nextVtxIdx));
        // second triangle face
        surface.VF.push_back(Tup3u(curVtxIdx + 1, nextVtxIdx + 1, nextVtxIdx));
      }
    }
  }

  return surface;
}

// TODO: Draw surface of revolution as a triangle mesh
void drawSurface(const Surface &surface, bool shaded) {
  // save the current OpenGL attributes
  glPushAttrib(GL_ALL_ATTRIB_BITS);

  // setup the rendering attributes
  if (shaded) {
    glEnable(GL_LIGHTING);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
  } else {
    glDisable(GL_LIGHTING);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(1);
  }

  // draw the surface
  glBegin(GL_TRIANGLES);
  for (unsigned i = 0; i < surface.VF.size(); i++) {
    glNormal(surface.VN[surface.VF[i][0]]);
    glVertex(surface.VV[surface.VF[i][0]]);
    glNormal(surface.VN[surface.VF[i][1]]);
    glVertex(surface.VV[surface.VF[i][1]]);
    glNormal(surface.VN[surface.VF[i][2]]);
    glVertex(surface.VV[surface.VF[i][2]]);
  }
  glEnd();

  // reset to previous OpenGL attributes
  glPopAttrib();
}

// TODO: Draw normals for vertices on the surface
void drawNormals(const Surface &surface, float len) {
  // save the current OpenGL attributes
  glPushAttrib(GL_ALL_ATTRIB_BITS);

  // setup the rendering attributes
  glDisable(GL_LIGHTING);
  glColor4f(0, 1, 1, 0);
  glLineWidth(1);

  // draw the normal vectors
  glBegin(GL_LINES);
  for (unsigned i = 0; i < surface.VV.size(); i++) {
    glVertex(surface.VV[i]);
    glVertex(surface.VV[i] + surface.VN[i] * len);
  }
  glEnd();

  // reset to previous OpenGL attributes
  glPopAttrib();
}
