#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
    if (argc < 2){ 
      std::cout << "Usage: ./main.cpp filename \n";
      return 1;
    }

    // Create file
    std::ofstream outfile(argv[1]);
    if(!outfile) {
        std::cout << "Error opening file.\n";
        return 1;
    }

    outfile.close();
    std::cout << "Successfully created " << argv[1] << "\n";
    return 0;
}