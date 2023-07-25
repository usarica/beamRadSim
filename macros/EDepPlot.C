#include "TCanvas.h"
#include "TTree.h"
#include "TFile.h"

void EDepPlot(){

  TChain ch("Events");
   ch.Add("/media/ryan/Storage/computing/beamRadSim/build/10keV.root");

  TH1F *hMEDep = new TH1F("hMEDep","Final Energy, 10 keV gammas",100,0,0.01001);
  hMEDep->GetXaxis()->SetTitle("Final energy (MeV)");
  hMEDep->GetYaxis()->SetTitle("Bin Members");

  TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);
  ch.Draw("finalEnergy_MeV>>hMEDep");
  
}
