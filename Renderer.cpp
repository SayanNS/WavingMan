//
// Created by sayan on 05.05.2022.
//

#include "Renderer.h"
#include "glad/glad.h"
#include <iostream>
#include <fstream>


#define CIRCLE_VERTEX_SHADER_PATH "circle.vs"
#define CIRCLE_FRAGMENT_SHADER_PATH "circle.fs"
#define TRAPEZIUM_VERTEX_SHADER_PATH "trapezium.vs"
#define TRAPEZIUM_FRAGMENT_SHADER_PATH "trapezium.fs"

#define MODEL_UNIFORM_LOCATION 0
#define PROJECTION_UNIFORM_LOCATION 1
#define PARAMS_UNIFORM_LOCATION 2

const float vertices[] = {
		-1.f, -1.f,
		-1.f, 1.f,
		1.f, 1.f,
		1.f, -1.f
};

const unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
};

unsigned int circle_program_id;
unsigned int trapezium_program_id;


bool compile_program(unsigned int &program_id, const char *vertex_shader, const char *fragment_shader)
{
	int success;
	char infoLog[512];

	std::string vertexShaderSource;
	std::ifstream vertexShaderSourceStream(vertex_shader, std::ios::binary);
	if (vertexShaderSourceStream.is_open()) {
		char buffer[1024];
		while (!vertexShaderSourceStream.eof()) {
			vertexShaderSourceStream.read(buffer, sizeof(buffer));
			vertexShaderSource.append(buffer, vertexShaderSourceStream.gcount());
		}
	} else {
		std::cerr << "Could not open file: " << vertex_shader << std::endl;
		return false;
	}

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char *vertexShaderPointer = vertexShaderSource.c_str();
	glShaderSource(vertexShader, 1, &vertexShaderPointer, nullptr);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	}

	std::string fragmentShaderSource;
	std::ifstream fragmentShaderSourceStream(fragment_shader, std::ios::binary);
	if (fragmentShaderSourceStream.is_open()) {
		char buffer[1024];
		while (!fragmentShaderSourceStream.eof()) {
			fragmentShaderSourceStream.read(buffer, sizeof(buffer));
			fragmentShaderSource.append(buffer, fragmentShaderSourceStream.gcount());
		}
	} else {
		std::cerr << "Could not open file: " << fragment_shader << std::endl;
		return false;
	}

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char *fragmentShaderPointer = fragmentShaderSource.c_str();
	glShaderSource(fragmentShader, 1, &fragmentShaderPointer, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	}

	program_id = glCreateProgram();
	glAttachShader(program_id, vertexShader);
	glAttachShader(program_id, fragmentShader);
	glLinkProgram(program_id);
	glUseProgram(program_id);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return true;
}

bool init_shaders_and_vertexes()
{
	if (!compile_program(circle_program_id, CIRCLE_VERTEX_SHADER_PATH, CIRCLE_FRAGMENT_SHADER_PATH)) {
		return false;
	}

	if (!compile_program(trapezium_program_id, TRAPEZIUM_VERTEX_SHADER_PATH, TRAPEZIUM_FRAGMENT_SHADER_PATH)) {
		return false;
	}

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	return true;
}

void draw_ellipse(Matrix3x3 &model, Matrix3x3 &projection)
{
	glUseProgram(circle_program_id);

	glUniformMatrix3fv(MODEL_UNIFORM_LOCATION, 1, GL_FALSE, model.getArray());
	glUniformMatrix3fv(PROJECTION_UNIFORM_LOCATION, 1, GL_FALSE, projection.getArray());

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void draw_trapezium(Matrix3x3 &model, Matrix3x3 &projection, float a, float b)
{
	glUseProgram(trapezium_program_id);

	glUniformMatrix3fv(MODEL_UNIFORM_LOCATION, 1, GL_FALSE, model.getArray());
	glUniformMatrix3fv(PROJECTION_UNIFORM_LOCATION, 1, GL_FALSE, projection.getArray());
	glUniform2f(PARAMS_UNIFORM_LOCATION, a, b);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
