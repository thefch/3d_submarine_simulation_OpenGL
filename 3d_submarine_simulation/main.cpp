
bool debug = true;
bool loadObjs = true;
#include "Header.h"
#pragma comment(lib, "glew32.lib")
//unsigned int m_vaoID;		    // vertex array object
//unsigned int m_vboID[3];		// two VBOs - used for colours and vertex data


glm::mat4 ProjectionMatrix; // matrix for the orthographic projection
glm::mat4 ModelViewMatrix;  // matrix for the modelling and viewing

bool keys[256];			// Array Used in the keyboard method.
int	mouse_x = 0, mouse_y = 0; int mousewheel = 100;
bool LeftPressed = false;
bool polygonMode = false;
int countMode = 0;
bool upPressed = false;
bool camXDecrease = false;
bool camXIncrease = false;
bool camYDecrease = false;
bool camYIncrease = false;
bool needToResetCam = false;


int screenWidth = 800, screenHeight = 800;
int camCounter = 0;
int bouble_cd = 0;

float dcamX = 0.0;
float dcamY = 0.0f;
float camXCD = 0.0f;
float camYCD = 0.0f;
unsigned int cubemapTexture;
/*
float actorX = 0.0;
float actorZ = 0.0;
float actorY = 0.0;
float camX = 0.0;
float camY = 0.0;
float camZ = 0.0;
*/

float amount = 0;
float temp = 0.0f;
float xtemp = 0, ytemp = 0, ztemp = 0;
float count_loaded = 0;

Submarine submarine(0.0, 0.0, 0.0);
Seabed seafloor = Seabed();
Wave wave = Wave();
Skybox skyboxCube = Skybox();
GameObject coral = GameObject(glm::vec3(30, -241.0, -721));
GameObject coral2 = GameObject(glm::vec3(246,-240, 174));

GameObject shell = GameObject(glm::vec3(530.451, -240.0, 17.20));
GameObject shell2 = GameObject(glm::vec3(-227, -240.0, -490));

GameObject rock = GameObject(glm::vec3(-1890.0, -215.0, 350.0));
GameObject rock2 = GameObject(glm::vec3(-630, -245, -530));

GameObject coralrock = GameObject(glm::vec3(-1800, -90, -1716));
GameObject coralrock1 = GameObject(glm::vec3(0, 0, 0));

GameObject ship = GameObject(glm::vec3(-1780, -280, 2050));

GameObject mixSeaObj1 = GameObject(glm::vec3(1350, -240, -1195));
GameObject mixSeaObj2 = GameObject(glm::vec3(577, -240, -1370));
GameObject mixSeaObj3 = GameObject(glm::vec3(750, -242, -834));

GameObject coralrock2 = GameObject(glm::vec3(1872,-200,-1644));



/***Collision Boxes****/
Rect r1 = Rect(glm::vec3(0,0,-1900),2200,250,170);	//frontwall
Rect r2 = Rect(glm::vec3(0, -270, 0), 2200, 40, 2200);  //seafloor
Rect r3 = Rect(glm::vec3(-2045, 0, 0), 150, 250, 2200); //leftwall
Rect r4 = Rect(glm::vec3(0, 0, 2300), 2000, 250, 120); //backwall
Rect r5 = Rect(glm::vec3(2090, 50, 0), 190, 280, 2200); //rightwall
Rect r6 = Rect(rock.getPos(), 90 ,60, 190); //rock box

Sphere s1 = Sphere(shell.getPos(),15); //shell
Sphere s2 = Sphere(coral.getPos(), 15); //coral
Sphere s3 = Sphere(rock.getPos()-glm::vec3(50,140,0.0),280); //rock1
Sphere s4 = Sphere(rock2.getPos() , 32); //rock1
Sphere s5 = Sphere(shell2.getPos(), 15); //shell2
Sphere s6 = Sphere(coral2.getPos(), 15); //coral2


Sphere s7 = Sphere(coralrock.getPos() + glm::vec3(-60, -350, -80), 630);// corlrock
Sphere s8 = Sphere(ship.getPos(),500);// ship

Sphere s9 = Sphere(mixSeaObj1.getPos(), 36);// mixObj1
Sphere s10 = Sphere(mixSeaObj2.getPos(), 36);// mixObj2
Sphere s11 = Sphere(mixSeaObj3.getPos(), 36);// mixObj3

