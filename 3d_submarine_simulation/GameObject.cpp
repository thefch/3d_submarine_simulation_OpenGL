#include "Header.h"

GameObject::GameObject()
{
	this->pos = glm::vec3(0, 0, 0);
}

GameObject::GameObject(glm::vec3 p)
{
	this->pos = p;
}

void GameObject::render(Shader *shader) {
	/*if (sub.isUnderWater()) {		//FOR DEBUGGING, REMOVE ! LATER
//	LightPosBot = { 0, 1800.0f, -400.0f, 0.0f };
		LightPos[3] = 0.0;
		LightPos[0] = sub.getPosX();
		LightPos[1] = sub.getPosY() + sub.getRot().y;
		LightPos[2] = sub.getPosZ();
	}*/

	glUniformMatrix4fv(glGetUniformLocation(shader->handle(), "ViewMatrix"), 1, GL_FALSE, &modelMatrix[0][0]);
	glUniform4fv(glGetUniformLocation(shader->handle(), "LightPos"), 1, LightPos);
	glUniform4fv(glGetUniformLocation(shader->handle(), "light_ambient"), 1, Light_Ambient_And_Diffuse);
	glUniform4fv(glGetUniformLocation(shader->handle(), "light_diffuse"), 1, Light_Ambient_And_Diffuse);
	glUniform4fv(glGetUniformLocation(shader->handle(), "light_specular"), 1, Light_Specular);
	
	glUniform4fv(glGetUniformLocation(shader->handle(), "material_ambient"), 1, Material_Ambient);
	glUniform4fv(glGetUniformLocation(shader->handle(), "material_diffuse"), 1, Material_Diffuse);
	glUniform4fv(glGetUniformLocation(shader->handle(), "material_specular"), 1, Material_Specular);
	glUniform1f(glGetUniformLocation(shader->handle(), "material_shininess"), Material_Shininess);
	
	
	//DRAW THE MODEL
	modelMatrix = glm::mat4(1.0);


	modelMatrix = glm::translate(modelMatrix, pos);
	modelMatrix = glm::rotate(modelMatrix, angleX, glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, angleY, glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, angleZ, glm::vec3(0, 0, 1));

	modelMatrix = Camera::getViewMatrix() * modelMatrix;

	//viewingMatrix = viewingMatrix * objectRotation;

	glUniformMatrix4fv(glGetUniformLocation(shader->handle(), "ModelViewMatrix"), 1, GL_FALSE, &modelMatrix[0][0]);


	normalMatrix = glm::inverseTranspose(glm::mat3(modelMatrix));
	glUniformMatrix3fv(glGetUniformLocation(shader->handle(), "NormalMatrix"), 1, GL_FALSE, &normalMatrix[0][0]);

	
	
	model.drawElementsUsingVBO(shader);
	//model.drawBoundingBox(sunShader);
	//model.drawOctreeLeaves(sunShader);

	minX = model.octree->minX;
	maxX = model.octree->maxX;
	minY = model.octree->minY;
	maxY = model.octree->maxY;
	minZ = model.octree->minZ;
	maxZ = model.octree->maxZ;
	calcWHD();
}


