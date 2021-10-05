#pragma once

#include <iostream>
#include <unordered_map>
#include <SFML/Graphics.hpp>

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	static sf::Texture* request_texture(std::string name);
	static sf::Font* request_font(std::string name);

	static void load_textures();
	static void load_fonts();

	static void clean_up();

private:
	static void load_texture(std::string path, std::string name);
	static void load_font(std::string path, std::string name);

	static std::unordered_map<std::string, sf::Texture*> textures;
	static std::unordered_map<std::string, sf::Font*> fonts;
};

