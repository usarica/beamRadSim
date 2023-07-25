#ifndef brSteppingVerbose_h
#define brSteppingVerbose_h 1

#include "G4SteppingVerbose.hh"
class brSteppingVerbose;

class brSteppingVerbose: public G4SteppingVerbose {
public:
	brSteppingVerbose();
	~brSteppingVerbose();

	void StepInfo();
	void TrackingStarted();
};

#endif
