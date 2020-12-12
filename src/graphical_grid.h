//
// Created by Jakub Molek on 23/10/2020.
//

#ifndef WENMAN_SRC_GRAPHICAL_GRID_H_
#define WENMAN_SRC_GRAPHICAL_GRID_H_

#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

class GraphicalGrid : public sf::Drawable, public sf::Transformable {
 public:
  bool Load(const std::string& tileset_filename, sf::Vector2u tile_size,
            std::vector<uint8_t> tiles, int width, int height);

  void Update(std::vector<uint8_t> tiles);

 private:
  int width_;
  int height_;
  sf::Vector2u tile_size_;
  sf::VertexArray vertices_;
  sf::Texture tileset_;

  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

};

#endif //WENMAN_SRC_GRAPHICAL_GRID_H_