Sphere s12 = Sphere(coralrock2.getPos(), 150);// mixObj3





/***********************************/
Shader* submarineShader;  
Shader* seaFloorTopShader;
Shader* seaFloorBotShader;
Shader* sphereShader;
Shader* rectShader;
Shader* waveShader;
Shader* skyboxShader;
Shader* pointShader;
Shader* objectShader;

Shader* texShader;
/***********************************/
Point p1 = Point();
Point p2 = Point();
Point p3 = Point();
Point p4 = Point();


vector<Rect> rects;
vector<Sphere> spheres;
//OPENGL FUNCTION PROTOTYPES
void display();				//called in winmain to draw everything to the screen
void reshape(int width, int height);				//called when the window is resized
void init();				//called in winmain when the program starts.
void processKeys();         //called in winmain to process keyboard input
void centerCamera();
void resetCamera();
void matLocConf(Shader* shader);

GLuint loadPNG(char* name);
GLuint matLocation;
/*************    START OF OPENGL FUNCTIONS   ****************/
void display()									
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	Camera::setViewMatrix(upPressed, dcamX, dcamY, submarine,mousewheel);
	ModelViewMatrix = Camera::getViewMatrix() * ModelViewMatrix;

	//***************************************************************
	if (loadObjs ) {
		matLocConf(objectShader);
		shell.render(objectShader);
		shell2.render(objectShader);

		coral.render(objectShader);
		coral2.render(objectShader);
		
		rock.render(objectShader);
		rock2.render(objectShader);
		
	
		coralrock.render(objectShader);
		//coralrock1.render(objectShader);
	
		ship.render(objectShader);

		mixSeaObj1.render(objectShader);
		mixSeaObj2.render(objectShader);
		mixSeaObj3.render(objectShader);
		coralrock2.render(objectShader);

	}
	//***************************************************************

	//matLocConf(sunShader);
	
	//***************************************************************
	matLocConf(waveShader);
	wave.renderWave(waveShader);

	//***************************************************************
	matLocConf(submarineShader);

	submarine.render(submarineShader, polygonMode);
	submarine.checkCollision(rects,spheres);

	//**************************************************************

	matLocConf(seaFloorBotShader);
	seafloor.renderBottom(seaFloorBotShader);
	matLocConf(seaFloorTopShader);
	seafloor.renderTop(seaFloorTopShader);
	//***************************************************************
	matLocConf(skyboxShader);
	skyboxCube.renderSkyboxCube(skyboxShader,submarine);
	//***************************************************************
	//***************************************************************
	if (debug && polygonMode) {
		matLocConf(rectShader);
		rects[0].render(rectShader, polygonMode);	//front wall
		rects[1].render(rectShader, polygonMode);	//seafloor
		rects[2].render(rectShader, polygonMode);	//left wall
		rects[3].render(rectShader, polygonMode);	//backwall	
		rects[4].render(rectShader, polygonMode);	//right wall
		
		//rects[5].render(rectShader, polygonMode);	//right wall

		matLocConf(sphereShader);
		spheres[0].render(sphereShader);
		spheres[1].render(sphereShader);
		spheres[2].render(sphereShader);
		spheres[3].render(sphereShader);
		spheres[4].render(sphereShader);
		spheres[5].render(sphereShader);
		spheres[6].render(sphereShader);
		spheres[7].render(sphereShader);
		spheres[8].render(sphereShader);
		spheres[9].render(sphereShader);
		spheres[10].render(sphereShader);
		spheres[11].render(sphereShader);


		
	}
	/***************************************************************/
	
	//cout << dcamX << " " << dcamY << endl;
	//cout << "Sub:   "<<submarine.getPosX()+submarine.getRot().x << "  " << submarine.getPosY() + submarine.getRot().y << "  " << submarine.getPosZ() + submarine.getRot().z<< endl;
	//cout << Camera::camPos.x << " " << Camera::camPos.y << " " << Camera::camPos.z << endl;	
	
	glUseProgram(0); //turn off the current shader
	glFlush();

}
void matLocConf(Shader* shader) {
	glUseProgram(shader->handle());  // use the shader
	matLocation = glGetUniformLocation(shader->handle(), "ProjectionMatrix");
	glUniformMatrix4fv(matLocation, 1, GL_FALSE, &ProjectionMatrix[0][0]);

}

