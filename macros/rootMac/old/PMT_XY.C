#include "TCanvas.h"
#include "TTree.h"
#include "TFile.h"

void PMT_XY(){

  TChain ch("Events");
   ch.Add("/data/chocula/schmitz/condor_output/HannahTestStand/data/1MeV_PMT_Gd007_small.root");

  TH2F *hXY = new TH2F("hXY","PMT XY Plot",500,-15,15,500,-15,15);
  hXY->GetXaxis()->SetTitle("X Position (mm)");
  hXY->GetYaxis()->SetTitle("Y Position (mm)");

  TCanvas *c1 = new TCanvas("c1","c1",200,200,600,600);
  ch.Draw("PMTHits->hitPosition.fX:hitPosition.fY>>hXY");
  
}
