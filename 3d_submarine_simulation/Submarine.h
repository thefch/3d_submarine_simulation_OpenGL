#pragma once

class Submarine
{
private:
	int count = 0;

	//Material properties
	float Material_Ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	float Material_Diffuse[4] = { 0.8f, 0.8f, 0.5f, 1.0f };
	float Material_Specular[4] = { 0.9f,0.9f,0.8f,1.0f };
	float Material_Shininess = 50;

	//Light Properties
	float Light_Ambient_And_Diffuse[4] = { 0.8f, 0.8f, 0.6f, 1.0f };
	float Light_Specular[4] = { 1.0f,1.0f,1.0f,1.0f };
	//float LightPos[4] = { 0.0f, 100.0f, 0.0f, 0.0f };
	//float LightPos[4] = { -466.0f, 18470.0f, -1805.0f, 0.0f };
	float LightPos[4] = { 0, 1800.0f, -400.0f, 0.0f };


	float tiltAngleX = 0.0f;
	float tiltAngleY = 0.0f;
	float tiltAngleZ = 0.0f;

	float height, width, depth;

	float lastZ = 0.0f;

	float subFromWaveDist = 0.0;
	float subFromBottomDist = 0.0;

	bool collisionDetected = false;
	bool onTopCollision = false;
	bool movingRight = false;
	bool movingLeft = false;
	bool movingUp = false;
	bool movingForward = false;
	bool movingDown = false;
	bool movingBackward = false;
	bool hasSphereCollision = false;

	bool stopMovingRight = false;
	bool stopMovingLeft = false;
	bool stopMovingUp = false;
	bool stopMovingForward = false;
	bool stopMovingDown = false;
	bool stopMovingBackward = false;
	bool isOnTopMoveBackwards = false;

	//string latestTiltAxis = " ";
	glm::mat4 modelMatrix;
	glm::mat4 normalMatrix;

	glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Fv = glm::vec3(0, 0, 1);
	glm::vec3 temp_Fv = glm::vec3(0, 0, 1);

	glm::vec3 last_pos;
	float velocity = 5.0f;  //1.0f

	float vel_scaler = 1.0f;
	float tiltVelocity = 1.0;
	float speedCounter = 0;
	ThreeDModel model;
	OBJLoader objLoader;

public:

	glm::vec3 test_points[3];

	Submarine(float x, float y, float z);
	~Submarine();
	float minX, minY, minZ, maxX, maxY, maxZ;

	//float posX = 0.0, posY = 0.0, posZ = 0.0;
	glm::vec3 forwardVec;
	glm::vec3 rightVec;
	glm::vec3 upVec;


	void render(Shader *submarine, bool pMode);
	glm::mat4 getModelMatrix();
	glm::vec3 getPosVec3();
	bool isMovingRight();
	bool isMovingLeft();
	bool isMovingUp();
	bool isMovingDown();
	bool isMovingForward();
	bool isMovingBackward();
	bool isMoving();
	bool isUnderWater();


	bool isSeperated(glm::vec3 aCorn[], glm::vec3 bCorn[], glm::vec3 axis);
	bool isIntercecting(Rect rect);
	bool isIntercectingSphere(Sphere s);
	void CRSphere(Sphere s);
	//bool findFirstHitCD(Octree* B, GameObject gameObj);

	float getTiltAngleX();
	float getTiltAngleY();
	float getTiltAngleZ();
	float getPosX();
	float getPosY();
	float getPosZ();
	
	glm::vec3 getRot();
	glm::vec3 getUpVec();
	glm::vec3 getRightVec();
	glm::vec3 getForwardVec();


	float getDistanceZ(Rect r);
	float getDistanceX(Rect r);
	float getDistanceY(Rect r);


	void load(Shader* subamrineShader);
	void tiltSubmarine();
	void resetTiltAngleZ();
	//void checkCollision(vector<Rect*> rects, Wave wave, GameObject seabed);
	void checkCollision(vector<Rect> rects, vector<Sphere> spheres);
	void checkFrontWallCollision(vector<Rect> rects);
	void checkLeftWallCollision(vector<Rect> rects);
	void checkBackWallCollision(vector<Rect> rects);
	void checkRightWallCollision(vector<Rect> rects);
	void checkWaveCollision(vector<Rect> rects);
	void checkGameObjectCollision(vector<Rect> rects);
	void checkSphereCollision(vector<Sphere> spheres);
	void checkSeafloorCollision(vector<Rect> rects);
	void updateSpeed();

	void setPosition(glm::vec3 p);
	void setMovingRight(bool r);
	void setMovingLeft(bool l);
	void setMovingUp(bool u);
	void setMovingDown(bool d);
	void setMovingForward(bool f);
	void setMovingBackward(bool b);


	void turnUp();
	void turnDown();
	void turnLeft();
	void turnRight();
	void moveForward();
	void moveBackward();
	void resetPos();
};

inline glm::mat4 Submarine::getModelMatrix() {
	return modelMatrix;
}

inline bool Submarine::isMovingRight() {
	return movingRight;
}

inline bool Submarine::isMovingLeft() {
	return movingLeft;
}

inline bool Submarine::isMovingUp() {
	return movingUp;
}

inline bool Submarine::isMovingDown() {
	return movingDown;
}

inline bool Submarine::isMovingForward() {
	return movingForward;
}

inline bool Submarine::isMovingBackward() {
	return movingBackward;
}

inline float Submarine::getTiltAngleX() {
	return tiltAngleX;
}

inline float Submarine::getTiltAngleY() {
	return tiltAngleY;
}

inline float Submarine::getTiltAngleZ() {
	return tiltAngleZ;
}

inline glm::vec3 Submarine::getPosVec3() {
	return pos;
}

inline float Submarine::getPosX() {
	return pos.x;
}

inline float Submarine::getPosY() {
	return pos.y;
}

inline float Submarine::getPosZ() {
	return pos.z;
}

inline glm::vec3 Submarine::getRot() {
	return this->Fv;
}

inline glm::vec3 Submarine::getForwardVec() {
	return glm::vec3(modelMatrix[2][0],modelMatrix[2][1],modelMatrix[2][2]);
}
inline glm::vec3 Submarine::getRightVec() {
	return glm::vec3(modelMatrix[0][0], modelMatrix[0][1], modelMatrix[0][2]);

}inline glm::vec3 Submarine::getUpVec() {
	return glm::vec3(modelMatrix[1][0], modelMatrix[1][1], modelMatrix[1][2]);

}


inline float Submarine::getDistanceZ(Rect r) {
	return sqrt(
		pow(r.pos.z - (pos.z - Fv.z), 2)
	);
}

inline float Submarine::getDistanceX(Rect r) {
	return sqrt(
		pow(r.pos.x - (pos.x + Fv.x), 2) 
	);
}

inline float Submarine::getDistanceY(Rect r) {
	return sqrt(
		pow(r.pos.y - (pos.y - Fv.y), 2)
	);
}


inline bool Submarine::isMoving() {
	return (movingForward || movingBackward);
}

/*******/

inline void Submarine::setMovingRight(bool r) {
	movingRight = r;
}

inline void Submarine::setMovingLeft(bool l) {
	movingLeft = l;
}

inline void Submarine::setMovingUp(bool u) {
	movingUp = u;
}

inline void Submarine::setMovingDown(bool d) {
	movingDown = d;
}

inline void Submarine::setMovingForward(bool f) {
	movingForward = f;
}

inline void Submarine::setMovingBackward(bool b) {
	movingBackward = b;
}

inline void Submarine::setPosition(glm::vec3 p) {
	this->pos = p;
}