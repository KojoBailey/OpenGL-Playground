#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <expected>

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
		window.instance = glfwCreateWindow(window.width, window.height, _name.c_str(), NULL, NULL);
		if (!window.instance) {
			glfwTerminate();
			return std::unexpected{"Failed to create GLFW window."};
		}	
		glfwMakeContextCurrent(window.instance);
		return window;
	}
};

}
