#pragma once
class Skybox
{
private:
	/*glm::vec3 leftPos = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 rightPos = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 topPos = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 backPos = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 frontPos = glm::vec3(0.0, 0.0, 0.0);

	glm::vec3 bottomPos = glm::vec3(0.0, 0.0, 0.0);
	*/
	glm::vec3 pos = glm::vec3(0.0, 0.0, 0.0);

/*	glm::mat4 leftMatrix;
	glm::mat4 rightMatrix;
	glm::mat4 topMatrix;
	glm::mat4 backMatrix;
	glm::mat4 frontMatrix;
	glm::mat4 bottomMatrix;*/
	glm::mat4 modelMatrix;


	/*ThreeDModel leftModel;
	ThreeDModel rightModel;
	ThreeDModel topModel;
	ThreeDModel backModel;
	ThreeDModel frontModel;*/
	ThreeDModel model;

	OBJLoader objLoader;


public:
	Skybox();
	~Skybox();
	/*void load(Shader* shader);
	void loadBack(Shader* shader);
	void loadFront(Shader* shader);
	void loadTop(Shader* shader);
	void loadLeft(Shader* shader);
	void loadRight(Shader* shader);*/
	void loadCube(Shader *shader);

	/*void render(Shader* shader, Submarine subamrine);
	void renderBack(Shader* shader, Submarine submarine);
	void renderFront(Shader* shader, Submarine submarine);
	void renderTop(Shader* shader, Submarine submarine);
	void renderRight(Shader* shader, Submarine submarine);
	void renderLeft(Shader* shader, Submarine submarine);*/
	void renderSkyboxCube(Shader *shader, Submarine submarine);

	/*void setLeftPos(glm::vec3 lpos);
	void setRightPos(glm::vec3 rpos);
	void setTopPos(glm::vec3 tpos);
	void setBackPos(glm::vec3 bpos);
	void setFrontPos(glm::vec3 fpos);*/
	void setPos(glm::vec3 pos); 


};
/*
inline void Skybox::setBackPos(glm::vec3 bpos) {
	this->backPos = bpos;
}

inline void Skybox::setFrontPos(glm::vec3 fpos) {
	this->frontPos = fpos;
}

inline void Skybox::setLeftPos(glm::vec3 lpos) {
	this->leftPos = lpos;
}

inline void Skybox::setRightPos(glm::vec3 rpos) {
	this->rightPos = rpos;
}

inline void Skybox::setTopPos(glm::vec3 tpos) {
	this->topPos = tpos;
}
*/
inline void Skybox::setPos(glm::vec3 pos) {
	this->pos = pos;
}