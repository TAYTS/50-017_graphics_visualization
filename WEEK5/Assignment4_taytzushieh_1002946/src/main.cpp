/***********************************************************************
 *
 *  Texture Mapping
 *
 *  Assignment 4 of SUTD Course 50.017 (May-Aug Term, 2020)
 *
 *  17/06/2020
 *
 *  Note: TODO functions are in the Texture Mapping section of this file
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

#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>
#include "math.h"
#include "OBJ_Loader.h"
#include "Helper.h"

using namespace std;

/***********************************************************************/
/**************************   global variables   ***********************/
/***********************************************************************/

#define _ZNEAR 0.1
#define _ZFAR 100.0

#define _ROTSCALE 0.5
#define MAX_BUFFER_SIZE 1024

#define IMG_WIDTH 64
#define IMG_HEIGHT 64

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

// OBJ model
objl::Loader objLoader;
Object objModel;

// Texture related
static GLuint texObj;
GLubyte* pBytes;

// Flags for rendering
bool showBBox = false;
bool showTexQuad = false;
bool showObject = true;
bool showTexture = false;

/***********************************************************************/
/**************************   Texture Mapping  *************************/
/***********************************************************************/

// TODO: fill this function to realize planar mapping
void calcPlanarMapping() {
  // calculate planar mapping
  // loop over all vertices and update objModel.vertices[i].t
  for (int i = 0; i < objModel.vertices.size(); i++) {
    objModel.vertices.at(i).t[0] = objModel.vertices.at(i).v[0] + 0.5;
    objModel.vertices.at(i).t[1] = objModel.vertices.at(i).v[1] + 0.5;
  }
}

// TODO: fill this function to realize cylindrical mapping
void calcCylindricalMapping() {
  // calculate cylindrical mapping
  // loop over all vertices and update objModel.vertices[i].t
  for (int i = 0; i < objModel.vertices.size(); i++) {
    float x = objModel.vertices.at(i).v[0];
    float y = objModel.vertices.at(i).v[1];
    float z = objModel.vertices.at(i).v[2];
    float angle = atan2f(z, x);

    objModel.vertices.at(i).t[S] = (angle + PI) / (2 * PI);
    objModel.vertices.at(i).t[T] = y + 0.5;
  }
}

// TODO: fill this function to realize spherical mapping
void calcSphericalMapping() {
  // calculate spherical mapping
  // loop over all vertices and update objModel.vertices[i].t
  for (int i = 0; i < objModel.vertices.size(); i++) {
    float x = objModel.vertices.at(i).v[0];
    float y = objModel.vertices.at(i).v[1];
    float z = objModel.vertices.at(i).v[2];
    float p = sqrtf(powf(x, 2) + powf(y, 2) + powf(z, 2));
    float theta = atan2f(z, x);
    float phi = acosf(y / p);

    objModel.vertices.at(i).t[S] = (theta + PI) / (2 * PI);
    objModel.vertices.at(i).t[T] = phi / PI;
  }
}

// TODO: fill this function to generate a 2D texture image
GLubyte* createTexImage() {
  // Store the 2D texture image in this array
  static GLubyte imgTexture[IMG_HEIGHT][IMG_WIDTH][3];

  const vector<vector<GLubyte>> colorMap = {
      {255, 0, 0},      // red
      {255, 255, 0},    // yellow
      {0, 255, 0},      // green
      {0, 255, 255},    // turquoise
      {0, 0, 255},      // blue
      {255, 0, 255},    // purple
      {255, 255, 255},  // white
      {0, 0, 0},        // black
  };
  const int numOfColor = colorMap.size();
  const int numRows = IMG_HEIGHT / numOfColor;
  const int numCols = IMG_WIDTH / numOfColor;
  const int blockHeight = IMG_HEIGHT / numOfColor;
  const int blockWidth = IMG_WIDTH / numOfColor;

  for (int r = 0; r < numRows; r++) {
    for (int c = 0; c < numCols; c++) {
      int colorIdx = (r + c) % numOfColor;
      for (int h = 0; h < blockHeight; h++) {
        for (int w = 0; w < blockWidth; w++) {
          imgTexture[r * blockHeight + w][c * blockWidth + h][0] = colorMap.at(colorIdx).at(0);
          imgTexture[r * blockHeight + w][c * blockWidth + h][1] = colorMap.at(colorIdx).at(1);
          imgTexture[r * blockHeight + w][c * blockWidth + h][2] = colorMap.at(colorIdx).at(2);
        }
      }
    }
  }

  return reinterpret_cast<GLubyte*>(imgTexture);
}

