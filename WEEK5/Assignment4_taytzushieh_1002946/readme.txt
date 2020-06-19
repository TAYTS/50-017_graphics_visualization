1. Generate Texture Image
   1.1 Create a vector to store all the colors (red, yellow, green, turquoise, blue, purple, white, black)
   1.2 The texture image is 64(width) x 64(height) and consists of 8 different colors, thus the texture image is split into 8(rows) x 8(cols) squares and each squares is 8(height) x 8(width) and consists of one color.
   1.3 Use two for loops to loop through each color square
   1.4 The color index of each square is calculated using (row_index + col_index) % 8
   1.5 Use two more for loops to paint the current color square
   1.6 Complexity: O(n^2)

2. Planar Parameterization
   2.1 Map the x & y coordinates in the model to the S & T coordinates in the texture image respectively
   2.2 The model(origin at its center with height of 1) coordinates is ranged from -0.5 to 0.5 but the texture map is ranged from 0 to 1, thus, we need to offset the x & y coordinate by 0.5 during the texture mapping

3. Cylindrical Parameterization
   3.1 Compute the angle theta which lies on the XZ-plane using arctan(z/x) since z = rsin(theta) and x = rcos(theta)
   3.2 The angle theta is range between -PI <= 0 <= PI and it needs to map to the texture map S axis which range from 0 to 1. The conversion can be done using (angle + PI) / (2 * PI)
   3.3 The y coordinates can be mapped to the height of the cylindrical which is the texture map T axis which range from 0 to 1. However, the model origin is at its center with height of 1, we need to offset the y coordinates by 0.5 during the texture mapping

4. Spherical Parameterization
   4.1 Calculate p(radius of circle) using sqrt(x^2 + y^2 + z^2)
   4.2 Calculate theta(XZ-plane) using arctan(z/x) and it ranges from -PI to PI
   4.3 Calculate phi(Y-axis) using arccos(y/p) and it ranges from 0 to PI
   4.4 Map the theta to the S axis of texture map which range from 0 to 1 using (theta + PI) / (2 * PI)
   4.5 Map the phi to the T axis of the texture map which range from 0 to 1 using phi/PI