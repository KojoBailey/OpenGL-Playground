#ifndef KOJO_GL_VERTEXARRAY
#define KOJO_GL_VERTEXARRAY

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace gl {

class VertexArray {
public:
	unsigned int instance;

	VertexArray()
	{
		glGenVertexArrays(1, &instance);
	}

	void free()
	{
		glDeleteVertexArrays(1, &instance);
	}

	~VertexArray()
	{
		free();
	}
};

}

#endif
