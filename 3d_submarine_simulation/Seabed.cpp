#include "Header.h"



Seabed::Seabed()
{
}


Seabed::~Seabed()
{
}

void Seabed::render(Shader *shader) {
	//Light Properties
	float Light_Ambient_And_Diffuse[4] = { 0.8f, 0.8f, 0.6f, 1.0f };
	float Light_Specular[4] = { 1.0f,1.0f,1.0f,1.0f };

	float LightPos[4] = { 0.0f, 100.0f, 0.0f, 0.0f };

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


	//DRAW THE MODEL
	modelMatrix = glm::mat4(1.0);

	modelMatrix = glm::translate(modelMatrix, pos);

	modelMatrix = Camera::getViewMatrix() * modelMatrix;

	//viewingMatrix = viewingMatrix * objectRotation;

	glUniformMatrix4fv(glGetUniformLocation(shader->handle(), "ModelViewMatrix"), 1, GL_FALSE, &modelMatrix[0][0]);


	glm::mat3 normalMatrix = glm::inverseTranspose(glm::mat3(modelMatrix));
	glUniformMatrix3fv(glGetUniformLocation(shader->handle(), "NormalMatrix"), 1, GL_FALSE, &normalMatrix[0][0]);



	model.drawElementsUsingVBO(shader);


	//model.drawBoundingBox(seaFloorShader);

}


//render the bottom part of the seabed
void Seabed::renderBottom(Shader *shader) {
	//Light Properties
	float Light_Ambient_And_Diffuse[4] = { 0.8f, 0.8f, 0.6f, 1.0f };
	float Light_Specular[4] = { 1.0f,1.0f,1.0f,1.0f };


	float LightPosBot[4] = { 1, 1800.0f, -400.0f, 0.0f };

	/*float sub_Fv[3] = { sub.getRot().x,sub.getRot().y,sub.getRot().z };
	float sub_Pos[3] = { sub.getRot().x+sub.getPosX(),
		sub.getRot().y+sub.getPosY()
		,sub.getRot().z +sub.getPosZ()};
	*/
	//Material properties
	float Material_Ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	float Material_Diffuse[4] = { 0.8f, 0.8f, 0.5f, 1.0f };
	float Material_Specular[4] = { 0.9f,0.9f,0.8f,1.0f };
	float Material_Shininess = 800;

	glUniformMatrix4fv(glGetUniformLocation(shader->handle(), "ViewMatrix"), 1, GL_FALSE, &botMatrix[0][0]);
	glUniform4fv(glGetUniformLocation(shader->handle(), "LightPos"), 1, LightPosBot);
	glUniform4fv(glGetUniformLocation(shader->handle(), "light_ambient"), 1, Light_Ambient_And_Diffuse);
	glUniform4fv(glGetUniformLocation(shader->handle(), "light_diffuse"), 1, Light_Ambient_And_Diffuse);
	glUniform4fv(glGetUniformLocation(shader->handle(), "light_specular"), 1, Light_Specular);

	glUniform4fv(glGetUniformLocation(shader->handle(), "material_ambient"), 1, Material_Ambient);
	glUniform4fv(glGetUniformLocation(shader->handle(), "material_diffuse"), 1, Material_Diffuse);
	glUniform4fv(glGetUniformLocation(shader->handle(), "material_specular"), 1, Material_Specular);
	glUniform1f(glGetUniformLocation(shader->handle(), "material_shininess"), Material_Shininess);
	//glUniform4fv(glGetUniformLocation(shader->handle(), "submarine_Fv"), 1, sub_Fv);
	//glUniform4fv(glGetUniformLocation(shader->handle(), "submarine_pos"), 1, sub_Pos);
	glUniform1f(glGetUniformLocation(shader->handle(), "useFog"), useFog);



	//DRAW THE MODEL
	botMatrix = glm::mat4(1.0);

	botMatrix = glm::translate(botMatrix, botPos);

	botMatrix = Camera::getViewMatrix() * botMatrix;

	//viewingMatrix = viewingMatrix * objectRotation;

	glUniformMatrix4fv(glGetUniformLocation(shader->handle(), "ModelViewMatrix"), 1, GL_FALSE, &botMatrix[0][0]);


	glm::mat3 normalMatrix = glm::inverseTranspose(glm::mat3(botMatrix));
	glUniformMatrix3fv(glGetUniformLocation(shader->handle(), "NormalMatrix"), 1, GL_FALSE, &normalMatrix[0][0]);



	botModel.drawElementsUsingVBO(shader);


	//model.drawBoundingBox(seaFloorShader);
	minXbot = botModel.octree->minX;
	maxXbot = botModel.octree->maxX;
	minYbot = botModel.octree->minY;
	maxYbot = botModel.octree->maxY;
	minZbot = botModel.octree->minZ;
	maxZbot = botModel.octree->maxZ;
}

