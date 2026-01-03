#include <iostream>
#include <GLFW/glfw3.h>
#include <vector>

using namespace std;

const float SCREEN_HEIGHT = 600.0f;
const float SCREEN_WIDTH = 800.0f;

const float BALL_RADIUS = 50.0f;
const float BALL_INITIAL_X = 400.0f;
const float BALL_INITIAL_Y = 300.0f;
const float BALL_INITIAL_VX = 0.0f;
const float BALL_INITIAL_VY = 0.0f;
const int BALL_RESOLUTION = 100;

const float GRAVITY = 9.81f;
const float PI = 3.141592653589f;

GLFWwindow* StartGLFW();
void drawCircle(float x, float y, float r, int res);

int main() {
	GLFWwindow* window = StartGLFW();

	float x = SCREEN_WIDTH / 2.0f;
	float y = SCREEN_HEIGHT / 2.0f;

	vector<float> position = { BALL_INITIAL_X, BALL_INITIAL_Y };
	vector<float> velocity = { BALL_INITIAL_VX, BALL_INITIAL_VY };

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		drawCircle(position[0], position[1], BALL_RADIUS, BALL_RESOLUTION);
		
		position[0] += velocity[0];
		position[1] += velocity[1];

		velocity[1] -= GRAVITY / 2000.0f;

		if (position[1] - BALL_RADIUS < 0) {
			position[1] = BALL_RADIUS;
			velocity[1] *= -0.95f;
		}

		if (position[1] + BALL_RADIUS > SCREEN_HEIGHT) {
			position[1] = SCREEN_HEIGHT - BALL_RADIUS;
			velocity[1] *= -0.95f;
		}

		if (position[0] - BALL_RADIUS < 0) {
			position[0] = BALL_RADIUS;
			velocity[0] *= -0.95f;
		}

		if (position[0] + BALL_RADIUS > SCREEN_WIDTH) {
			position[0] = SCREEN_WIDTH - BALL_RADIUS;
			velocity[0] *= -0.95f;
		}
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}

GLFWwindow* StartGLFW() {
	if (!glfwInit()) {
		cerr << "failed to initialize glfw" << endl;
		return nullptr;
	}

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "gravity_2d", NULL, NULL);
	if (!window) return nullptr;

	glfwMakeContextCurrent(window);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0, 0, 0, 1); 

	return window;
}

void drawCircle(float x, float y, float r, int res) {
	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(x, y);

	for (int i = 0; i <= res; i++) {
		float angle = 2.0f * PI * (static_cast<float>(i) / res);
		float vertexX = x + cos(angle) * r;
		float vertexY = y + sin(angle) * r;
		glVertex2d(vertexX, vertexY);
	}

	glEnd();
}