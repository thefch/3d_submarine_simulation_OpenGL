#pragma once
class Wave
{
private:
	glm::mat4 modelMatrix;
	glm::vec3 wavePos = glm::vec3(0.0, 0.0, 0.0);
	OBJLoader waveObjLoader;
	float displacement = 0.0;

	bool resetWave = false;

	float temp = 0;
public:
	Wave();

	void renderWave(Shader* handle);
	void loadWave(Shader *waveShader);
	ThreeDModel model;

	glm::vec3 getWavePos();

	void setWavePos(float x, float y, float z);

	double minX, minY, minZ, maxX, maxY, maxZ;

};


inline glm::vec3 Wave::getWavePos() {
	return this->wavePos;
}


inline void Wave::setWavePos(float x, float y, float z) {
	this->wavePos = glm::vec3(x, y, z);
}