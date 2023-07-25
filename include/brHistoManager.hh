/*
 * brHistoManager.hh
 *
 *  Created on: 22.04.2019
 *      Author: schmitz
 */

#ifndef BRHISTOMANAGER_HH_
#define BRHISTOMANAGER_HH_


#include "globals.hh"
#include "G4ThreeVector.hh"
#include "TROOT.h"
#include "TFile.h"
#include "TSystem.h"

#include "brROOTEvent.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

 class TFile;
 class TTree;



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class brHistoManager
{
  public:

    brHistoManager();
   ~brHistoManager();

    void book(G4String);
    void save();


    void FillEventNtuple(brROOTEvent* rootEvent);



  private:

    TFile*   rootFile;
    TTree*   ntuplEvent;

    brROOTEvent* myROOTEvent;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


#endif /* BRHISTOMANAGER_HH_ */
