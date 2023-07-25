/*
 * brSteppingMessenger.hh
 *
 *  Created on: 22.04.2019
 *      Author: schmitz
 */

#ifndef BRSTEPPINGMESSENGER_HH_
#define BRSTEPPINGMESSENGER_HH_

#include "G4UImessenger.hh"
#include "globals.hh"

class brSteppingAction;
class G4UIcmdWithABool;

class brSteppingMessenger: public G4UImessenger
{
public:
  brSteppingMessenger(brSteppingAction*);
  ~brSteppingMessenger();

  void SetNewValue(G4UIcommand*, G4String);

private:
  brSteppingAction*        stepping;
  G4UIcmdWithABool*  oneStepPrimariesCmd;

};



#endif /* BRSTEPPINGMESSENGER_HH_ */
