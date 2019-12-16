#include "Header.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}

glm::vec3 Camera::camPos(0.0, 0.0, 0.0);
glm::vec3 Camera::rot(0.0, 0.0, 0.0);


glm::mat4 Camera::viewMatrix = glm::mat4(1.0);
glm::mat4 Camera::objectRotation = glm::mat4(1.0);
glm::quat Camera::q;

int Camera::camera_index = 1;

float Camera::radius4 = -100.0;
float Camera::camX = 0.0;
float Camera::camY = 0.0;
float Camera::camZ = 0.0;

float Camera::tiltAngle = 0.0;


void Camera::setViewMatrix(bool upPressed, float DcamX, float DcamY, Submarine submarine, int mousewheel) {
	camX = DcamX;
	camY = DcamY;

	/*
		float radius controls the field of view of the camera,
		how much back the camera will be from the object
	*/
	if (camera_index == 1) {
		float radius = mousewheel;

		camPos = glm::vec3(0, 0, 0);

		glm::vec4 camPosTransform = glm::vec4(camPos, 1.0f);
		glm::mat4 camPosTransformMat(1.0);

		camPosTransformMat = glm::translate(camPosTransformMat, submarine.getPosVec3());

		camPosTransformMat = glm::rotate(camPosTransformMat, DcamX, glm::vec3(0.0, 1.0, 0.0));
		camPosTransformMat = glm::rotate(camPosTransformMat, DcamY, glm::vec3(1.0, 0.0, 0.0));

		camPosTransformMat = glm::translate(camPosTransformMat, glm::vec3(0, 30.0, radius));


		camPosTransform = camPosTransformMat * camPosTransform;

		camPos = glm::vec3(camPosTransform);

		viewMatrix = glm::lookAt(camPos, submarine.getPosVec3(), glm::vec3(0, 1, 0));
	}
	else if (camera_index == 2) {
		float radius = 200;

		camPos = glm::vec3(0, 0, 0);

		glm::vec4 camPosTransform = glm::vec4(camPos, 1.0f);
		glm::mat4 camPosTransformMat(1.0);

		camPosTransformMat = glm::translate(camPosTransformMat, submarine.getPosVec3());

		camPosTransformMat = glm::rotate(camPosTransformMat, 0.0f, glm::vec3(0.0, 1.0, 0.0));
		camPosTransformMat = glm::rotate(camPosTransformMat, 0.0f, glm::vec3(1.0, 0.0, 0.0));

		camPosTransformMat = glm::translate(camPosTransformMat, glm::vec3(0, radius,30));


		camPosTransform = camPosTransformMat * camPosTransform;

		camPos = glm::vec3(camPosTransform);

		viewMatrix = glm::lookAt(camPos, submarine.getPosVec3(), glm::vec3(0, 1, 0));
	}
	else if (camera_index == 3) {
		float radius = 100;
		cout << "here  3" << endl;
		camPos = glm::vec3(0, 0, 0);

		glm::vec3 new_sub_look = glm::vec3(submarine.getPosVec3().x, submarine.getPosVec3().y + 20.0, submarine.getPosVec3().z - 20.0);

		glm::vec4 camPosTransform = glm::vec4(camPos, 1.0f);
		glm::mat4 camPosTransformMat(1.0);

		


		camPosTransformMat = glm::translate(camPosTransformMat, new_sub_look);


		camPosTransformMat = glm::rotate(camPosTransformMat, DcamX, glm::vec3(0.0, 1.0, 0.0));
		camPosTransformMat = glm::rotate(camPosTransformMat, DcamY, glm::vec3(1.0, 0.0, 0.0));

		camPosTransformMat = glm::translate(camPosTransformMat, glm::vec3(0, 30, 40));

		//camPosTransformMat = glm::rotate(camPosTransformMat, -submarine.getTiltAngleY(), glm::vec3(0.0, 1.0, 0.0));


		camPosTransform = camPosTransformMat * camPosTransform;


		camPos = glm::vec3(camPosTransform);

		viewMatrix = glm::lookAt(camPos, new_sub_look, glm::vec3(0, 1, 0));
	}
	else if (camera_index == 4) {
	
		radius4 = -50;
		camPos = glm::vec3(0, 0, 0);

		glm::vec4 camPosTransform = glm::vec4(camPos, 1.0f);
		glm::mat4 camPosTransformMat(1.0);

		camPosTransformMat = glm::translate(camPosTransformMat, submarine.getPosVec3());

		camPosTransformMat = glm::rotate(camPosTransformMat, 0.0f, glm::vec3(0.0, 1.0, 0.0));
		camPosTransformMat = glm::rotate(camPosTransformMat, 0.0f, glm::vec3(1.0, 0.0, 0.0));

		camPosTransformMat = glm::translate(camPosTransformMat, glm::vec3(0, radius4, 30));


		camPosTransform = camPosTransformMat * camPosTransform;

		camPos = glm::vec3(camPosTransform);

		viewMatrix = glm::lookAt(camPos, submarine.getPosVec3(), glm::vec3(0, 1, 0));


	}
	//cout << viewMatrix[0][0] <<" " <<viewMatrix[0][1] << " "<<viewMatrix[0][2] << endl;
}

void Camera::setCamera(int cam) {
	Camera::camera_index = cam;
}