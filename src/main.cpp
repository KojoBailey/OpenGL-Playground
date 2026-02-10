#include "window.hpp"
#include "shader_program.hpp"
#include "triangle.hpp"

#include <iostream>

int main()
{
	auto maybe_window = gl::Window::create("OpenGL Test", 800, 600);
	if (!maybe_window) {
		std::cerr << maybe_window.error() << std::endl;
		return -1;
	}
	gl::Window window = *maybe_window;

	const char* shaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	auto maybe_vertex_shader = gl::Shader::create(GL_VERTEX_SHADER, shaderSource, "VERTEX");
	if (!maybe_vertex_shader) {
		std::cerr << maybe_vertex_shader.error() << std::endl;
		return -1;
	}
	gl::Shader vertex_shader = *maybe_vertex_shader;

	const char* fragmentSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";

	auto maybe_fragment_shader = gl::Shader::create(GL_FRAGMENT_SHADER, fragmentSource, "FRAGMENT");
	if (!maybe_fragment_shader) {
		std::cerr << maybe_fragment_shader.error() << std::endl;
		return -1;
	}
	gl::Shader fragment_shader = *maybe_fragment_shader;

	auto maybe_program = gl::ShaderProgram::create({vertex_shader, fragment_shader});
	if (!maybe_program) {
		std::cerr << maybe_program.error() << std::endl;
		return -1;
	}
	gl::ShaderProgram program = std::move(*maybe_program);

	vertex_shader.free();
	fragment_shader.free();

	gl::VertexArray vertex_array;
	gl::VertexArray vertex_array2;

	gl::VertexBuffer vertex_buffer;
	gl::VertexBuffer vertex_buffer2;

	std::vector<gl::Triangle> triangles;

	triangles.emplace_back(
		gl::Vec3{-1.0f, 1.0f, 0.0f},
		gl::Vec3{-0.7f, 1.0f, 0.0f},
		gl::Vec3{-1.0f, 0.7f, 0.0f}
	);
	triangles[0].bind(vertex_array, vertex_buffer);

	triangles.emplace_back(
		gl::Vec3{1.0f, -1.0f, 0.0f},
		gl::Vec3{1.0f, -0.7f, 0.0f},
		gl::Vec3{0.7f, -1.0f, 0.0f}
	);
	triangles[1].bind(vertex_array2, vertex_buffer2);

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!window.should_close()) {
		// input
		if (glfwGetKey(window.instance, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			window.close();
		}

		// rendering
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program.instance);
		triangles[0].draw(vertex_array);
		triangles[1].draw(vertex_array2);

		// check/call events and swap buffers
		glfwSwapBuffers(window.instance);
		glfwPollEvents();
	}

	glfwTerminate();
}
