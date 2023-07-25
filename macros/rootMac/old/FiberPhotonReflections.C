#include "TCanvas.h"
#include "TTree.h"
#include "TFile.h"

void FiberPhotonReflections(){

  TChain ch("Events");
   ch.Add("/home/schmitz/sim/data/EURECA.root");

  TH1F *hReflF = new TH1F("hReflF","Number of WLS Fiber Reflections Per Photon",100,1,100);
  hReflF->GetXaxis()->SetTitle("# of Reflections");
  hReflF->GetYaxis()->SetTitle("# of Occurrences");

  TCanvas *c1 = new TCanvas("c1","c1",200,200,600,600);
  ch.Draw("PhotonTracks->nbOfIntReflections>>hReflF");
  
}
