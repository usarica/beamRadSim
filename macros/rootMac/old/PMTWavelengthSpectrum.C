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



void PMTWavelengthSpectrum(double waveMin, double waveMax,int step){

  TChain rootEvents("Events");
  rootEvents.Add("/data/chocula/schmitz/condor_output/HannahTestStand/data/4GeV_muon_fiber_photonRun_90refl.root");
  std::cout << "Reading file..." << std::endl;


  eurROOTEvent* myROOTEvent = new eurROOTEvent();
  rootEvents.SetBranchAddress("ROOTEvent", &myROOTEvent);
  Long64_t nentries=rootEvents.GetEntries();
  double *numDet = new double[step];
  double *wlsCount = new double[step];
  double *totalCount = new double[step]; 
  double *pmtCount = new double[step]; 
  for (int k=0; k<step; k++){
  	numDet[k]=0;
	wlsCount[k]=0;
	totalCount[k]=0;
	pmtCount[k]=0;
	}
  double EDep=0;
  double h=4.135668*pow(10,-15);
  double c=3*pow(10,8);
  double wavelength=0;
  double waveCutLo[step];
  double waveCutHi[step];
  double final_x=0;
  double final_y=0;
  double final_z=0;
  double mag_xy=0;
  int tick =0;
  int numPhotonTracks=0;
  double fiber_radius = 0.0005; //meters
for(int y=0; y<step; y++) {
	waveCutLo[y]=waveMin+(waveMax-waveMin)*y/step;
	waveCutHi[y]=waveMin+(waveMax-waveMin)*(y+1)/step;
}

  for (Long64_t i=0;i<nentries;i++) {
	rootEvents.GetEntry(i);

	numPhotonTracks = myROOTEvent->GetPhotonTracks()->size();
	if (numPhotonTracks>0){
		for (int k=0; k<numPhotonTracks; k++){
			final_z = myROOTEvent->GetPhotonTracks()->at(k)->GetLastPositionZ();				
				EDep=myROOTEvent->GetPhotonTracks()->at(k)->GetInitialEnergy();		
				wavelength=h*c/(EDep)*pow(10,9);
				for (int z = 0; z<step; z++) {
					if (wavelength > waveCutLo[z] && wavelength < waveCutHi[z]) {
						if (final_z==0) pmtCount[z]++;
						totalCount[z]++;
						break;
					}
				}	
			
		}
	}

	if (myROOTEvent->GetPMTRHits()->size()>0){
		for (int chit = 0; chit < myROOTEvent->GetPMTRHits()->size(); chit++) {
			EDep=myROOTEvent->GetPMTRHits()->at(chit)->GetInitialEDep();
			wavelength=h*c/(EDep)*pow(10,9);


//			if (i%100000==0) std::cout << "Energy: " << EDep << std::endl << "wavelength: " << wavelength << std::endl;
			//wavelength will be in nm
			//0,violet is 380 nm to 450 nm
			//1,blue is 450 nm to 495 nm
			//2,green is 495 nm to 570 nm
			//3,yellow is 570 nm to 590 nm
			//4,orange is 590 nm to 620 nm
			//5,red is 620 nm to 750 nm
			for (int z = 0; z<step; z++) {
				if (wavelength > waveCutLo[z] && wavelength < waveCutHi[z]) {					
//					if (myROOTEvent->GetPMTRHits()->at(chit)->GetFiberToPMT()) {
//						wlsCount[z]++; }
					numDet[z]++;
					break;
				}
			}	

		}
			//if (count==100000){ 
			//	std::cout << "Photon Energy at index " << chit << " is " << myROOTEvent->GetPMTRHits()->at(chit)->GetInitialEDep() << std::endl;
			//	count=0; }
			//count++;
	}
   }

  double *DetEff = new double[step];
  for(int j=0;j<step;j++) {
  	if (totalCount[j]==0) DetEff[j]=0; //use on 1st and 3rd
  	//if (pmtCount[j]==0) DetEff[j]=0; //use on 2nd
	//else DetEff[j]=numDet[j]/totalCount[j]; }                           //For a give wavelength, percentage of generated photons which were detected
	//else DetEff[j]=numDet[j]/pmtCount[j]; }                        // per wavelength, percentage of photons which were made incident on the PMT which were actually detected
	else DetEff[j]=pmtCount[j]/totalCount[j]; }                             //per wavelength, percentage of generated photons which were made incident on the PMT
	//graph the results
	TGraph *gr = new TGraph(step,waveCutLo,DetEff);
	TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);
	gr->Draw("AB");
//std::cout << "WLS fiber efficency: " << WLSEff[colorNum] << std::endl << "color: " << colorNum << std::endl << "WLS Fiber counts: " << count[colorNum] << std:: endl << "counts overall in color: " << num[colorNum] << std::endl;


  //TH1F *hEDep = new TH1F("hAPD","Initial Energy Deposition",100,0,);
  //hEDep->GetXaxis()->SetTitle("Initial Energy Deposition (eV)");
  //hEDep->GetYaxis()->SetTitle("Bin Members");

  //TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);
  //ch.Draw("PMTHits->initalEDep_eV>>hEDep");
}

