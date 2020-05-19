#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif
#define STB_IMAGE_IMPLEMENTATION


#include "../lib/stb_image.h"
#include "GL/glew.h"
#include "../lib/glfw/glfw3.h"
#include <iostream>
#include "../project/Shader.h"
#include "../project/Buffer.h"
#include <../glm/ext.hpp>
#include "Mesh.h"
#include "Primitives.h"
#include "Texture.h"
#include "Material.h"

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

		std::shared_ptr<Shader> myShader = std::make_shared<Shader>("data/vertex.glsl", "data/fragment.glsl");

		std::shared_ptr<Texture> mytexture = Texture::load("data/front.png");
		std::shared_ptr<Texture> topTexture = Texture::load("data/top.png");

		Material* myMaterial = new Material(mytexture, myShader);
		Material* pTopMaterial = new Material(topTexture, myShader);

        Primitive t = Cube();
		Transform myTransform = Transform();
		Mesh* myMesh = new Mesh(t, myTransform, myMaterial);

		Primitive top = Quad();
		Transform myTopTransform = Transform();
		Mesh* pTopMesh = new Mesh(top, myTopTransform, pTopMaterial);

	    const glm::mat4 proj = glm::perspective<float>(glm::radians(45.0f), 
		    static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT),
		    1, 1000);
		const glm::mat4 view = glm::lookAt(glm::vec3(0, 5, 6), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

		//pTopMesh->setRotation(glm::vec3(90, 0, 0));

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

			myMesh->translate(glm::vec3(0, 0, 0));
			//myMesh->rotate(32.f, glm::vec3(0, 1, 0));
			myMesh->setRotation(glm::vec3(0, 32 * accumulated,0));
			myMesh->updateUniforms(*myShader, proj, view);
			myMesh->draw(myShader);

			pTopMesh->translate(glm::vec3(0, 0.5001, 0));
			pTopMesh->setRotation(glm::vec3(90, 0, 32 * -accumulated));
			//pTopMesh->rotate(90, glm::vec3(1, 0, 0));
			//pTopMesh->rotate(32.f, glm::vec3(0, 1, 0));

			pTopMesh->updateUniforms(*myShader, proj, view);
			pTopMesh->draw(myShader);

	        // refresh screen
		    glfwSwapBuffers(win);
		    glfwPollEvents();
	    }

		delete myMesh;
	    // shutdown
	    glfwTerminate();
	}
}