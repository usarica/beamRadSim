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


void photonEnergySpectrumAtPhotocath(int b){

//retreive file

  TChain rootEvents("Events");
  rootEvents.Add("/home/schmitz/sim/data/photonRun100_100refl.root");
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
  double XYMag=0;
  int fiberInc=0;
vector<double> wave;
int pmtCount=0;
int photonCount=0;
int numPhotonTracks=0;
//get data in file
  for (Long64_t i=0;i<nentries;i++) {
	//my issue may have to do with this
	rootEvents.GetEntry(i);

	//Photon Energies (before detection). size() evaluates to 100; each photon track seems to "contain" many smaller ones.
	if (b==0){
		numPhotonTracks = myROOTEvent->GetPhotonTracks()->size();
		if (numPhotonTracks>0){
			for (int k = 0; k < numPhotonTracks; k++) {
//				final_x = myROOTEvent->GetPhotonTracks()->at(k)->GetLastPositionX();
//				final_y = myROOTEvent->GetPhotonTracks()->at(k)->GetLastPositionY();
				final_z = myROOTEvent->GetPhotonTracks()->at(k)->GetLastPositionZ();
				if (final_z<0.0002){
					pmtCount++;
					EDep=myROOTEvent->GetPhotonTracks()->at(k)->GetInitialEnergy();
					wavelength=h*c/(EDep)*pow(10,9);
					wave.push_back(wavelength);
				}
				photonCount++;
			}
			}
		}
	else if (myROOTEvent->GetPMTRHits()->size()>0){
		for (int chit = 0; chit < myROOTEvent->GetPMTRHits()->size(); chit++) {
		//Post Detection
			EDep=myROOTEvent->GetPMTRHits()->at(chit)->GetInitialEDep();
			//the quantity below varies as the sim runs. this might be important
			//cout << "Photon Count: " << myROOTEvent->GetPMTRHits()->size() << endl;
			wavelength=h*c/(EDep)*pow(10,9);
			wave.push_back(wavelength);
			if (myROOTEvent->GetPMTRHits()->at(chit)->GetFiberToPMT()) fiberInc++;
//			if (i%100000==0) std::cout << "Energy: " << EDep << std::endl << "wavelength: " << wavelength << std::endl;
			//wavelength will be in nm
			//0,violet is 380 nm to 450 nm
			//1,blue is 450 nm to 495 nm
			//2,green is 495 nm to 570 nm
			//3,yellow is 570 nm to 590 nm
			//4,orange is 590 nm to 620 nm
			//5,red is 620 nm to 750 nm

		}
   }

	//graph the results

	//TGraph *gr = new TGraph();
	//TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);
	//gr->Draw("AB");
//std::cout << "WLS fiber efficency: " << WLSEff[colorNum] << std::endl << "color: " << colorNum << std::endl << "WLS Fiber counts: " << count[colorNum] << std:: endl << "counts overall in color: " << num[colorNum] << std::endl;


  //TH1F *hEDep = new TH1F("hAPD","Initial Energy Deposition",100,0,);
  //hEDep->GetXaxis()->SetTitle("Initial Energy Deposition (eV)");
  //hEDep->GetYaxis()->SetTitle("Bin Members");

  //TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);
  //ch.Draw("PMTHits->initalEDep_eV>>hEDep");
	}

TH1D *hWave= new TH1D("hWave","Wavelength spectrum",400,300,700);
for(int q=0;q<wave.size();q++){
	hWave->Fill(wave[q]);
}	
hWave->GetXaxis()->SetTitle("Wavelength (nm)");
hWave->GetYaxis()->SetTitle("Bin Members");

if (b==0) hWave->SetTitle("Pre-detection photon energy spectrum");
else hWave->SetTitle("Post-detection photon energy spectrum");

TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);
hWave->Draw();
if (b==0){
cout << "Photons generated: " << photonCount << endl;
cout << "Photons which were terminated on the PMT: " << pmtCount << endl;
cout << "Pct of all photons which terminated at the PMT: " << (double) pmtCount/photonCount << endl;
}
else {
cout << "Photons detected: " << (int) wave.size() << endl;
cout << "Photons detected in PMT from fiber: " << (int) fiberInc << endl;
}
wave.clear();
}
	
