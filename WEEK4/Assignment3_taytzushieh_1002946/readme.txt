1. Load Skeleton File
   1.1 Check the file has the correct extension
   1.2 Open the .skel file and read line by line
   1.3 Parse the x, y, z, parent joint index
   1.4 Create a 4x4 identity matrix and set the last column to <x, y, z, 1>
   1.5 Create new Joint instance and set the 4x4 matrix as the transform matrix
   1.6 If the parent joint index is -1, set the m_rootJoint, else add the new Joint instance to the child of the parent Joint
   1.7 Push the Joint instance into the m_joints

2. Draw Joints
   2.1 Create new helper function for drawing joint recursively
   2.2 Push the current joint node transformation matrix to the m_matrixStack
   2.3 Load the new transformation matrix using the m_matrixStack
   2.4 Draw the solid sphere
   2.5 For each child joint node call the helper function to draw the joint recursively
   2.6 Pop the transformation matrix at the top of the m_matrixStack

3. Draw Sekeleton (Recursive)
   3.1 Create new helper function for drawing skeleton recursively
   3.2 Push the current joint node transformation matrix to the m_matrixStack
   3.3 Create translate matrix for moving the cube to positive z (start from 0)
   3.4 For each child joint
       3.4.1 Get the child joint transform matrix last column as vector (child to parent vector)
       3.4.2 Compute the scaling matrix for the cube with 0.05 scale factor for x and y axis and using the child to parent vector to compute the scale factor for z (distance between child and parent)
       3.4.3 Get the z vector by normalise the child to parent vector
       3.4.4 Compute the y vector using z X <0, 0, 1>
       3.4.5 Compute the x vector using y X z
       3.4.6 Computet the alignment matrix by using the x, y, z vector computed earlier
       3.4.7 Compute the transformation matrix for drawing the skeleton box by (alignMatrix * scaleMatrix * translateMatrix) and push to the m_matrixStack and load the matrix
       3.4.8 Draw the solid cube
       3.4.9 Remove the transformation matrix for drawing box from the top of the m_matrixStack and call the draw skeleton helper function to draw the child joint
    3.5 Pop the transformation matrix at the top of the m_matrixStack

4. Change Pose of Skeleton
   4.1 Compute the rotation matrix using (rotateX matrix * rotateY matrix * rotateZ matrix)
   4.2  Set the rotation matrix computed earlier at the top left 3x3 matrix of the selected joint transform matrix