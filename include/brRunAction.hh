#ifndef brRunAction_h
#define brRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "G4Run.hh"

class brRunActionMessenger;
class brHistoManager;
class brRunAction: public G4UserRunAction {
public:
	brRunAction(brHistoManager*);
	~brRunAction();

	G4Run* GenerateRun();
	void BeginOfRunAction(const G4Run*);
	void EndOfRunAction(const G4Run*);

	void SetDataFileNamePrefix(G4String nPrefix)	{DataFileNamePrefix = nPrefix;}

private:
	  brHistoManager* histoManager;
	  brRunActionMessenger* runMessenger;

	  G4String DataFileNamePrefix;
};

#endif

