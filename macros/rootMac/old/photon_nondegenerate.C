#include "TCanvas.h"
#include "TTree.h"
#include "TGaxis.h"
#include "TStyle.h"
#include "TFile.h"
#include <iostream>
#include "TMath.h"
#include "TChain.h"
#include "/home/schmitz/sim/HannahTestStand/include/mqROOTEvent.hh"
#include "TGraph.h"
#include "TVector.h"
#include "TVectorF.h"
#include "TH1.h"
#include "TH1F.h"
#include <set>
using namespace std;


void photon_nondegenerate(){

//retreive file

  TChain rootEvents("Events");
  //rootEvents.Add("/home/schmitz/sim/data/photonRun10_MaskEllipH0mmAdd_0Refl.root");
  rootEvents.Add("/data/cdms1/schmitz/condor_output/HannahTestStand/data/paper/muon6/Al100R99Hole1p05mm/EURECA.root");
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
  double mag_xy_init=0;
  double fiber_radius = 0.001035/2; //meters
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
int pmtCountfar=0;
int numPhotonTracks=0;
int trapped=0;
int trappedfar=0;
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
int WLStrappedfar=0;
int reflections=0;
int multConv=0;
double initial_x=0;
double initial_y=0;
double initial_z=0;
bool absorption;
int wlsCount=0;
int PECount=0;
cout << "nentries: " << nentries << endl;
//cout << "Looking for greater than 200 PE... " << nentries << endl;
//get data in file
  for (Long64_t i=0;i<50;i++) {
  //for (Long64_t i=0;i<nentries;i++) {
	
	rootEvents.GetEntry(i);
	//Photon Energies (before detection). size() evaluates to 100; each photon track seems to "contain" many smaller ones
	PECount = myROOTEvent->GetPMTRHits()->size();
	if (PECount > 0) {//200 && PECount < 400 ) {
		numPhotonTracks = myROOTEvent->GetPhotonTracks()->size();
		numPhotons=numPhotons+numPhotonTracks;
		if (numPhotonTracks>0){
			for (int k = 0; k < numPhotonTracks; k++) {
				wls_conv=myROOTEvent->GetPhotonTracks()->at(k)->GetWLSConversion();
				absorption=myROOTEvent->GetPhotonTracks()->at(k)->GetAbsorption();
				final_x = myROOTEvent->GetPhotonTracks()->at(k)->GetLastPositionX();
				final_y = myROOTEvent->GetPhotonTracks()->at(k)->GetLastPositionY();
				initial_x=myROOTEvent->GetPhotonTracks()->at(k)->GetFirstPositionX();
				initial_y=myROOTEvent->GetPhotonTracks()->at(k)->GetFirstPositionY();
				initial_z=myROOTEvent->GetPhotonTracks()->at(k)->GetFirstPositionZ();
				trackID= myROOTEvent->GetPhotonTracks()->at(k)->GetTrackID();
				final_z= myROOTEvent->GetPhotonTracks()->at(k)->GetLastPositionZ();
				mag_xy=sqrt(pow(final_x,2)+pow(final_y,2)); 
				mag_xy_init=sqrt(pow(initial_x,2)+pow(initial_y,2)); 
				if (wls_conv){
					wls++;
					if (absorption) {abswls++;
						if (mag_xy <= fiber_radius) absInFiber++; }
					if (mag_xy > fiber_radius) {wlsOut++;}
					parentID= myROOTEvent->GetPhotonTracks()->at(k)->GetParentID();
					if (myROOTEvent->GetPhotonTrack(parentID)->GetWLSConversion()) {wls--;
					 multConv++;}
					//Get number of reflections of parent before being wls converted
					else {
						reflections = myROOTEvent->GetPhotonTrack(parentID)->GetNbOfReflections();
						nbReflections.push_back(reflections);
					}
					wlsCount++;
					wlsParentID.insert(parentID+10000000*i); //ten million times i plus parent ID; this makes sure we don't throw out good tracks by accident
				}
				if (absorption) {
					abs++;
					if (mag_xy <= fiber_radius) { fiberHitAbs++; }
					}
			//		parentID= myROOTEvent->GetPhotonTracks()->at(k)->GetParentID();
			//		if (myROOTEvent->GetPhotonTrack(parentID)->GetAbsorption()) {cout << "Parent was absorbed?" << endl;}
				if (final_z<0.001){
					if (mag_xy <= fiber_radius) {trapped++;
						if (wls_conv) WLStrapped++; }
					pmtCount++;
				} else if (final_z>0.044){
					if (mag_xy <= fiber_radius) {trappedfar++;
						if (wls_conv) WLStrappedfar++; }
					pmtCountfar++;
				}
				if (mag_xy<=fiber_radius) endInFiber++;
					zPos.push_back(mag_xy);
			}
		}
		}
cout << "Calculating: " << i+1 << " out of " << nentries << " complete" << endl;	
}

cout << "Number of total wls conversions: " << wlsCount << endl; //these two numbers should be the same, else there's a problem
cout << "Number of multiple wls conversions: " << multConv << endl; //these two numbers should be the same, else there's a problem
cout << "Number of original photon tracks which eventually undergo wls conversions: " << wls << endl;
cout << "Total number of photon tracks: " << numPhotons << endl;
cout << "Number of photons as daughters of the incident primaries (direct and indirect, one per generation): " << numPhotons-wlsParentID.size() << endl;
cout << "Number of absorbed photons: " << abs << endl;
cout << "Number of absorbed WLS converted photons: " << abswls << endl;
cout << "Number of absorbed WLS converted photons inside the fiber: " << absInFiber << endl;
cout << "Number of WLS photons which eventually left the WLS fiber and stayed out: " << wlsOut << endl;
cout << "Number of WLS photons which did not leave the fiber (with multiple conversions removed): " << wls-wlsOut << endl;
cout << "Number of photons which became absorbed in or on the boundary of the fiber: " << fiberHitAbs << endl;
cout << "Number of photons which end their tracks inside the fiber: " << endInFiber << endl;

cout << "Size of zPos:  " << zPos.size() << endl; //should be equal to totalPhotonCount-wls
cout << "# of final_z = 0 : " << pmtCount << endl;
cout << "# of photons with final_z=0, trapped in WLS: " << trapped << endl;
cout << "# of WLS photons with final_z=0, trapped in WLS: " << WLStrapped << endl;
cout << "# of final_z = non-PMT end : " << pmtCountfar << endl;
cout << "# of photons with final_z=non-PMT end, trapped in WLS: " << trappedfar << endl;
cout << "# of WLS photons with final_z=non-PMT end, trapped in WLS: " << WLStrappedfar << endl;
cout << "Percentage of photons which reach the PMT: " << (double) pmtCount/zPos.size() << endl;
//cout << "WLS Trapping Efficiency (denom: all generated photons): " << (double) trapped/originalPhotonCount << endl;
cout << "WLS Trapping Efficiency (denom: photons at PMT): " << (double) trapped/pmtCount << endl;
//Z Position Graph

TH1D *hzpos= new TH1D("hzpos","",1000,0,0.0015);
for(int q=0;q<zPos.size();q++){
	hzpos->Fill(zPos[q]);
}	
hzpos->GetXaxis()->SetTitle("Position Final");
hzpos->GetYaxis()->SetTitle("Bin Members");
hzpos->SetTitle("XY mag position of original-track WLS photons");

/*
TH1D *hReflect= new TH1D("hReflect","Number of Reflections of WLS Converted Parents",1000,0,50000);
for(int q=0;q<nbReflections.size();q++){
	hReflect->Fill(nbReflections[q]);
}	
hReflect->GetXaxis()->SetTitle("Number of Reflections");
hReflect->GetYaxis()->SetTitle("Bin Members");
hReflect->SetTitle("Number of Reflections");
*/


TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);
//hReflect->Draw();
hzpos->Draw();
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
