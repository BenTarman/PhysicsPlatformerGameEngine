#include "FontManager.h"



FontManager::FontManager(std::string text, std::string fontName, double x, double y)
{


    font.loadFromFile(fontName + ".ttf");
    sfml_text.setFont(font);
    sfml_text.setString(text);
    sfml_text.setPosition(x, y);
}

void FontManager::SetParameters(std::string text, std::string fontName, double x, double y)
{
    font.loadFromFile(fontName + ".ttf");
    sfml_text.setFont(font);
    sfml_text.setString(text);
    sfml_text.setPosition(x, y);




}

void FontManager::SetColor(sf::Color color)
{
    this->color = color;
    sfml_text.setColor(color);
}

sf::Text FontManager::GetText()
{

    return sfml_text;
}

sf::Font FontManager::GetFont()
{
    return font;
}