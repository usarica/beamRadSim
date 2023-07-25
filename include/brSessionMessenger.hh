#ifndef brSessionMessenger_h
#define brSessionMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class brSession;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithABool;

class brSessionMessenger: public G4UImessenger {
public:
	brSessionMessenger(brSession* Sess);
	~brSessionMessenger();

	void SetNewValue(G4UIcommand*, G4String);
private:
	G4UIdirectory* dirLogging;
	brSession* mySession;
	G4UIcmdWithABool* cmdLogOn;
	G4UIcmdWithAString* cmdLogFileName;
};

#endif
