#pragma once

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
#include "colorconverter.h"
#include "stbi.h"


class camera {
public:
    glm::vec3 CameraPos;
    glm::vec3 CameraFront;
    glm::vec3 CameraUp;

    float deltatime = 0.0f;
    float lastframe = 0.0f;
    float yaw = -90.0f;
    float pitch = 0.0f;
    float sensitivity = 0.1f;
    bool FirstMouse = true;
    float xlast = 500.0f;
    float ylast = 500.0f;
    float xoffset = 0.0f;
    float yoffset = 0.0f;
    float Fov = 45.0f;

    camera(); 
    void processinput(GLFWwindow* window , float deltatime); 
    void mousemovments(GLFWwindow* window, double xpos , double ypos);
    void ProcessMouseScroll(float yoffset);
    void updateCameraVectors();
    glm::mat4 GetViewMatrix();
};