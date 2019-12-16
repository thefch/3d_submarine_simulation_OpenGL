#pragma once

#include <windows.h>		// Header File For Windows
//#include <gl\gl.h>			// Header File For The OpenGL32 Library  
//#include <gl\glu.h>			// Header File For The GLu32 Library 
//-- OPENGL FILES INCLUDED IN GLEW see below

#include <math.h>     //sin and cos included in this header file.
#include <iostream>
#include <chrono>


#include "shaders/Shader.h"   // include shader header file, this is not part of OpenGL
	//Shader.h has been created using common glsl structure

#include "Image_Loading/nvImage.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\transform.hpp"

#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\matrix_inverse.hpp"

//--- OpenGL ---
#include "gl/glew.h"
#include "gl/wglew.h"

//MODEL LOADING
#include "3DStruct\threeDModel.h"
#include "Obj\OBJLoader.h"



#include "Octree/Octree.h"
#include "Rectangle.h"
#include "Sphere.h"
#include "Grid.h"
#include "Wave.h"
#include "Submarine.h"

#include "GameObject.h"
#include "Point.h"

#include "Seabed.h"
#include "Skybox.h"

#include "Camera.h"


#define PI (3.141592653589793f)

using namespace std;