#include "Header.h"
#pragma once


class GameObject
{
private:
	//Light Properties
	float Light_Ambient_And_Diffuse[4] = { 0.8f, 0.8f, 0.6f, 1.0f };
	float Light_Specular[4] = { 1.0f,1.0f,1.0f,1.0f };

	//float LightPos[4] = { 0.0f, 100.0f, 0.0f, 0.0f };
	float LightPos[4] = { 0, 1800.0f, -400.0f, 0.0f };



	//Material properties
	float Material_Ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	float Material_Diffuse[4] = { 1, 1, 1, 1.0f };
	float Material_Specular[4] = { 0.0f,0.0f,0.0f,1.0f };
	float Material_Shininess = 200;

	float verts[24];
	float cols[24];
	unsigned int tris[36];

	unsigned int m_vaoID;		    // vertex array object
	unsigned int m_vboID[2];		// two VBOs - used for colours and vertex data
	GLuint ibo;                     //identifier for the triangle indices

	const int numOfVerts = 8;
	const int numOfTris = 12;


	glm::mat4 modelMatrix;

	glm::mat3 normalMatrix;

	glm::vec3 pos = glm::vec3(0.0, 0.0, 0.0);
	

	OBJLoader objLoader;



public:
	glm::vec3 forwardVec;
	glm::vec3 rightVec;
	glm::vec3 upVec;
	ThreeDModel model;
	float minX, minY, minZ, maxX, maxY, maxZ;
	float width, height, depth;
	float angleX = 0.0;
	float angleY = 0.0;
	float angleZ = 0.0;

	GameObject();
	GameObject(glm::vec3 p);

	void render(Shader* shader);
	void createCube(Shader* myShader);
	void load(Shader* shader, char * file);
	void calcWHD();

	void setPos(float x, float y, float z);
	void setMaterialShiness(int s);

	glm::vec3 getRightVec();
	glm::vec3 getUpVec();
	glm::vec3 getForwardVec();
	glm::vec3 getPos();
};

inline void GameObject::setPos(float x, float y, float z) {
	this->pos = glm::vec3(x, y, z);
}

inline void GameObject::setMaterialShiness(int s) {
	this->Material_Shininess = s;
}

/*inline unsigned int GameObject::getVaoID() {
	return this->m_vaoID;
}

inline GLuint GameObject::getIBO() {
	return this->ibo;
}

inline const int GameObject::getNumOfTris() {
	return this->numOfTris;
}
*/

inline glm::vec3 GameObject::getPos() {
	return this->pos;
}

inline glm::vec3 GameObject::getRightVec() {
	return glm::vec3(modelMatrix[0][0], modelMatrix[0][1], modelMatrix[0][2]);
}

inline glm::vec3 GameObject::getUpVec() {
	return glm::vec3(modelMatrix[1][0], modelMatrix[1][1], modelMatrix[1][2]);
}

inline glm::vec3 GameObject::getForwardVec() {
	return glm::vec3(modelMatrix[2][0], modelMatrix[2][1], modelMatrix[2][2]);
}