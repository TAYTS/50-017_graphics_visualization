#include "surf.h"

using namespace std;

namespace
{
    
    // We're only implenting swept surfaces where the profile curve is
    // flat on the xy-plane.  This is a check function.
    static bool checkFlat(const Curve &profile)
    {
        for (unsigned i=0; i<profile.size(); i++)
            if (profile[i].V[2] != 0.0 ||
                profile[i].T[2] != 0.0 ||
                profile[i].N[2] != 0.0)
                return false;
        
        return true;
    }
}

Matrix3f getRotationalMatrix(float angle){
    Matrix3f rotMat(cos(angle), 0, sin(angle), 0, 1, 0, -1*sin(angle), 0, cos(angle));
    return rotMat;
}


// TODO: Create surface of revolution from a profile curve
Surface makeSurfRev(const Curve &profile, unsigned steps)
{
    Surface surface;


    return surface;
}


// TODO: Draw surface of revolution as a triangle mesh
void drawSurface(const Surface &surface, bool shaded)
{
   
}

// TODO: Draw normals for vertices on the surface
void drawNormals(const Surface &surface, float len)
{
   
}




