/***********************************************************************
 *
 *  Parametric Surface Modeler
 *
 *  Assignment 2 of SUTD Course 50.017 (May-Aug Term, 2020)
 *
 *  03/06/2020
 *
 *
 * Note: TODO functions of this assignment are in surf.cpp
 *
 ***********************************************************************/

/***********************************************************************/
/**************************   includes   *******************************/
/***********************************************************************/

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/OpenGL.h>
#elif defined _WIN32 || defined _WIN64
#include <glut.h>
#endif

#include "curve.h"
#include "math.h"
#include "parse.h"
#include "surf.h"
#include "vecmath.h"
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
#include <vector>

using namespace std;

/***********************************************************************/
/**************************   global variables   ***********************/
/***********************************************************************/

#define _ZNEAR 0.01
#define _ZFAR 100.0
#define _ROTSCALE 0.5

#define MAX_BUFFER_SIZE 1024

// Window size and position
int winW = 800;
int winH = 800;
int winPosX = 60;
int winPosY = 60;

// Current field of view
double currFovy = 60;

// Mouse interaction
GLint mouseModifiers = 0;
GLint mouseButton = 0;
int prevMouseX, prevMouseY;

// These STL Vectors store the control points, curves, and
// surfaces that will end up being drawn.  In addition, parallel
// STL vectors store the names for the curves and surfaces (as
// given by the files).
vector<vector<Vector3f>> gCtrlPoints;
vector<Curve> gCurves;
vector<string> gCurveNames;
vector<Surface> gSurfaces;
vector<string> gSurfaceNames;

// Render or hide curve/surface/normals
int showCurve = 1;
int showSurface = 1;
int showNormals = 1;

/***********************************************************************/
/*****************************   Init/Reset  ***************************/
/***********************************************************************/

void resetView() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0f, 0.0f,
               -7.5f); // move the object -5.0 along eye-Z away from eye
}

void resetProj() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(currFovy, winW / ((double)winH), _ZNEAR, _ZFAR);
  glMatrixMode(GL_MODELVIEW);
}

void initRendering() {
  GLfloat ambient[] = {0.3f, 0.3f, 0.3f, 1.0f};
  GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
  GLfloat diffuse[] = {0.5f, 0.5f, 0.9f, 1.0f};
  GLfloat shininess[] = {100.0};

  GLfloat position[] = {0.0f, 0.0f, 1.0f, 0.0f};

  ////////////////////////////////////////////////////////////////////
  // 1. various status

  glEnable(GL_DEPTH_TEST);
  glClearDepth(1.0f);
  glDepthFunc(GL_LESS);

  // Anti-aliasing
  glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
  glEnable(GL_POINT_SMOOTH);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  glEnable(GL_LINE_SMOOTH);

  // Auto-Normalization
  glEnable(GL_NORMALIZE);

  // Cull the back face (speedup and transparency)
  glCullFace(GL_BACK);

  ////////////////////////////////////////////////////////////////////
  // 2. set the projection and modelview

  resetView();

  ////////////////////////////////////////////////////////////////////
  // 3. Material

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);

  ////////////////////////////////////////////////////////////////////
  // 4. Lighting

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  glLightfv(GL_LIGHT0, GL_POSITION, position);

  glEnable(GL_LIGHTING); // Enable lighting calculations
  glEnable(GL_LIGHT0);

  glPopMatrix();
}

// Called when the window is resized
// w, h - width and height of the window in pixels.
void reshape(int w, int h) {
  winW = w;
  winH = h;

  glViewport(0, 0, winW, winH);

  resetProj();
}

/***********************************************************************/
/***************   Event Handler: keyboard function    **************/
/***********************************************************************/

// This function is called whenever a "Normal" key press is received.
void keyboard(unsigned char key, int x, int y) {

  const float rotateAngle = 5.0;
  const Vector3f rotateAxis = Vector3f(0, 1, 0);

  const float scale_out = 0.95;
  const float scale_in = 1.05;

  switch (key) {
  case 27: // Escape key
    exit(0);
    break;

  case 'C':
  case 'c':
    showCurve = (showCurve + 1) % 2;
    break;

  case 'S':
  case 's':
    showSurface = (showSurface + 1) % 2;
    break;

  case 'N':
  case 'n':
    showNormals = (showNormals + 1) % 2;
    break;

  case 'R':
  case 'r':
    // Reset the model pose
    resetView();
    break;

  default:
    cout << "Unhandled key press " << key << "." << endl;
  }

  // this will refresh the screen so that the user sees the color change
  glutPostRedisplay();
}

/***********************************************************************/
/***************   Event Handler: Mouse Click function    **************/
/***********************************************************************/

void mouse(int button, int state, int x, int y) {
  // flip it first
  y = winH - 1 - y;

  // since users might just use left/middle button to
  // close the pop-up menu, we cannot simply use XOR
  // here to compute mouseButton, we have to use two
  // cases here:
  if (state == GLUT_DOWN)
    mouseButton = mouseButton | (1 << (button));
  else
    mouseButton = mouseButton & (~(1 << (button)));

  mouseModifiers = glutGetModifiers();

  prevMouseX = x;
  prevMouseY = y;
}

/***********************************************************************/
/**************   Event Handler: Mouse Motion function    **************/
/***********************************************************************/

