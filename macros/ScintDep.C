#include "TCanvas.h"
#include "TTree.h"
#include "TFile.h"

void ScintDep(){

  TChain ch("Events");
   ch.Add("/media/ryan/Storage/computing/beamRadSim/data/Am241_mixedAbsScint_5stack/BeamRad.root");

  TH1F *hMEDep = new TH1F("hMEDep","Final Energy, 200 keV gammas",100,0,0.0001);
  hMEDep->GetXaxis()->SetTitle("Final energy (MeV)");
  hMEDep->GetYaxis()->SetTitle("Bin Members");

  TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);
  ch.Draw("Edep_MeV_ScintVeto>>hMEDep");
  
}
