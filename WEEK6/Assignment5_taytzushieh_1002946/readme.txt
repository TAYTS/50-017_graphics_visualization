1. Ray Tracing Pipeline
   1.1 Argument Parsing
       1.1.1 Created a new class "ProgramArgs" to store the command line arguments and it exposes a static method for parsing the arguments and return class instance.
   1.2 Image pre-processing/normalisation
       1.2.1 Set all the pixels in the image to the background color
       1.2.1 Normalize the image width & height to [-1:1]
       1.2.2 Image x-axis pixels is normalized using formula:
             2 * (x / (imageWidth - 1.0f)) - 1.0f
       1.2.3 Image y-axis pixels is normalized using formula:
             2 * (y / (imageHeight - 1.0f)) - 1.0f
       1.2.4 Formula reference from: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays
   1.3 Ray generation
       1.3.1 Pass the image pixel coordinates to the camera object to generate the ray vectors
   1.4 Compute lighting/color
       1.4.1 If the ray generated earlier interect with the objects in the group compute the ambient, diffuse, and specular lighting/color
       1.4.2 Ambient light is computed by multiplying the object diffuse color with the ambient light
       1.4.3 For diffuse and specular lighting, combine all the lightings from different light sources and add to the ambient lighting computed earlier
       1.4.4 The lighting at each pixels can be computed using the "getIllumination" method provided by the Light class and get the intersection point using the closest t parameter from the Hit class
       1.4.4 Set the image pixel color using the computed shaded color

2. Ray Generation
   2.1 Compute the extrinsic camera parameter w, u and v using the formulas provided in the handout
   2.2 Pre-compute the view transformation matrix for convert standard camera view to extrinsic camera view as the ray generation is based on standard camera (Reference lecture 8)
   2.3 Compute the field of view angle using tan(angle / 2.0f)
   2.4 Compute the ray direction (standard camera) by multiplying the point with the field of view to zoom in/out of the viewing scope
   2.5 Multiple the ray direction with the view transformation matrix and normalize to get the ray direction vector in the extrinsic camera view
   2.6 Create Ray instance using the extrinsic camera center and the normalized ray direction vector

3. Ray Intersection
   3.1 Group
       3.1.1 Pre-allocate space for storing all the objects based on the initialisation parameter
       3.1.2 Do boundary check before adding new object into the group
       3.1.3 Run "intersect" method for every objects in the group to make sure the ray parameter, t stored in the Hit is the closest to the camera
   3.2 Transform
       3.2.1 Reference from: https://www.scratchapixel.com/lessons/3d-basic-rendering/transforming-objects-using-matrices
       3.2.2 Transform the ray origin and direction using the transformation matrix by multiplying with the inverse of the transformation matrix and generate new Ray instance using the new origin and direction
       3.2.3 If the new ray intersects with the object, then compute the new normal vector by multiplying the computed normal vector of the Hit with the transpose of the inversed transformation matrix
       3.2.4 Update the Hit with the new normal vector
   3.3 Sphere
       3.3.1 Solve the ray parameter, t using quadratic equation by rearrange the || o + td - c || - r = 0 where
             a => d . d
             b => 2 * (d . (o - c))
             c => (o - c) . (o - c) - (r * r)
       3.3.2 Calculate the intersection points and the point must be (>tmin) and (<stored t in Hit) which is mean that the intersection point has to be in the positive direction of the ray and closest to the camera
       3.3.3 Compute the point normal by using the vector to the intersection point on the sphere surface (world coordinate) minus the vector to sphere center (world coordinate) which is radius vector of the sphere
       3.3.4 Normalize the normal vector and together with the computed ray parameter, t to update the Hit instance accordingly
   3.4 Plane
       3.4.1 Compute the ray parameter,t by solving the t using the formula:
             n(o + td) - d = 0
       3.4.2 If the computed t is (>tmin) and (<stored t in Hit), then update the Hit instance accordingly
   3.5 Triangle
       3.5.1 Solve the beta, gamma and parameter,t using Cramer rule
       3.5.2 If the computed t is (>tmin) and (<stored t in Hit) and (beta + gamma <= 1.0f) and (beta >= 0.0f) and (gamma >= 0.0f), then compute the triangle normal using the formula provided in the handout

4. Lighting Computation
   4.1 Compute the diffuse light intensity using the formula in lecture 9
   4.2 If the diffuse light intensity is greater than 0 (above the x-axis), then add the diffuse lighting to the shaded color by multiplying it with the material diffuse color and light source color
   4.3 Compute the specular light intensity using the formula in the lecture 9 and need to reverse the ray direction as it is in the opposite direction of the reflection direction
   4.4 If the diffuse light intensity and specular light intensity is (>0), then add the specular lighting to the shaded color by raising the specular light intensity to the power of the shininess then multiply it with the material specular color and light source color