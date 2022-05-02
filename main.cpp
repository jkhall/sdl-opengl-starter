#define GL_SILENCE_DEPRECATION

#include "SDL.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <stdio.h>
#include <iostream>
#include "shader.hpp"
#include "texture.hpp"

const int OPENGL_MAJOR_VERSION = 3;
const int OPENGL_MINOR_VERSION = 3;
const SDL_GLprofile OPENGL_PROFILE = SDL_GLprofile::SDL_GL_CONTEXT_PROFILE_CORE;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aCol;\n"
    "out vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
    "   ourColor = aCol;"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(ourColor, 1.0);"
    "}\0";

glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
};

float verticesCube[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

const float vertices[] = {
    -0.5f, -0.5f, 0.0f, 
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

const float vertices2[] = {
    -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,   0.0f, 0.0f, 
     0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
     0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
    -0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,   0.0f, 1.0f
};

const int indices[] = {
    0, 1, 3,
    1, 2, 3
};

unsigned int VBO, VAO, EBO;
unsigned int vertexShader;
unsigned int fragmentShader;
unsigned int shaderProgram;

int success;
char infoLog[512];

int main(int argc, char *argv[]) {
    SDL_Window* window = NULL;

    SDL_Surface* screenSurface = NULL;

    if(SDL_Init( SDL_INIT_VIDEO ) < 0) {
        printf("SDL could not init! Err: %s\n", SDL_GetError());
    }
    else
    {
        printf("creating window\n");
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
        if(window == NULL) {
            printf("Window could not be created!");
        }
        else
        {
            // SDL drudgery
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,OPENGL_PROFILE);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,OPENGL_MAJOR_VERSION);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,OPENGL_MINOR_VERSION);
            SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
            //SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

            SDL_GLContext glcontext = SDL_GL_CreateContext(window);


            // init glad
            if(!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
                std::cout << "Failed to init GLAD" << std::endl;
                return -1;
            }
            
            glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            
            Tex tex("./textures/container.jpg");
            Tex tex2("./textures/awesomeface.png", true, true);
            Shader shader("./shader.vs","./shader.fs"); 

            //vertexShader = glCreateShader(GL_VERTEX_SHADER);
            //glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
            //glCompileShader(vertexShader);
            //glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

            //if(!success) {
            //    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            //    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            //}
            //

            //fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            //glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
            //glCompileShader(fragmentShader);
            //glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

            //if(!success) {
            //    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            //    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
            //}


            //shaderProgram = glCreateProgram();
            //glAttachShader(shaderProgram, vertexShader);
            //glAttachShader(shaderProgram, fragmentShader);
            //glLinkProgram(shaderProgram);

            //glDeleteShader(vertexShader);
            //glDeleteShader(fragmentShader);

            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO); 
            glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCube), verticesCube, GL_STATIC_DRAW);

            //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            // linking vertex attributes
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)0);
            glEnableVertexAttribArray(0);

            //glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
            //glEnableVertexAttribArray(1);

            //texture
            glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(3*sizeof(float)));
            glEnableVertexAttribArray(2);    

            //glUseProgram(shaderProgram);

            //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            shader.use();
            shader.setInt("tex1",tex.texId);
            shader.setInt("tex2",tex2.texId);
            
            //trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0,0.0,1.0));
            //trans = glm::scale(trans, glm::vec3(0.5,0.5,0.5));
            SDL_Event e;
            int quit = 0;
            
            // matrices
            glm::mat4 model;
            glm::mat4 view; 
            glm::mat4 projection;
            

            unsigned int modelLoc = glGetUniformLocation(shader.ID,"model");
            unsigned int viewLoc = glGetUniformLocation(shader.ID,"view");
            unsigned int projectionLoc = glGetUniformLocation(shader.ID,"projection");

            
            while(!quit) {
                glClearColor(0.2f,0.3f,0.3f,1.0f);
                glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
                glEnable(GL_DEPTH_TEST);
                //glm::mat4 trans = glm::mat4(1.0f);
                //trans = glm::translate(trans, glm::vec3(0.5f,-0.5f,0.0f));

                //trans = glm::rotate(trans,(float)SDL_GetTicks()/1000.0f,glm::vec3(0.0f,0.0f,1.0f));
                //unsigned int tranLoc = glGetUniformLocation(shader.ID,"transform");
                //glUniformMatrix4fv(tranLoc, 1, GL_FALSE, glm::value_ptr(trans));
                model = glm::mat4(1.0f);
                view = glm::mat4(1.0f);

                for(int i=0;i<cubePositions.size();i++) {

                }

                model = glm::rotate(model,(SDL_GetTicks()/1000.0f)*glm::radians(50.0f), glm::vec3(0.5f,1.0f,0.0f));
                view = glm::translate(view, glm::vec3(0.0f,0.0f,-3.0f));
                projection = glm::perspective(glm::radians(45.0f),(float)SCREEN_WIDTH/(float)SCREEN_HEIGHT,0.1f,100.0f);

                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
                glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
                glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));



                // bind VAO
                //glUseProgram(shaderProgram);
                tex.bind();
                tex2.bind();

                glBindVertexArray(VAO);
                //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                //glBindVertexArray(0);
                glDrawArrays(GL_TRIANGLES, 0, 36);

                SDL_GL_SwapWindow(window); 

                while(SDL_PollEvent(&e)) {
                    if(e.type == SDL_QUIT) {
                        quit = 1;
                    }
                    if(e.type == SDL_KEYDOWN) {
                        quit = 1;
                    }
                    if(e.type == SDL_MOUSEBUTTONDOWN) {
                        quit = 1;
                    }
                }
            }

            return 0;
        }
    }
}

