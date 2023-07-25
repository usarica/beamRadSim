#include "TCanvas.h"
#include "TTree.h"
#include "TGaxis.h"
#include "TStyle.h"
#include "TFile.h"
#include <iostream>
#include "TMath.h"
#include "TChain.h"
#include "/home/schmitz/sim/HannahTestStand/include/eurROOTEvent.hh"
#include "TGraph.h"
#include "TVector.h"
#include "TVectorF.h"
#include "TH1.h"
#include "TH1F.h"
using namespace std;


void photonZPos_ParentOnly(){

//retreive file

  TChain rootEvents("Events");
  rootEvents.Add("/data/chocula/schmitz/condor_output/HannahTestStand/data/4GeV_muon_fiber_photonRun_100refl.root");
  std::cout << "Reading file..." << std::endl;
  eurROOTEvent* myROOTEvent = new eurROOTEvent();
  rootEvents.SetBranchAddress("ROOTEvent", &myROOTEvent);
  Long64_t nentries=rootEvents.GetEntries();

//initialize variables
  double EDep=0;
  double h=4.135668*pow(10,-15);
  double c=3*pow(10,8);
  double wavelength;
  double final_z=0;
  double final_x=0;
  double final_y=0;
  double init_x=0;
  double init_y=0;
  double init_z=0;
  double mag_xy=0;
  double init_mag_xy=0;
  double fiber_radius = 0.0005; //meters
  vector<double> zPos;
  vector<double> xyMag;

bool wls_conv;
int wls=0;
int parentID=0;
int parentCount=0;
int photonCount=0;
int numPhotonTracks=0;
int trapped=0;
int nonZeroCount=0;
int tick =0;
//get data in file
  for (Long64_t i=0;i<nentries;i++) {
	
	rootEvents.GetEntry(i);
	//Photon Energies (before detection). size() evaluates to 100; each photon track seems to "contain" many smaller ones.
		numPhotonTracks = myROOTEvent->GetPhotonTracks()->size();
		if (numPhotonTracks>0){
			for (int k = 0; k < numPhotonTracks; k++) {
				final_x = myROOTEvent->GetPhotonTracks()->at(k)->GetLastPositionX();
				final_y = myROOTEvent->GetPhotonTracks()->at(k)->GetLastPositionY();
				final_z = myROOTEvent->GetPhotonTracks()->at(k)->GetLastPositionZ();
				init_x  = myROOTEvent->GetPhotonTracks()->at(k)->GetFirstPositionX();
				init_y  = myROOTEvent->GetPhotonTracks()->at(k)->GetFirstPositionY();
				init_z  = myROOTEvent->GetPhotonTracks()->at(k)->GetFirstPositionZ();
				parentID= myROOTEvent->GetPhotonTracks()->at(k)->GetParentID();
				wls_conv=myROOTEvent->GetPhotonTracks()->at(k)->GetWLSConversion();
				//if (parentID!=1){
				if (parentID==1){
					parentCount++;
					//EDep=myROOTEvent->GetPhotonTracks()->at(k)->GetInitialEnergy();
					//wavelength=h*c/(EDep)*pow(10,9);	
					zPos.push_back(final_z);
					init_mag_xy=sqrt(pow(init_x,2)+pow(init_y,2));
					if (mag_xy <= fiber_radius) trapped++;
					if (wls_conv) wls++;
					if (final_z!=0){
						//check to see if terminated on fiber
						mag_xy=sqrt(pow(final_x,2)+pow(final_y,2));
					//	init_mag_xy=sqrt(pow(init_x,2)+pow(init_y,2));
					//	if (init_mag_xy <= fiber_radius) trapped++;
						//if (wls_conv) wls++;
						//xyMag.push_back(init_mag_xy);
						xyMag.push_back(mag_xy);
						nonZeroCount++;
					}
				}
				photonCount++;
//				tick++;
//				if (tick==10000){
//					cout << "Mag_XY: " << xyMag[xyMag.size()-1] << endl;
//					tick =0;
//				}
			}
			}
	}
//XY position graph

TH1D *hXYMag= new TH1D("hXYMag","Final XyMag",1000,0,0.0125);
for(int q=0;q<xyMag.size();q++){
	hXYMag->Fill(xyMag[q]);
//	tick++;
//	if (tick==10000){
//		cout << "mag_xy entry: " << xyMag[q] << endl;
//		tick=0;
//	}
}	
hXYMag->GetXaxis()->SetTitle("XY Magnitude (m)");
hXYMag->GetYaxis()->SetTitle("Bin Members");

hXYMag->SetTitle("XY Magnitude (m)");

TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);
hXYMag->Draw();
xyMag.clear();

/*
//Z Position graph
TH1D *hZPos= new TH1D("hZPos","Final Z Position",400,0,0.05);
for(int q=0;q<zPos.size();q++){
	hZPos->Fill(zPos[q]);
}	
hZPos->GetXaxis()->SetTitle("Z Position");
hZPos->GetYaxis()->SetTitle("Bin Members");
cout << "Size of zPos:  " << zPos.size() << endl;

hZPos->SetTitle("Final Z Position");

TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);
hZPos->Draw();
zPos.clear();
*/

cout << "Total parent photon count:  " << parentCount << endl;
cout << "Trapped (terminated at fiber) photon count:  " << trapped << endl;
cout << "Total photon count:  " << photonCount << endl;
cout << "Final_Z!=0 count:  " << nonZeroCount << endl;
cout << "WLS Converted photons: " << wls << endl;
cout << "ABOVE IS FOR NON-PARENT PHOTONS ONLY" << endl;
}	
