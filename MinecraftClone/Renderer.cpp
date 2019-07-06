#include "stdafx.h"
#include "Renderer.h"
#include "Block.h"

Renderer::Renderer() : window(initWindow()), camera(window), blockShader("block"), blocksSheet("blocks"),
blockMaterial(blockShader, blocksSheet) {
	camera.enable();

	// UBO Setup for Shaders
	// Cube Shader
	GLuint uniformCameraIndex = glGetUniformBlockIndex(blockShader.ID, "Camera");
	glUniformBlockBinding(blockShader.ID, uniformCameraIndex, 0);
};

GLFWwindow* Renderer::initWindow() {
	glfwInit();
#ifdef _DEBUG
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#else
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#endif
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE.c_str(), nullptr, nullptr);
	if(window == nullptr) {
		throw std::runtime_error("Window failed to create!");
		glfwTerminate();
	}
	prevFrameTime = glfwGetTime();
	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, &camera);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error("Failed to initialize GLAD");
	}

#ifdef _DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(glDebugCallback, nullptr);
	glfwSetErrorCallback([](int errorCode, const char* desc) {
		char error[255];
		sprintf_s(error, "GLFW Error %d: %s\n", errorCode, desc);
		throw std::runtime_error(error);
	});
#endif

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, 1280, 720);
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	});

	return window;
}

void Renderer::render() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera.update();
	for(const auto& obj : objects) obj->render();
	hud.render();

	glfwSwapBuffers(window);
	glfwPollEvents();

	handleEvents();

	updateWindowTitle();
}

void Renderer::updateWindowTitle() {
	frameCount++;
	double curTime = glfwGetTime();
	if(curTime - prevFrameTime >= 1) {
		double fps = frameCount / (curTime - prevFrameTime);
		glfwSetWindowTitle(window, (WINDOW_TITLE + " - " + std::to_string(fps) + " FPS").c_str());
		frameCount = 0;
		prevFrameTime = curTime;
	}
}

void Renderer::handleEvents() {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) camera.disable();
}


void APIENTRY glDebugCallback(GLenum source, GLenum mType, GLuint id, GLenum severity, GLsizei length,
	const GLchar* message, const void* userParam) {
	std::string src;
	switch(source) {
	case GL_DEBUG_SOURCE_API:
		src = "Windows";
		break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		src = "Shader Compiler";
		break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:
		src = "Third Party";
		break;
	case GL_DEBUG_SOURCE_APPLICATION:
		src = "Application";
		break;
	case GL_DEBUG_SOURCE_OTHER:
		src = "Other";
		break;
	}

	std::string type;
	switch(mType) {
	case GL_DEBUG_TYPE_ERROR:
		type = "Error";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		type = "Deprecated Behavior";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		type = "Undefined Behavior";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		type = "Portability Error";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		type = "Performance Error";
		break;
	case GL_DEBUG_TYPE_OTHER:
		type = "Other Error";
		break;
	}

	switch(severity) {
	case GL_DEBUG_SEVERITY_LOW:
		std::cout << "GL LOW - " + src + " " + type + ": " + message << std::endl;
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		std::cout << "GL MEDIUM - " + src + " " + type + ": " + message << std::endl;
		break;
	case GL_DEBUG_SEVERITY_HIGH:
		throw std::runtime_error("GL HIGH - " + src + " " + type + ": " + message);
		break;
	}
}
