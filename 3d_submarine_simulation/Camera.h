#pragma once
class Camera
{
private:
	static float camX;
	static float camY;
	static float camZ;

	static float tiltAngle;



public:
	Camera();
	~Camera();
	static glm::vec3 camPos;
	static glm::vec3 rot;
	static glm::mat4 objectRotation;
	static glm::quat q;

	static int camera_index;
	static float radius4;
//	static Actor actor;
	//static float cameraX;
	//static float cameraY;
	//static float cameraZ;

	//static glm::vec3 eye;
	//static glm::vec3 cameraWillLook;
	//static glm::vec3 cameraUp;

	static glm::mat4 viewMatrix;

	static glm::mat4 getViewMatrix() {
		return viewMatrix;
	}

	static void setViewMatrix(bool upPressed, float DcamX, float DcamY, Submarine submarine,int mousewheel);
	//static void setActorPos(float x, float y, float z);
	
	static void setCamera(int cam);

	static void update();

	static void updateTransform(float xinc, float yinc, float zinc);
};