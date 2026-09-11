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
#include "camera.h"



camera cam;

void mousecallback(GLFWwindow* window, double xpos, double ypos) {
    cam.mousemovments(window, xpos, ypos);
}
void scrollcallback(GLFWwindow* window, double xoffset, double yoffset) {
    cam.ProcessMouseScroll(static_cast<float>(yoffset));
}


// glGetShaderInfoLog OpenGL's newest versions 
int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Uploading window using GLFW , with , height and title name , if condaiton - if window didn't load . close immediately 

    GLFWwindow* window = glfwCreateWindow(1000 , 1000 , " OpenGL", nullptr, nullptr);
    if (!window) { 
        std::cout << "careful bro !\n " << std::endl;
    glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);


    gladLoadGL();
    glEnable(GL_DEPTH_TEST);


    //Main CPP code block for converting HEX to RGBA
    glm::vec3 bg = colorconverter::HEX("#000000"); //background 
    glm::vec3 top_right  = colorconverter::HEX("#FFFFFF");       
    glm::vec3 bottom_right = colorconverter::HEX("#FFFFFF"); 
    glm::vec3 bottom_left = colorconverter::HEX("#FFFFFF"); 
    glm::vec3 top_left = colorconverter::HEX("#FFFFFF");
    

    //GL float array for vertices , UV , colors 
    //x axis then y 
   // 24 vertices total (4 per face so UV mapping remains flat and clean on every side)
