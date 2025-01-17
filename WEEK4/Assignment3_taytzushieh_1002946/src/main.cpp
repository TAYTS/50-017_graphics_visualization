/***********************************************************************
 *
 *  Hierarchical Modeling
 *
 *  Assignment 3 of SUTD Course 50.017 (May-Aug Term, 2020)
 *
 *  10/06/2020
 *
 *
 *  Note: TODO functions of this assignment are in SkeletalModel.cpp
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
#include "vecmath.h"
#include <fstream>
#include <chrono>
#include <thread>
#include "math.h"
#include "SkeletalModel.h"
using namespace std;



/***********************************************************************/
/**************************   global variables   ***********************/
/***********************************************************************/


#define _ZNEAR        0.1
#define _ZFAR       100.0
#define _ROTSCALE     0.02

#define MAX_BUFFER_SIZE   1024
#define MY_PI 3.14159

// Window size and position
int winW = 800;
int winH = 800;
int winPosX = 60;
int winPosY = 60;

// Current field of view
double currFovy = 60;

// Mouse interaction
GLint mouseModifiers = 0 ;
GLint mouseButton    = 0 ;
int prevMouseX , prevMouseY ;


//// skeletal related
SkeletalModel myModel;
Matrix4f cameraMatrix(1, 0, 0, -0.5, 0, 1, 0, -0.5, 0, 0, 1, -1.6, 0, 0, 0, 1);
Matrix4f rotMatrix = Matrix4f::identity();




/***********************************************************************/
/*****************************   Init/Reset  ***************************/
/***********************************************************************/

void resetView()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //glTranslatef ( 0.0f , 0.0f , -3.0f ) ;  // move the object -5.0 along eye-Z away from eye
}

void resetProj()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(currFovy, winW/((double)winH), _ZNEAR, _ZFAR);
    glMatrixMode(GL_MODELVIEW);
}

void initRendering()
{
    GLfloat ambient[]  = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat diffuse[] = {  0.5f, 0.5f, 0.9f, 1.0f };
    GLfloat shininess[] = {100.0};

    GLfloat position[] = { 0.0f, 0.0f, 1.0f, 0.0f };


    ////////////////////////////////////////////////////////////////////
    // 1. various status

    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0f);
    glDepthFunc(GL_LESS);

    // Anti-aliasing
    glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
    glEnable(GL_LINE_SMOOTH);

    // Auto-Normalization
    glEnable(GL_NORMALIZE);

    // Cull the back face (speedup and transparency)
    glCullFace( GL_BACK );


    ////////////////////////////////////////////////////////////////////
    // 2. set the projection and modelview

    resetView();


    ////////////////////////////////////////////////////////////////////
    // 3. Material

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);


    ////////////////////////////////////////////////////////////////////
    // 4. Lighting

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    //glLightfv(GL_LIGHT0, GL_AMBIENT,  ambient);
    //glLightfv(GL_LIGHT0, GL_DIFFUSE,  diffuseColor);
    //glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glEnable(GL_LIGHTING);     // Enable lighting calculations
    glEnable(GL_LIGHT0);

    glPopMatrix();
}

// Called when the window is resized
// w, h - width and height of the window in pixels.
void reshape(int w, int h)
{
    winW = w;
    winH = h;

    glViewport(0, 0, winW, winH);

    resetProj(); 
}




/***********************************************************************/
/***************   Event Handler: keyboard function    **************/
/***********************************************************************/


// This function is called whenever a "Normal" key press is received.
void keyboard( unsigned char key, int x, int y )
{
    switch ( key )
    {
        case 27: // Escape key
            exit(0);
            break;

        case 'r':
            // reset modelMatrix;
			rotMatrix = Matrix4f::identity();
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

void mouse(int button, int state, int x, int y)
{
    // flip it first
    y = winH - 1 - y;

    // since users might just use left/middle button to 
    // close the pop-up menu, we cannot simply use XOR
    // here to compute mouseButton, we have to use two 
    // cases here:
    if (state == GLUT_DOWN)
        mouseButton = mouseButton|(1<<(button));
    else
        mouseButton = mouseButton&(~(1<<(button)));

    mouseModifiers = glutGetModifiers();

    prevMouseX = x;
    prevMouseY = y;
}




/***********************************************************************/
/**************   Event Handler: Mouse Motion function    **************/
/***********************************************************************/

// Model Transformation (Rotation)
void RotateModel(double angle, Vector3f axis)
{
    Matrix4f transMatrix  = Matrix4f::rotation(axis, angle);
    Matrix4f newRotMatrix = rotMatrix * transMatrix;
    rotMatrix = newRotMatrix;
}


// Model Transformation (Scaling)
void ScaleModel(double scale)
{
    rotMatrix(0, 0) = scale * rotMatrix(0, 0);
    rotMatrix(1, 1) = scale * rotMatrix(1, 1);
    rotMatrix(2, 2) = scale * rotMatrix(2, 2);
}


void motion ( int x , int y )
{
    double mat[16] ;
    double tx , ty , nx , ny , scale , angle ;
    int    dx , dy ;

    y  = winH - 1 - y   ;
    dx = x - prevMouseX ;
    dy = y - prevMouseY ;

    if ( dx == 0 && dy == 0 )
    return ;

    prevMouseX = x ;
    prevMouseY = y ;

    glMatrixMode ( GL_MODELVIEW ) ;


    switch ( mouseButton )
    {

      ////////////////////////////////////////
      // LEFT BUTTON

      case 0x1:

      // Scale the model
      if( mouseModifiers == GLUT_ACTIVE_SHIFT)
      {
        if( dy > 0 )
            scale = 1 + 0.001*sqrt(dx*dx + dy*dy);
        else
            scale = 1 - 0.001*sqrt(dx*dx + dy*dy);

		ScaleModel( scale );
      }

      // Rotate the model
      else
      {
        // Rotation
        nx    = -dy;
        ny    =  dx;
        scale = sqrt(nx*nx + ny*ny);

        // We use "ArcBall Rotation" to compute the rotation axis and angle based on the mouse motion
        nx    = nx / scale;
        ny    = ny / scale;
        angle = scale * _ROTSCALE * currFovy/90.0;

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




/************************************************************************/
/*****************************   Load SKEL file  ************************/
/************************************************************************/

// Load the .skel file here
void LoadInput()
{
    //local variables
    string inputString;
  
    cout << "Please enter filename.skel: ";
    cin >> inputString;
    cout << "Displaying: " << inputString <<endl;

    myModel.loadSkeleton(inputString.data());
}




/***********************************************************************/
/**********************   Drawing Routines   ***************************/
/***********************************************************************/

// This function is responsible for displaying the object.
void drawScene(void)
{
    // Clear the rendering window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    myModel.draw(cameraMatrix, rotMatrix);

    // Dump the image to the screen.
    glutSwapBuffers(); 
}




/***********************************************************************/
/**************************   Main program    **************************/
/***********************************************************************/

int main( int argc, char** argv )
{
    LoadInput();

    glutInit(&argc,argv);
    
    // We're going to animate it, so double buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    
    // Initial parameters for window position and size
    glutInitWindowPosition( winPosX, winPosY );
    glutInitWindowSize( winW, winH );
    glutCreateWindow("Assignment 3");
    
    // Initialize OpenGL parameters.
    initRendering();

    // Post Event Handlers
    glutReshapeFunc( reshape );
    glutDisplayFunc( drawScene );
    
    glutKeyboardFunc(keyboard); 
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    // Start the main loop.  glutMainLoop never returns.
    glutMainLoop( );
    
    return 0;	// This line is never reached.
}