void initTexture() {
  /* create texture object, texture environment and
       download the texture (use createTexImage) */
  glGenTextures(1, &texObj);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  pBytes = createTexImage();
}

void setupTexture() {
  /* enable texturing and bind texture */
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texObj);
  gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, IMG_WIDTH, IMG_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pBytes);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void finishTexture() {
  /* disable texturing and unbind texture */
  glDisable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);
  glDeleteTextures(1, &texObj);
}

/***********************************************************************/
/*****************************   Init/Reset  ***************************/
/***********************************************************************/

void resetView() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0f, 0.0f, -1.6f);  // move the object -5.0 along eye-Z away from eye
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

  //GLfloat position[] = { 0.0f, 0.0f, 1.0f, 0.0f };
  GLfloat position[] = {0.0f, 0.0f, 5.0f, 1.0f};

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
  //glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

  glEnable(GL_LIGHTING);  // Enable lighting calculations
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
  switch (key) {
    case '1':
      showTexture = false;
      break;

    case '2':
      showTexture = true;
      calcPlanarMapping();
      break;

    case '3':
      showTexture = true;
      calcCylindricalMapping();
      break;

    case '4':
      showTexture = true;
      calcSphericalMapping();
      break;

    case 'O':
    case 'o':
      showObject = !showObject;
      break;

    case 'B':
    case 'b':
      showBBox = !showBBox;
      break;

    case 'Q':
    case 'q':
      showTexQuad = !showTexQuad;
      break;

    case 'R':
    case 'r':
      resetView();
      break;

    case 27:
      exit(0);
  }

  // force the redraw function
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

// Model Transformation (Rotation)
void RotateModel(double angle, double axisX, double axisY, double axisZ) {
  double mat[16];

  glGetDoublev(GL_MODELVIEW_MATRIX, mat);
  glLoadIdentity();
  glTranslated(mat[12], mat[13], mat[14]);
  glRotated(angle, axisX, axisY, axisZ);
  glTranslated(-mat[12], -mat[13], -mat[14]);

  glMultMatrixd(mat);
}

// Model Transformation (Scaling)
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

        // We use "ArcBall Rotation" to compute the rotation axis and angle based on the mouse motion
        nx = nx / scale;
        ny = ny / scale;
        angle = scale * _ROTSCALE * currFovy / 90.0;

        RotateModel(angle, nx, ny, 0);
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

/**************************************************************************/
/******************************   Load OBJ file  **************************/
/**************************************************************************/

// Scale the OBJ model such that its bounding box's max(W, H, D) = 1
void scaleToUnitBox(void) {
  Point maxP;
  Point minP;

  maxP[0] = maxP[1] = maxP[2] = -1e35;
  minP[0] = minP[1] = minP[2] = 1e35;

  Vector vBoxSize;
  Point bboxCenterP;

  for (unsigned int i = 0; i < objModel.vertices.size(); i++) {
    Vertex& v = objModel.vertices[i];

    if (v.v[0] < minP[0]) minP[0] = v.v[0];
    if (v.v[1] < minP[1]) minP[1] = v.v[1];

    if (v.v[2] < minP[2]) minP[2] = v.v[2];
    if (v.v[0] > maxP[0]) maxP[0] = v.v[0];

    if (v.v[1] > maxP[1]) maxP[1] = v.v[1];
    if (v.v[2] > maxP[2]) maxP[2] = v.v[2];
  }

  subPnt(vBoxSize, maxP, minP);

  addScaled(bboxCenterP, minP, vBoxSize, 0.5);

  float modelScale = 1.f / maxComponent3(vBoxSize);

  //fprintf(stderr, "original bbox : %f %f %f -> %f %f %f\n", minP[0], minP[1], minP[2], maxP[0], maxP[1], maxP[2]);
  //fprintf(stderr, "original bbox : %f %f %f | %f %f %f\n", bboxCenterP[0], bboxCenterP[1], bboxCenterP[2], vBoxSize[0], vBoxSize[1], vBoxSize[2]);
  //fprintf(stderr, "%f %f\n", maxComponent3(vBoxSize), modelScale);

  for (unsigned int i = 0; i < objModel.vertices.size(); i++) {
    Vertex& v = objModel.vertices[i];

    v.v[0] = (v.v[0] - bboxCenterP[0]) * modelScale;
    v.v[1] = (v.v[1] - bboxCenterP[1]) * modelScale;
    v.v[2] = (v.v[2] - bboxCenterP[2]) * modelScale;
  }

  objModel.bBox.minP[0] = (minP[0] - bboxCenterP[0]) * modelScale;
  objModel.bBox.minP[1] = (minP[1] - bboxCenterP[1]) * modelScale;
  objModel.bBox.minP[2] = (minP[2] - bboxCenterP[2]) * modelScale;

  objModel.bBox.maxP[0] = (maxP[0] - bboxCenterP[0]) * modelScale;
  objModel.bBox.maxP[1] = (maxP[1] - bboxCenterP[1]) * modelScale;
  objModel.bBox.maxP[2] = (maxP[2] - bboxCenterP[2]) * modelScale;

  objModel.bBox.vSize[0] = vBoxSize[0] * modelScale;
  objModel.bBox.vSize[1] = vBoxSize[1] * modelScale;
  objModel.bBox.vSize[2] = vBoxSize[2] * modelScale;
}