// Layout per vertex: PosX, PosY, PosZ, U, V, ColorR, ColorG, ColorB
    GLfloat vertices[] = {
        // Positions             // UVs       // Colors
        // Front Face
        -0.5f, -0.5f,  0.5f,     0.0f, 0.0f,  bottom_left.r,  bottom_left.g,  bottom_left.b,
         0.5f, -0.5f,  0.5f,     1.0f, 0.0f,  bottom_right.r, bottom_right.g, bottom_right.b,
         0.5f,  0.5f,  0.5f,     1.0f, 1.0f,  top_right.r,    top_right.g,    top_right.b,
        -0.5f,  0.5f,  0.5f,     0.0f, 1.0f,  top_left.r,     top_left.g,     top_left.b,

        // Back Face
        -0.5f, -0.5f, -0.5f,     1.0f, 0.0f,  bottom_left.r,  bottom_left.g,  bottom_left.b,
         0.5f, -0.5f, -0.5f,     0.0f, 0.0f,  bottom_right.r, bottom_right.g, bottom_right.b,
         0.5f,  0.5f, -0.5f,     0.0f, 1.0f,  top_right.r,    top_right.g,    top_right.b,
        -0.5f,  0.5f, -0.5f,     1.0f, 1.0f,  top_left.r,     top_left.g,     top_left.b,

        // Top Face
        -0.5f,  0.5f,  0.5f,     0.0f, 0.0f,  top_left.r,     top_left.g,     top_left.b,
         0.5f,  0.5f,  0.5f,     1.0f, 0.0f,  top_right.r,    top_right.g,    top_right.b,
         0.5f,  0.5f, -0.5f,     1.0f, 1.0f,  top_right.r,    top_right.g,    top_right.b,
        -0.5f,  0.5f, -0.5f,     0.0f, 1.0f,  top_left.r,     top_left.g,     top_left.b,

        // Bottom Face
        -0.5f, -0.5f,  0.5f,     0.0f, 1.0f,  bottom_left.r,  bottom_left.g,  bottom_left.b,
         0.5f, -0.5f,  0.5f,     1.0f, 1.0f,  bottom_right.r, bottom_right.g, bottom_right.b,
         0.5f, -0.5f, -0.5f,     1.0f, 0.0f,  bottom_right.r, bottom_right.g, bottom_right.b,
        -0.5f, -0.5f, -0.5f,     0.0f, 0.0f,  bottom_left.r,  bottom_left.g,  bottom_left.b,

        // Right Face
         0.5f, -0.5f,  0.5f,     0.0f, 0.0f,  bottom_right.r, bottom_right.g, bottom_right.b,
         0.5f, -0.5f, -0.5f,     1.0f, 0.0f,  bottom_right.r, bottom_right.g, bottom_right.b,
         0.5f,  0.5f, -0.5f,     1.0f, 1.0f,  top_right.r,    top_right.g,    top_right.b,
         0.5f,  0.5f,  0.5f,     0.0f, 1.0f,  top_right.r,    top_right.g,    top_right.b,

         // Left Face
         -0.5f, -0.5f,  0.5f,     1.0f, 0.0f,  bottom_left.r,  bottom_left.g,  bottom_left.b,
         -0.5f, -0.5f, -0.5f,     0.0f, 0.0f,  bottom_left.r,  bottom_left.g,  bottom_left.b,
         -0.5f,  0.5f, -0.5f,     0.0f, 1.0f,  top_left.r,     top_left.g,     top_left.b,
         -0.5f,  0.5f,  0.5f,     1.0f, 1.0f,  top_left.r,     top_left.g,     top_left.b
    };

    // 36 indices forming 12 triangles across 6 faces
    GLuint indices[] = {
        0,  1,  2,   2,  3,  0,   // Front
        4,  5,  6,   6,  7,  4,   // Back
        8,  9,  10,  10, 11, 8,   // Top
        12, 13, 14,  14, 15, 12,  // Bottom
        16, 17, 18,  18, 19, 16,  // Right
        20, 21, 22,  22, 23, 20   // Left
    };

    //textures 
    //for flipping the pic upside down vertically on right position 
    stbi_set_flip_vertically_on_load(true);

    //loading image using stbi - load image , wefith , height , color 
    int imagewedith ,imageheight, color;
    unsigned char* bytes = stbi_load("CD.jpeg", &imagewedith, &imageheight, &color, 0);
    if (!bytes) {
        std::cout << "Failed to load texture!" << std::endl;
    }

    //*

    GLuint texture;
    glGenTextures(1 , &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glTexImage2D(GL_TEXTURE_2D, 0 , GL_RGB , imagewedith , imageheight , 0  , GL_RGB , GL_UNSIGNED_BYTE , bytes );
    stbi_image_free(bytes);



    //shaders- but still explain them again pls lol
    const char* vertSrc = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec2 aTexCoord;
    layout (location = 2) in vec3 aColor;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 proj;


    out vec2 TexCoord;
    out vec3 ourColor;

    void main() {
        gl_Position = proj * view * model * vec4(aPos, 1.0);
        TexCoord = aTexCoord;
        ourColor = aColor;
    }
)";

    const char* fragSrc = R"(
    #version 330 core
    in vec2 TexCoord;
    in vec3 ourColor;

    out vec4 FragColor;

    uniform sampler2D ourTexture;

    void main() {
        // Multiply texture color with vertex color (or just output texture alone)
        FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
    }
)";

    //Activates shaders 
    Shader shaderProgram(vertSrc, fragSrc);


    //binding verix array object - bind all OpenGL's attributes once so we don't have to bind them everytime we draw 
    VAO vao1;
    vao1.Bind();
    //vertex buffer object - stores all OpenGL's attributes in the VRAM
    VBO vbo1(vertices, sizeof(vertices));
    //Eelemnt buffer object , ordinates indices to control and arrange vertex
    EBO ebo1(indices, sizeof(indices));
 
    //linking all 
    GLsizei stride = 8 * sizeof(float);
    vao1.LinkAttrib(vbo1, 0, 3, GL_FLOAT, stride, (void*)0);
    vao1.LinkAttrib(vbo1, 1, 2, GL_FLOAT, stride, (void*)(3 * sizeof(float)));
    vao1.LinkAttrib(vbo1, 2, 3, GL_FLOAT, stride, (void*)(5 * sizeof(float)));

    //unbinding all , for avoiding any crashes 
    vao1.Unbind();
    vbo1.Unbind();
    ebo1.Unbind();
    glBindTexture(GL_TEXTURE_2D, 0);
    

    int modelloc = glGetUniformLocation(shaderProgram.ID, "model");
    int viewloc = glGetUniformLocation(shaderProgram.ID, "view");
    int projloc = glGetUniformLocation(shaderProgram.ID, "proj");




    float lastframe = 0.0f;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mousecallback);
    glfwSetScrollCallback(window, scrollcallback);



    // main Render Loop
    while (!glfwWindowShouldClose(window)) {
        //background color 
        glClearColor(bg.r, bg.g, bg.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //idienty matrix - 1s on the diagonal 

        shaderProgram.Activate();
        float currentFrame = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrame - lastframe;
        lastframe = currentFrame;
        
      


        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 proj = glm::mat4(1.0f);

       proj = glm::perspective(glm::radians(cam.Fov), 1000.0f / 1000.0f, 0.1f, 100.0f);


        //follow S-R-T , scale , rotate and translate 

        float speed = 2.0f;
        float angel = (float)glfwGetTime() * speed;



       
        model = glm::translate(model, glm::vec3(0.5f, -0.5f, 0.0f));


        cam.processinput(window, deltaTime);
        glm::mat4 view = cam.GetViewMatrix();
       

        glUniformMatrix4fv(modelloc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewloc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projloc, 1, GL_FALSE, glm::value_ptr(proj));

        vao1.Bind();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    vao1.Delete();
    vbo1.Delete();
    ebo1.Delete();
    shaderProgram.Delete();
    glDeleteTextures(1 , &texture);

    //detroy window when finish !
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}