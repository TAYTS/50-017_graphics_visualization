#include "curve.h"
#include "extra.h"
#ifdef WIN32
#include <windows.h>
#endif
#include <OpenGL/gl.h>
using namespace std;

namespace
{
    // Approximately equal to.  We don't want to use == because of
    // precision issues with floating point.
    inline bool approx( const Vector3f& lhs, const Vector3f& rhs )
    {
        const float eps = 1e-8f;
        return ( lhs - rhs ).absSquared() < eps;
    }
    
    
}

Vector3f findBinormal(Vector3f Tangent){
    
    float z = 1;
    float x = 1;
    float y = (- Tangent[0] - Tangent[2])/Tangent[1];
    Vector3f Bn (x,y,z);
    Bn.normalize();
    return Bn;
}

bool startState = false;
bool calledByBspline = false;
Vector3f previousB;

Curve evalBezier( const vector< Vector3f >& P, unsigned steps )
{
    // Check
    if( P.size() < 4 || P.size() % 3 != 1 )
    {
        cerr << "evalBezier must be called with 3n+1 control points." << endl;
        exit( 0 );
    }
    
    //Define start and end point. 20 step means 20 points generated between start and end. Increment is by: 1/20, since t is between 0 and 1
    Curve Bezier( steps+1 );
    Vector3f Pt(0,0,0);
    Vector3f Tg(0,0,0);
    Vector3f Nr(0,0,0);
    Vector3f Bn(0,0,0);
    
    Vector4f prePt;
    Vector4f prePtDerivative;
    
    
    float t = 0.0;
    float increment = 1.0/steps;
    Matrix4f Bernstein(1.0, -3.0, 3.0, -1.0, 0, 3, -6, 3, 0, 0, 3, -3, 0, 0, 0, 1);
    //Vector4f basis(1,t, pow(t,2), pow(t,3) );
    Matrix4f Geometry;
    
    cerr << "\t>>> evalBezier has been called with the following input:" << endl;
    
    cerr << "\t>>> Control points (type vector< Vector3f >): "<< endl;
    
    for( unsigned i = 0; i < P.size(); ++i )
    {
        Geometry(0,i) = P[i][0];
        Geometry(1,i) = P[i][1];
        Geometry(2,i) = P[i][2];
    }
    //getting Point and Tangent
    
    for (unsigned i = 0; i <= steps; i++){
        t = i*increment;
        Vector4f basis(1,t, pow(t,2), pow(t,3) );
        Vector4f basisDerivative(0, 1, t*2 , pow(t,2)*3);
        Vector4f basisSecondDerivative(0, 0, t, 6*t);
        prePt = Geometry * (Bernstein * basis);
        prePtDerivative = Geometry * (Bernstein * basisDerivative);
        Pt[0] = prePt[0];
        Pt[1] = prePt[1];
        Pt[2] = prePt[2];
        prePtDerivative.normalize();
        Tg[0] = prePtDerivative[0];
        Tg[1] = prePtDerivative[1];
        Tg[2] = prePtDerivative[2];
        
        //getting Binormal
        if (startState == false){
            startState = true;
            
            previousB = Vector3f(0,0,1);
            
        }
        // N1 = B0 x Tg1, B1 = Tg1 x N1
        Nr = Nr.cross(previousB,Tg).normalized();
        Bn = Bn.cross(Tg, Nr).normalized();
        previousB = Bn;
//        Nr[2] = 0;
        
        Bezier[i].V = Pt;
        Bezier[i].T = Tg;
        Bezier[i].B = Bn;
        Bezier[i].N = Nr;
    }
    
    if (calledByBspline == false){
        cout << "notcalled by B spline anymore" << endl;
        startState = false;
    }
    cerr << "\t>>> Returning bezier curve." << endl;
    return Bezier;
}