// Read obj file
bool LoadInput_OBJ() {
  // load the obj file here

  string inputString;

  //taking from standard input
  cout << "Please enter filename.obj: ";
  cin >> inputString;
  cout << "Displaying: " << inputString << endl;

  ifstream myfile(inputString);

  if (!myfile) {
    cerr << inputString << " not found\a" << endl;
    exit(0);
  }

  cerr << endl
       << "*** loading obj model ***" << endl;

  if (!objLoader.LoadFile(inputString)) {
    cerr << "\aerror in file format\a" << endl;
    myfile.close();
    return false;
  } else {
    //// only read the first mesh for simplicity
    objl::Mesh curMesh = objLoader.LoadedMeshes[0];

    Vertex tmpVertex;
    Face tmpFace;

    tmpVertex.v[3] = 1.f;
    tmpVertex.n[3] = 0.f;

    tmpVertex.t[S] = 0.f;
    tmpVertex.t[T] = 0.f;

    tmpVertex.c[R] = 1.f;
    tmpVertex.c[G] = 0.f;
    tmpVertex.c[B] = 0.f;

    // Go through each vertex and write its number,
    //  position, normal, and texture coordinate to Mesh object
    for (int j = 0; j < curMesh.Vertices.size(); j++) {
      tmpVertex.v[0] = curMesh.Vertices[j].Position.X;
      tmpVertex.v[1] = curMesh.Vertices[j].Position.Y;
      tmpVertex.v[2] = curMesh.Vertices[j].Position.Z;

      tmpVertex.n[0] = curMesh.Vertices[j].Normal.X;
      tmpVertex.n[1] = curMesh.Vertices[j].Normal.Y;
      tmpVertex.n[2] = curMesh.Vertices[j].Normal.Z;

      //// normalize the normal
      //double normal_length = sqrt(tmpVertex.n[0] * tmpVertex.n[0] + tmpVertex.n[1] * tmpVertex.n[1] + tmpVertex.n[2] * tmpVertex.n[2]);
      //tmpVertex.n[0] = tmpVertex.n[0] / normal_length;
      //tmpVertex.n[1] = tmpVertex.n[1] / normal_length;
      //tmpVertex.n[2] = tmpVertex.n[2] / normal_length;

      if (!objLoader.LoadedMaterials.empty()) {
        tmpVertex.t[0] = curMesh.Vertices[j].TextureCoordinate.X;
        tmpVertex.t[1] = curMesh.Vertices[j].TextureCoordinate.Y;
      }

      objModel.vertices.push_back(tmpVertex);
    }

    // Go through every 3rd index and write the
    //	triangle that these indices represent into Mesh object
    for (int j = 0; j < curMesh.Indices.size(); j += 3) {
      tmpFace.v1 = curMesh.Indices[j];
      tmpFace.v2 = curMesh.Indices[j + 1];
      tmpFace.v3 = curMesh.Indices[j + 2];

      objModel.faces.push_back(tmpFace);
    }
  }

  scaleToUnitBox();
  myfile.close();

  return true;
}

/***********************************************************************/
/**********************   Drawing Routines   ***************************/
/***********************************************************************/

void DrawTextureQuad() {
  setupTexture();

  glBegin(GL_QUADS);
  {
    glTexCoord2d(0.0, 0.0);
    glVertex2d(-0.5, -0.5);
    glTexCoord2d(1.0, 0.0);
    glVertex2d(0.5, -0.5);
    glTexCoord2d(1.0, 1.0);
    glVertex2d(0.5, 0.5);
    glTexCoord2d(0.0, 1.0);
    glVertex2d(-0.5, 0.5);
  }
  glEnd();

  finishTexture();
}