void reshape(int width, int height)		// Resize the OpenGL window
{
	screenWidth=width; screenHeight = height;           // to ensure the mouse coordinates match 
														// we will use these values to set the coordinate system

	glViewport(0,0,width,height);						// Reset The Current Viewport

	//Set the projection matrix
	ProjectionMatrix = glm::perspective(60.0f, (GLfloat)screenWidth/(GLfloat)screenHeight, 1.0f, 10000.0f);
}

void init()
{

	rects.push_back(r1);
	rects.push_back(r2);
	rects.push_back(r3);
	rects.push_back(r4);
	rects.push_back(r5);
	rects.push_back(r6); //rock

	spheres.push_back(s1);
	spheres.push_back(s2);
	spheres.push_back(s3);
	spheres.push_back(s4);
	spheres.push_back(s5);
	spheres.push_back(s6);
	spheres.push_back(s7);
	spheres.push_back(s8);
	spheres.push_back(s9);
	spheres.push_back(s10);
	spheres.push_back(s11);
	spheres.push_back(s12);



	seafloor.useFog = 1.0;	//0 DISABLE FOG, 1 ENABLE, Remove ! from underWater->Render->Seafloor

	/***********INIT POSITIONS****************/
	skyboxCube.setPos(glm::vec3(0.0f, 0.0f, 0.0f));//2000.0
	wave.setWavePos(0.0, 240, 0.0);
	seafloor.setTopPos(glm::vec3(-20, 980, 145));
	

	submarine.setPosition(glm::vec3(0.0f, 235.0, 0.0f));

	/******************************************/
	//menu.texture = loadPNG("Models/Menu/test.png");
	/******************************************/

	glClearColor(0.0, 0.0, 0.0, 0.0);						//sets the clear colour to yellow
														//glClear(GL_COLOR_BUFFER_BIT) in the display function
														//will clear the buffer to this colour
	glEnable(GL_DEPTH_TEST);

	waveShader = new Shader;
	wave.loadWave(waveShader);

	submarineShader = new Shader;
	submarine.load(submarineShader);
	count_loaded++;
	std::cout << "						SUBMARINE LOADED		" <<count_loaded <<endl;
	seaFloorTopShader = new Shader;
	seaFloorBotShader = new Shader;
	seafloor.loadBottom(seaFloorBotShader);
	seafloor.loadTop(seaFloorTopShader);
	count_loaded++;
	std::cout << "						SEAFLOOR LOADED		    " << count_loaded << endl;


	//seafloor.load(seaFloorBotShader);

	skyboxShader = new Shader;
	skyboxCube.loadCube(skyboxShader);
	count_loaded++;
	std::cout << "						SKYBOX LOADED		     " << count_loaded << endl;

	/*pointShader = new Shader;
	p1.load(pointShader);
	p2.load(pointShader);
	p3.load(pointShader);
	p4.load(pointShader);
	*/
	rectShader = new Shader();
	rects[0].constructGeometry(rectShader);
	rects[1].constructGeometry(rectShader);
	rects[2].constructGeometry(rectShader);
	rects[3].constructGeometry(rectShader);
	rects[4].constructGeometry(rectShader);
	rects[5].constructGeometry(rectShader);
	count_loaded++;
	std::cout << "						RECTANGELS LOADED		     " << count_loaded << endl;

	/*rects[6].constructGeometry(rectShader);
	rects[7].constructGeometry(rectShader);
	*/

	sphereShader = new Shader();
	spheres[0].createSphere(sphereShader, 16);
	spheres[1].createSphere(sphereShader, 16);
	spheres[2].createSphere(sphereShader, 16);
	spheres[3].createSphere(sphereShader, 16);
	spheres[4].createSphere(sphereShader, 16);
	spheres[5].createSphere(sphereShader, 16);
	spheres[6].createSphere(sphereShader, 40);
	spheres[7].createSphere(sphereShader, 16);
	spheres[8].createSphere(sphereShader, 16);
	spheres[9].createSphere(sphereShader, 16);
	spheres[9].createSphere(sphereShader, 16);
	spheres[10].createSphere(sphereShader, 16);
	spheres[11].createSphere(sphereShader, 16);


	count_loaded++;
	std::cout << "						SPHERES LOADED		     " << count_loaded << endl;


	objectShader = new Shader();

		shell.load(objectShader, "Models/shell/1/shell9.obj");
		shell2.load(objectShader, "Models/shell/2/2.1/shell.obj"); shell2.setMaterialShiness(200);
		count_loaded++;
		std::cout << "						SEA SHELLS LOADED		 " << count_loaded << endl;
	
		coral.load(objectShader, "Models/coral/1/coral.obj"); coral.setMaterialShiness(200); coral.angleZ = 10.0; coral.angleX = 30.0;	
		coral2.load(objectShader, "Models/coral/2/coral.obj"); //coral.setMaterialShiness(200); coral2.angleZ = 10.0; coral2.angleX = 30.0;
		count_loaded++;
		std::cout << "						CORALS LOADED		     " << count_loaded << endl;
	
		rock.load(objectShader, "Models/rock/1/1.2/1.2.1/model9.obj");
		rock2.load(objectShader, "Models/rock/2/2.1/model9.obj"); rock2.setMaterialShiness(200); rock2.angleZ = 20.0;
		count_loaded++;
		std::cout << "						SEA ROCKS LOADED		     " << count_loaded << endl;
	
		coralrock.load(objectShader, "Models/coralrock/1/1.3/largemodel.obj"); coralrock.angleY = 180.0; coralrock.angleX = 4;
	
		coralrock2.load(objectShader, "Models/coralrock/3/3.obj");
		count_loaded++;
		std::cout << "						CORAL ROCKS LOADED		     " << count_loaded << endl;
		
		ship.load(objectShader, "Models/ship/1/ship.obj"); ship.angleZ = 150;	ship.angleY = 90;
		count_loaded++;
		std::cout << "						SHIP LOADED		     " << count_loaded << endl;
		
		
		mixSeaObj1.load(objectShader, "Models/mixObj/1/1.obj");
		mixSeaObj2.load(objectShader, "Models/mixObj/1/1.obj");
		mixSeaObj3.load(objectShader, "Models/mixObj/2/2.obj");
		count_loaded++;
		std::cout << "						MIXSEA OBJs LOADED		     " << count_loaded << endl;

}

