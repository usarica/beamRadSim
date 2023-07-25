/*
 * brEventAction.hh
 *
 *  Created on: 22.04.2019
 *      Author: schmitz
 */

#ifndef BREVENTACTION_HH_
#define BREVENTACTION_HH_


#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"

class G4Event;
class brHistoManager;
//const G4int PMTnb = 72;
class brEventAction : public G4UserEventAction
{
public:
  brEventAction(brHistoManager*);
  ~brEventAction();

public:
  void BeginOfEventAction(const G4Event*);
  void EndOfEventAction(const G4Event*);

  void SetSaveThreshold(G4int save);

  void SetEventVerbose(G4int v){verbose=v;}

  void SetPMTThreshold(G4int t){pmtThreshold=t;}

  void SetForceDrawPhotons(G4bool b){forcedrawphotons=b;}

  void SetForceDrawNoPhotons(G4bool b){forcenophotons=b;}

private:

  brHistoManager* histoManager;


  G4int  saveThreshold;

  G4int  pmtCollID;

  G4int  crystalCollID;

  G4int  verbose;

  G4int  pmtThreshold;

  G4bool forcedrawphotons;

  G4bool forcenophotons;

  G4int pmtnb;

//  G4int crystalnb;

  G4bool storePMTHit;

  G4bool storeCrystalHit;

};


#endif /* BREVENTACTION_HH_ */
