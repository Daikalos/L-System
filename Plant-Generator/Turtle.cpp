#include "Turtle.h"

Turtle::Turtle(float steps, float angle)
	: steps(steps), angle(angle)
{
	position = sf::Vector2f(0, 0);
	direction = util::to_radians(-90.0f);

	tree.setPrimitiveType(sf::Lines);
	tree.clear();
}

void Turtle::interpret(std::string result)
{
	position = sf::Vector2f(0, 0);
	direction = util::to_radians(-90.0f);

	tree.clear();

	for (int i = 0; i < result.size(); ++i)
	{
		char c = result[i];
		switch (c)
		{
		case '+':
			turn_left(angle);
			break;
		case '-':
			turn_right(angle);
			break;
		case '[':
			save();
			break;
		case ']':
			load();
			break;
		default:
			if (c != ' ')
				move(steps);
			break;
		}
	}
}

void Turtle::move(float distance)
{
	sf::Vector2f temp_position = position;

	position.x += distance * cosf(direction);
	position.y += distance * sinf(direction);

	sf::Vertex 
		vertex_from(temp_position, sf::Color::Green), 
		vertex_to(position, sf::Color::Green);

	tree.append(vertex_from);
	tree.append(vertex_to);
}

void Turtle::move_to(sf::Vector2f position)
{
	this->position = position;
}

void Turtle::turn_left(float degrees)
{
	direction += util::to_radians(degrees);
}
void Turtle::turn_right(float degrees)
{
	direction -= util::to_radians(degrees);
}

void Turtle::save()
{
	save_stack.push(position.x);
	save_stack.push(position.y);
	save_stack.push(direction);
}
void Turtle::load()
{
	direction = save_stack.top();
	save_stack.pop();
	position.y = save_stack.top();
	save_stack.pop();
	position.x = save_stack.top();
	save_stack.pop();
}

void Turtle::draw(sf::RenderWindow* window)
{
	window->draw(tree);
}
