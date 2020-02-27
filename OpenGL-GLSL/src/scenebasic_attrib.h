/**
 * OpenGL Sample
 * 2010-02-01 K.OHWADA
 * original : https://github.com/daw42/glslcookbook/tree/master/chapter01
 */

#ifndef SCENEBASIC_ATTRIB_H
#define SCENEBASIC_ATTRIB_H

#include "scene.h"

#include "cookbookogl.h"
#include "glslprogram.h"

class SceneBasic_Attrib : public Scene
{
private:
    GLuint vaoHandle;
    GLSLProgram prog;

    void compileShaderProgram();

public:
    SceneBasic_Attrib();

    void initScene();
    void update( float t );
    void render();
    void resize(int, int);
};

#endif // SCENEBASIC_ATTRIB_H
