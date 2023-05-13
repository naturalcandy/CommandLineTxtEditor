#include "../include/TextBuffer.h"
#include <cstdint>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>

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

  // Insert characters into buffer
  TextBuffer *tb = new TextBuffer(in_file);
  in_file.close();

  std::ofstream out_file;
  out_file.open(file_name, std::ios::trunc);

  tb->text_buf_insert('P');
  tb->text_buf_insert('G');

  // Write buffer to file
  tb->text_buf_save(out_file);

  delete tb;
  out_file.close();
  return 0;
}
