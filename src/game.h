//
// Created by Jakub Molek on 22/10/2020.
//

#ifndef WENMAN_SRC_GAME_H_
#define WENMAN_SRC_GAME_H_

#include <TGUI/TGUI.hpp>
#include "graphical_grid.h"
#include "square.h"
#include "bunny.h"
#include "male_wolf.h"
#include "female_wolf.h"
#include <vector>


///
/// The main class of the program. Possesses methods required for creating
/// all the animals onto a square and those that aggregate their
/// movements and actions. Game's members contain the data of every single
/// animal object in appropriate vectors.
///
class Game {
 public:
  ///
  /// Vector that is passed to the GraphicalGrid object that generates
  /// graphical squares. More information about its usage in
  /// GraphicalGrid.Load()'s squares_states parameter.
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
  std::vector<Bunny> bunnies_vector {};
  /// Vector containing each Male Wolf object
  std::vector<MaleWolf> male_wolves_vector {};
  /// Vector containing each Female Wolf object
  std::vector<FemaleWolf> female_wolves_vector {};
  /// Vector containing each Square object
  std::vector<Square> squares_vector {};
  /// Vector containing indices of squares that are inside the hedge area
  std::vector<int> hedge_area_squares {};

  /// Number of horizontal squares
  int columns_;
  /// Number of vertical squares
  int rows_;
  /// Determines if a hedge (area accessible exclusively to bunnies) is present
  bool with_hedge_;

  ///
  /// This constructor loads the font file as well as the needed png files.
  /// It initializes objects for each square and sets the game's properties.
  ///
  Game(int columns,
       int rows,
       bool set_hedge,
       int hedge_size,
       int hedge_x_origin,
       int hedge_y_origin);
  /// Called when a bunny hit the 20% chance to reproduce.
  void CreateBunny(int pos);
  /// Put a wolf of random sex into the game, inheriting mother's pos. and fat.
  void CreateWolf(int pos, double fat = 1.0);
  void CreateFemaleWolf(int pos, double fat = 1.0);
  void CreateMaleWolf(int pos, double fat = 1.0);
  ///
  /// Gives each bunny a 20% chance to reproduce. If succeeded,
  /// creates a new bunny instantly. Then every bunny (except new-born ones)
  /// makes a random move and the game window is updated.
  ///
  void BunnyTurnActions(sf::RenderWindow& window);
  ///
  /// At first, the male wolves' moves are made and the squares are updated.
  /// Next the female wolves' moves and gestation-handling.
  /// After each event comes a short break.
  ///
  void WolfTurnActions(sf::RenderWindow& window);
  ///
  /// Checks each square whether the count of one animal type present therein
  /// is greater than 1. If so, writes the number next to the animal icon.
  ///
  void DrawAnimalsCount(sf::RenderWindow& window);
  /// Draws the sprites created in the constructor.
  void DrawHedge(sf::RenderWindow& window);
  ///
  /// Makes the app sleep for a given number of seconds,
  /// but keeps event polling - allowing to close the window.
  ///
  void Freeze(sf::RenderWindow& window, int n);
  /// Creates the animals that were chosen in the CLI and updates the window.
  void SetInitialState(const std::vector<int>& bunny_squares,
                       const std::vector<int>& female_wolf_squares,
                       const std::vector<int>& male_wolf_squares,
                       sf::RenderWindow& window);
  ///
  /// Initializes the game window.
  /// Receives 3 vectors of squares' indices for the animals to be created onto
  /// and passes them to SetInitialState.
  /// Keeps a loop calling wolves' and bunnies' moves alternately.
  /// Runs until the window is closed.
  ///
  void Run(const std::vector<int>& bunny_squares,
           const std::vector<int>& female_wolf_squares,
           const std::vector<int>& male_wolf_squares);
};

#endif //WENMAN_SRC_GAME_H_
