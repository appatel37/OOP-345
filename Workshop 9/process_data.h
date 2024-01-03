
#ifndef SDDS_PROCESSDATA_H
#define SDDS_PROCESSDATA_H

#include<string>

namespace sdds {
	void computeAvgFactor(const int* arr, int size, int divisor, double& avg);
	void computeVarFactor(const int* arr, int size, int divisor, double avg, double& var);

	class ProcessData {
		int total_items{};
		int* data{};
		
		int num_threads{ 0 }; // to hold number of threads 
		double* averages{ nullptr }; // to hold average factors 
		double* variances{ nullptr }; // to hold variance factors
		int* p_indices{ nullptr }; // to hold partitioning indices
	public:
		ProcessData(const std::string& input_file, int n_threads);
		ProcessData(const ProcessData&) = delete;
		ProcessData& operator=(const ProcessData&) = delete;
		~ProcessData();
		operator bool() const;
		int operator()(const std::string& target_file, double& avg, double& var);
	};
}

#endif
