#include "Header.h"
#include <math.h>
#include <algorithm>
#include <limits>

Submarine::Submarine(float x, float y, float z)
{
	this->pos.x = x;
	this->pos.y = y;
	this->pos.z = z;
}


Submarine::~Submarine()
{
}


void Submarine::render(Shader *submarineShader, bool pMode) {
	
	float sub_pos[4] = {
		pos.x + Fv.x,pos.y + Fv.y, pos.z + Fv.z
	};
 	glUniformMatrix4fv(glGetUniformLocation(submarineShader->handle(), "ViewMatrix"), 1, GL_FALSE, &modelMatrix[0][0]);
	glUniform4fv(glGetUniformLocation(submarineShader->handle(), "LightPos"), 1, LightPos);
	glUniform4fv(glGetUniformLocation(submarineShader->handle(), "light_ambient"), 1, Light_Ambient_And_Diffuse);
	glUniform4fv(glGetUniformLocation(submarineShader->handle(), "light_diffuse"), 1, Light_Ambient_And_Diffuse);
	glUniform4fv(glGetUniformLocation(submarineShader->handle(), "light_specular"), 1, Light_Specular);
	
	glUniform4fv(glGetUniformLocation(submarineShader->handle(), "material_ambient"), 1, Material_Ambient);
	glUniform4fv(glGetUniformLocation(submarineShader->handle(), "material_diffuse"), 1, Material_Diffuse);
	glUniform4fv(glGetUniformLocation(submarineShader->handle(), "material_specular"), 1, Material_Specular);
	glUniform1f(glGetUniformLocation(submarineShader->handle(), "material_shininess"), Material_Shininess);
	//if (isUnderWater()) {
	//	glUniform4fv(glGetUniformLocation(submarineShader->handle(), "sub_pos"), 1, sub_pos);
	//}
	//DRAW THE MODEL
	modelMatrix = glm::mat4(1.0);
	
	modelMatrix = glm::translate(modelMatrix, pos);

	tiltSubmarine();

	modelMatrix = Camera::getViewMatrix() * modelMatrix;

	glUniformMatrix4fv(glGetUniformLocation(submarineShader->handle(), "ModelViewMatrix"), 1, GL_FALSE, &modelMatrix[0][0]);

	glm::mat3 normalMatrix = glm::inverseTranspose(glm::mat3(modelMatrix));
	glUniformMatrix3fv(glGetUniformLocation(submarineShader->handle(), "NormalMatrix"), 1, GL_FALSE, &normalMatrix[0][0]);
	
	model.drawElementsUsingVBO(submarineShader);
	
	if(pMode) model.drawBoundingBox(submarineShader);
	//model.drawOctreeLeaves(submarineShader);

	
	minX = model.octree->minX;
	minY = model.octree->minY;
	minZ = model.octree->minZ;
	maxX = model.octree->maxX;
	maxY = model.octree->maxY;
	maxZ = model.octree->maxZ;

	depth = abs(minZ ) + abs(maxZ);
	height = abs(minY) + abs(maxY);
	width = abs(minX) + abs(maxX);


	count++;


	updateSpeed();
}

//update the speed of the submarine
void Submarine::updateSpeed() {
	//accelerate speed while moving
	if(isMoving()){
		if (movingForward) {
			speedCounter++;

			if (speedCounter > 80 && speedCounter <=81) {
				velocity += 1;
			}
			else if (speedCounter > 90 && speedCounter <= 91) {
				velocity  += 2;
			}
			else if (speedCounter > 115 && speedCounter <= 116) {
				velocity += 3;
			}
		}
	}
	else {
		speedCounter = 0;
		velocity = 5;
	}
}


void Submarine::load(Shader *submarineShader) {
	if (!submarineShader->load("BasicView", "glslfiles/basicTransformationsSub.vert", "glslfiles/basicTransformationsSub.frag"))
	{
		cout << "failed to load shader" << endl;
	}
	glUseProgram(submarineShader->handle());  // use the shader

	glEnable(GL_TEXTURE_2D);

	cout << " loading model " << endl;
	if (objLoader.loadModel("Models/submarine_/submarine v2/submarine5.obj", model))//returns true if the model is loaded, puts the model in the model parameter
	{
		cout << " model loaded " << endl;

		//if you want to translate the object to the origin of the screen,
		//first calculate the centre of the object, then move all the vertices
		//back so that the centre is on the origin.
		model.calcCentrePoint();
		model.centreOnZero();


		model.calcVertNormalsUsingOctree();  //the method will construct the octree if it hasn't already been created.


		//turn on VBO by setting useVBO to true in threeDmodel.cpp default constructor - only permitted on 8 series cards and higher
		model.initDrawElements();
		model.initVBO(submarineShader);
		//model.deleteVertexFaceData();
		
	}
	else
	{
		cout << " model failed to load " << endl;
	}


}