void DrawBoundingBox(void) {
  glDisable(GL_LIGHTING);

  glColor3f(0.0, 1.0, 0.0);

  glBegin(GL_LINE_LOOP);
  glVertex3f(objModel.bBox.minP[0], objModel.bBox.minP[1], objModel.bBox.minP[2]);
  glVertex3f(objModel.bBox.maxP[0], objModel.bBox.minP[1], objModel.bBox.minP[2]);
  glVertex3f(objModel.bBox.maxP[0], objModel.bBox.maxP[1], objModel.bBox.minP[2]);
  glVertex3f(objModel.bBox.minP[0], objModel.bBox.maxP[1], objModel.bBox.minP[2]);
  glEnd();

  glBegin(GL_LINE_LOOP);
  glVertex3f(objModel.bBox.minP[0], objModel.bBox.minP[1], objModel.bBox.maxP[2]);
  glVertex3f(objModel.bBox.maxP[0], objModel.bBox.minP[1], objModel.bBox.maxP[2]);
  glVertex3f(objModel.bBox.maxP[0], objModel.bBox.maxP[1], objModel.bBox.maxP[2]);
  glVertex3f(objModel.bBox.minP[0], objModel.bBox.maxP[1], objModel.bBox.maxP[2]);
  glEnd();

  glBegin(GL_LINES);
  glVertex3f(objModel.bBox.minP[0], objModel.bBox.minP[1], objModel.bBox.minP[2]);
  glVertex3f(objModel.bBox.minP[0], objModel.bBox.minP[1], objModel.bBox.maxP[2]);

  glVertex3f(objModel.bBox.maxP[0], objModel.bBox.minP[1], objModel.bBox.minP[2]);
  glVertex3f(objModel.bBox.maxP[0], objModel.bBox.minP[1], objModel.bBox.maxP[2]);

  glVertex3f(objModel.bBox.maxP[0], objModel.bBox.maxP[1], objModel.bBox.minP[2]);
  glVertex3f(objModel.bBox.maxP[0], objModel.bBox.maxP[1], objModel.bBox.maxP[2]);

  glVertex3f(objModel.bBox.minP[0], objModel.bBox.maxP[1], objModel.bBox.minP[2]);
  glVertex3f(objModel.bBox.minP[0], objModel.bBox.maxP[1], objModel.bBox.maxP[2]);
  glEnd();

  glEnable(GL_LIGHTING);
}

void DrawObject() {
  for (unsigned int i = 0; i < objModel.faces.size(); i++) {
    Vertex& v1 = objModel.vertices[objModel.faces[i].v1];
    Vertex& v2 = objModel.vertices[objModel.faces[i].v2];
    Vertex& v3 = objModel.vertices[objModel.faces[i].v3];

    glBegin(GL_TRIANGLES);
    {
      if (showTexture == true) {
        glTexCoord2f(v1.t[S], v1.t[T]);
      }

      glNormal3f(v1.n[0], v1.n[1], v1.n[2]);
      glVertex3f(v1.v[0], v1.v[1], v1.v[2]);

      if (showTexture == true) {
        glTexCoord2f(v2.t[S], v2.t[T]);
      }

      glNormal3f(v2.n[0], v2.n[1], v2.n[2]);
      glVertex3f(v2.v[0], v2.v[1], v2.v[2]);

      if (showTexture == true) {
        glTexCoord2f(v3.t[S], v3.t[T]);
      }

      glNormal3f(v3.n[0], v3.n[1], v3.n[2]);
      glVertex3f(v3.v[0], v3.v[1], v3.v[2]);
    }
    glEnd();
  }
}

// Main render function
void DrawScene() {
  // Just clean the screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (showTexQuad) DrawTextureQuad();
  if (showBBox) DrawBoundingBox();

  if (showObject) {
    if (showTexture == true) {
      setupTexture();
      DrawObject();
      finishTexture();
    }

    else {
      glEnable(GL_LIGHTING);
      DrawObject();
    }
  }

  // swap the buffers
  glutSwapBuffers();
}

/***********************************************************************/
/**************************   Main program    **************************/
/***********************************************************************/

int main(int argc, char** argv) {
  //// choose a way to load mesh (.m or .obj)
  //LoadInput_m("knot.m");
  if (!LoadInput_OBJ()) {
    cout << "Unable to load file. Please check again." << endl;
    return 1;
  }

  glutInit(&argc, argv);

  // We're going to animate it, so double buffer
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  // Initial parameters for window position and size
  glutInitWindowPosition(winPosX, winPosY);
  glutInitWindowSize(winW, winH);
  glutCreateWindow("Assignment 4");

  // Initialize OpenGL parameters.
  initRendering();

  // Post Event Handlers
  glutReshapeFunc(reshape);

  //// disp function is in Mesh.cpp
  glutDisplayFunc(DrawScene);

  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);

  initTexture();
  // Start the main loop.  glutMainLoop never returns.
  glutMainLoop();

  return 0;  // This line is never reached.
}
