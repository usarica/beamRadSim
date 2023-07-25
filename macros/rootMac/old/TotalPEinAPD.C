#include "TCanvas.h"
#include "TTree.h"
#include "TFile.h"

void TotalPEinAPD(){

  TChain ch("Events");
   ch.Add("/home/schmitz/sim/HannahTestStand/EURECA.root");

  TH1F *hAPD = new TH1F("hAPD","Nb Of PE in APD",55,-1,54);
  hAPD->GetXaxis()->SetTitle("Number of APD Hits");
  hAPD->GetYaxis()->SetTitle("Bin Members");

  TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);
  gPad->SetLogy();
  ch.Draw("totalNbOfPEAPD>>hAPD");
  
}
