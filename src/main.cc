#include "game.h"

int main() {
  int cols{};
  int rows{};
  bool with_hedge = false;
  int hedge_size{};
  int hedge_x_origin{};
  int hedge_y_origin{};
  std::vector<int> bunny_squares {};
  std::vector<int> female_wolf_squares {};
  std::vector<int> male_wolf_squares {};

  sf::RenderWindow window(sf::VideoMode(480, 320), "Wenman");
  window.setFramerateLimit(25);
  tgui::Theme theme{"../resources/themes/TransparentGrey.txt"};
  tgui::Gui gui(window);
  gui.add(tgui::Picture::create("../resources/island.jpg"));

  auto hedge_checkbox = tgui::CheckBox::create();
  hedge_checkbox->setRenderer(theme.getRenderer("CheckBox"));
  hedge_checkbox->setPosition(25, window.getSize().y / 2 - 125);
  hedge_checkbox->setText("With hedge");
  hedge_checkbox->setSize(25, 25);
  gui.add(hedge_checkbox);

  auto columns_slider = tgui::Slider::create();
  columns_slider->setRenderer(theme.getRenderer("Slider"));
  columns_slider->setPosition(25, window.getSize().y / 2 - 50);
  columns_slider->setSize(150, 20);
  columns_slider->setValue(8);
  columns_slider->setMinimum(6);
  columns_slider->setMaximum(14);
  gui.add(columns_slider);

  auto rows_slider = tgui::Slider::create();
  rows_slider->setRenderer(theme.getRenderer("Slider"));
  rows_slider->setPosition(25, window.getSize().y / 2 + 25);
  rows_slider->setSize(150, 20);
  rows_slider->setValue(8);
  rows_slider->setMinimum(6);
  rows_slider->setMaximum(17);
  gui.add(rows_slider);

  auto hedge_size_slider = tgui::Slider::create();
  hedge_size_slider->setRenderer(theme.getRenderer("Slider"));
  hedge_size_slider->setPosition(window.getSize().x - 175, window.getSize().y / 2 + -125);
  hedge_size_slider->setSize(150, 20);
  hedge_size_slider->setValue(1);
  hedge_size_slider->setMinimum(1);
  hedge_size_slider->setMaximum(std::min({columns_slider->getValue(), rows_slider->getValue()}));
  gui.add(hedge_size_slider);

  auto hedge_x_origin_slider = tgui::Slider::create();
  hedge_x_origin_slider->setRenderer(theme.getRenderer("Slider"));
  hedge_x_origin_slider->setPosition(window.getSize().x - 175, window.getSize().y / 2 - 50);
  hedge_x_origin_slider->setSize(150, 20);
  hedge_x_origin_slider->setValue(1);
  hedge_x_origin_slider->setMinimum(1);
  hedge_x_origin_slider->setMaximum(columns_slider->getValue() - hedge_size_slider->getValue() + 1);
  gui.add(hedge_x_origin_slider);

  auto hedge_y_origin_slider = tgui::Slider::create();
  hedge_y_origin_slider->setRenderer(theme.getRenderer("Slider"));
  hedge_y_origin_slider->setPosition(window.getSize().x - 175, window.getSize().y / 2 + 25);
  hedge_y_origin_slider->setSize(150, 20);
  hedge_y_origin_slider->setValue(1);
  hedge_y_origin_slider->setMinimum(1);
  hedge_y_origin_slider->setMaximum(rows_slider->getValue() - hedge_size_slider->getValue() + 1);
  gui.add(hedge_y_origin_slider);

  auto columns_value_label = tgui::Label::create();
  columns_value_label->setRenderer(theme.getRenderer("Label"));
  columns_value_label->setText(std::to_string(int(columns_slider->getValue())));
  columns_value_label->setPosition(87.5, window.getSize().y / 2 - 20);
  columns_value_label->setTextSize(18);
  gui.add(columns_value_label);

  auto rows_value_label = tgui::Label::create();
  rows_value_label->setRenderer(theme.getRenderer("Label"));
  rows_value_label->setText(std::to_string(int(rows_slider->getValue())));
  rows_value_label->setPosition(87.5, window.getSize().y / 2 + 55);
  rows_value_label->setTextSize(18);
  gui.add(rows_value_label);

  auto hedge_size_value_label = tgui::Label::create();
  hedge_size_value_label->setRenderer(theme.getRenderer("Label"));
  hedge_size_value_label->setText(std::to_string(int(hedge_size_slider->getValue())));
  hedge_size_value_label->setPosition(window.getSize().x - 107, window.getSize().y / 2 - 95);
  hedge_size_value_label->setTextSize(18);
  gui.add(hedge_size_value_label);

  auto hedge_x_origin_value_label = tgui::Label::create();
  hedge_x_origin_value_label->setRenderer(theme.getRenderer("Label"));
  hedge_x_origin_value_label->setText(std::to_string(int(hedge_x_origin_slider->getValue())));
  hedge_x_origin_value_label->setPosition(window.getSize().x - 107, window.getSize().y / 2 - 20);
  hedge_x_origin_value_label->setTextSize(18);
  gui.add(hedge_x_origin_value_label);

  auto hedge_y_origin_value_label = tgui::Label::create();
  hedge_y_origin_value_label->setRenderer(theme.getRenderer("Label"));
  hedge_y_origin_value_label->setText(std::to_string(int(hedge_y_origin_slider->getValue())));
  hedge_y_origin_value_label->setPosition(window.getSize().x - 107, window.getSize().y / 2 + 55);
  hedge_y_origin_value_label->setTextSize(18);
  gui.add(hedge_y_origin_value_label);

  auto columns_slider_label = tgui::Label::create();
  columns_slider_label->setRenderer(theme.getRenderer("Label"));
  columns_slider_label->setText("Columns");
  columns_slider_label->setPosition(25, window.getSize().y / 2 - 75);
  columns_slider_label->setTextSize(14);
  gui.add(columns_slider_label);

  auto rows_slider_label = tgui::Label::create();
  rows_slider_label->setRenderer(theme.getRenderer("Label"));
  rows_slider_label->setText("Rows");
  rows_slider_label->setPosition(25, window.getSize().y / 2);
  rows_slider_label->setTextSize(14);
  gui.add(rows_slider_label);

  auto hedge_size_slider_label = tgui::Label::create();
  hedge_size_slider_label->setRenderer(theme.getRenderer("Label"));
  hedge_size_slider_label->setText("Hedge size");
  hedge_size_slider_label->setPosition(window.getSize().x - 175, window.getSize().y / 2 - 150);
  hedge_size_slider_label->setTextSize(14);
  gui.add(hedge_size_slider_label);

  auto hedge_x_origin_slider_label = tgui::Label::create();
  hedge_x_origin_slider_label->setRenderer(theme.getRenderer("Label"));
  hedge_x_origin_slider_label->setText("X-origin of hedge");
  hedge_x_origin_slider_label->setPosition(window.getSize().x - 175, window.getSize().y / 2 - 75);
  hedge_x_origin_slider_label->setTextSize(14);
  gui.add(hedge_x_origin_slider_label);

  auto hedge_y_origin_slider_label = tgui::Label::create();
  hedge_y_origin_slider_label->setRenderer(theme.getRenderer("Label"));
  hedge_y_origin_slider_label->setText("Y-origin of hedge");
  hedge_y_origin_slider_label->setPosition(window.getSize().x - 175, window.getSize().y / 2);
  hedge_y_origin_slider_label->setTextSize(14);
  gui.add(hedge_y_origin_slider_label);

  auto button = tgui::Button::create();
  button->setRenderer(theme.getRenderer("Button"));
  button->setPosition(window.getSize().x / 2 - 50, window.getSize().y - 50);
  button->setText("Start");
  button->setSize(100, 30);
  button->connect("pressed", [&]() {
    cols = int(columns_slider->getValue());
    rows = int(rows_slider->getValue());
    hedge_checkbox->isChecked() ? with_hedge = true : with_hedge = false;
    hedge_size = int(hedge_size_slider->getValue());
    hedge_x_origin = int(hedge_x_origin_slider->getValue());
    hedge_y_origin = int(hedge_y_origin_slider->getValue());
    window.close();
  });
  gui.add(button);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
        return 0;
      }
      gui.handleEvent(event);
    }

    columns_value_label->setText(std::to_string(int(columns_slider->getValue())));
    rows_value_label->setText(std::to_string(int(rows_slider->getValue())));
    hedge_size_value_label->setText(std::to_string(int(hedge_size_slider->getValue())));
    hedge_x_origin_value_label->setText(std::to_string(int(hedge_x_origin_slider->getValue())));
    hedge_y_origin_value_label->setText(std::to_string(int(hedge_y_origin_slider->getValue())));
    hedge_size_slider->setMaximum(std::min({columns_slider->getValue(), rows_slider->getValue()}) - 1);
    hedge_x_origin_slider->setMaximum(columns_slider->getValue() - hedge_size_slider->getValue() + 1);
    hedge_y_origin_slider->setMaximum(rows_slider->getValue() - hedge_size_slider->getValue() + 1);
    window.clear();
    gui.draw();
    window.display();
  }

  Game simulation(cols, rows, with_hedge, hedge_size, hedge_x_origin, hedge_y_origin);
  simulation.Run(bunny_squares, female_wolf_squares, male_wolf_squares);

  return 0;
}