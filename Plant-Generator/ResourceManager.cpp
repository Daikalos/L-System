#include "ResourceManager.h"

std::unordered_map<std::string, sf::Texture*> ResourceManager::textures;
std::unordered_map<std::string, sf::Font*> ResourceManager::fonts;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	clean_up();
}

sf::Texture* ResourceManager::request_texture(std::string name)
{
	return textures[name];
}

sf::Font* ResourceManager::request_font(std::string name)
{
	return fonts[name];
}

void ResourceManager::load_textures()
{
	std::string path;

	path = "content/textures/empty.png";
	load_texture(path, "empty");

	path = "content/textures/wall.png";
	load_texture(path, "wall");

	path = "content/textures/chest.png";
	load_texture(path, "chest");

	path = "content/textures/item.png";
	load_texture(path, "item");

	path = "content/textures/monster.png";
	load_texture(path, "monster");

	path = "content/textures/entrance.png";
	load_texture(path, "entrance");

	path = "content/textures/exit.png";
	load_texture(path, "exit");
}
void ResourceManager::load_fonts()
{
	std::string path;

	path = "content/fonts/font_8bit.ttf";
	load_font(path, "8bit");
}

void ResourceManager::clean_up()
{
	for (std::unordered_map<std::string, sf::Texture*>::iterator itr = textures.begin(); itr != textures.end(); ++itr)
		delete itr->second;
	for (std::unordered_map<std::string, sf::Font*>::iterator itr = fonts.begin(); itr != fonts.end(); ++itr)
		delete itr->second;

	textures.clear();
	fonts.clear();
}

void ResourceManager::load_texture(std::string path, std::string name)
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(path);

	textures[name] = texture;
}
void ResourceManager::load_font(std::string path, std::string name)
{
	sf::Font* font = new sf::Font();
	font->loadFromFile(path);

	fonts[name] = font;
}