//tilt the submarine up
void Submarine::turnUp() {
	if (!stopMovingUp) {
		movingUp = true;

		tiltAngleZ += tiltVelocity;
		
		if (tiltAngleZ >= 25.0) {
			tiltAngleZ = 25.0;
		}
	}
}

//tilt the submarine down
void Submarine::turnDown() {

	if (!stopMovingDown) {
		movingDown = true;

		tiltAngleZ -= tiltVelocity;
		if (tiltAngleZ <= -25.0) {
			tiltAngleZ = -25.0;
		}
	}
}

//tilt the submarine left
void Submarine::turnLeft() {
	if(!stopMovingLeft) {
		movingLeft = true;

		tiltAngleY += (tiltVelocity);
	}
}

//tilt the submarine right
void Submarine::turnRight() {
	if (!stopMovingRight) {
		movingRight = true;
		tiltAngleY -= (tiltVelocity);

		/*tiltAngleX -= 0.1f;
		if (tiltAngleX <= -10.0) {
			tiltAngleX = -10.0;
		}*/
	}
}

//move the submarine forwards
//add a forward to the current position
void Submarine::moveForward() {
	if (!stopMovingForward) {
		movingForward = true;

		pos -= Fv * velocity*vel_scaler;
	}
}

//move the submarine forwards
//add a forward to the current position
void Submarine::moveBackward() {
	if (!stopMovingBackward) {
		movingBackward = true;

		pos += Fv * velocity*0.5f*vel_scaler;
	}

}

//reset the position od the submarine to 0,0,0
void Submarine::resetPos() {
	pos = glm::vec3(0.0,0.0,0.0);
}

/*
	Function responsible for tilting the submarine left,right or up depenging on where is moving to.

	Increases or decreases tiltAngle depending on the movement till it reached the maximum tilt value(10.0).
*/
void Submarine::tiltSubmarine() {


	modelMatrix = glm::rotate(modelMatrix, tiltAngleX, glm::vec3(0, 0, 1));
	modelMatrix = glm::rotate(modelMatrix, tiltAngleY, glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, tiltAngleZ, glm::vec3(1, 0, 0));

	glm::vec3 startFv(0, 0, 1);
	
	glm::mat4 rotMat = glm::mat4(1.0);

	rotMat = glm::rotate(rotMat, tiltAngleX, glm::vec3(0, 0, 1));
	rotMat = glm::rotate(rotMat, tiltAngleY, glm::vec3(0, 1, 0));
	rotMat = glm::rotate(rotMat, tiltAngleZ, glm::vec3(1, 0, 0));


	Fv = glm::vec3(rotMat*glm::vec4(startFv, 0.0));
	
}

//check submarine's collision with other objects,
//using the spheres and rectangels around the objects
void Submarine::checkCollision(vector<Rect> rects, vector<Sphere> spheres) {
	
	checkFrontWallCollision(rects);
	checkLeftWallCollision(rects);
	checkBackWallCollision(rects);
	checkRightWallCollision(rects);
	checkSeafloorCollision(rects);
	checkWaveCollision(rects);
	
	checkSphereCollision(spheres);
}

