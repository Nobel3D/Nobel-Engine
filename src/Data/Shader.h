#pragma once

#include <nedef.h>

NL_NAMEUSING

NE_NAMESTART

    // Get the type of the shader
    enum ShaderType {Vertex = 0x8B31, Fragment = 0x8B30, Geometry = 0};

    class Shader
    {
    private:
        GLuint sha_id;

    public:
        Shader();
        void Init(const ShaderType& type);
        void Load(const Filename& stream);
        void Load(const NString& code);
        void Compile();
        void Activate();
        void Deactivate();

        operator GLuint();

        GLuint getID() const;
    };

    class ShaderProgram
    {
	private:
		GLuint sha_program;   // The unique ID / handle for the shader program
		GLuint sha_iCount; // How many shaders are attached to the shader program
public:
		// Constructor
		ShaderProgram();

		// Destructor
		~ShaderProgram();
		// Method to attach a shader to the shader program
		void Attach(const Shader& shader);

		// Method to link the shader program and display the link status
		void Link();



		// Method to enable the shader program
		void Use();


		// Method to disable the shader program
		void Disable();

        // Returns value of a named attribute
        GLuint getAttribute(const NString &attribute);


		// Method to returns the bound location of a named uniform
		GLuint uniform(const NString &uniform);



		// Method to add an attrbute to the shader and return the bound location
		int addAttribute(const NString &attributeName);


		// Method to add a uniform to the shader and return the bound location
		int addUniform(const NString &uniformName);


};


NE_NAMECLOSE
