#ifndef KOJO_GL_SHADER
#define KOJO_GL_SHADER

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <expected>
#include <string>

namespace gl {

class Shader {
public:
	unsigned int instance;

	static auto create(GLenum type, const char* source, std::string name = "UNNAMED")
	-> std::expected<Shader, std::string>
	{
		Shader result;
		result.instance = glCreateShader(type);
		unsigned int& shader = result.instance;
		glShaderSource(shader, 1, &source, NULL);
		glCompileShader(shader);

		int success = false;
		char info_log_buffer[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 512, NULL, info_log_buffer);
			return std::unexpected{"ERROR::SHADER::" + name + "::COMPILATION_FAILED\n" + info_log_buffer};
		}

		return result;
	}

	void free()
	{
		glDeleteShader(instance);
	}
};

}

#endif