//check if the submarine is intercecting with a rectangle
bool Submarine::isIntercecting(Rect rect) {
	float sub_minX = minX + pos.x + Fv.x;
	float sub_minY = minY + pos.y + Fv.y;
	float sub_minZ = minZ + pos.z + Fv.z;
	float sub_maxX = maxX + pos.x + Fv.x;
	float sub_maxY = maxY + pos.y + Fv.y;
	float sub_maxZ = maxZ + pos.z + Fv.z;

	float r_minX = rect.minX + rect.pos.x;
	float r_minY = rect.minY + rect.pos.y;
	float r_minZ = rect.minZ + rect.pos.z;
	float r_maxX = rect.maxX + rect.pos.x;
	float r_maxY = rect.maxY + rect.pos.y;
	float r_maxZ = rect.maxZ + rect.pos.z;

	glm::vec3 pointsA[8] = {
		glm::vec3(sub_minX,sub_minY,sub_minZ),// 000
		glm::vec3(sub_minX,sub_minY,sub_maxZ),// 001
		glm::vec3(sub_minX,sub_maxY,sub_minZ),// 010
		glm::vec3(sub_minX,sub_maxY,sub_maxZ),// 011
		glm::vec3(sub_maxX,sub_minY,sub_minZ),// 100
		glm::vec3(sub_maxX,sub_minY,sub_maxZ),// 101
		glm::vec3(sub_maxX,sub_maxY,sub_minZ),// 110
		glm::vec3(sub_maxX,sub_maxY,sub_maxZ)//  111
	};
	glm::vec3 pointsB[8] = {
		glm::vec3(r_minX,r_minY,r_minZ),// 000
		glm::vec3(r_minX,r_minY,r_maxZ),// 001
		glm::vec3(r_minX,r_maxY,r_minZ),// 010
		glm::vec3(r_minX,r_maxY,r_maxZ),// 011
		glm::vec3(r_maxX,r_minY,r_minZ),// 100
		glm::vec3(r_maxX,r_minY,r_maxZ),// 101
		glm::vec3(r_maxX,r_maxY,r_minZ),// 110
		glm::vec3(r_maxX,r_maxY,r_maxZ)//  111
	};


	if (isSeperated(pointsA, pointsB, this->getRightVec()))
		return false;
	if (isSeperated(pointsA, pointsB, this->getUpVec()))
		return false;
	if (isSeperated(pointsA, pointsB, this->getForwardVec()))
		return false;

	if (isSeperated(pointsA, pointsB, rect.getRightVecSun()))
		return false;
	if (isSeperated(pointsA, pointsB, rect.getUpVecSun()))
		return false;
	if (isSeperated(pointsA, pointsB, rect.getForwardVecSun()))
		return false;

	if (isSeperated(pointsA, pointsB, glm::cross(this->getRightVec(), rect.getRightVecSun())))
		return false;
	if (isSeperated(pointsA, pointsB, glm::cross(this->getRightVec(), rect.getUpVecSun())))
		return false;
	if (isSeperated(pointsA, pointsB, glm::cross(this->getRightVec(), rect.getForwardVecSun())))
		return false;

	if (isSeperated(pointsA, pointsB, glm::cross(this->getUpVec(), rect.getRightVecSun())))
		return false;
	if (isSeperated(pointsA, pointsB, glm::cross(this->getUpVec(), rect.getUpVecSun())))
		return false;
	if (isSeperated(pointsA, pointsB, glm::cross(this->getUpVec(), rect.getForwardVecSun())))
		return false;

	if (isSeperated(pointsA, pointsB, glm::cross(this->getForwardVec(), rect.getRightVecSun())))
		return false;
	if (isSeperated(pointsA, pointsB, glm::cross(this->getForwardVec(), rect.getUpVecSun())))
		return false;
	if (isSeperated(pointsA, pointsB, glm::cross(this->getForwardVec(), rect.getForwardVecSun())))
		return false;

	return true;
}

//check if the submarine is intercecting with a spehere
bool Submarine::isIntercectingSphere(Sphere s) {
	float x = max(minX + pos.x + Fv.x, min(s.pos.x, maxX + pos.x + Fv.x));
	float y = max(minY + pos.y + Fv.y, min(s.pos.y, maxY + pos.y + Fv.y));
	float z = max(minZ + pos.z + Fv.z, min(s.pos.z, maxZ + pos.z + Fv.z));

	float distance = sqrt((x - s.pos.x) * (x - s.pos.x) +
		(y - s.pos.y) * (y - s.pos.y) +
		(z - s.pos.z) * (z - s.pos.z));

	if (distance <= s.getRadius()) {
		//cout << "collides with sphere" << endl;
		return true;
	}
	return false;
}

//collision response for collision with a sphere
void Submarine::CRSphere(Sphere s) {
	pos += glm::vec3(0,1,0)*5.0f;
}

