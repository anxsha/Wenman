//
// Created by Jakub Molek on 23/10/2020.
//

#include "graphical_grid.h"

bool GraphicalGrid::Load(const std::string& tileset_filename,
                         sf::Vector2u tile_size,
                         const std::vector<uint8_t>& squares_states,
                         int columns,
                         int rows) {
  // load the png file with possible square squares_states
  if (!tileset_.loadFromFile(tileset_filename)) { return false; }

  columns_ = columns;
  rows_ = rows;
  tile_size_ = tile_size;

  // set the size of the vertex array to hold data for every square
  vertices_.setPrimitiveType(sf::Quads);
  vertices_.resize(columns * rows * 4);
  Update(squares_states);
  return true;
}
void GraphicalGrid::Update(const std::vector<uint8_t>& squares_states) {
  // iterate every square and set its quad to represent the appropriate tile
  for (int i = 0; i < columns_; ++i) {
    for (int j = 0; j < rows_; ++j) {
      // the state of the square indicates which tile from the png
      // needs to be chosen
      int tile_number = squares_states[j * columns_ + i];
      // get a pointer to the current tile's quad
      sf::Vertex* quad = &vertices_[(i + j * columns_) * 4];
      // set its 4 corners on the grid
      quad[0].position = sf::Vector2f(i * tile_size_.x, j * tile_size_.y);
      quad[1].position = sf::Vector2f((i + 1) * tile_size_.x, j * tile_size_.y);
      quad[2].position = sf::Vector2f((i + 1) * tile_size_.x, (j + 1) * tile_size_.y);
      quad[3].position = sf::Vector2f(i * tile_size_.x, (j + 1) * tile_size_.y);
      // set its 4 corners inside the tileset texture
      quad[0].texCoords = sf::Vector2f(tile_number * tile_size_.x, 0);
      quad[1].texCoords = sf::Vector2f((tile_number + 1) * tile_size_.x, 0);
      quad[2].texCoords = sf::Vector2f((tile_number + 1) * tile_size_.x, tile_size_.y);
      quad[3].texCoords = sf::Vector2f(tile_number * tile_size_.x, tile_size_.y);
    }
  }
}
void GraphicalGrid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  states.texture = &tileset_;
  target.draw(vertices_, states);
}