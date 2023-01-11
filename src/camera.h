#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

using namespace std;
using namespace glm;


class Camera
{
public:
	float fov;
	float speed;
	float sensitivity;
	vec3 cameraPos;
	// Camera(FOV, moving speed, sensitivity, cemera position);
	Camera(float fov = 60.0f, float speed=2.5f, float sensitivity=0.05f, vec3 cameraPos = vec3(0.0f, 0.0f, 3.0f)) {
		this->fov = fov;
		this->speed = speed;
		this->sensitivity = sensitivity;
		this->cameraPos = cameraPos;
	}

	// keyboard
	void processInput(GLFWwindow* window)
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		float cameraSpeed = speed * deltaTime; // moving speed

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cameraPos += cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cameraPos -= cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cameraPos -= normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cameraPos += normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			cameraPos.y += cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			cameraPos.y -= cameraSpeed;
	}


	// mousePos
	void mousePos(double xpos, double ypos)
	{
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos;
		lastX = xpos;
		lastY = ypos;

		
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		Yaw += xoffset;
		Pitch += yoffset;

		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		cameraFront = glm::normalize(front);
	}
	// scroll
	void mouseScroll(double yoffset)
	{

		if (fov >= 1.0f && fov <= 85.0f)
			fov = fov - yoffset * 5;
		if (fov <= 15.0f)
			fov = 15.0f;
		if (fov >= 85.0f)
			fov = 85.0f;

	}

	mat4 getV() {
		return lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	}




private:
	
	vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
	vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);
	float deltaTime = 0.0f; // delta time = frame of moment - last frame
	float lastFrame = 0.0f; // last frame

	float Pitch = 0;
	float Yaw = -90;
	float lastX = 400, lastY = 300;
	bool firstMouse = true;
};

