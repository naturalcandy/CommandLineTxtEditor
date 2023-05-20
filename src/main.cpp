#include "../include/TextBuffer.h"
#include <cstdint>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>
#include <cctype>
#include <SFML/Graphics.hpp>


int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Usage: ./CmdLineEditor filename \n";
    return 1;
  }

  std::string file_name = (argv[1]);
  std::ifstream in_file;
  in_file.open(file_name);
  if (!in_file) {
    std::cout << "Error: file does not exist. Creating file '" << file_name
              << "'.\n";
    // Create the file
    in_file.open(file_name);
  }

  
  sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Text Editor");

  TextBuffer *tb = new TextBuffer(in_file);
  in_file.close();

  std::ofstream out_file;
  out_file.open(file_name, std::ios::trunc);

  tb->text_buf_insert('2');
  tb->text_buf_insert('2');
  tb->text_buf_insert('3');
  tb->text_buf_insert('4');
  tb->text_buf_insert('\n');  
  tb->text_buf_insert('1');
  tb->text_buf_insert('2');
  tb->text_buf_left();
  tb->text_buf_left();
  tb->text_buf_left();
  tb->text_buf_left();
  tb->text_buf_left();
  tb->text_buf_left();
  tb->text_buf_left();
  tb->text_buf_left();
  tb->text_buf_left();
  tb->text_buf_left();
  tb->text_buf_left();


  while (window.isOpen()) {
    std::string buf_str = tb->text_buf_to_str();
    sf::Font font;
    if (!font.loadFromFile("./arial.ttf"))
      return EXIT_FAILURE;
    sf::Text text(buf_str, font, 35);

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        tb->text_buf_save(out_file);
        window.close();
      }
      else if (event.type == sf::Event::TextEntered 
                && isprint(event.text.unicode)) {
        tb->text_buf_insert(static_cast<char>(event.text.unicode));
        buf_str = tb->text_buf_to_str();
      }
      else if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code)
        {
        case sf::Keyboard::Up:
          std::cout << "up" << std::endl;
          tb->text_buf_up();
          break;
        case sf::Keyboard::Down:
          std::cout << "down" << std::endl;
          tb->text_buf_down();
          break;
        case sf::Keyboard::Left:
          std::cout << "left" << std::endl;
          tb->text_buf_left();
          break;
        case sf::Keyboard::Right:
          std::cout << "right" << std::endl;
          tb->text_buf_right();
          break;
        case sf::Keyboard::BackSpace:
          std::cout << "backspace" << std::endl;
          tb->text_buf_delete();
          break;
        case sf::Keyboard::Enter:
          std::cout << "enter" << std::endl;
          tb->text_buf_insert('\n');
        default:
          break;
        }
      }
    }

    window.clear();
    window.draw(text);
    window.display();
  }

  delete tb;
  out_file.close();
  return EXIT_SUCCESS;
}
