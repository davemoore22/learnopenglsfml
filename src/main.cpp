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

// OpenGL based upon: https://learnopengl.com/Getting-started/Hello-Triangle
// SFML based upon:
// https://gist.github.com/gamepopper/1931ca297f3decdee90e785f12762192
#include "main.hpp"
#include "graphics.hpp"

int main() {

	bool exit{false};
	while (!exit) {

		// Create the main window
		std::string blurb{"SFML/LearnOpenGL Tutorial #2: Hello Rectangle"};
		sf::ContextSettings cs{24};
		sf::RenderWindow window(
			sf::VideoMode(800, 600), blurb, sf::Style::Default, cs);
		window.setVerticalSyncEnabled(true);

		// Setup GLEW
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
			return EXIT_FAILURE;

		// Setup the Shaders and Vertices
		std::unique_ptr<OpenGLTutorial::Graphics> graphics =
			std::make_unique<OpenGLTutorial::Graphics>();

		// Create the SFML Background
		sf::Texture bg_texture{};
		if (!bg_texture.loadFromFile("background.jpg"))
			return EXIT_FAILURE;
		sf::Sprite bg_sprite(bg_texture);

		// Create some text to draw on top of our OpenGL object
		sf::Font font{};
		if (!font.loadFromFile("sansation.ttf"))
			return EXIT_FAILURE;
		sf::Text fg_text(blurb, font);
		fg_text.setFillColor(sf::Color(255, 255, 255, 170));
		fg_text.setPosition(100.f, 450.f);

		// Make the window no longer the active window for OpenGL calls
		window.setActive(false);

		// Start the main loop
		sf::Event event{};
		while (window.isOpen()) {

			// Process events
			while (window.pollEvent(event)) {

				// Close Window
				if (event.type == sf::Event::Closed) {
					exit = true;
					window.close();
				}

				// Escape to Exit
				if ((event.type == sf::Event::KeyPressed) &&
					(event.key.code == sf::Keyboard::Escape)) {
					exit = true;
					window.close();
				}

				// Adjust the viewport when the window is resized
				if (event.type == sf::Event::Resized) {

					// Make the window the active window for OpenGL calls
					window.setActive(true);
					glViewport(0, 0, event.size.width, event.size.height);

					// Make the window no longer the active window for
					// OpenGL calls
					window.setActive(false);
				}
			}

			// Clear the depth buffer
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Configure the viewport (the same size as the window)
			glViewport(0, 0, window.getSize().x, window.getSize().y);

			// Draw the background
			window.pushGLStates();
			window.draw(bg_sprite);
			window.popGLStates();

			// Make the window the active window for OpenGL calls
			window.setActive(true);

			// Draw the Open GL Stuff
			graphics->render();

			// Reset Open GL Stuff
			glBindVertexArray(0);
			glUseProgram(0);
			glBindTexture(GL_TEXTURE_2D, 0);

			// Make the window no longer the active window for OpenGL calls
			window.setActive(false);

			// Draw some text on top of our OpenGL object
			window.pushGLStates();
			window.draw(fg_text);
			window.popGLStates();

			// Finally, display the rendered frame on screen
			window.display();
		}
	}

	return EXIT_SUCCESS;
}