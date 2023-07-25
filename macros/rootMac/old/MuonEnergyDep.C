#include "TCanvas.h"
#include "TTree.h"
#include "TFile.h"

void MuonEnergyDep(){

  TChain ch("Events");
   ch.Add("/data/chocula/schmitz/condor_output/HannahTestStand/data/paper/MuonEDepRun2800k_8cm.root");

  TH1F *hMEDep = new TH1F("hMEDep","Muon Energy Deposition",1500,0,150);
  hMEDep->GetXaxis()->SetTitle("Energy Deposited (MeV)");
  hMEDep->GetYaxis()->SetTitle("Bin Members");

  TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);
  ch.Draw("Edep_MeV>>hMEDep");
  
}
