#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GLU.h>

#include "ResourceManager.h"
#include "Camera.h"
#include "InputHandler.h"

int main()
{
	srand((unsigned int)time(NULL));

	sf::RenderWindow window(sf::VideoMode(2240, 1260), "dungeon-rooms");
	window.setActive(true);

	ResourceManager::load_textures();
	ResourceManager::load_fonts();

	sf::Font font = *ResourceManager::request_font("8bit");

	Camera camera(window);
	InputHandler inputHandler;

	sf::Clock clock;
	float deltaTime = FLT_EPSILON;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glScalef(1.0f, -1.0f, 1.0f);
	gluOrtho2D(0, window.getSize().x, 0, window.getSize().y);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		inputHandler.update();

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				glViewport(0, 0, window.getSize().x, window.getSize().y);
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				glScalef(1.0f, -1.0f, 1.0f);
				gluOrtho2D(0, window.getSize().x, 0, window.getSize().y);
				glMatrixMode(GL_MODELVIEW);
				break;
			case sf::Event::MouseWheelScrolled:
				inputHandler.set_scrollDelta(event.mouseWheelScroll.delta);
				break;
			}
		}

		

		camera.update(inputHandler);

		window.setView(camera.get_view());

		window.clear();

		

		window.display();
	}

	ResourceManager::clean_up();

	return 0;
}