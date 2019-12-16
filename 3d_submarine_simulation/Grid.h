

class Grid
{
private:
	//Material properties
	//float Material_Ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	//float Material_Diffuse[4] = { 0.8f, 0.8f, 0.5f, 1.0f };
	//float Material_Specular[4] = { 0.9f,0.9f,0.8f,1.0f };
	//float Material_Shininess = 50;

	////Light Properties
	//float Light_Ambient_And_Diffuse[4] = { 0.8f, 0.8f, 0.6f, 1.0f };
	//float Light_Specular[4] = { 1.0f,1.0f,1.0f,1.0f };
	////float LightPos[4] = { 0.0f, 100.0f, 0.0f, 0.0f };
	////float LightPos[4] = { -466.0f, 18470.0f, -1805.0f, 0.0f };
	//float LightPos[4] = { 0, 1800.0f, -400.0f, 0.0f };
	float Light_Ambient[4] = { 0.8, 0.8, 0.6, 1.0 };
	float Light_Diffuse[4] = { 0.9, 0.9, 0.7, 1.0 };
	float Light_Specular[4] = { 0.9, 0.9, 0.9, 1.0 };

	float Material_Ambient[4] = { 0.3, 0.3, 0.3, 1.0 };
	float Material_Diffuse[4] = { 0.6, 0.6, 0.6, 1.0 };
	float Material_Specular[4] = { 0.8, 0.8, 0.8, 1.0 };
	float Material_Shininess = 40.0;

	unsigned int m_vaoID;		    // vertex array object
	unsigned int m_vboID[2];		// two VBOs - used for colours and vertex data
	unsigned int ibo;				//separate id for the vbo for the triangle indices

	int numOfVerts;
	int numOfTris;
	float* verts;
	float* normals;
	unsigned int* tris;

	glm::vec3 pos = glm::vec3(0, 0, 0);

	glm::mat4 modelMatrix;
	glm::mat3 normalMatrix;

	ThreeDModel model;
	OBJLoader objLoader;

	float temp = 0;

public:
	Grid();
	void render(Shader* shader);
	void constructGeometry(Shader* s,int width, int dim);
	GLuint loadPNG(const char* strFileName);

	void setPos(glm::vec3 p);
	GLuint texName;
	glm::vec3 getPos();
};

inline void Grid::setPos(glm::vec3 p) {
	this->pos = p;
}

inline glm::vec3 Grid::getPos() {
	return this->pos;
}