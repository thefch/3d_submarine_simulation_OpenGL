#pragma once
class Seabed
{
private:


	glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.f);
	glm::vec3 botPos = glm::vec3(0.0f, 0.0f, 0.f);
	glm::vec3 midPos = glm::vec3(0.0f, 0.0f, 0.f);
	glm::vec3 topPos = glm::vec3(0.0f, 0.0f, 0.f);

	glm::mat4 modelMatrix;
	glm::mat4 botMatrix;
	glm::mat4 midMatrix;
	glm::mat4 topMatrix;


	

	OBJLoader objLoader;
public:
	Seabed();
	~Seabed();
	float useFog = 0.0;
	ThreeDModel midModel;
	ThreeDModel model;
	ThreeDModel botModel;
	ThreeDModel topModel;
	float minXbot, maxXbot, minYbot, maxYbot, minZbot, maxZbot;

	void render(Shader *shader);
	void renderBottom(Shader *shader);
	//void renderMid(Shader *shader);
	void renderTop(Shader *shader);


	void load(Shader *shader);
	void loadBottom(Shader *shader);
	void loadMid(Shader *shader);
	void loadTop(Shader *shader);

	void setPos(glm::vec3 p);
	void setBotPos(glm::vec3 p);
	void setMidPos(glm::vec3 p);
	void setTopPos(glm::vec3 p);


	glm::vec3 getPos();
	glm::vec3 getBotPos();
	glm::vec3 getMidPos();
	glm::vec3 getTopPos();

};

inline void Seabed::setPos(glm::vec3 p) {
	this->pos = p;
}

inline void Seabed::setBotPos(glm::vec3 p) {
	this->botPos = p;
}
inline void Seabed::setMidPos(glm::vec3 p) {
	this->midPos = p;
}
inline void Seabed::setTopPos(glm::vec3 p) {
	this->topPos = p;
}


inline glm::vec3 Seabed::getPos() {
	return this->pos;
}

inline glm::vec3 Seabed::getBotPos() {
	return this->botPos;
}

inline glm::vec3 Seabed::getMidPos() {
	return this->midPos;
}

inline glm::vec3 Seabed::getTopPos() {
	return this->topPos;
}