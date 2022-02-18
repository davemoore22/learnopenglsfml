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

#pragma once

#include "main.hpp"

namespace OpenGLTutorial {

	class Graphics {

	  public:
		Graphics();
		~Graphics();

		auto render() -> void;

	  private:
		GLint _vertex_shader;
		GLint _fragment_shader;
		GLint _shader_program;
		std::vector<GLfloat> _vertices;
		GLuint _vertex_buffer_object;
		GLuint _vertext_array_object;

		auto _bind_configure_vertices() -> void;
		auto _compile_shaders() -> bool;
		auto _get_shader_info_log(const GLuint shader) -> std::string;
		auto _link_shaders() -> bool;
		auto _setup_vertices() -> void;
	};

} // namespace OpenGLTutorial