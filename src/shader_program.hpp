#ifndef KOJO_GL_SHADERPROGRAM
#define KOJO_GL_SHADERPROGRAM

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"

#include <expected>
#include <string>
#include <format>
#include <vector>
#include <utility>

namespace gl {

class ShaderProgram {
public:
	unsigned int instance{0};

	ShaderProgram() = default;

	~ShaderProgram()
	{
		free();
	}

	ShaderProgram(const ShaderProgram&) = delete;
	ShaderProgram& operator=(const ShaderProgram&) = delete;

	ShaderProgram(ShaderProgram&& other) noexcept
		: instance(std::exchange(other.instance, 0)) {}

	ShaderProgram& operator=(ShaderProgram&& other) noexcept
	{
		if (this != &other) {
			free();
			instance = std::exchange(other.instance, 0);
		}
		return *this;
	}

	static auto create(std::vector<Shader> shaders)
	-> std::expected<ShaderProgram, std::string>
	{
		ShaderProgram result;
		result.instance = glCreateProgram();
		unsigned int& program = result.instance;

		for (auto& shader : shaders) {
			glAttachShader(program, shader.instance);
		}
		glLinkProgram(program);

		int success = false;
		char info_log_buffer[512];
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(program, 512, NULL, info_log_buffer);
			return std::unexpected{std::format("ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n{}", info_log_buffer)};
		}

		return result;
	}

	void free()
	{
		if (instance) {
			glDeleteProgram(instance);
		}
	}
};

}

#endif
