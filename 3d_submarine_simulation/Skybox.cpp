#include "Header.h"



Skybox::Skybox()
{
}


Skybox::~Skybox()
{
}


/*void Skybox::load(Shader *shader) {
	if (!shader->load("BasicTexture", "glslfiles/basicTransformationsSkybox.vert", "glslfiles/basicTransformationsSkybox.frag"))
	{
		cout << "failed to load shader" << endl;
	}

	loadLeft(shader);
	loadRight(shader);
	//loadTop(shader);
	loadFront(shader);
	loadBack(shader);

}

void Skybox::loadLeft(Shader *shader) {
	glUseProgram(shader->handle());  // use the shader

	glEnable(GL_TEXTURE_2D);

	cout << " loading model " << endl;
	if (objLoader.loadModel("Models/skybox/1/leftModel.obj", leftModel))//returns true if the model is loaded, puts the model in the model parameter
	{
		cout << " model loaded " << endl;

		//if you want to translate the object to the origin of the screen,
		//first calculate the centre of the object, then move all the vertices
		//back so that the centre is on the origin.
		leftModel.calcCentrePoint();
		leftModel.centreOnZero();

	
		leftModel.calcVertNormalsUsingOctree();  //the method will construct the octree if it hasn't already been created.


		//turn on VBO by setting useVBO to true in threeDmodel.cpp default constructor - only permitted on 8 series cards and higher
		leftModel.initDrawElements();
		leftModel.initVBO(shader);
		//model.deleteVertexFaceData();

	}
	else
	{
		cout << "Left model failed to load " << endl;
	}


}

void Skybox::loadRight(Shader *shader) {
	glUseProgram(shader->handle());  // use the shader

	glEnable(GL_TEXTURE_2D);

	cout << " loading model " << endl;
	if (objLoader.loadModel("Models/skybox/1/rightModel.obj", rightModel))//returns true if the model is loaded, puts the model in the model parameter
	{
		cout << " model loaded " << endl;

		//if you want to translate the object to the origin of the screen,
		//first calculate the centre of the object, then move all the vertices
		//back so that the centre is on the origin.
		rightModel.calcCentrePoint();
		rightModel.centreOnZero();


		rightModel.calcVertNormalsUsingOctree();  //the method will construct the octree if it hasn't already been created.


		//turn on VBO by setting useVBO to true in threeDmodel.cpp default constructor - only permitted on 8 series cards and higher
		rightModel.initDrawElements();
		rightModel.initVBO(shader);
		//model.deleteVertexFaceData();

	}
	else
	{
		cout << "Right model failed to load " << endl;
	}
}

void Skybox::loadTop(Shader *shader) {
	glUseProgram(shader->handle());  // use the shader

	glEnable(GL_TEXTURE_2D);

	cout << " loading model " << endl;
	if (objLoader.loadModel("Models/skybox/1/topModel.obj", topModel))//returns true if the model is loaded, puts the model in the model parameter
	{
		cout << " model loaded " << endl;

		//if you want to translate the object to the origin of the screen,
		//first calculate the centre of the object, then move all the vertices
		//back so that the centre is on the origin.
		topModel.calcCentrePoint();
		topModel.centreOnZero();


		topModel.calcVertNormalsUsingOctree();  //the method will construct the octree if it hasn't already been created.


		//turn on VBO by setting useVBO to true in threeDmodel.cpp default constructor - only permitted on 8 series cards and higher
		topModel.initDrawElements();
		topModel.initVBO(shader);
		//model.deleteVertexFaceData();

	}
	else
	{
		cout << "Top model failed to load " << endl;
	}


}

void Skybox::loadFront(Shader *shader) {

	glUseProgram(shader->handle());  // use the shader

	glEnable(GL_TEXTURE_2D);

	cout << " loading model " << endl;
	if (objLoader.loadModel("Models/skybox/1/frontModel.obj", frontModel))//returns true if the model is loaded, puts the model in the model parameter
	{
		cout << " model loaded " << endl;

		//if you want to translate the object to the origin of the screen,
		//first calculate the centre of the object, then move all the vertices
		//back so that the centre is on the origin.
		frontModel.calcCentrePoint();
		frontModel.centreOnZero();


		frontModel.calcVertNormalsUsingOctree();  //the method will construct the octree if it hasn't already been created.


		//turn on VBO by setting useVBO to true in threeDmodel.cpp default constructor - only permitted on 8 series cards and higher
		frontModel.initDrawElements();
		frontModel.initVBO(shader);
		//model.deleteVertexFaceData();

	}
	else
	{
		cout << "Front model failed to load " << endl;
	}


}

void Skybox::loadBack(Shader *shader) {
	glUseProgram(shader->handle());  // use the shader

	glEnable(GL_TEXTURE_2D);

	cout << " loading model " << endl;
	if (objLoader.loadModel("Models/skybox/1/backModel.obj", backModel))//returns true if the model is loaded, puts the model in the model parameter
	{
		cout << " model loaded " << endl;

		//if you want to translate the object to the origin of the screen,
		//first calculate the centre of the object, then move all the vertices
		//back so that the centre is on the origin.
		backModel.calcCentrePoint();
		backModel.centreOnZero();


		backModel.calcVertNormalsUsingOctree();  //the method will construct the octree if it hasn't already been created.


		//turn on VBO by setting useVBO to true in threeDmodel.cpp default constructor - only permitted on 8 series cards and higher
		backModel.initDrawElements();
		backModel.initVBO(shader);
		//model.deleteVertexFaceData();

	}
	else
	{
		cout << "Back model failed to load " << endl;
	}


}

void Skybox::render(Shader *shader, Submarine submarine) {
	renderLeft(shader,submarine);
	renderRight(shader, submarine);
	//renderTop(shader,submarine);
	renderBack(shader,submarine);
	renderFront(shader,submarine);
}

void Skybox::renderLeft(Shader *shader, Submarine submarine) {
	//Light Properties
	float Light_Ambient_And_Diffuse[4] = { 0.8f, 0.8f, 0.6f, 1.0f };
	float Light_Specular[4] = { 1.0f,1.0f,1.0f,1.0f };

	float LightPos[4] = { 100.0f, 100.0f, 0.0f, 0.0f };

	//Material properties
	float Material_Ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	float Material_Diffuse[4] = { 0.8f, 0.8f, 0.5f, 1.0f };
	float Material_Specular[4] = { 0.9f,0.9f,0.8f,1.0f };
	float Material_Shininess = 100;

	glUniformMatrix4fv(glGetUniformLocation(shader->handle(), "ViewMatrix"), 1, GL_FALSE, &leftMatrix[0][0]);
	/glUniform4fv(glGetUniformLocation(shader->handle(), "LightPos"), 1, LightPos);
	glUniform4fv(glGetUniformLocation(shader->handle(), "light_ambient"), 1, Light_Ambient_And_Diffuse);
	glUniform4fv(glGetUniformLocation(shader->handle(), "light_diffuse"), 1, Light_Ambient_And_Diffuse);
	glUniform4fv(glGetUniformLocation(shader->handle(), "light_specular"), 1, Light_Specular);

	glUniform4fv(glGetUniformLocation(shader->handle(), "material_ambient"), 1, Material_Ambient);
	glUniform4fv(glGetUniformLocation(shader->handle(), "material_diffuse"), 1, Material_Diffuse);
	glUniform4fv(glGetUniformLocation(shader->handle(), "material_specular"), 1, Material_Specular);
	glUniform1f(glGetUniformLocation(shader->handle(), "material_shininess"), Material_Shininess);/


	//DRAW THE MODEL
	leftMatrix = glm::mat4(1.0);

	leftMatrix = glm::translate(leftMatrix, leftPos + submarine.getPosVec3());

	leftMatrix = Camera::getViewMatrix() * leftMatrix;

	//viewingMatrix = viewingMatrix * objectRotation;

	glUniformMatrix4fv(glGetUniformLocation(shader->handle(), "ModelViewMatrix"), 1, GL_FALSE, &leftMatrix[0][0]);


	glm::mat3 normalMatrix = glm::inverseTranspose(glm::mat3(leftMatrix));
	glUniformMatrix3fv(glGetUniformLocation(shader->handle(), "NormalMatrix"), 1, GL_FALSE, &normalMatrix[0][0]);


	leftModel.drawElementsUsingVBO(shader);
	//seaFloorModel.drawBoundingBox(seaFloorShader);
}

void Skybox::renderRight(Shader *shader, Submarine submarine) {
	//Light Properties
	float Light_Ambient_And_Diffuse[4] = { 0.8f, 0.8f, 0.6f, 1.0f };
	float Light_Specular[4] = { 1.0f,1.0f,1.0f,1.0f };

	float LightPos[4] = { 0.0f, 100.0f, 0.0f, 0.0f };

	//Material properties
	float Material_Ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	float Material_Diffuse[4] = { 0.8f, 0.8f, 0.5f, 1.0f };
	float Material_Specular[4] = { 0.9f,0.9f,0.8f,1.0f };
	float Material_Shininess = 100;

	/glUniformMatrix4fv(glGetUniformLocation(shader->handle(), "ViewMatrix"), 1, GL_FALSE, &rightMatrix[0][0]);
	glUniform4fv(glGetUniformLocation(shader->handle(), "LightPos"), 1, LightPos);
	glUniform4fv(glGetUniformLocation(shader->handle(), "light_ambient"), 1, Light_Ambient_And_Diffuse);
	glUniform4fv(glGetUniformLocation(shader->handle(), "light_diffuse"), 1, Light_Ambient_And_Diffuse);
	glUniform4fv(glGetUniformLocation(shader->handle(), "light_specular"), 1, Light_Specular);

	glUniform4fv(glGetUniformLocation(shader->handle(), "material_ambient"), 1, Material_Ambient);
	glUniform4fv(glGetUniformLocation(shader->handle(), "material_diffuse"), 1, Material_Diffuse);
	glUniform4fv(glGetUniformLocation(shader->handle(), "material_specular"), 1, Material_Specular);
	glUniform1f(glGetUniformLocation(shader->handle(), "material_shininess"), Material_Shininess);
	/

	//DRAW THE MODEL
	rightMatrix = glm::mat4(1.0);

	rightMatrix = glm::translate(rightMatrix, rightPos+submarine.getPosVec3());

	rightMatrix = Camera::getViewMatrix() * rightMatrix;

	//viewingMatrix = viewingMatrix * objectRotation;

	glUniformMatrix4fv(glGetUniformLocation(shader->handle(), "ModelViewMatrix"), 1, GL_FALSE, &rightMatrix[0][0]);


	glm::mat3 normalMatrix = glm::inverseTranspose(glm::mat3(rightMatrix));
	glUniformMatrix3fv(glGetUniformLocation(shader->handle(), "NormalMatrix"), 1, GL_FALSE, &normalMatrix[0][0]);



	rightModel.drawElementsUsingVBO(shader);


	//seaFloorModel.drawBoundingBox(seaFloorShader);

}

void Skybox::renderTop(Shader *shader, Submarine submarine) {
	//Light Properties
	float Light_Ambient_And_Diffuse[4] = { 0.8f, 0.8f, 0.6f, 1.0f };
	float Light_Specular[4] = { 1.0f,1.0f,1.0f,1.0f };

	float LightPos[4] = { 0.0f, 100.0f, 0.0f, 0.0f };

	//Material properties
	float Material_Ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	float Material_Diffuse[4] = { 0.8f, 0.8f, 0.5f, 1.0f };
	float Material_Specular[4] = { 0.9f,0.9f,0.8f,1.0f };
	float Material_Shininess = 100;

	glUniformMatrix4fv(glGetUniformLocation(shader->handle(), "ViewMatrix"), 1, GL_FALSE, &topMatrix[0][0]);
	glUniform4fv(glGetUniformLocation(shader->handle(), "LightPos"), 1, LightPos);
	glUniform4fv(glGetUniformLocation(shader->handle(), "light_ambient"), 1, Light_Ambient_And_Diffuse);
	glUniform4fv(glGetUniformLocation(shader->handle(), "light_diffuse"), 1, Light_Ambient_And_Diffuse);
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


	//seaFloorModel.drawBoundingBox(seaFloorShader);

}

void Skybox::renderBack(Shader *shader, Submarine submarine) {
	//Light Properties
	float Light_Ambient_And_Diffuse[4] = { 0.8f, 0.8f, 0.6f, 1.0f };
	float Light_Specular[4] = { 1.0f,1.0f,1.0f,1.0f };

	float LightPos[4] = { 0.0f, 100.0f, 0.0f, 0.0f };

	//Material properties
	float Material_Ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	float Material_Diffuse[4] = { 0.8f, 0.8f, 0.5f, 1.0f };
	float Material_Specular[4] = { 0.9f,0.9f,0.8f,1.0f };
	float Material_Shininess = 100;

	/glUniformMatrix4fv(glGetUniformLocation(shader->handle(), "ViewMatrix"), 1, GL_FALSE, &backMatrix[0][0]);
	glUniform4fv(glGetUniformLocation(shader->handle(), "LightPos"), 1, LightPos);
	glUniform4fv(glGetUniformLocation(shader->handle(), "light_ambient"), 1, Light_Ambient_And_Diffuse);
	glUniform4fv(glGetUniformLocation(shader->handle(), "light_diffuse"), 1, Light_Ambient_And_Diffuse);
	glUniform4fv(glGetUniformLocation(shader->handle(), "light_specular"), 1, Light_Specular);

	glUniform4fv(glGetUniformLocation(shader->handle(), "material_ambient"), 1, Material_Ambient);
	glUniform4fv(glGetUniformLocation(shader->handle(), "material_diffuse"), 1, Material_Diffuse);
	glUniform4fv(glGetUniformLocation(shader->handle(), "material_specular"), 1, Material_Specular);
	glUniform1f(glGetUniformLocation(shader->handle(), "material_shininess"), Material_Shininess);
/

	//DRAW THE MODEL
	backMatrix = glm::mat4(1.0);

	backMatrix = glm::translate(backMatrix, backPos+submarine.getPosVec3());

	backMatrix = Camera::getViewMatrix() * backMatrix;

	//viewingMatrix = viewingMatrix * objectRotation;

	glUniformMatrix4fv(glGetUniformLocation(shader->handle(), "ModelViewMatrix"), 1, GL_FALSE, &backMatrix[0][0]);


	glm::mat3 normalMatrix = glm::inverseTranspose(glm::mat3(backMatrix));
	glUniformMatrix3fv(glGetUniformLocation(shader->handle(), "NormalMatrix"), 1, GL_FALSE, &normalMatrix[0][0]);



	backModel.drawElementsUsingVBO(shader);


	//seaFloorModel.drawBoundingBox(seaFloorShader);

}

void Skybox::renderFront(Shader *shader, Submarine submarine) {
	//Light Properties
	float Light_Ambient_And_Diffuse[4] = { 0.8f, 0.8f, 0.6f, 1.0f };
	float Light_Specular[4] = { 1.0f,1.0f,1.0f,1.0f };

	float LightPos[4] = { 0.0f, 100.0f, 0.0f, 0.0f };

	//Material properties
	float Material_Ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	float Material_Diffuse[4] = { 0.8f, 0.8f, 0.5f, 1.0f };
	float Material_Specular[4] = { 0.9f,0.9f,0.8f,1.0f };
	float Material_Shininess = 100;

	/*glUniformMatrix4fv(glGetUniformLocation(shader->handle(), "ViewMatrix"), 1, GL_FALSE, &frontMatrix[0][0]);
	glUniform4fv(glGetUniformLocation(shader->handle(), "LightPos"), 1, LightPos);
	glUniform4fv(glGetUniformLocation(shader->handle(), "light_ambient"), 1, Light_Ambient_And_Diffuse);
	glUniform4fv(glGetUniformLocation(shader->handle(), "light_diffuse"), 1, Light_Ambient_And_Diffuse);
	glUniform4fv(glGetUniformLocation(shader->handle(), "light_specular"), 1, Light_Specular);

	glUniform4fv(glGetUniformLocation(shader->handle(), "material_ambient"), 1, Material_Ambient);
	glUniform4fv(glGetUniformLocation(shader->handle(), "material_diffuse"), 1, Material_Diffuse);
	glUniform4fv(glGetUniformLocation(shader->handle(), "material_specular"), 1, Material_Specular);
	glUniform1f(glGetUniformLocation(shader->handle(), "material_shininess"), Material_Shininess);
	/

	//DRAW THE MODEL
	frontMatrix = glm::mat4(1.0);

	frontMatrix = glm::translate(frontMatrix, frontPos + submarine.getPosVec3());

	frontMatrix = Camera::getViewMatrix() * frontMatrix;

	//viewingMatrix = viewingMatrix * objectRotation;

	glUniformMatrix4fv(glGetUniformLocation(shader->handle(), "ModelViewMatrix"), 1, GL_FALSE, &frontMatrix[0][0]);


	glm::mat3 normalMatrix = glm::inverseTranspose(glm::mat3(frontMatrix));
	glUniformMatrix3fv(glGetUniformLocation(shader->handle(), "NormalMatrix"), 1, GL_FALSE, &normalMatrix[0][0]);



	frontModel.drawElementsUsingVBO(shader);


	//seaFloorModel.drawBoundingBox(seaFloorShader);

}

*/


