#include "DebugTools.hpp"

#include <glad/glad.h>

#include <iostream>

namespace Luna::Debug
{
    void _CheckGLError(const char* file, int line, const std::string& msg)
    {
	GLenum errorCode;
	std::string error;
	while ((errorCode = glGetError()) != GL_NO_ERROR)
	{
	    switch (errorCode)
	    {
	    case GL_INVALID_ENUM:
		error = "INVALID_ENUM";
		break;

	    case GL_INVALID_VALUE:
		error = "INVALID_VALUE";
		break;

	    case GL_INVALID_OPERATION:
		error = "INVALID_OPERATION";
		break;
	    
	    case GL_INVALID_FRAMEBUFFER_OPERATION:
		error = "INVALID_FRAMEBUFFER_OPERATION";
		break;

	    case GL_OUT_OF_MEMORY:
		error = "OUT_OF_MEMORY";
		break;
	    }

	    std::cerr << error << " | " << file << " (" << line << "): " << msg << '\n';
	}
    }
}

