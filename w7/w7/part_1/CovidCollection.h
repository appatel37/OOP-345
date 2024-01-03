
#ifndef SDDS_COVIDCOLLECTION_H
#define SDDS_COVIDCOLLECTION_H

#include <iostream>
#include <vector>

namespace sdds
{

	struct Covid {
		std::string m_country;	// Country
		std::string m_city;		// City
		std::string m_variant;	// Variant
		int m_year;				// Year
		size_t m_numCase;		// Number of cases
		size_t m_numDeath;		// Number of deaths
	};

	class CovidCollection {
		std::vector<Covid> m_collection{};	
	public:
		
		CovidCollection(const char* fileName);

		void display(std::ostream& out) const;
	};

	
	std::ostream& operator<<(std::ostream& out, const Covid& theCovid);
}
#endif 