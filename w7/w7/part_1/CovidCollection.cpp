#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include "CovidCollection.h"

namespace sdds {

	
	CovidCollection::CovidCollection(const char* fileName)
	{
	
		std::fstream file(fileName);

		
		if(file){
			
			while (file) {
				Covid covidCase;	
				std::string line;	
		
				if (std::getline(file, line)) {

					
					covidCase.m_country = line.substr(0, 25);
					covidCase.m_city = line.substr(25, 25);
					covidCase.m_variant = line.substr(50, 25);

					
					covidCase.m_year = std::stoi(line.substr(75, 5));
					covidCase.m_numCase = std::stoi(line.substr(80, 5));
					covidCase.m_numDeath = std::stoi(line.substr(85, 5));

					covidCase.m_country.erase(0, covidCase.m_country.find_first_not_of(" \t"));
					covidCase.m_country.erase(covidCase.m_country.find_last_not_of(" \t") + 1);

					covidCase.m_city.erase(0, covidCase.m_city.find_first_not_of(" \t"));
					covidCase.m_city.erase(covidCase.m_city.find_last_not_of(" \t") + 1);
				
					covidCase.m_variant.erase(0, covidCase.m_variant.find_first_not_of(" \t"));
					covidCase.m_variant.erase(covidCase.m_variant.find_last_not_of(" \t") + 1);

				
					m_collection.push_back(covidCase);
				}
			}
		}
	}

	void CovidCollection::display(std::ostream& out) const {
		
		
		std::for_each(m_collection.begin(), m_collection.end(), [&out](const Covid& covid) {
				out << covid << std::endl;
			});
		
	}

	
	std::ostream& operator<<(std::ostream& out, const Covid& theCovid) {

		out << "| " << std::left << std::setw(21) << theCovid.m_country
			<< " | " << std::setw(15) << theCovid.m_city
			<< " | " << std::setw(20) << theCovid.m_variant
			<< " | " << std::right << std::setw(6);
		
		if (theCovid.m_year < 0) {
			out << "  ";
		}
		else {
			out << theCovid.m_year;
		}
			out << " | " << std::setw(4) << theCovid.m_numCase
			<< " | " << std::setw(3) << theCovid.m_numDeath << " |";

		return out;
	}
}

