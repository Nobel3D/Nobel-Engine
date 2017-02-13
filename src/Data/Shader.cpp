#include "Shader.h"
#include <nedef.h>
#include <GL/glew.h>

NL_NAMEUSING
NE_NAMEUSING

Shader::Shader()
{
}

void Shader::Init(const ShaderType& type)
{
    // Create the vertex shader id / handle
    // Note: If you segfault here you probably don't have a valid rendering context.
    sha_id = glCreateShader(type);
}

void Shader::Load(const Filename& file)
{
    LOGSHADER("Starting Reading Shader -> " + file.getName())

    NFile* stream = new NFile(file);
    stream->Open(Reading);
    const char* _code = stream->ReadAll();

    stream->Close();
    delete[] stream;
    // Associate the source with the shader id
    glShaderSource(sha_id, 1, &_code, NULL);
}

void Shader::Load(const NString& code)
{
    LOGSHADER("Starting Reading Shader from RAM");
    ASSERT(!code.Null());

    const char* _code = code;
    int length = code.getLength();
    // Associate the source with the shader id
    glShaderSource(sha_id, 1, &_code, &length);

}

void Shader::Compile()
{
    LOGSHADER("Starting Compiling Shaders");
    // Compile the shader
    glCompileShader(sha_id);

    // Check the compilation status and report any errors
    GLint status;
    glGetShaderiv(sha_id, GL_COMPILE_STATUS, &status);

    // If the shader failed to compile, display the info log and quit out
    if (status == GL_FALSE)
    {
        GLint logLength;
        glGetShaderiv(sha_id, GL_INFO_LOG_LENGTH, &logLength);

        char* strLog = new char[logLength + 1];
        glGetShaderInfoLog(sha_id, logLength, NULL, strLog);

        LOGSHADER(NString("Shader Compilation Fail: ") + strLog);
    }
    else
        LOGSHADER("Shader Compilation OK");
}

GLuint Shader::getID() const
{
    return sha_id;
}

ShaderProgram::ShaderProgram()
{
    // Generate a unique Id / handle for the shader program
    // Note: We MUST have a valid rendering context before generating
    // the programId or it causes a segfault!
    sha_program = glCreateProgram();

    // Initially, we have zero shaders attached to the program
    sha_iCount = 0;
}

ShaderProgram::~ShaderProgram()
{
    // Delete the shader program from the graphics card memory to
    // free all the resources it's been using
    glDeleteProgram(sha_program);
}


void ShaderProgram::Attach(const Shader& shader)
{
    // Attach the shader to the program
    // Note: We identify the shader by its unique Id value
    glAttachShader( sha_program, shader.getID() );

    // Increment the number of shaders we have associated with the program
    sha_iCount++;
}


void ShaderProgram::Link()
{
    // If we have at least two shaders (like a vertex shader and a fragment shader)...
    if (sha_iCount >= 2)
    {
        // Perform the linking process
        glLinkProgram(sha_program);

        // Check the status
        GLint linkStatus;
        glGetProgramiv(sha_program, GL_LINK_STATUS, &linkStatus);
        if (linkStatus == GL_FALSE)
            ERRORSHADER("Failed to Link shaders")
        else
            LOGSHADER("Shaders Linked")
    }
    else
        ERRORSHADER("Can't link shaders - you need at least 2, but attached shader count is only: " + NString::fromInt(sha_iCount))
}


void ShaderProgram::Use()
{
    glUseProgram(sha_program);
}



void ShaderProgram::Disable()
{
    glUseProgram(0);
}