// aCorn and bCorn are arrays containing all corners (vertices) of the two OBBs
//returns false if they are overlaping or intercecting
bool Submarine::isSeperated(glm::vec3 aCorn[], glm::vec3 bCorn[], glm::vec3 axis) {

	// Handles the cross product = {0,0,0} case
	if (axis == glm::vec3(0.0, 0.0, 0.0))
		return false;

	//sets the values to the highest float value
	float aMin = numeric_limits<float>::max();
	float aMax = -numeric_limits<float>::max();
	float bMin = numeric_limits<float>::max();
	float bMax = -numeric_limits<float>::max();
	//cout << aMin << " " << aMax << " " << bMin << " " << bMax << endl;

	// Define two intervals, a and b. Calculate their min and max values
	for (int i = 0; i < 8; i++) {
		float aDist = glm::dot(aCorn[i], axis);
		aMin = (aDist < aMin) ? aDist : aMin;
		aMax = (aDist > aMax) ? aDist : aMax;
		float bDist = glm::dot(bCorn[i], axis);
		bMin = (bDist < bMin) ? bDist : bMin;
		bMax = (bDist > bMax) ? bDist : bMax;
		//cout << " a:" << aDist << "  b:" << bDist << endl;
	}

	// One-dimensional intersection test between a and b
	float longSpan = max(aMax, bMax) - min(aMin, bMin);		//max():returns the maximum,  min():returns the minimum
	float sumSpan = aMax - aMin + bMax - bMin;

	if (longSpan <= sumSpan)// Change this to <= if you want the case were they are touching but not overlapping, to count as an intersection
		return false;
	return true;
}

//check collision witht the front wall
void Submarine::checkFrontWallCollision(vector<Rect> rects) {
	bool intercecting = false;
	//cout << getDistanceZ(rects[0]) << "   h:" << rects[0].height+rects[0].pos.y <<" | "<<pos.y<< endl;
	//cout << getDistanceZ(rects[2]) << "   rpos:" << rects[2].pos.y << " | subpos:" << pos.x << " " << pos.y << endl;
	float dist = getDistanceZ(rects[0]);
	//cout << pos.x << " " << pos.y << " " << pos.z << "  dist:" << dist << endl;

	if (dist < 183.0) {
		intercecting = isIntercecting(rects[0]);
		if (intercecting) {
			pos.z = rects[0].pos.z + rects[0].depth + depth / 2;
		//	cout << "collides front  ";
		}
	}
}

//check collision witht the left wall
void Submarine::checkLeftWallCollision(vector<Rect> rects) {
	bool collides = false;

	float dist = getDistanceX(rects[2]);
	
	/*cout << pos.x + Fv.x << "  " << pos.y + Fv.y << "  " << pos.z + Fv.z <<
		" "<<pos.x<<" "<<pos.y<<"  "<<pos.z<<
		" | dist: " << dist << endl;
	*/
	if (dist < 165.0) {
		collides = isIntercecting(rects[2]);

		if (collides) {
			//cout << "collision  ";
			pos.x = rects[2].pos.x + rects[2].width + width/2;
		}
	}
}

//check collision witht the back wall
void Submarine::checkBackWallCollision(vector<Rect> rects) {
	bool collides = false;
	
	float dist = getDistanceZ(rects[3]);
	
	//cout << pos.x + Fv.x << "  " << pos.y + Fv.y << "  " << pos.z + Fv.z << " | dist: " << dist << endl;

	if (dist < 134.0) {
		collides = isIntercecting(rects[3]);

		if (collides) {
		//	cout << "collides with back wall" << endl;
			pos.z = rects[3].pos.z - rects[3].depth - depth/2 ;
		}
	}

}

//check collision witht the right wall
void Submarine::checkRightWallCollision(vector<Rect> rects) {
	bool collides = false;

	float dist = getDistanceX(rects[4]);
	if (dist < 200.0) {
		collides = isIntercecting(rects[4]);
		
		if (collides) {
			pos.x = rects[4].pos.x - rects[4].width - width/2;
		}
	}
	//cout << pos.x + Fv.x << "  " << pos.y + Fv.y << "  " << pos.z + Fv.z << " | dist: " << dist << endl;

}

//check collision witht the seafloor
void Submarine::checkSeafloorCollision(vector<Rect> rects) {
	bool collidesFloor = false;
	float dist = getDistanceY(rects[1]);

	/*cout << pos.x << " " << pos.y << " " << pos.z
		<< "  floor: " << rects[1].pos.x << " " << rects[1].pos.y << " " << rects[1].pos.z << "   dist:"<<dist<<endl;
	*/
	float y = pos.y + Fv.y;

	if (y-height/2 < rects[1].height + rects[1].pos.y) {
		//Fv -= glm::vec3(rects[1].normalMatrix[1][0], rects[1].normalMatrix[1][1], rects[1].normalMatrix[1][2]);
		pos.y = rects[1].height + rects[1].pos.y+height/2;
		collidesFloor = true;

	}
}

