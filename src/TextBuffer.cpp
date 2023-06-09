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
  select_cursor = buffer.begin();
}

std::vector<char> buffer;
std::vector<char>::iterator cursor;
std::vector<char>::iterator select_cursor;

void TextBuffer::text_buf_insert(char c) {
  // TODO: Fix this. it doesn't delete the selected text before inserting
  if (cursor != select_cursor) {
    text_buf_delete();
  }
  cursor = buffer.insert(cursor, c);
  cursor++;
}

void TextBuffer::text_buf_delete() {
  if (cursor > buffer.end())
    return;
  if (cursor > select_cursor) {
    cursor = buffer.erase(select_cursor, cursor);
  } else if (cursor < select_cursor) {
    cursor = buffer.erase(cursor, select_cursor);
  } else if (cursor != buffer.begin()) {
    cursor = buffer.erase(cursor - 1);
  }
}

void TextBuffer::text_buf_save(std::ofstream &file) {
  std::cout << "Writing:\n";
  for (auto i = 0; i < buffer.size(); i++) {
    file << buffer.at(i);
    std::cout << buffer.at(i);
  }
  std::cout << std::endl;
  std::cout << "Wrote " << buffer.size() << " bytes to file.\n";
}

void TextBuffer::text_buf_left() {
  if (cursor == buffer.begin())
    return;
  cursor = cursor - 1;
}

void TextBuffer::text_buf_right() {
  if (cursor == buffer.end())
    return;
  cursor = cursor + 1;
}

std::vector<char>::iterator
TextBuffer::prev_newline(std::vector<char>::iterator cursor) {
  if (cursor == buffer.begin())
    return --cursor;
  std::vector<char>::iterator iter = cursor;
  do {
    iter--;
  } while (*iter != '\n' && iter != buffer.begin() - 1);
  return iter;
}

std::vector<char>::iterator
TextBuffer::next_newline(std::vector<char>::iterator cursor) {
  if (cursor == buffer.end())
    return cursor;
  std::vector<char>::iterator iter = cursor;
  do {
    iter++;
  } while (*iter != '\n' && iter != buffer.end());
  return iter;
}

void TextBuffer::text_buf_up() {
  // At first line in the buffer
  if (prev_newline(cursor) == buffer.begin() - 1)
    return;

  auto dist{std::distance(prev_newline(cursor), cursor)};
  auto prev_prev_newline{prev_newline(prev_newline(cursor))};

  auto prev_line_length =
      std::distance(prev_prev_newline, prev_newline(cursor));
  if (dist > prev_line_length) {
    cursor = prev_newline(cursor);
  } else {
    cursor = prev_prev_newline + dist;
  }
}

void TextBuffer::text_buf_down() {
  // At last line in the buffer
  if (next_newline(cursor) == buffer.end())
    return;

  auto dist{std::distance(prev_newline(cursor), cursor)};
  auto next_next_newline = next_newline(next_newline(cursor));

  auto next_line_length =
      std::distance(next_newline(cursor), next_next_newline);
  if (dist > next_line_length) {
    cursor = next_next_newline;
  } else {
    cursor = next_newline(cursor) + dist;
  }
}

void TextBuffer::update_select_cursor() {
  // updates select cursor when we are not highlighting text
  select_cursor = cursor;
}

void TextBuffer::print_buffer_state() {
  std::cout << "====== Printing buffer state =====\n";
  std::cout << "<";
  for (auto iter = buffer.begin(); iter != buffer.end(); iter++) {
    if (iter == cursor) {
      std::cout << "['" << *iter << "']"
                << ",";
    } else {
      std::cout << "'" << *iter << "'"
                << ",";
    }
  }
  std::cout << ">\n";
  std::cout << "====== End buffer state =====\n";
}

std::string TextBuffer::text_buf_to_str() {
  std::string output = "";
  for (auto iter = buffer.begin(); iter != buffer.end(); iter++) {
    if (iter == cursor) {
      // TODO: remove brackets, simplify with iterator
      // Add cursor implementation using graphics library
      output.push_back('|');
    }
    if (iter == select_cursor) {
      output.push_back('!');
    }
    output.push_back(*iter);
  }
  if (cursor == buffer.end()) {
    output.append("|");
  }
  if (select_cursor == buffer.end()) {
    output.append("!");
  }
  return output;
}
