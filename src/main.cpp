#include <iostream>
#include <fstream>
#include <string>
#include <vector>


std::fstream edit_file(std::string file_name) {
    std::fstream file; 
    file.open(file_name, std::fstream::in | std::fstream::out);

    if (!file) {
      file = std::fstream(file_name, std::fstream::out);
      std::cout << "File " << file_name << " does not exist. Created file.\n";
    }
    return file;
}

class TextBuffer {
  public:
    TextBuffer(std::fstream &file) {
      char c;
      while ((c = file.get()) != EOF) {
        buffer.push_back(c);
      }
      cursor = buffer.begin();
    }

    std::vector<char> buffer;
    std::vector<char>::iterator cursor;

    void TextBufferInsert (char c) {
      cursor = buffer.insert(cursor, c);
      cursor = cursor + 1;
    }

    void TextBufferDelete() { return; }
    void TextBufferSave(std::fstream &file) { 
      for (auto &c : buffer) {
        file.put(c);
      }
    }
    void TextBufferLeft() { return; }
    void TextBufferRight() { return; }
    void TextBufferUp() { return;}
    void TextBufferDown() { return; }
};


int main(int argc, char *argv[]) {
    if (argc < 2) { 
      std::cout << "Usage: ./main.cpp filename \n";
      return 1;
    }

    std::string file_name = (argv[1]);
    std::fstream file = edit_file(file_name);

    TextBuffer *tb = new TextBuffer(file);
    tb->TextBufferInsert('H');
    tb->TextBufferSave(file);

    file.close();
    delete tb;
    return 0;
}