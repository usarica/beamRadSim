/*
 * brSteppingMessenger.cc
 *
 *  Created on: 22.04.2019
 *      Author: schmitz
 */

#include "brSteppingMessenger.hh"
#include "brSteppingAction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithABool.hh"

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
brSteppingMessenger::brSteppingMessenger(brSteppingAction* step)
:stepping(step)
{
  oneStepPrimariesCmd = new G4UIcmdWithABool("/BeamRad/WaterTank/oneStepPrimaries",this);
  oneStepPrimariesCmd->SetGuidance("Only allows primaries to go one step in the scintillator volume before being killed.");
}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
brSteppingMessenger::~brSteppingMessenger(){
  delete oneStepPrimariesCmd;
}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void
brSteppingMessenger::SetNewValue(G4UIcommand* command,G4String newValue){
  if( command == oneStepPrimariesCmd ){
    stepping->SetOneStepPrimaries(oneStepPrimariesCmd
				  ->GetNewBoolValue(newValue));
  }
}




