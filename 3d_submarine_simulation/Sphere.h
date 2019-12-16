
#include "gl\glew.h"

class Shader;

class Sphere
{
private:
	unsigned int m_vaoID;		    // vertex array object
	unsigned int m_vboID[3];		// two VBOs - used for colours, vertex and normals data
	GLuint ibo;                     //identifier for the triangle indices

	int numOfVerts;
	int numOfTris;

	float* verts;
	float* norms;
	unsigned int* tInds;

	float cx, cy, cz; //centre of the sphere
	float r;		//radius of the sphere

public:
	glm::vec3 pos = glm::vec3(0.0, 0.0, 0.0);
	glm::mat3 normalMatrix;
	glm::mat4 modelMatrix;
	Sphere();
	Sphere(glm::vec3 pos, float rad);

	void createSphere(Shader* myShader, int level);
	void render(Shader* sphereShader);

	void setRadius(float rad);
	void setCentre(float x, float y, float z);
	void setPosition(glm::vec3 pos);

	float getRadius();
	unsigned int getVaoID();
};

inline unsigned int Sphere::getVaoID() {
	return this->m_vaoID;
}

inline float Sphere::getRadius() {
	return this->r;
}

inline void Sphere::setPosition(glm::vec3 pos) {
	this->pos = pos;
}