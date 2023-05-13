#include "../include/TextBuffer.h"
#include <fstream>
#include <iostream>
#include <vector>

TextBuffer::TextBuffer(std::ifstream &file) {
  std::cout << "pre-existing file contents: ";
  char c;
  while (file.get(c)) {
    std::cout << c;
    buffer.push_back(c);
  }
  std::cout << std::endl;
  cursor = buffer.begin();
  buffer.begin();
}

std::vector<char> buffer;
std::vector<char>::iterator cursor;

void TextBuffer::text_buf_insert(char c) {
  cursor = buffer.insert(cursor, c);
  cursor++;
}

void TextBuffer::text_buf_delete() { return; }
void TextBuffer::text_buf_save(std::ofstream &file) {

  std::cout << "<";
  for (auto c : buffer) {
    std::cout << "'" << c << "'"
              << ", ";
  }
  std::cout << ">";

  std::cout << "Writing: ";
  for (auto i = 0; i < buffer.size(); i++) {
    file << buffer.at(i);
    std::cout << buffer.at(i);
  }
  std::cout << std::endl;
  std::cout << "Wrote " << buffer.size() << " bytes to file.\n";
}
void TextBuffer::text_buf_left() { return; }
void TextBuffer::text_buf_right() { return; }
void TextBuffer::text_buf_up() { return; }
void TextBuffer::text_buf_down() { return; }