//creates a temp cube
void GameObject::createCube(Shader *shader) {
	if (!shader->load("BasicView", "glslfiles/basic.vert", "glslfiles/basic.frag"))
	{
		cout << "failed to load shader" << endl;
	}

	// First simple object
	float dim = 10;
	verts[0] = -dim;   verts[1] = -dim;  verts[2] = -dim;
	verts[3] = -dim;   verts[4] = dim;  verts[5] = -dim;
	verts[6] = dim;   verts[7] = dim;  verts[8] = -dim;
	verts[9] = dim;   verts[10] = -dim;  verts[11] = -dim;

	verts[12] = -dim;   verts[13] = -dim;  verts[14] = dim;
	verts[15] = -dim;   verts[16] = dim;  verts[17] = dim;
	verts[18] = dim;   verts[19] = dim;  verts[20] = dim;
	verts[21] = dim;   verts[22] = -dim;  verts[23] = dim;

	cols[0] = 1.0;   cols[1] = 0.0;  cols[2] = 0.0;
	cols[3] = 0.0;   cols[4] = 1.0;  cols[5] = 0.0;
	cols[6] = 0.0;   cols[7] = 0.0;  cols[8] = 1.0;
	cols[9] = 1.0;   cols[10] = 1.0;  cols[11] = 0.0;

	cols[12] = 1.0;   cols[13] = 0.0;  cols[14] = 0.0;
	cols[15] = 0.0;   cols[16] = 1.0;  cols[17] = 0.0;
	cols[18] = 0.0;   cols[19] = 0.0;  cols[20] = 1.0;
	cols[21] = 1.0;   cols[22] = 1.0;  cols[23] = 0.0;

	tris[0] = 0; tris[1] = 1; tris[2] = 2;
	tris[3] = 0; tris[4] = 2; tris[5] = 3;
	tris[6] = 4; tris[7] = 6; tris[8] = 5;
	tris[9] = 4; tris[10] = 7; tris[11] = 6;
	tris[12] = 1; tris[13] = 5; tris[14] = 6;
	tris[15] = 1; tris[16] = 6; tris[17] = 2;
	tris[18] = 0; tris[19] = 7; tris[20] = 4;
	tris[21] = 0; tris[22] = 3; tris[23] = 7;
	tris[24] = 0; tris[25] = 5; tris[26] = 1;
	tris[27] = 0; tris[28] = 4; tris[29] = 5;
	tris[30] = 3; tris[31] = 2; tris[32] = 7;
	tris[33] = 2; tris[34] = 6; tris[35] = 7;

	// VAO allocation
	glGenVertexArrays(1, &m_vaoID);

	// First VAO setup
	glBindVertexArray(m_vaoID);

	glGenBuffers(2, m_vboID);

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID[0]);
	//initialises data storage of vertex buffer object
	glBufferData(GL_ARRAY_BUFFER, numOfVerts * 3 * sizeof(GLfloat), verts, GL_STATIC_DRAW);
	GLint vertexLocation = glGetAttribLocation(shader->handle(), "in_Position");
	glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vertexLocation);


	glBindBuffer(GL_ARRAY_BUFFER, m_vboID[1]);
	glBufferData(GL_ARRAY_BUFFER, numOfVerts * 3 * sizeof(GLfloat), cols, GL_STATIC_DRAW);
	GLint colorLocation = glGetAttribLocation(shader->handle(), "in_Color");
	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colorLocation);


	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numOfTris * 3 * sizeof(unsigned int), tris, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void GameObject::load(Shader *shader, char * file) {
	if (!shader->load("BasicView", "glslfiles/basicTransformationsGameObj.vert", "glslfiles/basicTransformationsGameObj.frag"))
	{
		cout << "failed to load shader" << endl;
	}
	glUseProgram(shader->handle());  // use the shader

	glEnable(GL_TEXTURE_2D);

	cout << " loading model " << endl;
	if (objLoader.loadModel(file, model))//returns true if the model is loaded, puts the model in the model parameter
	{
		cout << " model loaded " << endl;

		//if you want to translate the object to the origin of the screen,
		//first calculate the centre of the object, then move all the vertices
		//back so that the centre is on the origin.
		model.calcCentrePoint();
		model.centreOnZero();


		model.calcVertNormalsUsingOctree();  //the method will construct the octree if it hasn't already been created.


		//turn on VBO by setting useVBO to true in threeDmodel.cpp default constructor - only permitted on 8 series cards and higher
		model.initDrawElements();
		model.initVBO(shader);
		//model.deleteVertexFaceData();

	}
	else
	{
		cout << " model failed to load " << endl;
	}
}

//calclulate the width,height and depth of the object
void GameObject::calcWHD() {
	width = abs(maxX - minX);
	height = abs(maxY - minY);
	depth = abs(maxZ - minZ);
}