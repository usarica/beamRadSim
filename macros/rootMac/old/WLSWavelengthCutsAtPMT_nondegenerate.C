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
#include <set>


void WLSWavelengthCutsAtPMT_nondegenerate(double waveMin, double waveMax,int step){

  TChain rootEvents("Events");
  rootEvents.Add("/data/chocula/schmitz/condor_output/HannahTestStand/data/4GeV_muon_fiber_photonRun_100refl.root");
  std::cout << "Reading file..." << std::endl;


  eurROOTEvent* myROOTEvent = new eurROOTEvent();
  rootEvents.SetBranchAddress("ROOTEvent", &myROOTEvent);
  Long64_t nentries=rootEvents.GetEntries();
  double *numDet = new double[step];
  double *wlsCount = new double[step];
  double *wlsPreCount = new double[step]; 
  double *pmtCount = new double[step]; 
  double *totalCount = new double[step]; 
  for (int k=0; k<step; k++){
  	numDet[k]=0;
	wlsCount[k]=0;
	wlsPreCount[k]=0;
	pmtCount[k]=0;
	totalCount[k]=0;
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
  
  set<double> wlsParentID;
  int tick =0;
  int parentID;
  int trackID;
  bool wls_conv;
  int wls=0;

  int numPhotonTracks=0;
  double fiber_radius = 0.0005; //meters
for(int y=0; y<step; y++) {
	waveCutLo[y]=waveMin+(waveMax-waveMin)*y/step;
	waveCutHi[y]=waveMin+(waveMax-waveMin)*(y+1)/step;
}

  for (Long64_t i=0;i<nentries;i++) {
	
	rootEvents.GetEntry(i);
	//Photon Energies (before detection). size() evaluates to 100; each photon track seems to "contain" many smaller ones.
		numPhotonTracks = myROOTEvent->GetPhotonTracks()->size();
		if (numPhotonTracks>0){
			for (int k = 0; k < numPhotonTracks; k++) {
				parentID= myROOTEvent->GetPhotonTracks()->at(k)->GetParentID();
				wls_conv=myROOTEvent->GetPhotonTracks()->at(k)->GetWLSConversion();
				if (wls_conv){
					wls++;
					wlsParentID.insert(parentID+10000000*i); //ten million times i plus parent ID; this makes sure we don't throw out good tracks by accident
				}
			}
		}
	}


  for (Long64_t i=0;i<nentries;i++) {
	rootEvents.GetEntry(i);

	numPhotonTracks = myROOTEvent->GetPhotonTracks()->size();
	if (numPhotonTracks>0){
		for (int k=0; k<numPhotonTracks; k++){
			trackID = myROOTEvent->GetPhotonTracks()->at(k)->GetTrackID();
			if (wlsParentID.find(trackID+10000000*i)==wlsParentID.end()) { //rule out double counted photon tracks
				final_z = myROOTEvent->GetPhotonTracks()->at(k)->GetLastPositionZ();
				
				//if (final_z == 0){
					
					wls_conv=myROOTEvent->GetPhotonTracks()->at(k)->GetWLSConversion();
					
					//time consuming, but best method to recover original spectrum
					if (wls_conv){
						parentID=myROOTEvent->GetPhotonTracks()->at(k)->GetParentID();
						EDep=myROOTEvent->GetPhotonTrack(parentID)->GetInitialEnergy();
						wls_conv=myROOTEvent->GetPhotonTrack(parentID)->GetWLSConversion();
					while (wls_conv){
						parentID=myROOTEvent->GetPhotonTrack(parentID)->GetParentID();
						EDep=myROOTEvent->GetPhotonTrack(parentID)->GetInitialEnergy();
						wls_conv=myROOTEvent->GetPhotonTrack(parentID)->GetWLSConversion();
						}
					}
				        else EDep=myROOTEvent->GetPhotonTracks()->at(k)->GetInitialEnergy();		
					wavelength=h*c/(EDep)*pow(10,9);
					
					for (int z = 0; z<step; z++) {
						if (wavelength > waveCutLo[z] && wavelength < waveCutHi[z]) {
							if (final_z == 0){
								final_x = myROOTEvent->GetPhotonTracks()->at(k)->GetLastPositionX();
								final_y = myROOTEvent->GetPhotonTracks()->at(k)->GetLastPositionY();
								mag_xy=sqrt(pow(final_x,2)+pow(final_y,2));
								
								if (mag_xy <= fiber_radius){
									wlsPreCount[z]++;
								}

							pmtCount[z]++;
							}
							totalCount[z]++;
						break;
						}
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
					if (myROOTEvent->GetPMTRHits()->at(chit)->GetFiberToPMT()) {
						wlsCount[z]++; }
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
   cout << "Progress: " << i << " out of 100" << endl;
   
   }

  double *WLSEff = new double[step];
  for(int j=0;j<step;j++) {
  	//if (pmtCount[j]==0) WLSEff[j]=0; //use on 1st and 2nd
  	//if (numDet[j]==0) WLSEff[j]=0; //use on 3rd
  	if (totalCount[j]==0) WLSEff[j]=0; //use on 4th	
	//if (numDet[j]==0||wlsPreCount[j]==0||pmtCount[j]==0) WLSEff[j]=0; //use on last
	//else WLSEff[j]=wlsCount[j]/pmtCount[j]; }                           //Standard, WLS eff. with # photons reaching PMT as denominator
	//else WLSEff[j]=wlsPreCount[j]/pmtCount[j]; }                        //WLS Efficiency prior to applying quantum efficiency
	//else WLSEff[j]=wlsCount[j]/numDet[j]; }                             //WLS Efficiency after applying quantum efficiency
	else WLSEff[j]=wlsCount[j]/totalCount[j]; }                         //true WLS Efficiency (detected WLS photons over all generated photons, non-double counted
	//else WLSEff[j]=wlsCount[j]/numDet[j]/(wlsPreCount[j]/pmtCount[j]); } //ratio of WLS Efficiency Pre/Post application of quantum efficiency
									      		//greater than 1 = relatively more photons from the fiber were detected as compared to a typical photon
	//graph the results
	TGraph *gr = new TGraph(step,waveCutLo,WLSEff);
	TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);
	gr->Draw("AB");
//std::cout << "WLS fiber efficency: " << WLSEff[colorNum] << std::endl << "color: " << colorNum << std::endl << "WLS Fiber counts: " << count[colorNum] << std:: endl << "counts overall in color: " << num[colorNum] << std::endl;


  //TH1F *hEDep = new TH1F("hAPD","Initial Energy Deposition",100,0,);
  //hEDep->GetXaxis()->SetTitle("Initial Energy Deposition (eV)");
  //hEDep->GetYaxis()->SetTitle("Bin Members");

  //TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);
  //ch.Draw("PMTHits->initalEDep_eV>>hEDep");
}
	
