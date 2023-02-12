#include<iostream>

#include<SFML/Graphics.hpp>
#include<map>

#include<vector>
#include"Cell.h"

int Cell::numOfCheckedCells;
bool win = false;

bool CheckDraw()
{
    if (Cell::numOfCheckedCells < 1)
    {
        std::cout << "Draw" << std::endl;
        return true;
    }
    
  
}
void ChangeToWinColor(Cell &c1,Cell &c2,Cell &c3)
{
    sf::Color winColor = sf::Color(34, 139, 34);

    c1.rect.setFillColor(winColor);
    c2.rect.setFillColor(winColor);
    c3.rect.setFillColor(winColor);

}
void CheckWinningCells(int index1, int index2, int index3,std::vector<int> &typeOfCell, std::vector<Cell>& cells)
{
    if (typeOfCell[index1] == -1 && typeOfCell[index2] == -1 && typeOfCell[index3] == -1)
    {
        ChangeToWinColor(cells[index1], cells[index2], cells[index3]);
        win = true;
    }

    else if (typeOfCell[index1] == 1 && typeOfCell[index2] == 1 && typeOfCell[index3] == 1)
    {
        ChangeToWinColor(cells[index1], cells[index2], cells[index3]);
        win = true;

    }
}

void CheckWin(std::vector<int> & typeOfCell,std::vector<Cell> &cells)
{
    //first three rows
    CheckWinningCells(0, 1, 2, typeOfCell, cells);
    CheckWinningCells(3, 4, 5, typeOfCell, cells);
    CheckWinningCells(6, 7, 8, typeOfCell, cells);

    CheckWinningCells(0, 3, 6, typeOfCell, cells);
    CheckWinningCells(1, 4, 7, typeOfCell, cells);
    CheckWinningCells(2, 5, 8, typeOfCell, cells);

    CheckWinningCells(0, 4, 8, typeOfCell, cells);
    CheckWinningCells(2, 4, 6, typeOfCell, cells);
    
}

int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "My window");

    std::vector<sf::RectangleShape> lines;
    std::vector<int> typeOfCell;
    for (size_t i = 0; i < 9; i++)
    {
        bool x = 0;
        typeOfCell.push_back(x);
    }

    std::vector<Cell> cells;

    int cellIndex = 0;
    for (size_t i = 0; i < 3; i++)
    {

        for (size_t j = 0; j < 3; j++)
        {            
            Cell cell(sf::Vector2f( (j * window.getSize().x / 3), (i * window.getSize().y / 3) ) , sf::Vector2f(window.getSize().x / 3 , window.getSize().y / 3));
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
        l.setSize(sf::Vector2f(5000, 3));
    }


    lines[0].setPosition(sf::Vector2f(0,  window.getSize().y / 3));
    lines[1].setPosition(sf::Vector2f(0, window.getSize().y / 1.5));
    lines[2].setPosition(sf::Vector2f(window.getSize().x / 3, 0));
    lines[3].setPosition(sf::Vector2f(window.getSize().x / 1.5, 0));

    lines[2].setRotation(90);
    lines[3].setRotation(90);

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
                        if(win)
                            break;
                        if (c.isChecked)
                            continue;

                        if (mouseX < c.boundPos.x && mouseY < c.boundPos.y)
                        {
                            c.isChecked = true;
                           std::cout << mouseX <<" "<< c.boundPos.x  <<" " << mouseY <<" " << c.boundPos.y << std::endl;
                            
                            if (X == -1)
                            {
                                c.type = "X";
                                typeOfCell[c.cellIndex] = -1;
                            }
                            else if (X == 1) 
                            {
                                c.type = "O";
                                typeOfCell[c.cellIndex] = 1;

                            }

                           

                            std::cout << c.type << std::endl;
                            X *= -1;
                            c.draw();
                            CheckWin(typeOfCell, cells);

                            if (CheckDraw())
                                break;
                            break;
                        }
                        
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