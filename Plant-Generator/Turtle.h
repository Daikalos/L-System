#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GLU.h>

#include <stack>

#include "Utilities.h"
#include "VecUtil.h"

class Turtle
{
public:
	Turtle(float steps, float angle);

	void move(float distance);
	void move_to(sf::Vector2f position);

	void turn_left(float degrees);
	void turn_right(float degrees);

	void save();
	void load();

	void interpret(std::string result);

	void draw(sf::RenderWindow* window);

private:
	sf::VertexArray tree;

	float steps, angle;

	sf::Vector2f position;
	sf::Color color;
	float direction;

	std::stack<float> save_stack;
};

