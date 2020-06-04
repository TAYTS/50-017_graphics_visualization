To run the program:
program_binary_output <path_to_obj_file>

1. Mesh Loading
   a. check the file has the correct extension
   b. open the .obj file and read line by line
   c. if the line start with 'v ', create Vector3f instance and add to global variable vecv
   d. if the line start with 'vt', create Vector3f instance and add to global variable vect
   e. if the line start with 'vn', create Vector3f instance and add to global variable vecn
   f. if the line start with 'f ', parse the line with respect to 'a/b/c d/e/f g/h/i' and create an unsigned array and add it to the global variable vecf
   g. close the file after finish reading
   h. return 0 if no error else return 1

2. Mesh Display
   a. for loop the face vector stored in the global variable vecf and set the 'glNormal3d' and 'glVertex3d' with the respective pair: 'a-c', 'd-f', 'g-i'

3. Mesh Coloring
   a. replace the global variable diffuseColor array with the colorTable on the current 'colorID' index using for loop
   b. set the 'glMaterialfv' using the updated diffuseColor

4. Mesh Transformation
   a. get the model view matrix and translate(shift) the view before and after the rotate and scale transformation
   b. multiply the new model view
   c. use 'glRotatef' to set the model rotation
   d. use 'glScalef' to scale the model