/*
void Seabed::renderMid(Shader *shader) {
	//Light Properties
	float Light_Ambient_And_Diffuse[4] = { 0.8f, 0.8f, 0.6f, 1.0f };
	float Light_Specular[4] = { 1.0f,1.0f,1.0f,1.0f };

	float LightPos[4] = { 0.0f, 100.0f, 0.0f, 0.0f };

	//Material properties
	float Material_Ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	float Material_Diffuse[4] = { 0.8f, 0.8f, 0.5f, 1.0f };
	float Material_Specular[4] = { 0.9f,0.9f,0.8f,1.0f };
	float Material_Shininess = 100;

	glUniformMatrix4fv(glGetUniformLocation(shader->handle(), "ViewMatrix"), 1, GL_FALSE, &midMatrix[0][0]);
	glUniform4fv(glGetUniformLocation(shader->handle(), "LightPos"), 1, LightPos);
	glUniform4fv(glGetUniformLocation(shader->handle(), "light_ambient"), 1, Light_Ambient_And_Diffuse);
	glUniform4fv(glGetUniformLocation(shader->handle(), "light_diffuse"), 1, Light_Ambient_And_Diffuse);
	glUniform4fv(glGetUniformLocation(shader->handle(), "light_specular"), 1, Light_Specular);

	glUniform4fv(glGetUniformLocation(shader->handle(), "material_ambient"), 1, Material_Ambient);
	glUniform4fv(glGetUniformLocation(shader->handle(), "material_diffuse"), 1, Material_Diffuse);
	glUniform4fv(glGetUniformLocation(shader->handle(), "material_specular"), 1, Material_Specular);
	glUniform1f(glGetUniformLocation(shader->handle(), "material_shininess"), Material_Shininess);


	//DRAW THE MODEL
	midMatrix = glm::mat4(1.0);

	midMatrix = glm::translate(midMatrix, midPos);

	midMatrix = Camera::getViewMatrix() * midMatrix;

	//viewingMatrix = viewingMatrix * objectRotation;

	glUniformMatrix4fv(glGetUniformLocation(shader->handle(), "ModelViewMatrix"), 1, GL_FALSE, &midMatrix[0][0]);


	glm::mat3 normalMatrix = glm::inverseTranspose(glm::mat3(midMatrix));
	glUniformMatrix3fv(glGetUniformLocation(shader->handle(), "NormalMatrix"), 1, GL_FALSE, &normalMatrix[0][0]);



	midModel.drawElementsUsingVBO(shader);


	//model.drawBoundingBox(seaFloorShader);

}
*/
//render the top part of the seafloor
void Seabed::renderTop(Shader *shader) {
	//Light Properties
	float Light_Ambient_And_Diffuse[4] = { 0.8, 0.8f, 0.6, 1.0f };
	float Light_Specular[4] = { 1.0f,1.0f,1.0f,1.0f };

	float LightPos[4] = { 0, 1800.0f, -400.0f, 0.0f };

	//Material properties
	float Material_Ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	float Material_Diffuse[4] = { 0.8f, 0.8f, 0.5, 1.0f };
	float Material_Specular[4] = { 0.9f,0.9f,0.8f,1.0f };
	float Material_Shininess = 10;

	glUniformMatrix4fv(glGetUniformLocation(shader->handle(), "ViewMatrix"), 1, GL_FALSE, &topMatrix[0][0]);
	glUniform4fv(glGetUniformLocation(shader->handle(), "LightPos"), 1, LightPos);
	glUniform4fv(glGetUniformLocation(shader->handle(), "light_ambient"), 1, Light_Ambient_And_Diffuse);
	//glUniform4fv(glGetUniformLocation(shader->handle(), "light_diffuse"), 1, Light_Ambient_And_Diffuse);
	glUniform4fv(glGetUniformLocation(shader->handle(), "light_specular"), 1, Light_Specular);

	glUniform4fv(glGetUniformLocation(shader->handle(), "material_ambient"), 1, Material_Ambient);
	glUniform4fv(glGetUniformLocation(shader->handle(), "material_diffuse"), 1, Material_Diffuse);
	glUniform4fv(glGetUniformLocation(shader->handle(), "material_specular"), 1, Material_Specular);
	glUniform1f(glGetUniformLocation(shader->handle(), "material_shininess"), Material_Shininess);


	//DRAW THE MODEL
	topMatrix = glm::mat4(1.0);

	topMatrix = glm::translate(topMatrix, topPos);

	topMatrix = Camera::getViewMatrix() * topMatrix;

	//viewingMatrix = viewingMatrix * objectRotation;

	glUniformMatrix4fv(glGetUniformLocation(shader->handle(), "ModelViewMatrix"), 1, GL_FALSE, &topMatrix[0][0]);


	glm::mat3 normalMatrix = glm::inverseTranspose(glm::mat3(topMatrix));
	glUniformMatrix3fv(glGetUniformLocation(shader->handle(), "NormalMatrix"), 1, GL_FALSE, &normalMatrix[0][0]);



	topModel.drawElementsUsingVBO(shader);


	//topModel.drawBoundingBox(shader);

}




