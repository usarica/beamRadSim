/*
 * brTrackingAction.hh
 *
 *  Created on: 22.04.2019
 *      Author: schmitz
 */

#ifndef BRTRACKINGACTION_HH_
#define BRTRACKINGACTION_HH_

#include "G4UserTrackingAction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"
class brHistoManager;

class brTrackingAction : public G4UserTrackingAction {

public:
  brTrackingAction(brHistoManager*);
  ~brTrackingAction() {};

  void PreUserTrackingAction(const G4Track*);
  void PostUserTrackingAction(const G4Track*);

private:
  brHistoManager* histoManager;
  G4int verbose;
  G4bool photonTrackStorage;
  G4bool gammaTrackStorage;
  G4bool neutronTrackStorage;
  G4bool muonTrackStorage;
  G4int trackID;
  G4int parentID;
  G4String particleName;
  G4ThreeVector initialPosition;
  G4String initialVolumeName;
  G4String initialProcessName;
  G4double initialEnergy;
  G4double initialTime;


};



#endif /* BRTRACKINGACTION_HH_ */
