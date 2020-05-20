# Assignment_0


## For Mac

Download and instal CMake for Mac OS: https://cmake.org/download/

Input the following commands on the Terminal: 
1. cd to the folder: `Assingment_0/build`
2. `cmake ..`
3. `make`
4. `./Assignment_0`


## For Windows

Download and install CMake for Windows: https://cmake.org/download/
Download and install Visual Studio: https://visualstudio.microsoft.com/

1. Copy `Assingment_0\win\glut32.dll` to `C:\WINDOWS\SysWOW64\`
2. Input the following commands on the CMD Terminal: 
   - cd to the folder: `Assingment_0\build`
   - `cmake ..` (if you have more than one VS version, using -G to specify one, e.g., cmake .. -G "Visual Studio 14 2015")
3. Open the `Assignment_0.sln` file in `Assingment_0\build` folder with your Visual Studio
4. Build and Run the Visual Studio Project

