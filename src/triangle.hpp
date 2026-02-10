#ifndef KOJO_GL_TRIANGLE
#define KOJO_GL_TRIANGLE

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "vertex_array.hpp"
#include "vertex_buffer.hpp"

namespace gl {

struct Vec3 {
	float x, y, z;
};

class Triangle {
public:
	std::array<Vec3, 3> vertices;

	Triangle(Vec3 vertex1, Vec3 vertex2, Vec3 vertex3)
	{
		vertices = {vertex1, vertex2, vertex3};
	}

	void bind(VertexArray& va, VertexBuffer& vb)
	{
		glBindVertexArray(va.instance);
		glBindBuffer(GL_ARRAY_BUFFER, vb.instance);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);
	}

	void draw(VertexArray& va)
	{
		glBindVertexArray(va.instance);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
};

}

#endif
