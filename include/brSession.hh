#ifndef brSession_h
#define brSession_h 1

#include "G4UIsession.hh"
#include "brSessionMessenger.hh"
#include <iostream>
#include <fstream>

class brSession: public G4UIsession {
public:
	brSession();
	~brSession();

	G4int ReceiveG4cout(G4String coutString);
	G4int ReceiveG4cerr(G4String cerrString);
	void logOn(G4bool myOnOff);
	void SetLogFileName(G4String filename);
private:
	void reinitFile();
	std::ofstream logFile;
	brSessionMessenger* mySessionMessenger;
	G4String logFileName;
	G4bool logOnOff;
};

#endif
