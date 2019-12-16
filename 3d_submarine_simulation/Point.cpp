#include "Header.h"



Point::Point()
{
}


Point::~Point()
{
}


void Point::render(Shader* shader,glm::vec3 p) {
	//Light Properties
	float Light_Ambient_And_Diffuse[4] = { 0.8f, 0.8f, 0.6f, 1.0f };
	float Light_Specular[4] = { 1.0f,1.0f,1.0f,1.0f };

	float LightPos[4] = { 100.0f, 100.0f, 0.0f, 0.0f };

	//Material properties
	float Material_Ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	float Material_Diffuse[4] = { 0.8f, 0.8f, 0.5f, 1.0f };
	float Material_Specular[4] = { 0.9f,0.9f,0.8f,1.0f };
	float Material_Shininess = 100;

	glUniformMatrix4fv(glGetUniformLocation(shader->handle(), "ViewMatrix"), 1, GL_FALSE, &modelMatrix[0][0]);
	glUniform4fv(glGetUniformLocation(shader->handle(), "LightPos"), 1, LightPos);
	glUniform4fv(glGetUniformLocation(shader->handle(), "light_ambient"), 1, Light_Ambient_And_Diffuse);
	glUniform4fv(glGetUniformLocation(shader->handle(), "light_diffuse"), 1, Light_Ambient_And_Diffuse);
	glUniform4fv(glGetUniformLocation(shader->handle(), "light_specular"), 1, Light_Specular);

	glUniform4fv(glGetUniformLocation(shader->handle(), "material_ambient"), 1, Material_Ambient);
	glUniform4fv(glGetUniformLocation(shader->handle(), "material_diffuse"), 1, Material_Diffuse);
	glUniform4fv(glGetUniformLocation(shader->handle(), "material_specular"), 1, Material_Specular);
	glUniform1f(glGetUniformLocation(shader->handle(), "material_shininess"), Material_Shininess);


	pos = p;
	//DRAW THE MODEL
	modelMatrix = glm::mat4(1.0);

	modelMatrix = glm::translate(modelMatrix, p);

	modelMatrix = Camera::getViewMatrix() * modelMatrix;

	//viewingMatrix = viewingMatrix * objectRotation;

	glUniformMatrix4fv(glGetUniformLocation(shader->handle(), "ModelViewMatrix"), 1, GL_FALSE, &modelMatrix[0][0]);


	glm::mat3 normalMatrix = glm::inverseTranspose(glm::mat3(modelMatrix));
	glUniformMatrix3fv(glGetUniformLocation(shader->handle(), "NormalMatrix"), 1, GL_FALSE, &normalMatrix[0][0]);


	model.drawElementsUsingVBO(shader);
	//model.drawBoundingBox(seaFloorShader);
}

void Point::load(Shader* shader) {
	if (!shader->load("BasicView", "glslfiles/basicTransformations.vert", "glslfiles/basicTransformations.frag"))
	{
		cout << "failed to load shader" << endl;
	}
	glUseProgram(shader->handle());  // use the shader

	glEnable(GL_TEXTURE_2D);

	cout << " loading model " << endl;
	if (objLoader.loadModel("Models/point/point.obj", model))//returns true if the model is loaded, puts the model in the model parameter
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
		cout << "Point model failed to load " << endl;
	}
}