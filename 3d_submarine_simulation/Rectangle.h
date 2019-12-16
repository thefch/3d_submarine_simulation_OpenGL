#pragma once


class Rect
{

private:
	unsigned int m_vaoID;
	unsigned int m_vboID[3];
	GLuint ibo;

	static int numOfVerts;
	static int numOfTris;

	float verts[24];
	float cols[24];
	unsigned int tris[36];
	
	glm::mat4 rectMatrix;


public:
	Rect();
	Rect(glm::vec3 pos, int dim);
	Rect(glm::vec3 pos, int width, int height, int depth);
	float cx=0, cy=0, cz=0;
	int dim;
	int width, height, depth;
	float minX, minY, minZ, maxX, maxY, maxZ;
	float tiltAngleY = 0.0;
	
	glm::mat3 normalMatrix;
	glm::vec3 pos = glm::vec3(0, 0, 0);
	glm::vec3 Fv = glm::vec3(0, 1, 0);

	void Rect::constructGeometry(Shader* myShader);
	void render(Shader* shader,bool polygoneMode);
	void calcMinMax();
	void setPos(glm::vec3 p);
	void setTiltAngleY(float a);

	glm::vec3 getPos();

	glm::vec3 getRightVecSun();
	glm::vec3 getUpVecSun();
	glm::vec3 getForwardVecSun();

};

inline void Rect::setPos(glm::vec3 p) {
	this->pos = p;
}

inline void Rect::setTiltAngleY(float a) {
	this->tiltAngleY = a;
}

/************************************/

inline glm::vec3 Rect::getPos() {
	return this->pos;
}

inline glm::vec3 Rect::getRightVecSun() {
	return glm::vec3(rectMatrix[0][0], rectMatrix[0][1], rectMatrix[0][2]);
}

inline glm::vec3 Rect::getUpVecSun() {
	return glm::vec3(rectMatrix[1][0], rectMatrix[1][1], rectMatrix[1][2]);
}

inline glm::vec3 Rect::getForwardVecSun() {
	return glm::vec3(rectMatrix[2][0], rectMatrix[2][1], rectMatrix[2][2]);
}