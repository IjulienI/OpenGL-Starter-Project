#include <iostream>
#include <fstream>
#include <string>
#include <SDL.h>
#include <glew.h>
using namespace std;
//#define GLEW_STATIC

string LoadShader(string fileName);

void randomColor(unsigned int shaderProgram);

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
	}
	else
	{
		cout << "SDL initialization succeeded!\n";
	}
	///////////SETTING UP SDL/////////////
	//Create a simple window
	int width = 1000;
	int height = 1000;
	float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	unsigned int center = SDL_WINDOWPOS_CENTERED;
	SDL_Window* Window = SDL_CreateWindow("CrazyTrianle!!", center, center, width, height, SDL_WINDOW_OPENGL);
	//SDL_WINDOW_OPENGL is a u32 flag !


	//Create an OpenGL compatible context to let glew draw on it
	SDL_GLContext Context = SDL_GL_CreateContext(Window);

	/////////SETTING UP OPENGL WITH GLEW///
	//Initialize glew
	glewExperimental = GL_TRUE;
	if (glewInit() == GLEW_OK) {
		cout << "Glew initialized successfully\n";
	}

	//Set the viewing frame through which we will see the objects
	glViewport(0,0, width, height);
	
	//Put the color you want here for the background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	string vertexAppleFile = LoadShader("simpleVertex.glsl");
	const char *vertexAppleShaderSource = vertexAppleFile.c_str();

	string fragmentAppleFile = LoadShader("simpleFragment.glsl");
	const char *fragmentAppleShaderSource = fragmentAppleFile.c_str();

	//Describe the shape by its vertices
	float vertices[]={
		//Apple
		//FAN
		0.0f, 0.0f, 0.0f,	0.0f,0.0f,0.0f,
		-0.1f, 0.2f, 0.0f,	0.0f,0.0f,0.0f,
		-0.2f, 0.0f, 0.0f,	0.0f,0.0f,0.0f,
		-0.1f, -0.2f, 0.0f,	0.0f,0.0f,0.0f,
		0.1f, -0.2f, 0.0f,	0.0f,0.0f,0.0f,
		0.1f, -0.2f, 0.0f,	0.0f,0.0f,0.0f,
		0.2f, -0.1f, 0.0f,	0.0f,0.0f,0.0f,
		0.1f, -0.05f, 0.0f,	0.0f,0.0f,0.0f,
		0.1f, 0.05f, 0.0f,	0.0f,0.0f,0.0f,
		0.2f, 0.1f, 0.0f,	0.0f,0.0f,0.0f,
		0.1f, 0.2f, 0.0f,	0.0f,0.0f,0.0f,
		-0.1f, 0.2f, 0.0f,	0.0f,0.0f,0.0f,
		//STRIP
		0.0f, 0.2f, 0.0f,	0.0f,0.0f,0.0f,
		0.0f, 0.3f, 0.0f,	0.0f,0.0f,0.0f,
		0.1f, 0.25f, 0.0f,	0.0f,0.0f,0.0f,
		0.1f, 0.35f, 0.0f,	0.0f,0.0f,0.0f,
		//Snake
		//HEAD FAN
		0.0f, 0.0f, 0.0f,	0.0f,0.0f,0.0f,
		-0.05f, 0.04f, 0.0f,	0.0f,0.0f,0.0f,
		-0.01f, 0.05f, 0.0f,	0.0f,0.0f,0.0f,
		0.02f, 0.04f, 0.0f,	0.0f,0.0f,0.0f,
		0.05f, 0.02f, 0.0f,	0.0f,0.0f,0.0f,
		0.06f, 0.0f, 0.0f,	0.0f,0.0f,0.0f,
		0.05f, -0.02f, 0.0f,	0.0f,0.0f,0.0f,
		0.02f, -0.04f, 0.0f,	0.0f,0.0f,0.0f,
		-0.01f, -0.05f, 0.0f,	0.0f,0.0f,0.0f,
		-0.05f, -0.04f, 0.0f,	0.0f,0.0f,0.0f,
		-0.05f, 0.0f, 0.0f,	0.0f,0.0f,0.0f,
		-0.05f, 0.04f, 0.0f,	0.0f,0.0f,0.0f,
	};
	
	//Create an ID to be given at object generation
	unsigned int vbo;
	//Pass how many buffers should be created and the reference of the ID to get the value set
	glGenBuffers(1, &vbo);

	unsigned int vertexShaderID;
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

	//now that we have vertex shader, let's put the code text inside
	glShaderSource(vertexShaderID, 1, &vertexAppleShaderSource, nullptr);

	//compile shaders
	glCompileShader(vertexShaderID);

	//Do the same with the fragment shader !
	unsigned int fragmentShaderID;
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID, 1, &fragmentAppleShaderSource, nullptr);
	glCompileShader(fragmentShaderID);

	// unsigned int fixVertexShaderID;
	// fixVertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	// glShaderSource(fixVertexShaderID, 1, &fixVertexShaderSource, nullptr);
	// glCompileShader(fixVertexShaderID);
	//
	// unsigned int fixFragmentShaderID;
	// fixFragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	// glShaderSource(fixFragmentShaderID, 1, &fixFragmentShaderSource, nullptr);
	// glCompileShader(fixFragmentShaderID);

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	unsigned int fixShaderProgram;
	fixShaderProgram = glCreateProgram();

	// glAttachShader(fixShaderProgram, fixVertexShaderID);
	// glAttachShader(fixShaderProgram, fixFragmentShaderID);

	//attach shaders to use into the program
	glAttachShader(shaderProgram, vertexShaderID);
	glAttachShader(shaderProgram, fragmentShaderID);

	//link the program shader
	glLinkProgram(shaderProgram);
	glLinkProgram(fixShaderProgram);

	//use the program
	glUseProgram(shaderProgram);

	//create one ID to be given at object generation
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//bind the buffer linked th this ID to the vertex array buffer to be
	//rendered. Put 0 instead of the vbo to reset the value
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//send the vertices array in the array buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
	//enabled my vertex attribute array number 0 ( we only have one attribute of position )
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Use depth management
	glEnable(GL_DEPTH_TEST);

	//0 is our origin, the higher the z, the farther the object
	glDepthFunc(GL_LESS);
	
	float posX = 0.0f;
	float posY = 0.0f;
	bool left = false;
	bool up = true;
	int SnakeRotation = 1;

	float lastDeltaTime = 0.0f;
	float deltaTime = 0.0f;

	bool isRunning = true;
	while(isRunning)
	{
		//Inputs
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_UP) SnakeRotation = 2;			
				if(event.key.keysym.sym == SDLK_DOWN) SnakeRotation = 3;
				if(event.key.keysym.sym == SDLK_LEFT) SnakeRotation = 0;
				if(event.key.keysym.sym == SDLK_RIGHT) SnakeRotation = 1;
				break;
			default:
				break;
			}
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen

		// float speed = 2.0f;
		// float timeValue = ((float)SDL_GetTicks()/1000) * speed;
		// float trianglePosX = (sin(timeValue * speed) / 2.0f );
		// float triangleSizeX = (cos(timeValue * speed) / 2.0f );
		// float triangleSizeY = (cos(timeValue * speed) + 2 / 2.0f );
		// float triangleSizeZ = (sin(timeValue * speed) + 4 / 2.0f );
		// int vertexLocation = glGetUniformLocation(shaderProgram, "xOffset");
		// int vertexSize = glGetUniformLocation(shaderProgram, "size");
		// glUseProgram(shaderProgram);		
		// glUniform3f(vertexSize,triangleSizeX,triangleSizeY,triangleSizeZ );
		// glUniform1f(vertexLocation, trianglePosX);

		
		//OMG WE FINALLY DRAW ! We use the GL_TRIANGLES primitive type
		//We draw from vertex 0 and we will be drawing 3 vertices
		int vertexAspectRatio = glGetUniformLocation(shaderProgram, "aspectRatio");
		int vertexSize = glGetUniformLocation(shaderProgram, "size");		
		int vertexColor = glGetUniformLocation(shaderProgram, "color");
		int vertexLocation = glGetUniformLocation(shaderProgram, "offsets");
		int vertexRotation = glGetUniformLocation(shaderProgram, "rotation");

		float timeValue = (float)SDL_GetTicks()/1000;
		float redColor = (sin(timeValue) / 2.0f) + 0.5f;
		float greenColor = (sin(timeValue + 2) / 2.0f) + 0.5f;
		float blueColor = (sin(timeValue + 4) / 2.0f) + 0.5f;
		glUseProgram(shaderProgram);
		glUniform1f(vertexAspectRatio, aspectRatio);
		glUniform3f(vertexSize, 0.75f, 0.75f,0.75f);
		glUniform3f(vertexColor, redColor, greenColor, blueColor);
		glUniform2f(vertexLocation, 0.0f, 0.0f);
		glUniform1i(vertexRotation, SnakeRotation);
		glDrawArrays(GL_TRIANGLE_FAN, 16,12);

		//Apple
		glUniform3f(vertexColor, 1.0f, 0.341f, 0.29f);
		glUniform3f(vertexSize, 0.2f, 0.2f, 0.2f);
		glUniform2f(vertexLocation, 0.5f, 0.5f);
		glUniform1i(vertexRotation, 1);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 12);
		glDrawArrays(GL_TRIANGLE_STRIP, 12,4);
		//glUseProgram(fixShaderProgram);
		//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		
		SDL_GL_SwapWindow(Window); // Swapbuffer
	}
	// Quit
	SDL_DestroyWindow(Window);
	SDL_GL_DeleteContext(Context);

	cin.get();
	return 0;
}

string LoadShader(string fileName) {
	ifstream myFile;
	myFile.open(fileName);
	if (myFile.fail()) {
		cerr << "Error - failed to open " << fileName << endl;
	}
	string fileText = "";
	string line = "";
	while (getline(myFile, line)) {
		fileText += line + '\n';
	}
  
	myFile.close();
	return fileText;
}

void randomColor(unsigned int shaderProgram)
{
	int shaderColor = glGetUniformLocation(shaderProgram, "color");
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	glUniform3f(shaderColor,r ,g ,b);
}