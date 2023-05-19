#include "../include/TextBuffer.h"
#include <cstdint>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>
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

  
  sf::RenderWindow window(sf::VideoMode(800, 600), "Text Editor");

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
  tb->print_buffer_state();

  while (window.isOpen()) {
    sf::Font font;
    if (!font.loadFromFile("./arial.ttf"))
      return EXIT_FAILURE;
    sf::Text text(tb->text_buf_to_str(), font, 14);

    window.clear();
    window.draw(text);
    window.display();

  }

  delete tb;
  out_file.close();
  return EXIT_SUCCESS;
}