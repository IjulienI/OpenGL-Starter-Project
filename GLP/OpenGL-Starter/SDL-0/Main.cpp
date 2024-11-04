﻿#include <iostream>
#include <fstream>
#include <string>
#include <SDL.h>
#include <glew.h>
using namespace std;
//#define GLEW_STATIC

string LoadShader(string fileName);

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
	unsigned int center = SDL_WINDOWPOS_CENTERED;
	SDL_Window* Window = SDL_CreateWindow("OpenGL?", center, center, width, height, SDL_WINDOW_OPENGL);
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
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f);

	string vertexFile = LoadShader("simpleVertex.shader");
	const char *vertexShaderSource = vertexFile.c_str();

	string fragmentFile = LoadShader("simpleFragment.shader");
	const char *fragmentShaderSource = fragmentFile.c_str();

	//Describe the shape by its vertices
	float vertices[]={
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   
	   -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
	};
	
	//Create an ID to be given at object generation
	unsigned int vbo;
	//Pass how many buffers should be created and the reference of the ID to get the value set
	glGenBuffers(1, &vbo);

	unsigned int vertexShaderID;
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

	//now that we have vertex shader, let's put the code text inside
	glShaderSource(vertexShaderID, 1, &vertexShaderSource, nullptr);

	//compile shaders
	glCompileShader(vertexShaderID);

	//Do the same with the fragment shader !
	unsigned int fragmentShaderID;
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShaderID);

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	//attach shaders to use into the program
	glAttachShader(shaderProgram, vertexShaderID);
	glAttachShader(shaderProgram, fragmentShaderID);

	//link the program shader
	glLinkProgram(shaderProgram);

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
			default:
				break;
			}
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen

		float speed = 2.0f;
		float timeValue = ((float)SDL_GetTicks()/1000) * speed;
		float trianglePosX = (sin(timeValue * speed) / 2.0f );
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "move");
		glUseProgram(shaderProgram);
		glUniform1f(vertexColorLocation, trianglePosX);

		//OMG WE FINALLY DRAW ! We use the GL_TRIANGLES primitive type
		//We draw from vertex 0 and we will be drawing 3 vertices
		glDrawArrays(GL_TRIANGLES, 0, 3);		
		
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
