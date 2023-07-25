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
#include <set>
using namespace std;


void photon_reflections(int parent, int WLS){

//retreive file

  TChain rootEvents("Events");
  rootEvents.Add("/home/schmitz/sim/data/EURECA.root");
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
  set<double> wlsParentID;
  vector<int> nbReflections;

bool wls_conv;
int wls=0;
int parentID=0;
int parentCount=0;
int photonCount=0;
int pmtCount=0;
int numPhotonTracks=0;
int trapped=0;
int nonZeroCount=0;
int tick =0;
int trackID=0;
int originalPhotonCount=0;
int numPhotons=0;
int abs=0;
int abswls=0;
int wlsOut=0;
int endInFiber=0;
int absInFiber=0;
int fiberHitAbs=0;
int WLStrapped=0;
int reflections=0;
bool absorption;
cout << "nentries: " << nentries << endl;
//get data in file
  for (Long64_t i=0;i<nentries;i++) {
	
	rootEvents.GetEntry(i);
	//Photon Energies (before detection). size() evaluates to 100; each photon track seems to "contain" many smaller ones.
		numPhotonTracks = myROOTEvent->GetPhotonTracks()->size();
		numPhotons=numPhotons+numPhotonTracks;
		if (numPhotonTracks>0){
			for (int k = 0; k < numPhotonTracks; k++) {
				wls_conv=myROOTEvent->GetPhotonTracks()->at(k)->GetWLSConversion();
				//absorption=myROOTEvent->GetPhotonTracks()->at(k)->GetAbsorption();
				//final_x = myROOTEvent->GetPhotonTracks()->at(k)->GetLastPositionX();
				//final_y = myROOTEvent->GetPhotonTracks()->at(k)->GetLastPositionY();
				trackID= myROOTEvent->GetPhotonTracks()->at(k)->GetTrackID();
				//final_z= myROOTEvent->GetPhotonTracks()->at(k)->GetLastPositionZ();
				//mag_xy=sqrt(pow(final_x,2)+pow(final_y,2)); 
				if (wls_conv){
					parentID= myROOTEvent->GetPhotonTracks()->at(k)->GetParentID();
					if (!myROOTEvent->GetPhotonTrack(parentID)->GetWLSConversion()){
					//Get number of reflections of parent before being wls converted
					if (parent&&!WLS) reflections = myROOTEvent->GetPhotonTrack(parentID)->GetNbOfReflections();
					else if (parent&&WLS) reflections = myROOTEvent->GetPhotonTrack(parentID)->GetNbOfIntReflections();
					else if (!parent&&!WLS) reflections = myROOTEvent->GetPhotonTracks()->at(k)->GetNbOfReflections();
					else if (!parent&&WLS) reflections = myROOTEvent->GetPhotonTracks()->at(k)->GetNbOfIntReflections();
						
					nbReflections.push_back(reflections);
					}
				}
			}
		}
cout << "Calculating: " << i+1 << " out of " << nentries << " complete" << endl;	
	}
TH1D *hReflect= new TH1D("hReflect","Number of Reflections",500,0,500);
for(int q=0;q<nbReflections.size();q++){
	hReflect->Fill(nbReflections[q]);
}	
hReflect->GetXaxis()->SetTitle("Number of Reflections");
hReflect->GetYaxis()->SetTitle("Bin Members");
hReflect->SetTitle("Number of Reflections in Fiber by First-Child");

TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);
hReflect->Draw();
zPos.clear();
nbReflections.clear();
/*
 for (Long64_t i=0;i<nentries;i++){
	rootEvents.GetEntry(i);
	numPhotonTracks = myROOTEvent->GetPhotonTracks()->size();
	if (numPhotonTracks>0){
		for (int k = 0; k < numPhotonTracks; k++){
			trackID= myROOTEvent->GetPhotonTracks()->at(k)->GetTrackID();
			//if (wlsParentID.find(trackID+10000000*i)==wlsParentID.end()) {
				final_z = myROOTEvent->GetPhotonTracks()->at(k)->GetLastPositionZ();
				//init_x  = myROOTEvent->GetPhotonTracks()->at(k)->GetFirstPositionX();
				//init_y  = myROOTEvent->GetPhotonTracks()->at(k)->GetFirstPositionY();
				//init_z  = myROOTEvent->GetPhotonTracks()->at(k)->GetFirstPositionZ();
				if (final_z<0.0002){
					final_x = myROOTEvent->GetPhotonTracks()->at(k)->GetLastPositionX();
					final_y = myROOTEvent->GetPhotonTracks()->at(k)->GetLastPositionY();
					mag_xy=sqrt(pow(final_x,2)+pow(final_y,2));
					if (mag_xy < fiber_radius) {trapped++;}
				pmtCount++;
				}
				
				else if (final_z<0.0002) {
					if (mag_xy < fiber_radius) {//pmtCount++;
					cout << "Photon at PMT outside fiber! XYMag: " << mag_xy << " params k, i, trackID: " <<  k << "     " << i << "   " << trackID<< endl; }
					}	
				zPos.push_back(final_z);
			//}
		}
	}
 }
*/



//XY position graph
/*
TH1D *hXYMag= new TH1D("hXYMag","Final XyMag",1000,0,0.0125);
for(int q=0;q<xyMag.size();q++){
	hXYMag->Fill(xyMag[q]);
//	tick++;
//	if (tick==10000){
//		cout << "mag_xy entry: " << xyMag[q] << endl;
//		tick=0;
//	}
}	
XYMag->GetXaxis()->SetTitle("XY Magnitude (m)");
hXYMag->GetYaxis()->SetTitle("Bin Members");

hXYMag->SetTitle("XY Magnitude (m)");

TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);
hXYMag->Draw();
xyMag.clear();
*/

//Z Position graph

//cout << "Total parent photon count:  " << parentCount << endl;
}	
