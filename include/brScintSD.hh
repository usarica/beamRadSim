/*
 * brScintSD.hh
 *
 *  Created on: 22.04.2019
 *      Author: schmitz
 */

#ifndef BRSCINTSD_HH_
#define BRSCINTSD_HH_

#include "G4VSensitiveDetector.hh"
#include "brScintHit.hh"
#include <G4StepPoint.hh>
#include <fstream>
#include <iostream>

//#include "brScintHitCollection.hh"

class G4Step;
class G4HCofThisEvent;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class brScintSD : public G4VSensitiveDetector
{
  public:
      brScintSD(G4String);
     ~brScintSD();

      void Initialize(G4HCofThisEvent*);
      G4bool ProcessHits(G4Step*, G4TouchableHistory*);
      G4bool ProcessHits2(const G4Step*, G4TouchableHistory*);
      void EndOfEvent(G4HCofThisEvent*);
      G4int HCID;

  	  private:
      brScintHitsCollection* scintCollection;
      G4int verbose;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



#endif /* BRSCINTSD_HH_ */
