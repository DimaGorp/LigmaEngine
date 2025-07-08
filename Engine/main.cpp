/*
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>

namespace callbacks {
    void error_callback(int error, const char* desc) {
        std::cerr << "ERROR: " << desc << std::endl;
    }
    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
}



float cube_positions[] = {
    //Outer Square
    -0.5f  ,0.5f    ,0.0f    , 1.0f,
    0.5f  , 0.5f    ,0.0f    , 1.0f,
    0.5f  , -0.5f    ,0.0f    , 1.0f, 
    -0.5f  ,-0.5f    ,0.0f    , 1.0f,
        //Inner Square
     0.0f  ,0.5f    ,0.0f    , 1.0f,
     0.5  , 0.0f    ,0.0f    , 1.0f,
      0.0f  , -0.5f    ,0.0f    , 1.0f,
      -0.5f  ,-0.0f    ,0.0f    , 1.0f,
    
    
     
    
   
    
   
};
GLuint indexes[] = {
    0,4,7,
    3,7,6,
    2,6,5,
    1,5,4
    //2,6,5,
    //4,5,
};
float cube_color[] = {
    1.0f  ,0.0f    ,0.0f    , 1.0f,
    1.0f  , 1.0f    ,0.0f    , 1.0f,
    0.0f  ,0.0f    ,1.0f    , 1.0f,
    1.0f  , 1.0f    ,0.0f    , 1.0f,

    1.0f  ,0.0f    ,0.0f    , 1.0f,
    1.0f  , 1.0f    ,0.0f    , 1.0f,
    0.0f  ,0.0f    ,1.0f    , 1.0f,
    1.0f  , 1.0f    ,0.0f    , 1.0f,
};






std::string LoadShader(const char * fileName) {
    char buffer[1024];
    char* direction = _getcwd_dbg(buffer, 1024, 0, "main.cpp", 0);
    std::string FILE = direction;
    FILE += "\\";
    FILE += fileName;
    std::cout << FILE << std::endl;
    std::ifstream in;
    in.open(FILE);
    if (!in.is_open())
        std::cout << "cant open a file\n";
    std::string program;
    std::string line;
    while (!in.eof())
    {
        std::getline(in, line);
        program += line + "\n";
    }
    in.close();
    return program;
}


void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
   
}
void ConfigureGLFW()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //Set Error callback
    glfwSetErrorCallback(callbacks::error_callback);
}
int main()
{
    ConfigureGLFW();
    GLFWwindow* window;
    
    //Create a windowed mode window and its OpenGL context 
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    //Make the window's context current
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return-1;
    }

    glViewport(0, 0, 640, 640);
    glfwSetFramebufferSizeCallback(window, callbacks::framebuffer_size_callback);

    std::cout << glGetString(GL_VERSION) << std::endl;
    std::string vertexProg, fragmentprog;
    vertexProg = LoadShader("VertexShader.txt");
    const char* vertexProgram = vertexProg.c_str();
    fragmentprog = LoadShader("FragmentShader.txt");
    const char* fragmentProgram = fragmentprog.c_str();


    //std::cout << vertexProgram << std::endl;
    //std::cout << fragmentProgram << std::endl;
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexProgram, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentProgram, NULL);
    glCompileShader(fragmentShader);


    unsigned int ProgramId = glCreateProgram();
    glAttachShader(ProgramId, vertexShader);
    glAttachShader(ProgramId, fragmentShader); 
    glLinkProgram(ProgramId);
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    
    
    //Create a Buffer
    unsigned int VAO;



    unsigned int VBO;
    unsigned int EBO;
    unsigned int CBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
   
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_positions), cube_positions, GL_STATIC_DRAW);
    glVertexAttribPointer(0,4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    

    glGenBuffers(1, &CBO);
    glBindBuffer(GL_ARRAY_BUFFER, CBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_color), cube_color, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);


    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);

    // Unbind VAO to avoid accidental modification
    glBindBuffer(GL_ARRAY_BUFFER, 1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    

    
   
    


    glClearColor(0, .25, 0, 1);
    //Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        //Render here 
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Bind VAO and draw the square
        glUseProgram(ProgramId);
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
        //S wap front and back buffers
        glfwSwapBuffers(window);

        //Poll for and process events
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &CBO);
    glDeleteBuffers(0, &VBO);
    glDeleteBuffers(0, &EBO);

    glDeleteProgram(ProgramId);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
*/


#include <iostream>
#include <Core/Core.hpp>


template<int n>
struct fact{
    enum{result = n * fact<n-1>::result};
};
template<>
struct fact<0>{
    enum {result = 1};
};


int main(){
    
    std::cout << fact<3>::result<<std::endl;
    return 0;
}