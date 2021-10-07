#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GLU.h>

#include <vector>
#include <regex>

#include "Utilities.h"

struct Rule
{
public:
	Rule(std::string variable, std::string rule, float probability = 1.0f)
		: variable(variable), rule(rule) {}

	std::string variable;
	std::string rule;
};

class LSystem
{
public:
	LSystem(std::string);
	LSystem(std::vector<std::string>);
	LSystem(std::string, std::vector<std::string>);

	~LSystem();

	void add_rule(std::string rule);
	void set_axiom(std::string& axiom);

	void iterate(int iterations = 1);

	inline std::string get_axiom() const { return axiom; }
	inline std::vector<Rule> get_rules() { return rules; }
	inline int get_iterations() const { return current_iterations; }

	inline std::string get_result() const { return state; }

private:
	void extract_rule(std::string r);

private:
	std::string axiom, state;
	std::vector<Rule> rules;

	int current_iterations;

	LSystem() = delete;
	LSystem(const LSystem& rhs) = delete;
	LSystem& operator=(const LSystem& rhs) = delete;
};

