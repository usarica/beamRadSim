#include "TCanvas.h"
#include "TTree.h"
#include "TFile.h"

void gammaEnergySpec(){

  TChain ch("Events");
   ch.Add("/media/ryan/Storage/computing/beamRadSim/data/eBremData/gammaDepositPreSteel/BeamRad.root");

  TH1F *hMEDep = new TH1F("hMEDep","XRay Energy from 60 keV Electrons Post-Steel",200,0,0.065);
  hMEDep->GetXaxis()->SetTitle("XRay Energy (MeV)");
  hMEDep->GetYaxis()->SetTitle("Bin Members");

  TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);
  ch.Draw("GammaTracks->finalEnergy_MeV>>hMEDep");
  
}
