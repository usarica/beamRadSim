#include "TCanvas.h"
#include "TTree.h"
#include "TGaxis.h"
#include "TStyle.h"
#include "TFile.h"
#include <iostream>
#include "TMath.h"
#include "TChain.h"
#include "TGraph.h"
#include "TGraph2D.h"
#include "TVector.h"
#include "TVectorF.h"
#include "TH1.h"
#include "TH1F.h"
using namespace std;


void Plot2D(){

TCanvas *c1 = new TCanvas("c1", "2D Graph", 0,0,600,400);
TGraph2D *dt = new TGraph2D();
dt->SetTitle("Light output for varying bulk att leng, reflectivity; Reflectivity; Bulk Att Leng (m); Light Output (PE Counts)");

dt->SetPoint(0,0.97,0.5,475);
dt->SetPoint(1,0.97,1,695);
dt->SetPoint(2,0.97,2.5,937);
dt->SetPoint(3,0.97,5,1055);
dt->SetPoint(4,0.98,0.5,580);
dt->SetPoint(5,0.98,1,830);
dt->SetPoint(6,0.98,2.5,1180);
dt->SetPoint(7,0.98,5,1300);
dt->SetPoint(8,0.99,1,1040);
dt->SetPoint(9,0.99,2.5,1510);
dt->SetPoint(10,0.99,5,1730);
dt->SetPoint(11,1.00,0.5,765);
dt->SetPoint(12,1.00,1,1305);
dt->SetPoint(13,1.00,2.5,1995);
dt->SetPoint(14,1.00,5,2420);

gStyle->SetPalette(1);
dt->Draw("colz");

TCanvas *c2 = new TCanvas("c2", "2D Graph", 0,0,600,400);
TGraph2D *ft = new TGraph2D();
ft->SetTitle("Effective Attenuation Length for varying bulk att leng, reflectivity; Reflectivity; Bulk Att Leng (m); Effective Att Leng (cm)");

ft->SetPoint(0,0.97,0.5,6.4);
ft->SetPoint(1,0.97,1,8.1);
ft->SetPoint(2,0.97,2.5,10.5);
ft->SetPoint(3,0.97,5,11.7);
ft->SetPoint(4,0.98,0.5,7.3);
ft->SetPoint(5,0.98,1,9.1);
ft->SetPoint(6,0.98,2.5,13.2);
ft->SetPoint(7,0.98,5,15.0);
ft->SetPoint(8,0.99,0.5,6.4);
ft->SetPoint(9,0.99,1,11.1);
ft->SetPoint(10,0.99,2.5,19.0);
ft->SetPoint(11,0.99,5,24.0);
ft->SetPoint(12,1.00,0.5,8.7);
ft->SetPoint(13,1.00,1,14.9);
ft->SetPoint(14,1.00,2.5,31.7);
ft->SetPoint(15,1.00,5,70.3);

gStyle->SetPalette(1);
ft->Draw("colz");
}
