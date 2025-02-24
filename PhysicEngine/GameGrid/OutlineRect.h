#pragma once
#include <SFML/Graphics.hpp>

class OutlineRectangle : public sf::Drawable {
private:
    sf::Vertex vertices[5];

public:
    OutlineRectangle(float width, float height, const sf::Vector2f& position, const sf::Color& color = sf::Color::White) {
        // Define the 4 corners of the rectangle
        vertices[0].position = position;                          // top-left
        vertices[1].position = position + sf::Vector2f(width, 0); // top-right
        vertices[2].position = position + sf::Vector2f(width, height); // bottom-right
        vertices[3].position = position + sf::Vector2f(0, height); // bottom-left
        vertices[4].position = position;                          // top-left again to close the loop

        for (int i = 0; i < 5; ++i) {
            vertices[i].color = color;
        }
    }

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(vertices, 5, sf::LinesStrip, states);
    }
};
