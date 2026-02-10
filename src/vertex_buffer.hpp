#ifndef KOJO_GL_VERTEXBUFFER
#define KOJO_GL_VERTEXBUFFER

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace gl {

class VertexBuffer {
public:
	unsigned int instance;

	VertexBuffer()
	{
		glGenBuffers(1, &instance);
	}

	void free()
	{
		glDeleteBuffers(1, &instance);
	}

	~VertexBuffer()
	{
		free();
	}
};

}

#endif
