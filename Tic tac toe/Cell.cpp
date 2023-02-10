
#include"Cell.h"

void Cell::loadTexture()
{	

	if (!texture.loadFromFile("Assets/"+type+".png"))
	{
		std::cout << "Failed to load Texture" << std::endl;
	}
}




void Cell::draw()
{
	loadTexture();

	sprite.setTexture(texture);
	sprite.setScale(0.1, 0.1);

	sf::Vector2f spritePos(rect.getPosition());

	spritePos.x +=  rect.getLocalBounds().width*0.4f;
	spritePos.y += rect.getLocalBounds().height*0.4f;

	sprite.setPosition(spritePos);
	//std::cout << sprite.getPosition().x << sprite.getPosition().y << std::endl;

	numOfCheckedCells--;
}

Cell::Cell(sf::Vector2f p_pos, sf::Vector2f p_size)
	:pos(p_pos),size(p_size),boundPos(p_pos)
{
	rect.setSize(size);
	rect.setPosition(pos);

	boundPos.x += rect.getLocalBounds().left + rect.getLocalBounds().width;
	boundPos.y += rect.getLocalBounds().width;

	numOfCheckedCells ++;

	type = " ";
}
