//
// Created by Jakub Molek on 22/10/2020.
//

#ifndef WENMAN_SRC_GAME_H_
#define WENMAN_SRC_GAME_H_

#include <vector>

#include <SFML/Graphics.hpp>

#include "graphical_grid.h"
#include "animals.h"

///
/// Every object of this class contains information about one assigned
/// graphical square. It is the source, based on which graphical grid is
/// generated.
///
class Square {
 public:
  /// Returns the number of bunnies that occupy this square.
  [[nodiscard]] int Bunnies() const;
  /// Returns the number of male wolves that occupy this square.
  [[nodiscard]] int MaleWolves() const;
  /// Returns the number of female wolves that occupy this square.
  [[nodiscard]] int FemaleWolves() const;
  /// Returns the index of this square in Game's square vector that contains them all.
  [[nodiscard]] int VectorIndex() const;
  /// Increments the number of bunnies on this square.
  void AddBunny();
  /// Decrements the number of bunnies on this square.
  void RemoveBunny();
  /// Increments the number of female wolves on this square.
  void AddFemaleWolf();
  /// Decrements the number of female wolves on this square.
  void RemoveFemaleWolf();
  /// Increments the number of male wolves on this square.
  void AddMaleWolf();
  /// Decrements the number of male wolves on this square.
  void RemoveMaleWolf();
  ///
  /// The constructor sets the number of all animals on this square to 0.
  /// Receives the Game's vector which consists of all squares as a parameter to identify
  /// its index therein.
  ///
  explicit Square(std::vector<Square>& v);

 private:
  int bunnies_;   ///< Number of Bunnies present on that square
  int male_wolves_;   ///< Number of male wolves present on that square
  int female_wolves_;   ///< Number of female wolves present on that square
  int vector_index_;    ///< Number identifying that square's index in the game's grid vector

};

///
/// The main class of the program. Possesses methods required for creating all
/// the animals onto a square and those that aggregate their movements and actions.
/// Game's members contain the data of every single animal object in appropriate vectors.
///
class Game {
 public:
  ///
  /// Vector that is passed to the GraphicalGrid object that generates graphical squares.
  /// More information about its usage in GraphicalGrid.Load()'s tiles parameter.
  ///
  std::vector<uint8_t> map_tiles;
  /// Font file loaded in the constructor.
  sf::Font font;

  /// PNG image of top/bottom parts of hedge
  sf::Image hedge_horizontal;
  /// Texture for top/bottom parts of hedge
  sf::Texture hedge_h_texture;
  /// PNG image of left/right parts of hedge
  sf::Image hedge_vertical;
  /// Texture for left/right parts of hedge
  sf::Texture hedge_v_texture;
  /// Vector containing sprites of the top part of hedge
  std::vector<sf::Sprite> hedge_top_sprites;
  /// Vector containing sprites of the bottom part of hedge
  std::vector<sf::Sprite> hedge_bottom_sprites;
  /// Vector containing sprites of the left part of hedge
  std::vector<sf::Sprite> hedge_left_sprites;
  /// Vector containing sprites of the right part of hedge
  std::vector<sf::Sprite> hedge_right_sprites;
  /// GraphicalGrid instance. More in GraphicalGrid.
  GraphicalGrid square_map;

  /// Vector containing each Bunny object
  std::vector<Bunny> bunnies_vector{};
  /// Vector containing each Male Wolf object
  std::vector<MaleWolf> male_wolves_vector{};
  /// Vector containing each Female Wolf object
  std::vector<FemaleWolf> female_wolves_vector{};
  /// Vector containing each Square object
  std::vector<Square> squares_vector{};
  /// Vector containing indices of squares that are inside the hedge area
  std::vector<int> hedge_area_squares {};

  /// Number of horizontal squares
  int columns_;
  /// Number of vertical squares
  int rows_;
  /// Determines if a hedge - area accessible exclusively to bunnies - is present
  bool with_hedge;

  ///
  /// This constructor loads the font file as well as the png file that contains all
  /// possible tiles. It initializes objects for each square
  ///
  ///
  Game(int columns, int rows, bool set_hedge = false, int hedge_size = 6, int hedge_x_origin = 5, int hedge_y_origin = 5);
  void CreateBunny(int pos);
  void CreateWolf(int pos, double fat = 1.0);
  void BunnyTurnActions(sf::RenderWindow& window);
  void WolfTurnActions(sf::RenderWindow& window);
  void DrawAnimalsCount(sf::RenderWindow& window);
  void Drawhedge(sf::RenderWindow& window);
  void SetInitialState();
  void Freeze(sf::RenderWindow& window, int n);
  void Run();
};

#endif //WENMAN_SRC_GAME_H_
