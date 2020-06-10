#ifndef EXTRA_H
#define EXTRA_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/OpenGL.h>
#elif defined _WIN32 || defined _WIN64
#include <glut.h>
#include <windows.h>
#endif

// Inline functions to help with drawing
inline void glVertex( const Vector3f& a )
{
    glVertex3fv(a);
}

inline void glNormal( const Vector3f& a ) 
{
    glNormal3fv(a);
}

inline void glLoadMatrix( const Matrix4f& m )
{
    //glLoadMatrixf( m );
}

inline void glMultMatrix( const Matrix4f& m )
{
   // glMultMatrixf( m );
}

#endif
