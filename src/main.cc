#include "../lib/termcolor.hpp"
#include "game.h"
#include <iostream>
#include <iomanip>

int main() {
  while (true) {
    int cols {};
    int rows {};
    bool with_hedge = false;
    int hedge_size {};
    int hedge_x_origin {};
    int hedge_y_origin {};
    std::string buf {};
    int bunny_count {};
    int female_wolf_count {};
    int male_wolf_count {};
    std::vector<int> hedge_area_squares {};
    int animal_square {};
    std::vector<int> bunny_squares {};
    std::vector<int> female_wolf_squares {};
    std::vector<int> male_wolf_squares {};

    std::cout << termcolor::on_cyan << termcolor::yellow << "Welcome to the Wenman simulation\n";
    std::cout << termcolor::yellow << "Choose the size of the field\n"
                                      "Columns <6-14>\n"
                                      "Rows <6-20>\n";
    std::cout << termcolor::blue << "Columns: ";
    std::cin >> cols;
    while (std::cin.fail() || cols > 14 || cols < 6) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << termcolor::red << "Incorrect input, please try again\n";
      std::cout << termcolor::blue << "Columns: ";
      std::cin >> cols;
    }
    std::cout << termcolor::blue << "Rows: ";
    std::cin >> rows;
    while (std::cin.fail() || rows > 20 || rows < 6) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << termcolor::red << "Incorrect input, please try again\n";
      std::cout << termcolor::blue << "Rows: ";
      std::cin >> rows;
    }
    std::cout << termcolor::yellow << "Do you want to include a hedge?\n";
    std::cout << termcolor::blue << "(Y) / (N): ";
    std::cin >> buf;
    if (buf == "y" || buf == "Y") {
      with_hedge = true;
      std::cout << termcolor::yellow << "Hedge size (n x n)\n";
      std::cout << termcolor::blue << "n: ";
      std::cin >> hedge_size;
      while (std::cin.fail() || hedge_size < 1 || hedge_size > (cols - 1) || hedge_size > (rows - 1)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << termcolor::red << "Incorrect input, please try again\n";
        std::cout << termcolor::blue << "n: ";
        std::cin >> hedge_size;
      }
      std::cout << termcolor::blue << "Hedge's x-axis origin: ";
      std::cin >> hedge_x_origin;
      while (std::cin.fail() || hedge_x_origin < 1) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << termcolor::red << "Incorrect input, please try again\n";
        std::cout << termcolor::blue << "Hedge's x-axis origin: ";
        std::cin >> hedge_x_origin;
      }
      std::cout << termcolor::blue << "Hedge's y-axis origin: ";
      std::cin >> hedge_y_origin;
      while (std::cin.fail() || hedge_y_origin < 1) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << termcolor::red << "Incorrect input, please try again\n";
        std::cout << termcolor::blue << "Hedge's y-axis origin: ";
        std::cin >> hedge_y_origin;
      }
      hedge_area_squares.reserve(hedge_size * hedge_size);
      if (hedge_x_origin > cols - hedge_size + 1) {
        hedge_x_origin = cols - hedge_size + 1;
      }
      if (hedge_y_origin > rows - hedge_size + 1) {
        hedge_y_origin = rows - hedge_size + 1;
      }
    }
    std::cout << termcolor::yellow << "How many animals do you want to spawn?\n";
    std::cout << termcolor::blue << "Bunnies: ";
    std::cin >> bunny_count;
    while (std::cin.fail() || bunny_count < 0) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << termcolor::red << "Incorrect input, please try again\n";
      std::cout << termcolor::blue << "Bunnies: ";
      std::cin >> bunny_count;
    }
    std::cout << termcolor::blue << "Female wolves: ";
    std::cin >> female_wolf_count;
    while (std::cin.fail() || female_wolf_count < 0) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << termcolor::red << "Incorrect input, please try again\n";
      std::cout << termcolor::blue << "Female wolves: ";
      std::cin >> female_wolf_count;
    }
    std::cout << termcolor::blue << "Male wolves: ";
    std::cin >> male_wolf_count;
    while (std::cin.fail() || male_wolf_count < 0) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << termcolor::red << "Incorrect input, please try again\n";
      std::cout << termcolor::blue << "Male wolves: ";
      std::cin >> male_wolf_count;
    }
    if (with_hedge) {
      // fill the vector with hedge-confined squares to draw them distinctly
      for (int i = hedge_y_origin - 1; i < hedge_y_origin - 1 + hedge_size; ++i) {
        for (int j = hedge_x_origin - 1; j < hedge_x_origin - 1 + hedge_size; ++j) {
          hedge_area_squares.push_back(cols * i + j);
        }
      }
    }
    std::cout << termcolor::on_white
              << termcolor::yellow << "The field with indexed squares "
                                      "(green area is not accessible to wolves)\n"
              << termcolor::grey;
    int square_idx {};
    // draw the grid
    for (int y = 0; y < rows; ++y) {
      std::cout << "|";
      for (int x = 0; x < cols; ++x) {
        square_idx = y * cols + x;
        if (std::find(hedge_area_squares.begin(), hedge_area_squares.end(), square_idx) != hedge_area_squares.end()) {
          std::cout << termcolor::on_green << " -";
          std::cout << std::setfill('0') << std::setw(3) << square_idx;
          std::cout << "- ";
          std::cout << termcolor::on_white;
        } else {
          std::cout << " -";
          std::cout << std::setfill('0') << std::setw(3) << square_idx;
          std::cout << "- ";
        }
        std::cout << "|";
      }
      std::cout << "\n\n";
    }
    // ask to choose squares for the animals
    if (bunny_count || female_wolf_count || male_wolf_count) {
      std::cout << termcolor::on_cyan << termcolor::yellow << "Insert animals onto selected squares\n";
      for (int i = 0; i < bunny_count; ++i) {
        std::cout << termcolor::blue << "Spawn a bunny on square: ";
        std::cin >> animal_square;
        while (std::cin.fail() || animal_square < 0 || animal_square > (rows * cols - 1)) {
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::cout << termcolor::red << "Incorrect input, please try again\n";
          std::cout << termcolor::blue << "Spawn a bunny on square: ";
          std::cin >> animal_square;
        }
        bunny_squares.push_back(animal_square);
      }
      for (int i = 0; i < female_wolf_count; ++i) {
        std::cout << termcolor::blue << "Spawn a female wolf on square: ";
        std::cin >> animal_square;
        while (std::cin.fail() || animal_square < 0 || animal_square > (rows * cols - 1)
            || std::find(hedge_area_squares.begin(), hedge_area_squares.end(), animal_square)
                != hedge_area_squares.end()) {
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::cout << termcolor::red << "Incorrect input, please try again\n";
          std::cout << termcolor::blue << "Spawn a female wolf on square: ";
          std::cin >> animal_square;
        }
        female_wolf_squares.push_back(animal_square);
      }
      for (int i = 0; i < male_wolf_count; ++i) {
        std::cout << termcolor::blue << "Spawn a male wolf on square: ";
        std::cin >> animal_square;
        while (std::cin.fail() || animal_square < 0 || animal_square > (rows * cols - 1)
            || std::find(hedge_area_squares.begin(), hedge_area_squares.end(), animal_square)
                != hedge_area_squares.end()) {
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::cout << termcolor::red << "Incorrect input, please try again\n";
          std::cout << termcolor::blue << "Spawn a male wolf on square: ";
          std::cin >> animal_square;
        }
        male_wolf_squares.push_back(animal_square);
      }
    }

    Game simulation(cols, rows, with_hedge, hedge_size, hedge_x_origin, hedge_y_origin);
    simulation.Run(bunny_squares, female_wolf_squares, male_wolf_squares);

    std::cout << termcolor::grey << termcolor::on_white << "Do you want to try once again?\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << termcolor::blue << "(Y) / (N): ";
    std::cin >> buf;
    if (buf == "y" || buf == "Y") {
      continue;
    }
    break;
  }
  return 0;
}