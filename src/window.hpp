#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <expected>
#include <string>

namespace gl {

class Window {
public:
	unsigned int width, height;

	GLFWwindow* instance;

	static auto create(std::string _name, unsigned int _width, unsigned int _height)
	-> std::expected<Window, std::string>
	{
		Window window;
		window.width = _width;
		window.height = _height;

		if (!glfwInit()) {
			return std::unexpected{"Failed to initialise GLFW."};
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window.instance = glfwCreateWindow(window.width, window.height, _name.c_str(), NULL, NULL);
		if (!window.instance) {
			glfwTerminate();
			return std::unexpected{"Failed to create GLFW window."};
		}	
		glfwMakeContextCurrent(window.instance);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			return std::unexpected{"Failed to initialise GLAD."};
		}

		glViewport(0, 0, window.width, window.height);
		glfwSetFramebufferSizeCallback(window.instance, [](GLFWwindow* _window, int _width, int _height) {
			glViewport(0, 0, _width, _height);
		});

		return window;
	}

	bool should_close()
	{
		return glfwWindowShouldClose(instance);
	}

	void close()
	{
		glfwSetWindowShouldClose(instance, true);
	}
};

}
