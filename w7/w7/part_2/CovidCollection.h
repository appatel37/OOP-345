

#ifndef SDDS_COVIDCOLLECTION_H
#define SDDS_COVIDCOLLECTION_H

#include <iostream>
#include <vector>
#include <list>

namespace sdds
{
	// Struct that store the information of covid details.
	struct Covid {
		std::string m_country{};		// Country
		std::string m_city{};			// City
		std::string m_variant{};		// Variant
		int m_year{};					// Year
		size_t m_numCase{};				// Number of cases
		size_t m_numDeath{};			// Number of deaths
		std::string m_status{"General"};// The status of the city
	};

	class CovidCollection {
		std::vector<Covid> m_collection{};	// The collection of Covid struct
	public:
	
		CovidCollection(const char* fileName);

		// Display function. Display the details of each collection.
		void display(std::ostream& out, const std::string& country = {"ALL"}) const;

		// Sort the collection of Covid objects in ascending order based on the field received as parameter.
		void sort(const std::string& field = "country");
		
		
		bool inCollection(const std::string& variant, const std::string& country, unsigned int deaths) const;

		// Create and return a collection of Covid objects from the current instance where the number of deaths is at least as the value specified as parameter.
		std::list<Covid> getListForDeaths(unsigned int deaths) const;

		void updateStatus();
	};

	// Inserts one Covid object into the first parameter.
	std::ostream& operator<<(std::ostream& out, const Covid& theCovid);
}
#endif //!SDDS_COVIDCOLLECTION_H