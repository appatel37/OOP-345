#include <iostream>
#include <iomanip>
#include <fstream>
#include "Book.h"
#include "Book.h" 

#ifndef SDDS_BOOK_H
    #error "The header guard for 'Book.h' doesn't follow the convention!"
#endif

int cout = 0; 

enum AppErrors
{
	CannotOpenFile = 1,
	BadArgumentCount = 2, 
};

int main(int argc, char** argv)
{
	std::cout << "Command Line:\n";
	std::cout << "--------------------------\n";
	for (int i = 0; i < argc; i++)
		std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
	std::cout << "--------------------------\n\n";

	sdds::Book library[7];
	if (argc == 2) {
        size_t cnt = 0;
        std::ifstream file(argv[1]);
        if (!file) {
            std::cerr << "ERROR: Cannot open file.\n";
            exit(AppErrors::CannotOpenFile);
        }
        std::string bookLine;
        do {
            std::getline(file, bookLine);
            if(file) {
                if(bookLine[0] != '#') {
                    library[cnt] = sdds::Book(bookLine);
                    ++cnt;
                }
            }
        } while(file);
        file.close();
	}
	else
	{
		std::cerr << "ERROR: Incorrect number of arguments.\n";
		exit(AppErrors::BadArgumentCount);
	}

	double usdToCadRate = 1.3;
	double gbpToCadRate = 1.5;
    
    auto price = [=](sdds::Book& book) {
        if(book.country() == "US") {
            book.price() *= usdToCadRate;
        }
        else if(book.country() == "UK" && book.year() >= 1990 && book.year() <= 1998) {
            book.price() *= gbpToCadRate;
        }
    };


	std::cout << "-----------------------------------------\n";
	std::cout << "The library content\n";
	std::cout << "-----------------------------------------\n";
    for(size_t i = 0; i < sizeof(library) / sizeof(library[0]); i++) {
        std::cout << library[i];
    }



	std::cout << "-----------------------------------------\n\n";

    for(size_t i = 0; i < sizeof(library) / sizeof(library[0]); i++) {
        price(library[i]);
    }



	std::cout << "-----------------------------------------\n";
	std::cout << "The library content (updated prices)\n";
	std::cout << "-----------------------------------------\n";
    for(size_t i = 0; i < sizeof(library) / sizeof(library[0]); i++) {
        std::cout << library[i];
    }


	std::cout << "-----------------------------------------\n";

	return cout;
}
