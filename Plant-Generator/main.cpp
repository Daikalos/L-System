#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GLU.h>

#include <functional>

#include "ResourceManager.h"
#include "Camera.h"
#include "InputHandler.h"

#include "LSystem.h"
#include "Turtle.h"

int main()
{
	srand((unsigned int)time(NULL));

	sf::RenderWindow window(sf::VideoMode(2240, 1260), "plants");
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

	LSystem lsystem("F", { "F=F[+F]F[-F][F]" });

	Turtle turtle(15.0f, 20.0f);

	sf::Text infoText;
	infoText.setFont(font);
	infoText.setString("f to begin");

	std::string info;

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

		if (inputHandler.key_pressed(sf::Keyboard::Key::F))
		{
			lsystem.iterate();
			turtle.interpret(lsystem.get_result());

			std::string ruleInfo;
			for (int i = 0; i < lsystem.get_rules().size(); ++i)
			{
				ruleInfo += 
					" " + lsystem.get_rules().at(i).variable + 
					" = " + lsystem.get_rules().at(i).rule + '\n';
			}

			info =
				"Iterations: " + std::to_string(lsystem.get_iterations()) + '\n' +
				"Axiom: " + lsystem.get_axiom() + '\n' +
				"Rules:" + '\n' + ruleInfo;

			infoText.setString(info);
		}

		infoText.setPosition(camera.view_to_world(sf::Vector2f(10, 10)));
		infoText.setScale(1.0f / camera.get_scale(), 1.0f / camera.get_scale());

		window.setView(camera.get_view());

		window.clear();

		turtle.draw(&window);

		window.draw(infoText);

		window.display();
	}

	ResourceManager::clean_up();

	return 0;
}