#include "Header.h"



Wave::Wave()
{
}

//render the wave
//change the texture with displacement
void Wave::renderWave(Shader *waveShader) {
	//Light Properties
	float Light_Ambient_And_Diffuse[4] = { 0.8f, 0.8f, 0.6f, 1.0f };
	float Light_Specular[4] = { 1.0f,1.0f,1.0f,1.0f };

//	float LightPos[4] = { 0.0f, 100.0f, 0.0f, 0.0f };
	float LightPos[4] = { 0, 1800.0f, -400.0f, 0.0f };


	//Material properties
	float Material_Ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	float Material_Diffuse[4] = { 0.8f, 0.8f, 0.5f, 1.0f };
	float Material_Specular[4] = { 0.9f,0.9f,0.8f,1.0f };
	float Material_Shininess = 100;
	

	glUniformMatrix4fv(glGetUniformLocation(waveShader->handle(), "ViewMatrix"), 1, GL_FALSE, &modelMatrix[0][0]);
	glUniform4fv(glGetUniformLocation(waveShader->handle(), "LightPos"), 1, LightPos);
	glUniform4fv(glGetUniformLocation(waveShader->handle(), "light_ambient"), 1, Light_Ambient_And_Diffuse);
	glUniform4fv(glGetUniformLocation(waveShader->handle(), "light_diffuse"), 1, Light_Ambient_And_Diffuse);
	glUniform4fv(glGetUniformLocation(waveShader->handle(), "light_specular"), 1, Light_Specular);

	glUniform4fv(glGetUniformLocation(waveShader->handle(), "material_ambient"), 1, Material_Ambient);
	glUniform4fv(glGetUniformLocation(waveShader->handle(), "material_diffuse"), 1, Material_Diffuse);
	glUniform4fv(glGetUniformLocation(waveShader->handle(), "material_specular"), 1, Material_Specular);
	glUniform1f(glGetUniformLocation(waveShader->handle(), "material_shininess"), Material_Shininess);
	glUniform1f(glGetUniformLocation(waveShader->handle(), "displacement"), displacement);

	float incr = 0.00002;
	if (resetWave) {
		displacement -= incr;
		if (displacement <= 0.0) {
			resetWave = false;
		}
	}
	else if(!resetWave){
		displacement += incr;
		if (displacement >= 0.06) {
			resetWave = true;
		}
	}
		
	modelMatrix = glm::mat4(1.0);

	modelMatrix = glm::translate(modelMatrix, wavePos);
	

	modelMatrix = Camera::getViewMatrix() * modelMatrix;


	glUniformMatrix4fv(glGetUniformLocation(waveShader->handle(), "ModelViewMatrix"), 1, GL_FALSE, &modelMatrix[0][0]);


	glm::mat3 normalMatrix = glm::inverseTranspose(glm::mat3(modelMatrix));
	glUniformMatrix3fv(glGetUniformLocation(waveShader->handle(), "NormalMatrix"), 1, GL_FALSE, &normalMatrix[0][0]);



	model.drawElementsUsingVBO(waveShader);
	//waveModel.drawOctreeLeaves(waveShader);
	//waveModel.drawBoundingBox(waveShader);

	minX = model.octree->minX;
	minY = model.octree->minY;
	minZ = model.octree->minZ; 
	maxX = model.octree->maxX; 
	maxY = model.octree->maxY;
	maxZ = model.octree->maxZ;
}

void Wave::loadWave(Shader *waveShader) {
	if (!waveShader->load("BasicTransDisplacementWave", "glslfiles/basicTransformationsWithDisplacementWave.vert", "glslfiles/basicTransformationsWithDisplacementWave.frag"))
	{
		cout << "failed to load shader" << endl;
	}
	glUseProgram(waveShader->handle());  // use the shader

	glEnable(GL_TEXTURE_2D);

	cout << " loading model " << endl;
	if (waveObjLoader.loadModel("Models/wave/wave2.obj", model))//returns true if the model is loaded, puts the model in the model parameter
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
		model.initVBO(waveShader);
		//seaFloorModel.deleteVertexFaceData();

	}
	else
	{
		cout << " model failed to load " << endl;
	}
}

