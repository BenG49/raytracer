#pragma once

#include "SFML/Graphics.hpp"

class FPSCounter
{
public:
    FPSCounter()
    {
        if (!font.loadFromFile("CascadiaCode.ttf"))
            throw -1;
        
        text.setFont(font);
        text.setPosition({ 5, 5 });
        text.setFillColor(sf::Color::Black);
        text.setCharacterSize(14);
    }

    void update()
    {
        ++frameCount;

        // 0.2 is magic !
        if (timer.getElapsedTime().asSeconds() > 0.2)
        {
            fps = frameCount / timer.restart().asSeconds();
            frameCount = 0;
        }
    }

    void render(sf::RenderTarget &win)
    {
        text.setString("FPS: "+std::to_string(fps));
        win.draw(text);
    }

private:
    sf::Font font;
    sf::Text text;
    sf::Clock timer;

    int fps;
    int frameCount;
};