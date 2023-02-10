#include<iostream>

#include<SFML/Graphics.hpp>
#include<map>

#include<vector>
#include"Cell.h"

int Cell::numOfCheckedCells;

void CheckDraw()
{
    if (Cell::numOfCheckedCells < 1)
        std::cout << "Draw" << std::endl;
}



int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "My window");

    std::vector<sf::RectangleShape> lines;
    std::vector<Cell> cells;

    int cellIndex = 0;
    for (size_t i = 0; i < 3; i++)
    {

        for (size_t j = 0; j < 3; j++)
        {            
            Cell cell(sf::Vector2f( (j * window.getSize().x / 3), (i * window.getSize().y / 3) ) , sf::Vector2f(window.getSize().x / 3, window.getSize().y / 3));
           // std::cout << cell.boundPos.x<<" "<< cell.boundPos.y << std::endl;
            cell.rect.setFillColor(sf::Color((i * 20, j * 20, 0)));
            cell.cellIndex = cellIndex;
            cellIndex++;

            cells.push_back(cell);
        }

    }

    sf::RectangleShape line1;
    sf::RectangleShape line2;
    sf::RectangleShape line3;
    sf::RectangleShape line4;

    lines.push_back(line1);
    lines.push_back(line2);
    lines.push_back(line3);
    lines.push_back(line4);

    for (auto& l : lines)
    {
        l.setSize(sf::Vector2f(800, 3));
    }


    lines[0].setPosition(sf::Vector2f(0, 200));
    lines[1].setPosition(sf::Vector2f(0, 400 ));
    lines[2].setPosition(sf::Vector2f(200, 0));
    lines[3].setPosition(sf::Vector2f(400, 0));

    lines[2].setRotation(90);
    lines[3].setRotation(90);

    bool win = false;
    int X = 1;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && !win)
            {
                if (event.key.code == sf::Mouse::Left)
                {
                    std::cout << "mouse Clicked at pos (" << event.mouseButton.x<<","<<event.mouseButton.y<<")"<<std::endl;

                    auto mouseX = event.mouseButton.x;
                    auto mouseY = event.mouseButton.y;
                
                    for (auto& c : cells)
                    {                                       
                        if (c.isChecked)
                            continue;

                        if (mouseX < c.boundPos.x && mouseY < c.boundPos.y)
                        {
                            c.isChecked = true;
                           // std::cout << c.cellIndex << std::endl;
                            
                            if (X == 1)
                                c.type = "O";

                            else if (X == -1)
                                c.type = "X";

                            std::cout << c.type << std::endl;
                            X *= -1;
                            c.draw();
                            break;
                        }
                        CheckDraw();
                    }                  
                }

            }
        }

        window.clear(sf::Color::Black);

        for(auto & l : lines)
        {
            window.draw(l);
        }

        for (auto& c : cells)
        {
            window.draw(c.rect);
            window.draw(c.sprite);

        }


        window.display();
    }

    return 0;
}