//check collision witht the wave
void Submarine::checkWaveCollision(vector<Rect> rects) {
	bool collides = false;
	//cout << modelMatrix[2][0] << " " << modelMatrix[2][1] << "  " << modelMatrix[2][2] << endl;
	float dist = 0;
	//cout << pos.x + Fv.x << "  " << pos.y + Fv.y << "  " << pos.z + Fv.z << " | dist: " << dist << endl;
	
	//collision response fot the wave collision
	if (pos.y + Fv.y >= 240.0 && !movingDown) {
		pos.y = 240.0 + height/2 - 5.0;
		resetTiltAngleZ();
		stopMovingUp = true;
	}
	else stopMovingUp = false;

	//disable submarine to move backwards if its point down when it's on the top of the submarine
	if (movingDown && collides) {
		if (movingBackward) {
			pos.y = 240.0 + height / 2 - 5.0;
		}
	}
}

void Submarine::checkGameObjectCollision(vector<Rect> rects) {
	bool collides = false;
	cout << "FIX IT!!" << endl;
	//collides = isIntercecting(rects[5]);
/*	if (collides) {
		if(movingForward)
			Fv += glm::vec3(rects[5].normalMatrix[2][0],
				rects[5].normalMatrix[2][1],
				rects[5].normalMatrix[2][2]);

		cout << "collides with rock" << endl;
	}*/
}

//chcek if there is a collision with a sphere
void Submarine::checkSphereCollision(vector<Sphere> spheres) {
	bool collides = false;
	for (auto s : spheres) {
		collides = isIntercectingSphere(s);
		if (collides) {
			hasSphereCollision = true;
			CRSphere(s);
			vel_scaler = 0.1f;
			cout << "Sphere collision   ";
		}
		else {
			vel_scaler = 1.0f;
			last_pos = pos;
		}
	}
	if (!collides) hasSphereCollision = false;
}

void Submarine::resetTiltAngleZ() {
	if (tiltAngleZ <= 0.0) {
		tiltAngleZ = 0.0;
	}
	else {
		tiltAngleZ -= tiltVelocity;
	}
}

//check if the submarine id under the water
bool Submarine::isUnderWater() {
	if (pos.y + Fv.y < 240.0) {
		return true;
	}
	return false;
}

//bool Submarine::findFirstHitCD(Octree* B, GameObject gameObj) {
//
//	bool collision = false;
//	cout << "LVL: " << B->getLevel() << "  MAX D:" << MAX_DEPTH << endl;
//	if (B->getLevel() <= MAX_DEPTH ) //leaf
//	{
//		cout << "count: " << count << "   LVL:" << B->getLevel() << endl;
//		for (int i = 0; i < 8; i++) {
//			if (B->getChild(i) != NULL) {
//				/*bminX = B->getChild(i)->minX;
//				bminY = B->getChild(i)->minY;
//				bminZ = B->getChild(i)->minZ;
//				bmaxX = B->getChild(i)->maxX;
//				bmaxY = B->getChild(i)->maxY;
//				bmaxZ = B->getChild(i)->maxZ; */
//				float bminX = B->getChild(i)->minX + gameObj.getSunPos().x;
//				float bminY = B->getChild(i)->minY + gameObj.getSunPos().y;
//				float bminZ = B->getChild(i)->minZ + gameObj.getSunPos().z;
//				float bmaxX = B->getChild(i)->maxX + gameObj.getSunPos().x;
//				float bmaxY = B->getChild(i)->maxY + gameObj.getSunPos().y;
//				float bmaxZ = B->getChild(i)->maxZ + gameObj.getSunPos().z;
//				if(X_min <= X <= X_max and Y_min <= Y <= Y_max and Z_min <= Z <= Z_max)
//				cout << bminX << "|" << bmaxX << "  " << bminY << "|" << bmaxY << "  " << bminZ << "|" << bmaxZ << endl;
//				for (int k = 0; k < 3; k++) {
//					float x = test_points[k].x;
//					float y = test_points[k].y;
//					float z = test_points[k].z;
//					if (bminX <= x && x <= bmaxX
//						&& bminY <= y && y <= bmaxY
//						&& bminZ <= z && z <= bmaxZ)
//					{
//						cout << "collides" << endl;
//						collision = true;
//						return collision;
//				
//					}
//					else {
//						cout << "no collision" << endl;
//						
//					}
//				}
//			}
//			if(!collision)
//				findFirstHitCD(B->getChild(i), gameObj);
//		}
//		 the point of the submarine is inside the octree points of the other object (min,max)
//		if inside check the leaves to find where it collides
//		return true
//		if (/*point inside the other object*/) {
//		/*	for (int i = 0; i < 8; i++)
//			{
//				if (children[i] != NULL)
//					children[i]->drawBoxesAtLeaves(myShader);
//			}
//		}*/
//	}
//	
//	
//	return false;
//}