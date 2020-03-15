/*
 * OpenGL Sample
 * 2020-02-01 K.OHWADA
 * reference : http://nn-hokuson.hatenablog.com/entry/2017/02/24/171230
 */


#include "texture_util.hpp"



/**
 * crateShader
 */
GLuint crateShader()
{

    // Vertex Shader
    std::string STR_VERTEX_SHADER = R"#(
    attribute vec3 position;
    attribute vec2 uv;
    varying vec2 vuv;
    void main(void){
        gl_Position = vec4(position, 1.0);
        vuv = uv;
    }
    )#";

    // Fragment Shader
    std::string STR_FRAGMENT_SHADER = R"#(
    varying vec2 vuv;
    uniform sampler2D texture;
    void main(void){
        gl_FragColor = texture2D(texture, vuv);
    }
    )#";



    // Compiling vertex Shaders
    GLuint vShaderId = glCreateShader(GL_VERTEX_SHADER);

    const char* vs = STR_VERTEX_SHADER.c_str();
    glShaderSource(vShaderId, 1, &vs, NULL);
    glCompileShader(vShaderId);
    
    // Compile the fragment Shader
    GLuint fShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    const char* fs = STR_FRAGMENT_SHADER.c_str();
    glShaderSource(fShaderId, 1, &fs, NULL);
    glCompileShader(fShaderId);

    // Creating a program object
    GLuint programId = glCreateProgram();
    glAttachShader(programId,vShaderId);
    glAttachShader(programId,fShaderId);

    // Link
    glLinkProgram(programId);

    glUseProgram(programId);

    return programId;
}


/**
 * setupTexture
 */
GLuint setupTexture(char *image, int width, int height)
{

    // Generate Texture ID
    GLuint texID;
    glGenTextures(1, &texID);

    // Transfer texture to GPU
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glBindTexture(GL_TEXTURE_2D, texID);


//　Associate an image with Texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);   


    // Texture settings
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Unbind Texture
    glBindTexture(GL_TEXTURE_2D, 0);

    // relese memory
    delete[] image;

    return texID;
}


/**
 * display
 */
void display(GLuint  programId, GLuint texID)
{

        // Vertex data
        float ARR_VERTEX_POSITION[] = {
            0.5f, 0.5f,
            -0.5f, 0.5f,
            -0.5f, -0.5f,
            0.5f, -0.5f
        };

        // Vertex UV data
        const GLfloat ARR_VERTEX_UV[] = {
            1, 0,
            0, 0,
            0, 1,
            1, 1,
        };


        // Gray
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

        // Screen initialization
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearDepth(1.0);


        // The number of the attribute variable
        int positionLocation = glGetAttribLocation(programId, "position");
        int uvLocation = glGetAttribLocation(programId, "uv");
        int textureLocation = glGetUniformLocation(programId, "texture");
        
        // Enable attribute attribute
        glEnableVertexAttribArray(positionLocation);
        glEnableVertexAttribArray(uvLocation);
        
        // Set uniform attribute
        glUniform1i(textureLocation, 0);

        // Register attribute attribute
        glVertexAttribPointer(positionLocation, 2, GL_FLOAT, false, 0, ARR_VERTEX_POSITION);
        glVertexAttribPointer(uvLocation, 2, GL_FLOAT, false, 0, ARR_VERTEX_UV);

        // Drawing the model
        glBindTexture(GL_TEXTURE_2D, texID);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

}


/**
 * dumpGLInfo
 */
void dumpGLInfo() 
{

    std::string vendor = (char *)glGetString(GL_VENDOR);
    std::string renderer = (char *)glGetString(GL_RENDERER);
    std::string version = (char *)glGetString(GL_VERSION);

    std::string glfw_version = glfwGetVersionString();	


    std::cout << "OpenGL Vender: " << vendor << std::endl;
    std::cout << "OpenGL Renderer: " << renderer << std::endl;
    std::cout << "OpenGL Version: " << version << std::endl;
    std::cout << "glfw Version: " << glfw_version << std::endl;

}


