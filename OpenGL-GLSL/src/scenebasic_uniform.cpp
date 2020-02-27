/**
 * OpenGL Sample
 * 2010-02-01 K.OHWADA
 * original : https://github.com/daw42/glslcookbook/tree/master/chapter01
 */

// rotate Triangle
// require GLM

#include "scenebasic_uniform.h"

#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>

#include "glutils.h"

#include <glm/gtc/matrix_transform.hpp>


 using std::string;
using std::cerr;
using std::endl;
using glm::vec3;


/**
 * SceneBasic_Uniform
 */
SceneBasic_Uniform::SceneBasic_Uniform() : 

angle(0.0f) {}


/**
 * initScene
 */
void SceneBasic_Uniform::initScene()
{
    compile();

    std::cout << std::endl;

    prog.printActiveUniforms();

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
    glGenBuffers(2, vboHandles);
    GLuint positionBufferHandle = vboHandles[0];
    GLuint colorBufferHandle = vboHandles[1];

    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), positionData, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), colorData, GL_STATIC_DRAW);

    // Create and set-up the vertex array object
    glGenVertexArrays( 1, &vaoHandle );
    glBindVertexArray(vaoHandle);

    glEnableVertexAttribArray(0);  // Vertex position
    glEnableVertexAttribArray(1);  // Vertex color

    #ifdef __APPLE__
        glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL );

        glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL );
    #else
    		glBindVertexBuffer(0, positionBufferHandle, 0, sizeof(GLfloat)*3);
    		glBindVertexBuffer(1, colorBufferHandle, 0, sizeof(GLfloat)*3);

    		glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
    		glVertexAttribBinding(0, 0);
    		glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 0);
    	  glVertexAttribBinding(1, 1);
    #endif
    glBindVertexArray(0);
}


/**
 * compile
 */
void SceneBasic_Uniform::compile()
{
	try {
		prog.compileShader("shader/basic_uniform.vert");
		prog.compileShader("shader/basic_uniform.frag");
		prog.link();
		prog.use();
	} catch (GLSLProgramException &e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}


/**
 * update
 */
void SceneBasic_Uniform::update( float t )
{
	if( m_animate ) {

        // slow down because too fast
    	//angle += 1.0f;
    	angle += 0.01f;

    	if( angle >= 360.0f) angle -= 360.0f;
    }
}


/**
 * render
 */
void SceneBasic_Uniform::render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, vec3(0.0f,0.0f,1.0f));

    GLuint programHandle = prog.getHandle();
    GLuint location = glGetUniformLocation(programHandle, "RotationMatrix");
    glUniformMatrix4fv(location, 1, GL_FALSE, &rotationMatrix[0][0]);
    
    glBindVertexArray(vaoHandle);
    glDrawArrays(GL_TRIANGLES, 0, 3 );
}


/**
 * resize
 */
void SceneBasic_Uniform::resize(int w, int h)
{
    width = w;
    height = h;
    glViewport(0,0,w,h);
}
