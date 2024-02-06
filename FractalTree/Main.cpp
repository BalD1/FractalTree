#include <SFML/Graphics.hpp>
#include <list>
#include <cmath>

const float WIN_SIZE_X = 1600;
const float WIN_SIZE_Y = 1200;

const float LINE_BASE_SIZE_X = 5;
const float LINE_BASE_SIZE_Y = 150;
sf::RectangleShape lineShape;

sf::RenderWindow window(sf::VideoMode(WIN_SIZE_X, WIN_SIZE_Y), "Fractal Tree");

std::list<sf::RectangleShape> lines;

int fractalCount = 10;

float fractalRotation = 10;
float sizeDiff = 0.8f;

void CreateBranch(int count, float xPos, float yPos, float xSize, float ySize, float rotation)
{
    if (count == 0) return;
    count--;

    sf::RectangleShape line = sf::RectangleShape(sf::Vector2f(xSize, ySize));
    line.rotate(rotation);
    line.setPosition(xPos, yPos);
    lines.push_back(line);

    float newXR = xPos - ySize * std::sin(rotation * 3.14f / 180);
    float newYR = yPos + ySize * std::cos(rotation * 3.14f / 180);

    float newXL = xPos - ySize * std::sin(rotation * 3.14f / 180);
    float newYL = yPos + ySize * std::cos(rotation * 3.14f / 180);

    CreateBranch(count, newXR, newYR, xSize, ySize * sizeDiff, rotation + fractalRotation);
    CreateBranch(count, newXL, newYL, xSize, ySize * sizeDiff, rotation - fractalRotation);
}

void CreateTree()
{
    lines.clear();
    CreateBranch(fractalCount, WIN_SIZE_X / 2, WIN_SIZE_Y, LINE_BASE_SIZE_X, LINE_BASE_SIZE_Y, 180);
}

int main()
{
    window.setFramerateLimit(60);

    lines = std::list<sf::RectangleShape>();
    CreateTree();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::R:
                        CreateTree();
                        break;
                    case sf::Keyboard::Right:
                        fractalRotation += 1;
                        CreateTree();
                        break;
                    case sf::Keyboard::Left:
                        fractalRotation -= 1;
                        CreateTree();
                        break;
                    case sf::Keyboard::Up:
                        sizeDiff += 0.05f;
                        CreateTree();
                        break;
                    case sf::Keyboard::Down:
                        sizeDiff -= 0.05f;
                        CreateTree();
                        break;
                    case sf::Keyboard::Add:
                        fractalCount++;
                        CreateTree();
                        break;
                    case sf::Keyboard::Subtract:
                        if (fractalCount <= 0) break;
                        fractalCount--;
                        CreateTree();
                        break;
                }
            }
        }

        window.clear();
        if (lines.size() > 0)
        {
            for (auto line : lines) window.draw(line);
        }
        window.display();
    }

    return 0;
}