// Copyright (C) 2021 Dave Moore
//
// This file is part of learnopenglsfml.
//
// learnopenglsfml is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation, either version 2 of the License, or (at your option)
// any later version.
//
// learnopenglsfml is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
// more details.
//
// You should have received a copy of the GNU General Public License along
// with learnopenglsfml.  If not, see <http://www.gnu.org/licenses/>.
//
// If you modify this program, or any covered work, by linking or combining
// it with the libraries referred to in README (or a modified version of
// said libraries), containing parts covered by the terms of said libraries,
// the licensors of this program grant you additional permission to convey
// the resulting work.

#include "graphics.hpp"

OpenGLTutorial::Graphics::Graphics() {

	// First do the Shaders
	auto is_compiled{_compile_shaders()};
	if (!is_compiled)
		exit(EXIT_SUCCESS);

	auto is_linked{_link_shaders()};
	if (!is_linked)
		exit(EXIT_SUCCESS);

	// Then set up the Vertices
	_setup_vertices();
	_bind_configure_vertices();
}

OpenGLTutorial::Graphics::~Graphics() {

	// Do Tidy Up
	glDeleteVertexArrays(1, &_vertex_array_object);
	glDeleteBuffers(1, &_vertex_buffer_object);
	glDeleteBuffers(1, &_element_buffer_object);
	glDeleteProgram(_shader_program);
}

auto OpenGLTutorial::Graphics::render() -> void {

	// Draw our Triangle!
	glUseProgram(_shader_program);
	glBindVertexArray(_vertex_array_object);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

// Compile OpenGL Shaders
auto OpenGLTutorial::Graphics::_compile_shaders() -> bool {

	// Compile the Vertex Shader and check for any Errors
	_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	const char *vertex_shader_source_c{Shaders::vertex_shader_source.c_str()};
	glShaderSource(_vertex_shader, 1, &vertex_shader_source_c, NULL);
	glCompileShader(_vertex_shader);
	GLint success{};
	glGetShaderiv(_vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		std::cout << _get_shader_info_log(_vertex_shader);
		return false;
	}

	// Compile the Fragment Shader and check for any Errors
	_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	const char *_fragment_shader_source_c{
		Shaders::fragment_shader_source.c_str()};
	glShaderSource(_fragment_shader, 1, &_fragment_shader_source_c, NULL);
	glCompileShader(_fragment_shader);
	glGetShaderiv(_fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		std::cout << _get_shader_info_log(_fragment_shader);
		return false;
	}

	return true;
}

// Link Open GL Shaders
auto OpenGLTutorial::Graphics::_link_shaders() -> bool {

	// Link the Shaders and check for any Errors
	_shader_program = glCreateProgram();
	glAttachShader(_shader_program, _vertex_shader);
	glAttachShader(_shader_program, _fragment_shader);
	glLinkProgram(_shader_program);
	GLint success{};
	glGetProgramiv(_shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		std::cout << _get_shader_info_log(_shader_program);
		return false;
	}

	// And Tidy Up!
	glDeleteShader(_vertex_shader);
	glDeleteShader(_fragment_shader);

	return true;
}

// Load Vertex Data
auto OpenGLTutorial::Graphics::_setup_vertices() -> void {

	_vertices.clear();
	_indices.clear();

	// Vertices
	_vertices.push_back(0.5f);
	_vertices.push_back(0.5f);
	_vertices.push_back(0.0f);

	_vertices.push_back(0.5f);
	_vertices.push_back(-0.5f);
	_vertices.push_back(0.0f);

	_vertices.push_back(-0.5f);
	_vertices.push_back(-0.5f);
	_vertices.push_back(0.0f);

	_vertices.push_back(-0.5f);
	_vertices.push_back(0.5f);
	_vertices.push_back(0.0f);

	// Indices start from 0
	_indices.push_back(0);
	_indices.push_back(1);
	_indices.push_back(3);
	_indices.push_back(1);
	_indices.push_back(2);
	_indices.push_back(3);
}

// From https://learnopengl.com/Getting-started/Hello-Triangle
auto OpenGLTutorial::Graphics::_bind_configure_vertices() -> void {

	glGenVertexArrays(1, &_vertex_array_object);
	glGenBuffers(1, &_vertex_buffer_object);
	glGenBuffers(1, &_element_buffer_object);

	glBindVertexArray(_vertex_array_object);

	glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_object);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(GLfloat),
		&_vertices.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _element_buffer_object);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		_indices.size() * sizeof(unsigned int), &_indices.front(),
		GL_STATIC_DRAW);

	glVertexAttribPointer(
		0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

// Get the Shader Error Message (if any)
auto OpenGLTutorial::Graphics::_get_shader_info_log(const GLuint shader)
	-> std::string {

	GLint total_length{0};
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &total_length);
	std::string logs{};
	logs.resize(total_length);
	glGetShaderInfoLog(shader, total_length, NULL, &logs[0]);
	return logs;
}