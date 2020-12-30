#ifndef CPU_JOB_H
#define CPU_JOB_H

#include <iostream>

/*
 * CPU_Job holds information for a process to run on the processor
 */
struct CPU_Job {
public:
    int ID;     // process ID
    int length; // process length
    int prior;  // process priority
    CPU_Job(int a = 0, int b = 0, int c = 0) : ID(a), length(b), prior(c) {};
};

/*
 * Operator declarations
 */
// bool operator<(const CPU_Job& lhs, const CPU_Job& rhs);
// std::istream& operator>>(std::istream& in, CPU_Job& job);
// std::ostream& operator<<(std::ostream& out, const CPU_Job& job);

bool operator<(const CPU_Job& lhs, const CPU_Job& rhs){
	if (lhs.prior == rhs.prior) {
		if (lhs.length == rhs.length)
			return lhs.ID < rhs.ID;
		return lhs.length < rhs.length; 
	}
	return lhs.prior < rhs.prior; 
}

bool operator==(const CPU_Job& lhs, const CPU_Job& rhs){
	return lhs.ID == rhs.ID && lhs.length == rhs.length && lhs.prior == rhs.prior;
}

std::istream& operator>>(std::istream& in, CPU_Job& job){
	int a, b, c;
	in >> job.ID; //a;
	in >> job.length;
	in >> job.prior;

	// CPU_Job temp(a,b,c);
	// job = temp;

	//job.ID = a;
	//job.length = b;
	//job.prior = c;
}
std::ostream& operator<<(std::ostream& out, const CPU_Job& job){
	out << "Job " << job.ID << " with length " << job.length << " and priority " << job.prior;
}

#endif