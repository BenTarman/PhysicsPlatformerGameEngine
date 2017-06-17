#pragma once




#include <SFML/Graphics.hpp>
#include <string>
#include <map>




class FontManager
{
private:

    std::map<std::string, sf::Text> texts;

    sf::Font font;
    std::string text;
    sf::Text sfml_text;

    sf::Color color;

public:
    FontManager::FontManager()
    {}
    FontManager::FontManager(std::string text, std::string fontName, double x, double y);

    void SetParameters(std::string text, std::string fontName, double x, double y);

    sf::Text GetText();

    void SetColor(sf::Color color);

    sf::Font GetFont();
};







