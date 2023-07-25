#include "TCanvas.h"
#include "TTree.h"
#include "TFile.h"

void PhotonReflections(){

  TChain ch("Events");
   ch.Add("/home/schmitz/sim/data/photonRun10_MaskFixed.root");

  TH1F *hRefl = new TH1F("hRefl","Number of Total Internal Reflections, WLS Photons",100,1,100);
  hRefl->GetXaxis()->SetTitle("# of Reflections");
  hRefl->GetYaxis()->SetTitle("# of Occurrences");

  TCanvas *c1 = new TCanvas("c1","c1",200,200,600,600);
  ch.Draw("PhotonTracks->nbOfReflections>>hRefl");
  
}
