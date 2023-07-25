#include "TCanvas.h"
#include "TTree.h"
#include "TFile.h"

void EnergyDeposition(){

  TChain ch("Events");
   ch.Add("/data/chocula/schmitz/condor_output/HannahTestStand/data/EURECA.root");

  TH1F *hEDep = new TH1F("hEDep","Initial Energy Deposition",100,1.9,3.175);
  hEDep->GetXaxis()->SetTitle("Initial Energy Deposition (eV)");
  hEDep->GetYaxis()->SetTitle("Bin Members");

  TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);
  ch.Draw("PMTHits->initalEDep_eV>>hEDep");
  
}
