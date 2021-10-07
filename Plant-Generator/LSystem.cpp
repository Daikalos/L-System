#include "LSystem.h"

LSystem::LSystem(std::string axiom) : state(axiom) 
{ 
	this->axiom = axiom;
	current_iterations = 0;
}
LSystem::LSystem(std::vector<std::string> rules)
{ 
	current_iterations = 0; 

	for (const std::string& r : rules)
		extract_rule(r);
}
LSystem::LSystem(std::string axiom, std::vector<std::string> rules) : state(axiom)
{ 
	this->axiom = axiom;
	current_iterations = 0; 

	for (const std::string& r : rules)
		extract_rule(r);
}

LSystem::~LSystem()
{

}

void LSystem::extract_rule(std::string r)
{
	std::string variable;
	std::string rule;
	float probability;

	int pos1 = r.find("=");

	variable = r.substr(0, pos1);
	rule = r.substr(pos1 + 1, r.size() - pos1 - 1);

	rules.emplace_back(variable, rule);
}

void LSystem::add_rule(std::string rule)
{
	extract_rule(rule);
}
void LSystem::set_axiom(std::string& axiom)
{
	this->axiom = state = axiom;
}

void LSystem::iterate(int iterations)
{
	for (int i = 0; i < iterations; ++i)
	{
		std::string new_state;

		for (int j = 0; j < state.size(); ++j)
		{
			std::string current(1, state[j]);

			for (const Rule& r : rules)
			{
				if (r.variable == current)
				{
					current = r.rule;
					break;
				}
			}

			new_state += current;
		}

		state = new_state;

		++current_iterations;
	}
}

