#pragma once
class Point
{
private:

	glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::mat4 modelMatrix;
	ThreeDModel model;
	OBJLoader objLoader;
public:
	Point();
	~Point();

	void render(Shader* shader,glm::vec3 p);
	void load(Shader* shader);

	void setPos(glm::vec3 p);

	glm::vec3 getPos();
};

inline void Point::setPos(glm::vec3 p) {
	this->pos = p;
}

inline glm::vec3 Point::getPos() {
	return this->pos;
}