//// Mesh Transformation (Rotation)
void RotateModel(double angle, Vector3f axis) {
  double mat[16];

  glGetDoublev(GL_MODELVIEW_MATRIX, mat);
  glLoadIdentity();
  glTranslated(mat[12], mat[13], mat[14]);
  glRotated(angle, axis[0], axis[1], axis[2]);
  glTranslated(-mat[12], -mat[13], -mat[14]);

  glMultMatrixd(mat);
}

//// Mesh Transformation (Scaling)
void ScaleModel(double scale) {
  double mat[16];

  glGetDoublev(GL_MODELVIEW_MATRIX, mat);
  glLoadIdentity();
  glTranslated(mat[12], mat[13], mat[14]);
  glScaled(scale, scale, scale);
  glTranslated(-mat[12], -mat[13], -mat[14]);

  glMultMatrixd(mat);
}

void motion(int x, int y) {
  double mat[16];
  double tx, ty, nx, ny, scale, angle;
  int dx, dy;

  y = winH - 1 - y;
  dx = x - prevMouseX;
  dy = y - prevMouseY;

  if (dx == 0 && dy == 0)
    return;

  prevMouseX = x;
  prevMouseY = y;

  glMatrixMode(GL_MODELVIEW);

  switch (mouseButton) {

    ////////////////////////////////////////
    // LEFT BUTTON

  case 0x1:

    // Scale the model
    if (mouseModifiers == GLUT_ACTIVE_SHIFT) {
      if (dy > 0)
        scale = 1 + 0.001 * sqrt(dx * dx + dy * dy);
      else
        scale = 1 - 0.001 * sqrt(dx * dx + dy * dy);

      ScaleModel(scale);
    }

    // Rotate the model
    else {
      // Rotation
      nx = -dy;
      ny = dx;
      scale = sqrt(nx * nx + ny * ny);

      // We use "ArcBall Rotation" to compute the rotation axis and angle based
      // on the mouse motion
      nx = nx / scale;
      ny = ny / scale;
      angle = scale * _ROTSCALE * currFovy / 90.0;

      RotateModel(angle, Vector3f(nx, ny, 0));
    }

    glutPostRedisplay();

    break;

    ////////////////////////////////////////
    // MIDDLE BUTTON

  case 0x2:

    break;

    ////////////////////////////////////////
    // RIGHT BUTTON

  case 0x4:

    break;
  }
}

/******************************************************************************/
/********************************   Load SWP file  ****************************/
/******************************************************************************/

int LoadInput_SWP() {
  // local variables
  string inputString;
  Vector3f v;
  string s;
  char buffer[MAX_BUFFER_SIZE];

  // taking from standard input
  cout << "Please enter filename.swp: ";
  cin >> inputString;
  cout << "Displaying: " << inputString << endl;

  ifstream myfile(inputString);

  if (!myfile) {
    cerr << inputString << " not found\a" << endl;
    exit(0);
    return 1;
  }

  cerr << endl
       << "*** loading and constructing curves and surfaces ***" << endl;

  if (!parseFile(myfile, gCtrlPoints, gCurves, gCurveNames, gSurfaces,
                 gSurfaceNames)) {
    cerr << "\aerror in file format\a" << endl;
    myfile.close();
    exit(-1);
    return 1;
  }

  myfile.close();

  return 0;
}

/***********************************************************************/
/**********************   Drawing Routines   ***************************/
/***********************************************************************/

// Draw input curve
void RenderCurve() {
  GLuint gCurveLists;
  gCurveLists = glGenLists(1);
  glNewList(gCurveLists, GL_COMPILE);

  for (unsigned i = 0; i < gCurves.size(); i++) {
    drawCurve(gCurves[i], 0.0);
  }

  glEndList();

  glCallList(gCurveLists);
}

// Draw surface of revolution
void RenderSurface() {
  GLuint gSurfaceLists;
  gSurfaceLists = glGenLists(1);
  glNewList(gSurfaceLists, GL_COMPILE);

  for (unsigned i = 0; i < gSurfaces.size(); i++) {
    drawSurface(gSurfaces[i], true);
  }

  glEndList();

  glCallList(gSurfaceLists);
}

// Draw surface normals
void RenderNormals() {
  const float normalLen = 0.3f;

  GLuint gSurfaceLists;
  gSurfaceLists = glGenLists(1);
  glNewList(gSurfaceLists, GL_COMPILE);

  for (unsigned i = 0; i < gSurfaces.size(); i++) {
    drawNormals(gSurfaces[i], normalLen);
  }

  glEndList();

  glCallList(gSurfaceLists);
}

// This function is responsible for displaying the object.
void drawScene(void) {
  // Clear the rendering window
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (showCurve)
    RenderCurve();

  if (showSurface)
    RenderSurface();

  if (showNormals)
    RenderNormals();

  // Dump the image to the screen.
  glutSwapBuffers();
}

/***********************************************************************/
/**************************   Main program    **************************/
/***********************************************************************/

int main(int argc, char **argv) {
  int x = LoadInput_SWP();

  if (x == 1) {
    cout << "Unable to load file. Please check again." << endl;
    return 1;
  }

  glutInit(&argc, argv);

  // We're going to animate it, so double buffer
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  // Initial parameters for window position and size
  glutInitWindowPosition(winPosX, winPosY);
  glutInitWindowSize(winW, winH);
  glutCreateWindow("Assignment 2");

  // Initialize OpenGL parameters.
  initRendering();

  // Post Event Handlers
  glutReshapeFunc(reshape);
  glutDisplayFunc(drawScene);

  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);

  // Start the main loop.  glutMainLoop never returns.
  glutMainLoop();

  return 0; // This line is never reached.
}
