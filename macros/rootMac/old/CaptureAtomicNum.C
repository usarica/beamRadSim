#include "TCanvas.h"
#include "TTree.h"
#include "TFile.h"

void CaptureAtomicNum(){

  TChain ch("Events");
   ch.Add("/data/chocula/schmitz/condor_output/HannahTestStand/data/EURECA.root");

  TH1F *hNum = new TH1F("hNum","Atomic Number of Atom Capturing Neutrons",100,1,100);
  hNum->GetXaxis()->SetTitle("Atomic Number");
  hNum->GetYaxis()->SetTitle("# of Occurrences");

  TCanvas *c1 = new TCanvas("c1","c1",200,200,600,600);
  ch.Draw("NeutronTracks->captureAtomicNum>>hNum");
  
}
