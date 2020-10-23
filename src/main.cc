#include "game.h"

int main() {
  Game Simulation(20, 14);
  Simulation.Run();
  return 0;
}

//  std::string two{"2"};
//  sf::Font font;
//  if (!font.loadFromFile("../resources/DejaVuSansCondensed.ttf")) {
//// error...
//  }
//
//  sf::Text text;
//  sf::Text text2;
//  sf::Text text3;
//
//// select the font
//  text.setFont(font); // font is a sf::Font
//  text2.setFont(font); // font is a sf::Font
//  text3.setFont(font); // font is a sf::Font
//
//// set the string to display
//  text.setString(two);
//  text2.setString(two);
//  text3.setString(two);
//
//// set the character size
//  text.setCharacterSize(14); // in pixels, not points!
//  text2.setCharacterSize(14); // in pixels, not points!
//  text3.setCharacterSize(14); // in pixels, not points!
//
//  text.setPosition(6.f, 5.f);
//  text2.setPosition(33.f + 360.f, 45.f);
//  text3.setPosition(47.f + 240.f, 19.f);
//
//// set the color
//  text.setFillColor(sf::Color::Black);
//  text2.setFillColor(sf::Color::Black);
//  text3.setFillColor(sf::Color::Black);
//