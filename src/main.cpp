#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

struct Vec2 {
	int x, y;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	// Press `Esc` to close the window.
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	if (!glfwInit()) {
		std::cerr << "Failed to initialise GLFW." << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	const Vec2 default_window_dimensions{800, 600};
	GLFWwindow* window = glfwCreateWindow(default_window_dimensions.x, default_window_dimensions.y, "OpenGL Project", NULL, NULL);
	if (!window) {
		std::cerr << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return -1;
	}	
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialise GLAD." << std::endl;
		return -1;
	}

	glViewport(0, 0, default_window_dimensions.x, default_window_dimensions.y);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(1.0f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		processInput(window);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}
