/**
 * OpenGL Sample
 * 2010-02-01 K.OHWADA
 */

// original : https://github.com/itoru257/GLFWDemo-Mac

//
//  main.cpp
//  GLFWDemo-Mac
//
//  Created by itoh on 2016/06/28.
//  Copyright © 2016 tohru itoh. All rights reserved.
//
//  Based on Example code for the OpenGL Shading Language Cookbook
//  https://github.com/daw42/glslcookbook
//

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>

std::string shader_basic_vert =
R"(
#version 410
layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec3 VertexColor;

out vec3 Color;

void main()
{
    Color = VertexColor;
    gl_Position = vec4(VertexPosition,1.0);
}
)";


std::string shader_basic_frag =
R"(
#version 410

in vec3 Color;
layout (location=0) out vec4 FragColor;

void main() {
    FragColor = vec4(Color, 1.0);
}
)";


/**
 * CreateCompileShader
 */
bool CreateCompileShader( std::string code, GLenum shaderType, GLuint& shader )
{
    // Create the shader object
    shader = glCreateShader( shaderType );
    
    if( 0 == shader ) {
        fprintf( stderr, "Error creating shader\n" );
        return false;
    }
    
    // Load the source code into the shader object
    const GLchar* codeArray[] = { code.c_str() };
    glShaderSource( shader, 1, codeArray, NULL );
    
    // Compile the shader
    glCompileShader( shader );
    
    // Check compilation status
    GLint result;
    glGetShaderiv( shader, GL_COMPILE_STATUS, &result );
    if( GL_FALSE == result ) {
        fprintf( stderr, "shader compilation failed!\n" );
        
        GLint logLen;
        glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logLen );
        
        if( logLen > 0 ) {
            char * log = new char[logLen];
            
            GLsizei written;
            glGetShaderInfoLog( shader, logLen, &written, log );
            
            fprintf( stderr, "Shader log: \n%s", log );
            
            delete [] log;
        }
        
        return false;
    }
    
    return true;
}


/**
 * LinkShader
 */
bool LinkShader( GLint shader1, GLint shader2 )
{
    // Create the program object
    GLuint programHandle = glCreateProgram();
    if(0 == programHandle) {
        fprintf(stderr, "Error creating program object.\n");
        return false;
    }
    
    // Attach the shaders to the program object
    glAttachShader( programHandle, shader1 );
    glAttachShader( programHandle, shader2 );
    
    // Link the program
    glLinkProgram( programHandle );
    
    // Check for successful linking
    GLint status;
    glGetProgramiv( programHandle, GL_LINK_STATUS, &status );
    
    if (GL_FALSE == status) {
        
        fprintf( stderr, "Failed to link shader program!\n" );
        
        GLint logLen;
        glGetProgramiv( programHandle, GL_INFO_LOG_LENGTH, &logLen );
        
        if( logLen > 0 ) {
            char * log = new char[logLen];
            
            GLsizei written;
            glGetProgramInfoLog( programHandle, logLen, &written, log );
            
            fprintf( stderr, "Program log: \n%s", log );
            
            delete [] log;
        }
        
        return false;
        
    } else {
        
        glUseProgram( programHandle );
        
    }
    
    return true;
}


/**
 * main
 */
int main(int argc, const char * argv[]) 
{
    printf("OpenGL/glfw3 Triangle \n");

    GLFWwindow* window;
    
    // Initialize the library
    if (!glfwInit())
        return -1;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow( 640, 480, "OpenGL/glfw3 Triangle", NULL, NULL );
    if (!window) {
        glfwTerminate();
        return -1;
    }
    
    // Make the window's context current
    glfwMakeContextCurrent(window);
    
    printf("OpenGL Version: %s \n", glGetString(GL_VERSION) );

    // Create a Shader and Compile a Shader
    GLuint vertShader, fragShader;
    if( !CreateCompileShader( shader_basic_vert, GL_VERTEX_SHADER, vertShader ) ){
        return -1;
    }
    
    if( !CreateCompileShader( shader_basic_frag, GL_FRAGMENT_SHADER, fragShader ) ){
        return -1;
    }
    
    if( !LinkShader( vertShader, fragShader ) ){
        return -1;
    }
    
    /////////////////// Create the VBO ////////////////////
    float positionData[] = {
        -0.8f, -0.8f, 0.0f,
        0.8f, -0.8f, 0.0f,
        0.0f,  0.8f, 0.0f };
    
    float colorData[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f };
    
    // Create and populate the buffer objects
    GLuint vboHandles[2];
    glGenBuffers( 2, vboHandles );
    GLuint positionBufferHandle = vboHandles[0];
    GLuint colorBufferHandle = vboHandles[1];
    
    glBindBuffer( GL_ARRAY_BUFFER, positionBufferHandle );
    glBufferData( GL_ARRAY_BUFFER, 9 * sizeof(float), positionData, GL_STATIC_DRAW );
    
    glBindBuffer( GL_ARRAY_BUFFER, colorBufferHandle);
    glBufferData( GL_ARRAY_BUFFER, 9 * sizeof(float), colorData, GL_STATIC_DRAW );
    
    // Create and set-up the vertex array object
    GLuint vaoHandle;
    glGenVertexArrays( 1, &vaoHandle );
    glBindVertexArray( vaoHandle );
    
    glEnableVertexAttribArray( 0 );  // Vertex position
    glEnableVertexAttribArray( 1 );  // Vertex color
    
    glBindBuffer( GL_ARRAY_BUFFER, positionBufferHandle );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL );
    
    glBindBuffer( GL_ARRAY_BUFFER, colorBufferHandle );
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL );
    glBindVertexArray( 0 );
  

    // Loop until the user closes the window
    while( !glfwWindowShouldClose( window ) ) {

        // Gray
        glClearColor(0.5, 0.5, 0.5, 1.0);
 
        // Render
        glClear( GL_COLOR_BUFFER_BIT) ;
        glBindVertexArray( vaoHandle );
        glDrawArrays( GL_TRIANGLES, 0, 3 );
        glBindVertexArray( 0 );
        
        // Swap front and back buffers
        glfwSwapBuffers( window );
        
        // Poll for and process events
        glfwPollEvents();
        
    }
    
    glfwTerminate();
    
    return 0;
}
