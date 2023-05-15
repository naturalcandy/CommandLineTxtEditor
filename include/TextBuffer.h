// TextBuffer.h
#ifndef TEXTBUFFER_H
#define TEXTBUFFER_H
#endif

#include <fstream>
#include <vector>

class TextBuffer {
public:
  // Constructor
  TextBuffer(std::ifstream &file);

  void text_buf_insert(char c);
  void text_buf_delete();
  void text_buf_save(std::ofstream &file);
  void text_buf_left();
  void text_buf_right();
  void text_buf_up();
  void text_buf_down();
  void print_buffer_state();

private:
  std::vector<char> buffer;
  std::vector<char>::iterator cursor;
  std::vector<char>::iterator prev_newline(std::vector<char>::iterator);
  std::vector<char>::iterator next_newline(std::vector<char>::iterator);
};
