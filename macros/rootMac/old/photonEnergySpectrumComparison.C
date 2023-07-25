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
#include "TMultiGraph.h"
using namespace std;


void photonEnergySpectrumComparison(){

//retreive file

  TChain rootEvents("Events");
  rootEvents.Add("/data/chocula/schmitz/condor_output/HannahTestStand/data/4GeV_muon_fiber_photonRun.root");
  std::cout << "Reading file..." << std::endl;
  eurROOTEvent* myROOTEvent = new eurROOTEvent();
  rootEvents.SetBranchAddress("ROOTEvent", &myROOTEvent);
  Long64_t nentries=rootEvents.GetEntries();

//initialize variables
  double EDep=0;
  double h=4.135668*pow(10,-15);
  double c=3*pow(10,8);
  double wavelength;

vector<double> wave;
int index=0;
int numPhotonTracks=0;
int binNum=400;
int binMin=300;
int binMax=700;
int maxVal=0;
int maxBin=0;

//get data in file
  for (Long64_t i=0;i<nentries;i++) {
	rootEvents.GetEntry(i);

	//Photon Energies (before detection). size() evaluates to 100; each photon track seems to "contain" many smaller ones.
	numPhotonTracks = myROOTEvent->GetPhotonTracks()->size();
	if (numPhotonTracks>0){
			for (int k = 0; k < numPhotonTracks; k++) {
				EDep=myROOTEvent->GetPhotonTracks()->at(k)->GetInitialEnergy();
				//myROOTEvent->GetPhotonTracks()->size()=varying, large number
				//myROOTEvent->GetPhotonTrack(i) has a range for i of 0 to nentries-1
				wavelength=h*c/(EDep)*pow(10,9);
				wave.push_back(wavelength);
			}
		}
	}
	
	double binX[binNum];
	double relativeOutput[binNum];
	
	TH1D *hWave1= new TH1D("hWave1","Wavelength spectrum",binNum,binMin,binMax);
	for(int q=0;q<wave.size();q++){
		hWave1->Fill(wave[q]);
	}
	maxBin=hWave1->GetMaximumBin();
	maxVal=hWave1->GetBinContent(maxBin);
	for(int n=0;n<binNum;n++){
		relativeOutput[n]=hWave1->GetBinContent(n)/maxVal;
		binX[n]=(double) n+binMin;//binX[n]=binMin+(binMax-binMin)*(n+0.5)/binNum; //x bin will be located at center of each binning range
		if (n%25==0) cout << "relativeOutput (top): " << relativeOutput[n] << endl;
	}
	TGraph *gr1 = new TGraph (binNum,binX,relativeOutput);	
	TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);
	wave.clear();
	gr1->SetMarkerColor(2);
	gr1->GetXaxis()->SetTitle("Wavelength (nm)");
	gr1->GetYaxis()->SetTitle("Relative output");
	gr1->SetTitle("Relative output, before and after detection");
	gr1->Draw("AC");		
	
  for (Long64_t i=0;i<nentries;i++) {
	rootEvents.GetEntry(i);

	if (myROOTEvent->GetPMTRHits()->size()>0){
		for (int chit = 0; chit < myROOTEvent->GetPMTRHits()->size(); chit++) {
		//Post Detection
			EDep=myROOTEvent->GetPMTRHits()->at(chit)->GetInitialEDep();
			//the quantity below varies as the sim runs. this might be important
			//cout << "Photon Count: " << myROOTEvent->GetPMTRHits()->size() << endl;
			wavelength=h*c/(EDep)*pow(10,9);
			wave.push_back(wavelength);


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


TH1D *hWave2= new TH1D("hWave1","Wavelength spectrum",binNum,binMin,binMax);
for(int q=0;q<wave.size();q++){
	hWave2->Fill(wave[q]);
}
maxBin=hWave2->GetMaximumBin();
maxVal=hWave2->GetBinContent(maxBin);
for(int n=0;n<binNum;n++){
	relativeOutput[n]=hWave2->GetBinContent(n)/maxVal;
	binX[n]=(double) n+binMin;//binX[n]=binMin+(binMax-binMin)*(n+0.5)/binNum; //x bin will be located at center of each binning range
	if (n%25==0) cout << "relativeOutput: " << relativeOutput[n] << endl;
	}

TGraph *gr2 = new TGraph (binNum,binX,relativeOutput);	
gr2->SetMarkerColor(5);
gr2->Draw("Same");		
//mg->Add(gr1);
//mg->Add(gr2);
//mg->Draw("LP");
wave.clear();
}
	
