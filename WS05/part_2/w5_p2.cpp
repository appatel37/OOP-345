#include <iostream>
#include <iomanip>
#include <fstream>
#include "Collection.h"
#include "Collection.h"     
#include "SpellChecker.h"
#include "SpellChecker.h"  
#include "Book.h"
#include "Book.h"          
#include "Movie.h"
#include "Movie.h"          

#ifndef SDDS_BOOK_H
    #error "The header guard for 'Book.h' doesn't follow the convention!"
#endif
#ifndef SDDS_MOVIE_H
    #error "The header guard for 'Movie.h' doesn't follow the convention!"
#endif
#ifndef SDDS_SPELLCHECKER_H
    #error "The header guard for 'SpellChecker.h' doesn't follow the convention!"
#endif
#ifndef SDDS_COLLECTION_H
    #error "The header guard for 'Collection.h' doesn't follow the convention!"
#endif

int cout = 0; 

enum AppErrors
{
	CannotOpenFile = 1, 
	BadArgumentCount = 2, 
};

void bookAddedObserver(const sdds::Collection<sdds::Book>& theCollection,
	const sdds::Book& theBook)
{
	std::cout << "Book \"" << theBook.title() << "\" added!\n";
}

void movieAddedObserver(const sdds::Collection<sdds::Movie>& theCollection,
	const sdds::Movie& theMovie)
{
	std::cout << "Movie \"" << theMovie.title()
		<< "\" added to collection \"" << theCollection.name()
		<< "\" (" << theCollection.size() << " items).\n";
}

int main(int argc, char** argv)
{
	std::cout << "Command Line:\n";
	std::cout << "--------------------------\n";
	for (int i = 0; i < argc; i++)
		std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
	std::cout << "--------------------------\n\n";

	sdds::Collection<sdds::Book> library("Bestsellers");
	if (argc == 5) {
		
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
                    library += sdds::Book(bookLine);
                    cnt++;
                }
            }
        } while(cnt < 4);
		
        
		library.setObserver(bookAddedObserver);

		
        do {
            std::getline(file, bookLine);
            if(file) {
                if(bookLine[0] != '#') {
                    library += sdds::Book(bookLine);
                    cnt++;
                }
            }
        } while(file);
        file.close();

	}
	else
	{
		std::cerr << "ERROR: Incorrect number of arguments.\n";
		std::exit(AppErrors::BadArgumentCount);
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
	std::cout << library;
	std::cout << "-----------------------------------------\n\n";

	
    for(size_t i = 0; i < library.size(); i++) {
        price(library[i]);
    }



	std::cout << "-----------------------------------------\n";
	std::cout << "The library content (updated prices)\n";
	std::cout << "-----------------------------------------\n";
	std::cout << library;
	std::cout << "-----------------------------------------\n\n";

	sdds::Collection<sdds::Movie> theCollection("Action Movies");

	sdds::Movie movies[5];
	if (argc > 2) {
		
        size_t cnt = 0;
        std::ifstream file(argv[2]);
        if (!file) {
            std::cerr << "ERROR: Cannot open file.\n";
            exit(AppErrors::CannotOpenFile);
        }
        std::string movieLine;
        do {
            std::getline(file, movieLine);
            if(file) {
                if(movieLine[0] != '#') {
                    movies[cnt] = sdds::Movie(movieLine);
                    cnt++;
                }
            }
        } while(cnt < 5);

        file.close();

	}

	std::cout << "-----------------------------------------\n";
	std::cout << "Testing addition and callback function\n";
	std::cout << "-----------------------------------------\n";
	if (argc > 2) {
		((theCollection += movies[0]) += movies[1]) += movies[2];
		theCollection += movies[1];
		theCollection.setObserver(movieAddedObserver);
		theCollection += movies[3];
		theCollection += movies[3];
		theCollection += movies[4];
	}
	else {
		std::cout << "** No movies in the Collection\n";
	}
	std::cout << "-----------------------------------------\n\n";
	
	std::cout << "-----------------------------------------\n";
	std::cout << "Testing exceptions and operator[]\n";
	std::cout << "-----------------------------------------\n";


		
    try {
        for (auto i = 0u; i < 10; ++i) {
            std::cout << theCollection[i];
        }
    }catch (std::out_of_range &err) {
            std::cerr << "** EXCEPTION: " << err.what() << std::endl;
        }

	std::cout << "-----------------------------------------\n\n";


	std::cout << "-----------------------------------------\n";
	std::cout << "Testing the functor\n";
	std::cout << "-----------------------------------------\n";
	for (auto i = 3; i < argc; ++i)
	{
			
        try {
            sdds::SpellChecker sp(argv[i]);
            for (auto j = 0u; j < library.size(); ++j)
                library[j].fixSpelling(sp);
            sp.showStatistics(std::cout);
            
            for (auto j = 0u; j < theCollection.size(); ++j)
                theCollection[j].fixSpelling(sp);
            sp.showStatistics(std::cout);
        }
        catch(const char* err) {
            std::cerr << "** EXCEPTION: " << err << std::endl;
        }
	}
	if (argc < 3) {
		std::cout << "** Spellchecker is empty\n";
		std::cout << "-----------------------------------------\n";
	}
	std::cout << "\n";

	std::cout << "=========================================\n";
	std::cout << "Wrapping up this workshop\n";
	std::cout << "--------------- Movies ------------------\n";
	std::cout << theCollection;
	std::cout << "--------------- Books -------------------\n";
	std::cout << library;
	std::cout << "-----------------------------------------\n";
	std::cout << "Testing operator[] (the other overload)\n";
	std::cout << "-----------------------------------------\n";
	const sdds::Movie* aMovie = theCollection["Terminator 2"];
	if (aMovie == nullptr)
		std::cout << "** Movie Terminator 2 not in collection.\n";
	aMovie = theCollection["Dark Phoenix"];
	if (aMovie != nullptr)
		std::cout << "In this collection:\n" << *aMovie;
	std::cout << "-----------------------------------------\n";

	return cout;
}
