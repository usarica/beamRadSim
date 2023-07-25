#include "TCanvas.h"
#include "TTree.h"
#include "TFile.h"

void GammaPMTHit(){

  TChain ch("Events");
   ch.Add("/data/chocula/schmitz/condor_output/HannahTestStand/data/paper/EURECA.root");

  TH1F *hMEDep = new TH1F("hMECount","Photoelectrons Detected Per Incident Gamma (511 keV)",200,0,200);
  hMECount->GetXaxis()->SetTitle("Number of Photoelectrons Detected");
  hMECount->GetYaxis()->SetTitle("Bin Members");

  TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);
  ch.Draw("NbOfPMTHits>>hMECount");
  
}