//Bspline can have more than 4control points, need to move 4 by 4 and call the evalBezier
Curve evalBspline( const vector< Vector3f >& P, unsigned steps )
{
    int stepp = (int) steps;
    int numberOfPoints = ( (int)P.size() - 4 ) * (stepp+1) + stepp + 1;
    Curve Bspline(numberOfPoints);
    int counter = 0;
    vector<Vector3f> fourP;
    
    for (unsigned i = 0; i< 4; i++){
        fourP.push_back(Vector3f(0,0,0));
    }
    
    //  Change the control points to: GB2B1-1
    float oneSix = 1.0/6.0;
    Matrix4f Bernstein(1.0, -3.0, 3.0, -1.0, 0, 3, -6, 3, 0, 0, 3, -3, 0, 0, 0, 1);
    Matrix4f BSpline (1*oneSix, -3*oneSix, 3*oneSix, -1*oneSix, 4*oneSix, 0*oneSix, -6*oneSix, 3*oneSix, 1*oneSix, 3*oneSix, 3*oneSix, -3*oneSix, 0*oneSix, 0*oneSix,0*oneSix ,1*oneSix);
    Matrix4f Geometry;
    
    // Check
    cout << P.size() << "this is size of p" << endl;
    if( P.size() < 4 )
    {
        cerr << "evalBspline must be called with 4 or more control points." << endl;
        exit( 0 );
    }
    
    
    cerr << "\t>>> evalBSpline has been called with the following input:" << endl;
    
    cerr << "\t>>> Control points (type vector< Vector3f >): "<< endl;
    calledByBspline = true;
    cout << "bspline calling" << endl;
    for (unsigned g = 0; g < P.size(); g++){
        vector<Vector3f> newP;
        //Get p1-4 to fourP
        if ((g+4) > P.size()){
            cout << "Finished" << endl;
            break;
        }
        else{
            cout << "Not finished yet" << endl;
            for (unsigned k = 0; k < 4; k++){
                fourP[k] = P[k+g];
            }
            
            for( unsigned i = 0; i < fourP.size(); ++i )
            {
                Geometry(0,i) = fourP[i][0];
                Geometry(1,i) = fourP[i][1];
                Geometry(2,i) = fourP[i][2];
                newP.push_back(Vector3f(0,0,0));
            }
            //G B2 B1-1 is the new point for B1 which is bezier curve
            Geometry = Geometry * BSpline;
            Geometry = Geometry * Bernstein.inverse();
            for (unsigned i = 0; i<fourP.size(); i++){
                newP[i][0] = Geometry(0,i);
                newP[i][1] = Geometry(1,i);
                newP[i][2] = Geometry(2,i);
            }
            
            
            
            cerr << "\t>>> Steps (type steps): " << steps << endl;
            
            Curve cr = evalBezier(newP, steps);
            for (unsigned l = 0 ; l<cr.size(); l++){
                Bspline[counter].B = cr[l].B ;
                Bspline[counter].N = cr[l].N  ;
                Bspline[counter].T = cr[l].T ;
                Bspline[counter].V= cr[l].V ;
                counter ++;
            }
            
        }
    }

    
    // if the first and the last vertex is at the same location, but diff normal values,
    if (approx(Bspline.back().V, Bspline.front().V) && !approx(Bspline.back().N,Bspline.front().N)) {
        
        float angle = acos( Vector3f::dot(Bspline.back().N, Bspline.front().N));
        printf("Angle is: %f \n", angle);
        
        float angleStep = angle / (Bspline.size() - 1);
        
        //check if the last normal is aligned when you do negative rotation (opp right hand rule)
        Vector3f new_n = Matrix3f::rotation(Bspline[Bspline.size()-1].T, -angle)*Bspline[Bspline.size()-1].N;
        
        float currAngle;
        // if yes, rotate every vertex from 1 to end in negative direction (thumb at tangent, opposite fingers direction)
        if (Vector3f::dot(new_n, Bspline[Bspline.size()-1].N) > 0.00001){
            currAngle = -angleStep;
            angleStep = -angleStep;
        }
        else{
            // else, rotate every vertex from 1 to end in positive direction (thumb at tangent, follow right hand rule)
            currAngle = angleStep;
        }
        
        
        // rotate every point after the start by a fixed step
        for (long i = 1; i < Bspline.size(); i++) {
            //rotate the normal and binormal wrt to tangent as axis
            Bspline[i].B = Matrix3f::rotation(Bspline[i].T, currAngle)*Bspline[i].B ;
            Bspline[i].N = Matrix3f::rotation(Bspline[i].T, currAngle)*Bspline[i].N;
            // adds more step
            currAngle += angleStep;
        }
    }   
    
    cerr << "\t>>> Returning Bspline curve." << endl;
    calledByBspline = false;
    return Bspline;
}


void drawCurve( const Curve& curve, float framesize )
{
    // Save current state of OpenGL
    glPushAttrib( GL_ALL_ATTRIB_BITS );
    
    // Setup for line drawing
    glDisable( GL_LIGHTING );
    glColor4f( 1, 1, 1, 1 );
    glLineWidth( 1 );
    
    // Draw curve
    glBegin( GL_LINE_STRIP );
    for( unsigned i = 0; i < curve.size(); ++i )
    {
        glVertex( curve[ i ].V );
    }
    glEnd();
    
    glLineWidth( 1 );
    
    // Draw coordinate frames if framesize nonzero
    if( framesize != 0.0f )
    {
        Matrix4f M;
        
        for( unsigned i = 0; i < curve.size(); ++i )
        {
            M.setCol( 0, Vector4f( curve[i].N, 0 ) );
            M.setCol( 1, Vector4f( curve[i].B, 0 ) );
            M.setCol( 2, Vector4f( curve[i].T, 0 ) );
            M.setCol( 3, Vector4f( curve[i].V, 1 ) );
            
            glPushMatrix();
            glMultMatrixf( M );
            glScaled( framesize, framesize, framesize );
            glBegin( GL_LINES );
            glColor3f( 1, 0, 0 ); glVertex3d( 0, 0, 0 ); glVertex3d( 1, 0, 0 );
            glColor3f( 0, 1, 0 ); glVertex3d( 0, 0, 0 ); glVertex3d( 0, 1, 0 );
            glColor3f( 0, 0, 1 ); glVertex3d( 0, 0, 0 ); glVertex3d( 0, 0, 1 );
            glEnd();
            glPopMatrix();
        }
    }
    
    // Pop state
    glPopAttrib();
}

