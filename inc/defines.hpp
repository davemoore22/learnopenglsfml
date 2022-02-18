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

#include <string>

// Shaders defined here
namespace OpenGLTutorial {

	namespace Shaders {

		const std::string vertex_shader_source{
			"#version 330 core\n"
			"layout (location = 0) in vec3 aPos;"
			"void main() {"
			"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);"
			"}"};
		const std::string fragment_shader_source{
			"#version 330 core\n"
			"out vec4 FragColor;"
			"void main() {"
			"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
			"}"};

	} // namespace Shaders

} // namespace OpenGLTutorial