#ifndef brGenFileName_h
#define brGenFileName_h 1

#include "G4String.hh"

class brGenFileName {
public:
	brGenFileName();
	~brGenFileName();
	static G4String genFileName(char postfix[6]);
private:
	static char prefix[24];
};

#endif
