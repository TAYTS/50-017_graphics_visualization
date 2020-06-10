1. Surface vertices
   1.1 Since we are only rotating the vertices of the profile around the y-axis, we just need to compute the 3x3 rotation transformation matrix
   1.2 The rotation increment angle is calculated by 2*pi*(current_profile_step)/(total_steps) and it is computed from step 0 to (total_steps) [distribute the profile vertices around the y-axis/360degree based on the number of steps provided]
   1.3 Multiply the rotation transformation matrix with the profile vectors and append to the Surface.VV vector

2. Surfae normal
   2.1 Using the rotation transformation matrix that computed earlier in (1), compute its inverse then transpose it (based on the information provided in the handout) to get the transformation matrix for computing the rotated vertex normal
   2.2 As our profile normal vectors are computed counter-clockwise resulted that the normal vetors is facing toward the surface that we want to form later, we need to reverse the normal vector by simply negate the value of the normal vectors
   2.3 Multiply the reversed normal vectors with the transformation matrix computed earlier and append to the Surface.VF vector

3. Surface faces
   3.1 Get the current vertex index by using (current_profile_step)*(total_profile_vertices)+(current_profile_vertex_index)
   3.2 Get the next profile section corresponding vertex index by using ((computed_current_vertex_index)+(total_profile_vertices))%((total_profile_vertices)*(total_steps))
   3.3 Create a tuple that add the face vertices in the counter-clockwise order
        * - *      1 - 3      3
        | / |  =>  | /      / |
        * - *      2      1 - 2
   3.4 ** Skip the last vertex of the profile **

4. Draw smooth Surface
   4.1 Save the original OpenGL attributes
   4.2 If "shaded" is specify, set the following:
       4.2.1 glEnable(GL_LIGHTING) => Enable lighting
       4.2.2 glPolygonMode(GL_FRONT_AND_BACK, GL_FILL) => Fill the polygon(triangle)
   4.3 Else
       4.3.1 glDisable(GL_LIGHTING) => Disable the lighting
       4.3.2 glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) => Draw the polygons outline only
       4.3.3 glLineWidth(1) => Set the polygon lines width to 1
   4.4 Draw the triangle polygons using the glBegin(GL_TRIANGLES) and draw in counter-clockwise order as specified in the Surface.VF tuples
   4.5 Use glEnd() to stop the drawing and glPopAttrib() to reset to original OpenGL attributes

5. Draw vertex normals
   5.1 Save the original OpenGL attributes
   5.2 Set the attributes for drawing the vertex normal vector
       5.2.1 glDisable(GL_LIGHTING) => Disable the lighting
       5.2.2 glColor4f(0, 1, 1, 0) => Change the line color to cyan
       5.2.3 glLineWidth(1) => Set the polygon lines width to 1
   5.3 Draw the normal vectors using the glBegin(GL_LINES) and using the Surface.VV, Surface.VN and the length specified
   5.4 Use glEnd() to stop the drawing and glPopAttrib() to reset to original OpenGL attributes