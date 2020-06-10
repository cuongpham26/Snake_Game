#include <iostream>
#include <conio.h>
#include <windows.h>
#include "Coordinate.h"

bool gameOver = false;
constexpr int width = 20, height = 20;
int score, totalTail, level = 5;
Coordinate snakeHead(width/2, height/2), fruit(width/level, height/level), tail[(width - 2)*(height - 2)];
enum class Direction {STOP, LEFT, RIGHT, UP, DOWN} direction;
std::string error;

void Print()
{
    for(int cursorX = 1; cursorX <= width; ++cursorX)
    {
        std::cout << ".";
    }
    std::cout << std::endl;
    for(int cursorY = 2; cursorY < height; ++cursorY)
    {
        for(int cursorX = 1; cursorX <= width; ++cursorX)
        {
            if(cursorX == 1 || cursorX == width)
            {
                std::cout << ".";
            }
            else if(snakeHead == Coordinate(cursorX, cursorY))
            {
                std::cout << "O";
            }
            else if(fruit == Coordinate(cursorX, cursorY))
            {
                std::cout << "F";
            }
            else
            {
                bool hasPrintTail = false;
                for(int tailNum = 1; tailNum <= totalTail; ++tailNum)
                {
                    if(tail[tailNum] == Coordinate(cursorX, cursorY))
                    {
                        hasPrintTail = true;
                        std::cout << "o";
                    }
                }
                if(!hasPrintTail)
                    std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
    for(int cursorX = 1; cursorX <= width; ++cursorX)
    {
        std::cout << ".";
    }
    std::cout << "\n\nLevel: " << level;
    std::cout << "\nScore: " << score;
    std::cout << "\nSnake length: " << totalTail + 1;
}

void Input()
{
    if(_kbhit())
    {
        switch(_getch())
        {
        case 'a':
            if(totalTail == 0 || direction != Direction::RIGHT)
            {
                direction = Direction::LEFT;
                break;
            }
        case 'd':
            if(totalTail == 0 || direction != Direction::LEFT)
            {
                direction = Direction::RIGHT;
                break;
            }
        case 'w':
            if(totalTail == 0 || direction != Direction::DOWN)
            {
                direction = Direction::UP;
                break;
            }
        case 's':
            if(totalTail == 0 || direction != Direction::UP)
            {
                direction = Direction::DOWN;
                break;
            }
        }
    }
}

void Logic()
{
    if(snakeHead.getX() == 1 || snakeHead.getX() == width || snakeHead.getY() == 1 || snakeHead.getY() == height)
    {
        gameOver = true;
        error = "You hit the wall";
        return;
    }
    for(int tailNum = 1; tailNum < totalTail; ++tailNum)
    {
        if(snakeHead == tail[tailNum])
        {
            gameOver = true;
            error = "You ate your own tail";
            return;
        }
    }

    for(int i = totalTail; i >= 2; --i)
    {
        tail[i] = tail[i-1];
    }
    tail[1] = snakeHead;

    switch(direction)
    {
    case Direction::LEFT:
        --snakeHead.getX();
        break;
    case Direction::RIGHT:
        ++snakeHead.getX();
        break;
    case Direction::UP:
        --snakeHead.getY();
        break;
    case Direction::DOWN:
        ++snakeHead.getY();
        break;
    }
    if(snakeHead == fruit)
    {
        ++totalTail;
        score += 10;
        do{
            fruit.setPoint(rand() % width, rand() % height);
        }while(fruit.getX() < 3 || fruit.getX() == (width - 1)  || fruit.getY() < 3 || (fruit.getY() == height-1));
    }

}

int ask_level()
{
    int num;
    std::cout << "Enter the level of difficulty (0 to 10): ";
    while(true)
    {
        std::cin >> num;
        if(std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(12345, '\n');
            std::cout << "Enter a number, not a string\nRe-enter: ";
            continue;
        }
        if(std::cin.get() != '\n' || num < 0 || num > 10 || int(num) != num)
        {
            std::cout << "Invalid input\nRe-enter: ";
            continue;
        }
        break;
    }
    return num;
}

int main()
{
    level = ask_level();
    char c;
    while(!gameOver)
    {
        system("cls");
        Print();
        Input();
        Logic();
        Sleep(150 - level*15);
    }
    std::cout << "\n\n" << error << "\nGame over!";
    std::cin.get();
}
