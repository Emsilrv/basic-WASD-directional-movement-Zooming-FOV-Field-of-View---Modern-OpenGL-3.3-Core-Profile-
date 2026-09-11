#include "glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>
#include "packages/stb_img/stb_img.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Shader.h"
#include <glm/glm.hpp>                  
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>   
#include "stbi.h"
#include "camera.h"


camera::camera() {
    CameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
}


void camera::processinput(GLFWwindow* window , float deltatime) {
    float velocity = 2.5f * deltatime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        CameraPos += velocity * CameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        CameraPos -= velocity * CameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        CameraPos -= glm::normalize(glm::cross(CameraFront, CameraUp)) * velocity;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        CameraPos += glm::normalize(glm::cross(CameraFront, CameraUp)) * velocity;
}

void camera::mousemovments(GLFWwindow* window, double xpos, double ypos) {

    if (FirstMouse) {
        xlast = static_cast<float>(xpos);
        ylast = static_cast<float>(ypos);
        FirstMouse = false;
    }


   xoffset = static_cast<float>(xpos) - xlast;
   yoffset = ylast - static_cast<float>(ypos);
    
   xlast = static_cast<float>(xpos);
   ylast = static_cast<float>(ypos);


    xoffset *= sensitivity;
    yoffset *= sensitivity;


    yaw += xoffset;
    pitch+= yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
       pitch = -89.0f;

    updateCameraVectors();
}

void camera::updateCameraVectors() {
    
    glm::vec3 dircetion(0.0f);

    dircetion.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    dircetion.y = sin(glm::radians(pitch));
    dircetion.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));


      CameraFront = glm::normalize(dircetion);
}

void camera::ProcessMouseScroll(float yoffset) {
    Fov -= yoffset;
    if (Fov < 1.0f)   Fov = 1.0f;   
    if (Fov > 45.0f)  Fov = 45.0f;  
}



glm::mat4 camera::GetViewMatrix() {
    return glm::lookAt(CameraPos, CameraPos + CameraFront, CameraUp);
};