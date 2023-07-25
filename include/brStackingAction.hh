/*
 * brStackingAction.hh
 *
 *  Created on: 22.04.2019
 *      Author: schmitz
 */

#ifndef BRSTACKINGACTION_HH_
#define BRSTACKINGACTION_HH_

#include "globals.hh"
#include "G4UserStackingAction.hh"

class brStackingAction : public G4UserStackingAction
{
public:
  brStackingAction();
  ~brStackingAction();

  virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
  virtual void NewStage();
  virtual void PrepareNewEvent();

private:
};




#endif /* BRSTACKINGACTION_HH_ */