void Skybox::renderSkyboxCube(Shader *shader, Submarine submarine) {
	//Light Properties
	/*float Light_Ambient_And_Diffuse[4] = { 0.8f, 0.8f, 0.6f, 1.0f };
	float Light_Specular[4] = { 1.0f,1.0f,1.0f,1.0f };

	float LightPos[4] = { 0.0f, 100.0f, 0.0f, 0.0f };

	//Material properties
	float Material_Ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	float Material_Diffuse[4] = { 0.8f, 0.8f, 0.5f, 1.0f };
	float Material_Specular[4] = { 0.9f,0.9f,0.8f,1.0f };
	float Material_Shininess = 100;*/

	/*glUniformMatrix4fv(glGetUniformLocation(shader->handle(), "ViewMatrix"), 1, GL_FALSE, &modelMatrix[0][0]);
	glUniform4fv(glGetUniformLocation(shader->handle(), "LightPos"), 1, LightPos);
	glUniform4fv(glGetUniformLocation(shader->handle(), "light_ambient"), 1, Light_Ambient_And_Diffuse);
	glUniform4fv(glGetUniformLocation(shader->handle(), "light_diffuse"), 1, Light_Ambient_And_Diffuse);
	glUniform4fv(glGetUniformLocation(shader->handle(), "light_specular"), 1, Light_Specular);

	glUniform4fv(glGetUniformLocation(shader->handle(), "material_ambient"), 1, Material_Ambient);
	glUniform4fv(glGetUniformLocation(shader->handle(), "material_diffuse"), 1, Material_Diffuse);
	glUniform4fv(glGetUniformLocation(shader->handle(), "material_specular"), 1, Material_Specular);
	glUniform1f(glGetUniformLocation(shader->handle(), "material_shininess"), Material_Shininess);
	*/

	//DRAW THE MODEL
	modelMatrix = glm::mat4(1.0);

	modelMatrix = glm::translate(modelMatrix, pos + submarine.getPosVec3());

	modelMatrix = Camera::getViewMatrix() * modelMatrix;


	glUniformMatrix4fv(glGetUniformLocation(shader->handle(), "ModelViewMatrix"), 1, GL_FALSE, &modelMatrix[0][0]);


	glm::mat3 normalMatrix = glm::inverseTranspose(glm::mat3(modelMatrix));
	glUniformMatrix3fv(glGetUniformLocation(shader->handle(), "NormalMatrix"), 1, GL_FALSE, &normalMatrix[0][0]);



	model.drawElementsUsingVBO(shader);

}


void Skybox::loadCube(Shader *shader) {
	if (!shader->load("BasicTexture", "glslfiles/basicTransformationsSkybox.vert", "glslfiles/basicTransformationsSkybox.frag"))
	{
		cout << "failed to load shader" << endl;
	}
	glUseProgram(shader->handle());  // use the shader

	glEnable(GL_TEXTURE_2D);

	cout << " loading model " << endl;
	if (objLoader.loadModel("Models/skybox/2/skybox.obj", model))//returns true if the model is loaded, puts the model in the model parameter
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
		cout << "Left model failed to load " << endl;
	}


}