void Seabed::load(Shader *shader) {
	if (!shader->load("BasicView", "glslfiles/basicTransformationsFloor.vert", "glslfiles/basicTransformationsFloor.frag"))
	{
		cout << "failed to load shader" << endl;
	}
	glUseProgram(shader->handle());  // use the shader

	glEnable(GL_TEXTURE_2D);

	cout << " loading model " << endl;
	if (objLoader.loadModel("Models/seaFloor/5/seabed.obj", model))//returns true if the model is loaded, puts the model in the model parameter
	//if (seaFloorObjLoader.loadModel("Models/seaFloor/top/top.obj", seaFloorModel))//returns true if the model is loaded, puts the model in the model parameter
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
		//seaFloorModel.deleteVertexFaceData();

	}
	else
	{
		cout << " model failed to load " << endl;
	}
}


//load the bottom part of the seafloor
void Seabed::loadBottom(Shader *shader) {
	if (!shader->load("BasicView", "glslfiles/basicTransformationsFloor.vert", "glslfiles/basicTransformationsFloor.frag"))
	{
		cout << "failed to load shader" << endl;
	}
	glUseProgram(shader->handle());  // use the shader

	glEnable(GL_TEXTURE_2D);

	cout << " loading model " << endl;
	if (objLoader.loadModel("Models/seaFloor/4/bottom.obj", botModel))//returns true if the model is loaded, puts the model in the model parameter
	//if (seaFloorObjLoader.loadModel("Models/seaFloor/top/top.obj", seaFloorModel))//returns true if the model is loaded, puts the model in the model parameter
	{
		cout << " model loaded " << endl;

		//if you want to translate the object to the origin of the screen,
		//first calculate the centre of the object, then move all the vertices
		//back so that the centre is on the origin.
		botModel.calcCentrePoint();
		botModel.centreOnZero();


		botModel.calcVertNormalsUsingOctree();  //the method will construct the octree if it hasn't already been created.


											 //turn on VBO by setting useVBO to true in threeDmodel.cpp default constructor - only permitted on 8 series cards and higher
		botModel.initDrawElements();
		botModel.initVBO(shader);
		//seaFloorModel.deleteVertexFaceData();

	}
	else
	{
		cout << "bottom model failed to load " << endl;
	}
}


//load the top part of the seafloor
void Seabed::loadTop(Shader *shader) {
	if (!shader->load("BasicView", "glslfiles/basicTransformations.vert", "glslfiles/basicTransformations.frag"))
	{
		cout << "failed to load shader" << endl;
	}
	glUseProgram(shader->handle());  // use the shader

	glEnable(GL_TEXTURE_2D);

	cout << " loading model " << endl;
	if (objLoader.loadModel("Models/seaFloor/4/top.obj", topModel))//returns true if the model is loaded, puts the model in the model parameter
	//if (seaFloorObjLoader.loadModel("Models/seaFloor/top/top.obj", seaFloorModel))//returns true if the model is loaded, puts the model in the model parameter
	{
		cout << "Top model loaded " << endl;

		//if you want to translate the object to the origin of the screen,
		//first calculate the centre of the object, then move all the vertices
		//back so that the centre is on the origin.
		topModel.calcCentrePoint();
		topModel.centreOnZero();


		topModel.calcVertNormalsUsingOctree();  //the method will construct the octree if it hasn't already been created.


											 //turn on VBO by setting useVBO to true in threeDmodel.cpp default constructor - only permitted on 8 series cards and higher
		topModel.initDrawElements();
		topModel.initVBO(shader);
		//seaFloorModel.deleteVertexFaceData();

	}
	else
	{
		cout << "top model failed to load " << endl;
	}
}