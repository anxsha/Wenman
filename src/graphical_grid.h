//
// Created by Jakub Molek on 23/10/2020.
//

#ifndef WENMAN_SRC_GRAPHICAL_GRID_H_
#define WENMAN_SRC_GRAPHICAL_GRID_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
///
/// It is responsible for handling data, passed by the game,
/// representing squares' states.
/// Creates and updates a vertex array of quads, which
/// consist of graphical tiles, appropriate for each square
/// depending on animals present within their bounds.
/// The array can be then drawn to the window by calling
/// window.draw with a GraphicalGrid instance.
///
class GraphicalGrid : public sf::Drawable, public sf::Transformable {
 public:
  /// Saves the game's parameters (rows, columns, size of a tile)
  /// for later use. Initializes the vertex array to be of quad type
  /// and resizes it properly. Then runs the initial update cycle
  /// for the graphical squares.
  /// \param tileset_filename filename of the png tileset to be loaded
  /// \param tile_size vector of 2 unsigned ints, x and y dimensions
  ///        holding one tile's size in pixels
  /// \param squares_states Vector holding an eight-bit number for each square.
  ///        Only the first 3 bits are of use (remaining ones are always 0s).
  ///        Each of these 3 represents one animal type's
  ///        (bunny, female wolf, male wolf) presence on that square.
  ///        Bit 0 - bunny, bit 1 - female wolf, bit 2 - male wolf
  ///        Does not take the number of animals into account.
  ///        E.g. 0b00000011 (decimal 3) - at least one bunny and one female wolf
  ///        That number allows to choose the right graphical tile
  ///        in the png tileset.
  ///        Due to this, animal moves are handled with bit masks,
  ///        e.g. moving to a square is a bitwise OR with a 1 for that animal's
  ///        bit and if a square's counter of animals reaches 0,
  ///        bitwise AND with a 0 for that animal's bit is used.
  /// \param columns game's horizontal dimensions
  /// \param rows game's vertical dimensions
  /// \return false if the png tileset failed to load, true else
  bool Load(const std::string& tileset_filename, sf::Vector2u tile_size,
            const std::vector<uint8_t>& squares_states, int columns, int rows);
  /// Fills the vertex array with tiles.
  void Update(const std::vector<uint8_t>& squares_states);

 private:
  int columns_;
  int rows_;
  sf::Vector2u tile_size_;
  sf::VertexArray vertices_;
  sf::Texture tileset_;
  /// Enables the window.draw call to this class.
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
#endif //WENMAN_SRC_GRAPHICAL_GRID_H_