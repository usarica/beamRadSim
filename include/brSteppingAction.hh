/*
 * brSteppingAction.hh
 *
 *  Created on: 22.04.2019
 *      Author: schmitz
 */

#ifndef BRSTEPPINGACTION_HH_
#define BRSTEPPINGACTION_HH_

#include "globals.hh"
#include "G4UserSteppingAction.hh"


#include  "brEventAction.hh"
#include  "brTrackingAction.hh"
#include  "brSteppingMessenger.hh"
#include  "brHistoManager.hh"

class brSteppingAction : public G4UserSteppingAction
{
public:
  brSteppingAction(brHistoManager*);
  ~brSteppingAction();
  virtual void UserSteppingAction(const G4Step*);

  void SetOneStepPrimaries(G4bool b){oneStepPrimaries=b;}
  G4bool GetOneStepPrimaries(){return oneStepPrimaries;}

private:
  G4bool oneStepPrimaries;
  brSteppingMessenger* steppingMessenger;
  brHistoManager* histoManager;
  G4bool killPhoton;
};



#endif /* BRSTEPPINGACTION_HH_ */