void processKeys() {
	float x_incr = 1.0f;
	float y_incr = 1.0f;
	float actor_increment = 0.3f;
	
	if (keys['1']) {
		Camera::setCamera(1);
	}
	if (keys['2']) {
		Camera::setCamera(2);
	}
	if (keys['3']) {
		Camera::setCamera(3);
	}
	if (keys['4']) {
		Camera::setCamera(4);
	}
	if (keys[VK_LEFT]) {
		dcamX -= x_incr;
	}

	if (keys[VK_RIGHT]) {
		dcamX += x_incr;
	}

	if (keys[VK_UP]) {
		dcamY -= y_incr;
	}

	if (keys[VK_DOWN]) {
		dcamY += y_incr;
	}

	//reset position of the object
	//determines whether in needs to center the camera position on x and y axis
	if (keys['R']) {
		resetCamera();
	} 
	if (keys['T']) {
		submarine.resetPos();
	}
	
	if (keys['P'] && countMode > 100) {
		if (polygonMode) {
			polygonMode = false;
		}
		else polygonMode = true;
		countMode = 0;

	}
	countMode++;
	
	if (keys['A']) {
		submarine.turnLeft();
	}
	else submarine.setMovingLeft(false);


	if (keys['D']) {
		submarine.turnRight();
	}
	else { submarine.setMovingRight(false); }

	if (keys['W']) {
		submarine.moveForward();
	}
	else { submarine.setMovingForward(false); }

	if (keys['S']) {
		submarine.moveBackward();
	}
	else { submarine.setMovingBackward(false); }

	if (keys[' ']) {
		submarine.turnUp();
	}
	else { submarine.setMovingUp(false); }

	if (keys[VK_CONTROL]) {
		submarine.turnDown();
	}
	else { submarine.setMovingDown(false);	}

	//center the camera position when no rotation arrows are pressed
	if (needToResetCam && !keys[VK_DOWN] && !keys[VK_UP] && !keys[VK_LEFT] && !keys[VK_RIGHT]) {
		centerCamera();
	}
	//do not center camera position when any arrow button pressed
	else {
		needToResetCam = false;
	}

	/*
	   used as a cooldown value for the camera
	    is being used to get the camera's coords 5 frames before.

		used in the resetCamera and centerCamera functions
	*/
	if (camCounter % 5 == 0) {
		camXCD = dcamX;
		camYCD = dcamY;
	}
	camCounter++;
	//Camera::updateTransform(dcamX, dcamY, 0.0f);
//	submarine.updateTransform(xtemp,ytemp,ztemp);
}

