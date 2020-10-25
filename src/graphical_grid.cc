//
// Created by Jakub Molek on 23/10/2020.
//

#include "graphical_grid.h"

bool GraphicalGrid::Load(const std::string &tileset_filename,
                         sf::Vector2u tile_size,
                         std::vector<uint8_t> tiles,
                         int width,
                         int height) {
  // load the tileset texture
  if (!tileset_.loadFromFile(tileset_filename)) return false;

  width_ = width;
  height_ = height;
  tile_size_ = tile_size;

  // resize the vertex array to fit the level size
  vertices_.setPrimitiveType(sf::Quads);
  vertices_.resize(width * height * 4);

  // populate the vertex array, with one quad per tile
  for (int i = 0; i < width; ++i) {
    for (int j = 0; j < height; ++j) {
      // get the current tile number
      int tile_number = tiles[i + j * width];

      // find its position in the tileset texture
      int tu = tile_number % (tileset_.getSize().x / tile_size.x);
      int tv = tile_number / (tileset_.getSize().x / tile_size.x);

      // get a pointer to the current tile's quad
      sf::Vertex *quad = &vertices_[(i + j * width) * 4];

      // define its 4 corners
      quad[0].position = sf::Vector2f(i * tile_size.x, j * tile_size.y);
      quad[1].position = sf::Vector2f((i + 1) * tile_size.x, j * tile_size.y);
      quad[2].position = sf::Vector2f((i + 1) * tile_size.x, (j + 1) * tile_size.y);
      quad[3].position = sf::Vector2f(i * tile_size.x, (j + 1) * tile_size.y);

      // define its 4 texture coordinates
      quad[0].texCoords = sf::Vector2f(tu * tile_size.x, tv * tile_size.y);
      quad[1].texCoords = sf::Vector2f((tu + 1) * tile_size.x, tv * tile_size.y);
      quad[2].texCoords = sf::Vector2f((tu + 1) * tile_size.x, (tv + 1) * tile_size.y);
      quad[3].texCoords = sf::Vector2f(tu * tile_size.x, (tv + 1) * tile_size.y);
    }
  }

  return true;
}
void GraphicalGrid::Update(std::vector<uint8_t> tiles) {

  // populate the vertex array, with one quad per tile
  for (int i = 0; i < width_; ++i) {
    for (int j = 0; j < height_; ++j) {
      // get the current tile number
      int tile_number = tiles[i + j * width_];

      // find its position in the tileset texture
      int tu = tile_number % (tileset_.getSize().x / tile_size_.x);
      int tv = tile_number / (tileset_.getSize().x / tile_size_.x);

      // get a pointer to the current tile's quad
      sf::Vertex *quad = &vertices_[(i + j * width_) * 4];

      // define its 4 corners
      quad[0].position = sf::Vector2f(i * tile_size_.x, j * tile_size_.y);
      quad[1].position = sf::Vector2f((i + 1) * tile_size_.x, j * tile_size_.y);
      quad[2].position = sf::Vector2f((i + 1) * tile_size_.x, (j + 1) * tile_size_.y);
      quad[3].position = sf::Vector2f(i * tile_size_.x, (j + 1) * tile_size_.y);

      // define its 4 texture coordinates
      quad[0].texCoords = sf::Vector2f(tu * tile_size_.x, tv * tile_size_.y);
      quad[1].texCoords = sf::Vector2f((tu + 1) * tile_size_.x, tv * tile_size_.y);
      quad[2].texCoords = sf::Vector2f((tu + 1) * tile_size_.x, (tv + 1) * tile_size_.y);
      quad[3].texCoords = sf::Vector2f(tu * tile_size_.x, (tv + 1) * tile_size_.y);
    }
  }
}
void GraphicalGrid::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  // apply the transform
  states.transform *= getTransform();

  // apply the tileset texture
  states.texture = &tileset_;

  // draw the vertex array
  target.draw(vertices_, states);
}
