#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "GL/glew.h"
#include "../lib/glfw/glfw3.h"
#include <iostream>
#include "../project/Shader.h"
#include "../project/Buffer.h"
#include <../glm/glm.hpp> 
#include <../glm/ext.hpp>
#include "Mesh.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

GLFWwindow* win;

bool Init()
{
	// init glfw
	if (!glfwInit())
	{
		std::cout << "could not initialize glfw" << std::endl;
		return false;
	}
	// create window
	//glfwWindowHint(GLFW_RESIZABLE, false);
	glfwWindowHint(GLFW_SAMPLES, 8);
	win = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Practica 1", nullptr, nullptr);
	if (!win)
	{
		std::cout << "could not create opengl window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(win);

	//glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "could not initialize glew" << std::endl;
		return false;
	}


	return true;
}

int main()
{


    if(Init())
	{
	        
	    glEnable(GL_DEPTH_TEST);
	    glEnable(GL_SCISSOR_TEST);

	    
	    //load Shaders
	    Shader* myShader = new Shader("data/vertex.glsl", "data/fragment.glsl");
	    myShader->use();

	    std::vector<Vertex> vertices;
	    vertices.emplace_back(Vertex(glm::vec3(0, 0.5f, 0), glm::vec3(1, 0, 0)));
	    vertices.emplace_back(Vertex(glm::vec3(-0.5f, -0.5f, 0), glm::vec3(0, 1, 0)));
	    vertices.emplace_back(Vertex(glm::vec3(0.5f, -0.5f, 0), glm::vec3(0, 0, 1)));

	    std::vector<uint16_t> indices {0,1,2};

		Mesh* myMesh = new Mesh(vertices, indices);
	    //Buffer* myBuffer = new Buffer(vertices, indices);

	    const glm::mat4 proj = glm::perspective<float>(glm::radians(45.0f), 
		    static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT),
		    1, 1000);
		const glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 6), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

		glm::vec3 position(0.f);
		glm::vec3 rotation(0.f);
		glm::vec3 scale(1.f);
        glm::mat4 modelMatrix(1.f);
		modelMatrix = glm::translate(modelMatrix, position);
		modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1,0,0));
		modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0,1,0));
		modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0,0,1));
		modelMatrix = glm::scale(modelMatrix, scale);




	    // main loop
	    while ( !glfwWindowShouldClose(win) && !glfwGetKey(win, GLFW_KEY_ESCAPE) )
	    {
		    // get delta time
			static double lastTime = glfwGetTime();
		    float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
		    lastTime = glfwGetTime();
		    int screenWidth, screenHeight;

		    static float accumulated = 0;
		    accumulated += deltaTime;
		    // get window size
		    glfwGetWindowSize(win, &screenWidth, &screenHeight);

		    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			for (int z = 0; z >= -6; z -= 3)
			{
		        for (int x = -3; x <= 3; x += 3) 
		        {
					modelMatrix = glm::translate(glm::mat4(), glm::vec3(x, 0, z));
					modelMatrix = glm::rotate(modelMatrix, glm::radians(32.f * accumulated), glm::vec3(0, 1, 0));
					myShader->setMatrix(myShader->getLocation("mvp"), proj * view * modelMatrix);
					myMesh->draw(*myShader);
				}
		    }
		    // refresh screen
		    glfwSwapBuffers(win);
		    glfwPollEvents();
	    }

	    // shutdown
	    glfwTerminate();
	}
}