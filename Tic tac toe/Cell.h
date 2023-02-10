#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>

struct Cell
{
	static int numOfCheckedCells;
	std::string  type;
	sf::Vector2f pos = { 0,0 };
	sf::Vector2f boundPos = { 0,0 };
	sf::Vector2f size = { 0,0 };

	int cellIndex;
	bool isChecked = false;
	sf::RectangleShape rect;

	Cell(sf::Vector2f p_pos, sf::Vector2f p_size);
	
	sf::Texture texture;

	sf::Sprite sprite;

	void loadTexture();
	void draw();

};

