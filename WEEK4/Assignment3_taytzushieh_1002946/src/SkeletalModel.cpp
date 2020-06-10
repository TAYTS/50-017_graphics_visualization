

#include "SkeletalModel.h"

using namespace std;


/*******************************************************************************/
/*****************************   Load .skel File    ****************************/
/*******************************************************************************/


// TODO: Load the skeleton from file here, create hierarchy of joints
void SkeletalModel::loadSkeleton( const char* filename )
{
   

}




/*******************************************************************************/
/************************   Draw Joints and Skeleton     ***********************/
/*******************************************************************************/

void SkeletalModel::draw(Matrix4f cameraMatrix, Matrix4f rotMatrix)
{
    if( m_joints.size() == 0 )
        return;

    // draw() gets called whenever a redraw is required
    // (after an update() occurs, when the camera moves, the window is resized, etc)
    Matrix4f Trans_model = Matrix4f(1, 0, 0, rotation_center_.x(), 0, 1, 0, rotation_center_.y(), 0, 0, 1, rotation_center_.z(), 0, 0, 0, 1);
    Matrix4f Trans_model_back = Matrix4f(1, 0, 0, -rotation_center_.x(), 0, 1, 0, -rotation_center_.y(), 0, 0, 1, -rotation_center_.z(), 0, 0, 0, 1);
    m_matrixStack.clear();
    m_matrixStack.push(cameraMatrix);
    m_matrixStack.push(Trans_model);
    m_matrixStack.push(rotMatrix);
    m_matrixStack.push(Trans_model_back);
 
    drawJoints();      
    drawSkeleton();
}

// TODO: draw joints of the skeleton
void SkeletalModel::drawJoints( )
{
    // Draw a sphere at each joint. You will need to add a recursive helper function to traverse the joint hierarchy.
    //
    // We recommend using glutSolidSphere( 0.025f, 12, 12 )
    // to draw a sphere of reasonable size.
    //
    // You are *not* permitted to use the OpenGL matrix stack commands
    // (glPushMatrix, glPopMatrix, glMultMatrix).
    // You should use your MatrixStack class
    // and use glLoadMatrix() before your drawing call.
}


// TODO: draw bones of the skeleton
void SkeletalModel::drawSkeleton( )
{
    // Draw boxes between the joints. You will need to add a recursive helper function to traverse the joint hierarchy.
 
}




/*******************************************************************************/
/*********************   Set Joint Angles for Transform     ********************/
/*******************************************************************************/

// TODO: Set the rotation part of the joint's transformation matrix based on the passed in Euler angles.
void SkeletalModel::setJointTransform(int jointIndex, float rX, float rY, float rZ)
{


}