//resets the camera's position
//it uses the centerCamera() to change the values of pich and yaw
void resetCamera() {
	/*****FOR CAMX***

	 1)  if less than -180 -> decrease until -360 -> set it to 0   -

	 2)  if 0> x > -180 -> increase until 0 -> set it to 0         +

	 3)  if greater than 180 -> increase until 360 -> set it to 0  +

	 4)  if 0< x < 180 -> decrease until 0 -> set it to 0          -

	*/

	//1
	if (dcamX < -180.0) {
		camXDecrease = true;
		needToResetCam = true;
	}
	
	//2
	else if (dcamX < 0.0 && dcamX >= -180.0) {
		camXIncrease = true;
		needToResetCam = true;
	}

	//3
	else if (dcamX > 180.0) {
		//increase
		camXIncrease = true;
		needToResetCam = true;
	}

	//4
	else if (dcamX > 0.0 && dcamX < 180.0) {
		//decrease
		camXDecrease = true;
		needToResetCam = true;
	}

	/*
	 5) if y less than 0     +

	 6) if y greater than 0  -

	*/

	//5
	if (dcamY <= 0.0) {
		camYIncrease = true;
		needToResetCam = true;
	}

	//6
	else if (dcamY > 0.0) {
		camYDecrease = true;
		needToResetCam = true;
	}
}

//center the camera's position to (0,0,0)
void centerCamera() {
	float x_incr = 1;
	float y_incr = 1;

	if (camXIncrease) {
		dcamX += x_incr;

		if (dcamX >= 0.0 && camXCD < 0.0) {
			dcamX = 0.0;
			//camIncrease = false;
		}

		if (dcamX >= 360.0) {
			dcamX = 0.0;
			//camIncrease = false;
		}

		if (dcamX == 0.0){// && dcamY == 0.0) {
			camXIncrease = false;
			//needToResetCam = false;

		}
	}

	if (camXDecrease) {
		dcamX -= x_incr;

		if (dcamX <= -360.0) {
			dcamX = 0.0;
		}

		if (dcamX <= 0.0 && camXCD > 0.0) {
			dcamX = 0.0;
		}

		if (dcamX == 0.0 ){
			camXDecrease = false;
		}
	}

	if (camYIncrease) {
		dcamY += y_incr;


		if (dcamY >= 0.0) {
			dcamY = 0.0;
			camYIncrease = false;
		}
	}

	if (camYDecrease) {
		dcamY -= y_incr;

		if (dcamY <= 0.0) {
			dcamY = 0.0;
			camYIncrease = false;
		}
	}

	if (dcamX == 0.0 && dcamY == 0.0) {
		needToResetCam = false;
	}
}

/**************** END OPENGL FUNCTIONS *************************/

//WIN32 functions
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc
void KillGLWindow();									// releases and destroys the window
bool CreateGLWindow(char* title, int width, int height); //creates the window
int WINAPI WinMain(	HINSTANCE, HINSTANCE, LPSTR, int);  // Win32 main function

//win32 global variabless
HDC			hDC=NULL;		// Private GDI Device Context
HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application


/******************* WIN32 FUNCTIONS ***************************/
int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
					HINSTANCE	hPrevInstance,		// Previous Instance
					LPSTR		lpCmdLine,			// Command Line Parameters
					int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	bool	done=false;								// Bool Variable To Exit Loop

	AllocConsole();
	FILE* stream;
	freopen_s(&stream, "CONOUT$", "w", stdout);

	// Create Our OpenGL Window
	if (!CreateGLWindow("OpenGL Win32 Example",screenWidth,screenHeight))
	{
		return 0;									// Quit If Window Was Not Created
	}

	while(!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
			{
				done=true;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			if(keys[VK_ESCAPE])
				done = true;

			processKeys();			//process keyboard
			
			display();					// Draw The Scene
			//update();					// update variables
			SwapBuffers(hDC);				// Swap Buffers (Double Buffering)
		}
	}

	
	// Shutdown
	KillGLWindow();									// Kill The Window
	return (int)(msg.wParam);						// Exit The Program
}

