#include "TCanvas.h"
#include "TTree.h"
#include "TFile.h"

void GammaEnergyDep(){

  TChain ch("Events");
   ch.Add("/data/chocula/schmitz/condor_output/HannahTestStand/data/paper/GammaEDepRun2000k_8cm.root");

  TH1F *hMEDep = new TH1F("hMEDep","Gamma (511 keV) Energy Deposition",6000,0,0.6);
  hMEDep->GetXaxis()->SetTitle("Energy Deposited (MeV)");
  hMEDep->GetYaxis()->SetTitle("Bin Members");

  TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);
  ch.Draw("Edep_MeV>>hMEDep");
  
}
