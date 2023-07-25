// ------------------------------------------------
//
//  brRunActionMessenger.cc
//
// ------------------------------------------------

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithABool.hh"

#include "G4RunManager.hh"

#include "brRunActionMessenger.hh"
#include "brRunAction.hh"

// ------------------------------------------------

brRunActionMessenger::brRunActionMessenger(brRunAction* brRun):pRunAction(brRun)
{ 
  // Create the run directory
  brRunDir = new G4UIdirectory("/BeamRad/");
  brRunDir->SetGuidance("BeamRad specific run controls.");
  //

  //  run directory already exists

  // Set file name
  setRunFileName = new G4UIcmdWithAString("/run/fname",this);
  setRunFileName->SetGuidance("Set the name of the output files.");
  setRunFileName->SetParameterName("fname",true);
  setRunFileName->SetDefaultValue("Sim");
  setRunFileName->AvailableForStates(G4State_PreInit,G4State_Idle);

}

// ------------------------------------------------

brRunActionMessenger::~brRunActionMessenger()
{
  delete setRunFileName;     
}

// ------------------------------------------------

void brRunActionMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 

  if( command == setRunFileName ) {
    pRunAction->SetDataFileNamePrefix(newValue);
  }

}

// ------------------------------------------------