//WIN32 Processes function - useful for responding to user inputs or other events.
LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}
		break;

		case WM_SIZE:								// Resize The OpenGL Window
		{
			reshape(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}
		break;

		case WM_LBUTTONDOWN:
			{
	            mouse_x = LOWORD(lParam);          
				mouse_y = screenHeight - HIWORD(lParam);
				LeftPressed = true;
			}
		break;

		case WM_LBUTTONUP:
			{
	            LeftPressed = false;
			}
		break;

		case WM_MOUSEMOVE:
			{
	            mouse_x = LOWORD(lParam);          
				mouse_y = screenHeight  - HIWORD(lParam);
			}
		break;
		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			keys[wParam] = true;					// If So, Mark It As TRUE
			return 0;								// Jump Back
		}
		break;
		case WM_KEYUP:								// Has A Key Been Released?
		{
			keys[wParam] = false;					// If So, Mark It As FALSE
			return 0;								// Jump Back
		}
		break;

		case WM_MOUSEWHEEL:								
		{
			if ((short)HIWORD(wParam) < 0) {
				mousewheel += 10;
			}else 
				mousewheel -= 10;

			if (mousewheel <= 10) {
				mousewheel = 10;
			}
			if (mousewheel >= 120) {
				mousewheel = 120;
			}

			std::cout << "mousewheel:  "<<mousewheel <<"  wParam:"<<wParam<< "  LOWORD"<< LOWORD(lParam)<<"  HIWORD:" << HIWORD(lParam) <<endl;
			return 0;
		}
		break;
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

void KillGLWindow()								// Properly Kill The Window
{
	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*/
 
bool CreateGLWindow(char* title, int width, int height)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;											// Return FALSE
	}
	
	dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
	dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	
	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
								"OpenGL",							// Class Name
								title,								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								0, 0,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,								// No Parent Window
								NULL,								// No Menu
								hInstance,							// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		24,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		24,											// 24Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	HGLRC tempContext = wglCreateContext(hDC);
	wglMakeCurrent(hDC, tempContext);

	glewInit();

	int attribs[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 1,
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		0
	};
	
    if(wglewIsSupported("WGL_ARB_create_context") == 1)
    {
		hRC = wglCreateContextAttribsARB(hDC,0, attribs);
		wglMakeCurrent(NULL,NULL);
		wglDeleteContext(tempContext);
		wglMakeCurrent(hDC, hRC);
	}
	else
	{	//It's not possible to make a GL 3.x context. Use the old style context (GL 2.1 and before)
		hRC = tempContext;
		std::cout << " not possible to make context "<< endl;
	}

	//Checking GL version
	const GLubyte *GLVersionString = glGetString(GL_VERSION);

	std::cout << GLVersionString << endl;

	//OpenGL 3.2 way of checking the version
	int OpenGLVersion[2];
	glGetIntegerv(GL_MAJOR_VERSION, &OpenGLVersion[0]);
	glGetIntegerv(GL_MINOR_VERSION, &OpenGLVersion[1]);

	std::cout << OpenGLVersion[0] << " " << OpenGLVersion[1] << endl;

	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	reshape(width, height);					// Set Up Our Perspective GL Screen

	init();
	
	return true;									// Success
}


GLuint loadPNG(char* name)
{
	// Texture loading object
	nv::Image img;

	GLuint myTextureID;

	// Return true on success
	if (img.loadImageFromFile(name))	//open the tecture file
	{
		glGenTextures(1, &myTextureID);
		glBindTexture(GL_TEXTURE_2D, myTextureID);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexImage2D(GL_TEXTURE_2D, 0, img.getInternalFormat(), img.getWidth(), img.getHeight(), 0, img.getFormat(), img.getType(), img.getLevel(0));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	}
	else
		MessageBox(NULL, "Failed to load texture", "End of the world", MB_OK | MB_ICONINFORMATION);

	return myTextureID;
}