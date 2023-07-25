// ------------------------------------------------
//
//  brRunActionMessenger.hh
//
// ------------------------------------------------

#ifndef brRunActionMessenger_h
#define brRunActionMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

// ------------------------------------------------

class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithABool;

class brRunAction;

// ------------------------------------------------

class brRunActionMessenger: public G4UImessenger
{
public:
  brRunActionMessenger(brRunAction* );
  ~brRunActionMessenger();

  void SetNewValue(G4UIcommand*, G4String);

private:
  brRunAction*      	  pRunAction;
  G4UIdirectory*          brRunDir;

  // Run Element Activation

  G4UIcmdWithAString*     setRunFileName;
};

#endif
