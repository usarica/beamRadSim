/*
 * brUserEventInformation.cc
 *
 *  Created on: 22.04.2019
 *      Author: schmitz
 */

#include "brUserEventInformation.hh"
#include "brPhotonTrack.hh"
#include "brGammaTrack.hh"
#include "brNeutronTrack.hh"
#include "brMuonTrack.hh"
#include "brROOTEvent.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include <vector>

template<class SequenceType>
void DeleteAll(SequenceType& sequence) {
	for (typename SequenceType::iterator it = sequence.begin(); it != sequence.end(); ++it) {
		delete (*it);
	}
	sequence.clear();
}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
brUserEventInformation::brUserEventInformation()
  :GammaTracks(0),NbOfGammaTracks(0),
   NeutronTracks(0),NbOfNeutronTracks(0),
   PhotonTracks(0),NbOfPhotonTracks(0),
   MuonTracks(0),NbOfMuonTracks(0),
   PMTHits(0),NbOfPMTHits(0),
   ScintHits(0), NbOfScintHits(0),
   peCountPMT(0),absorptionCount(0),boundaryAbsorptionCount(0),
   totalEDepInCrystals(0.),totalNREDepInCrystals(0.),
   pmtsAboveThreshold(0),
   photonCount_Scint(0),
   photonCount(0),
   photonCount_Cheren(0),
   //primMutrackLength(0.),
   protScat(0.),
   Edep_MeV_Si1(0.),
   Edep_MeV_Si2(0.),
   Edep_MeV_Si3(0.),
   Edep_MeV_Si4(0.),
   Edep_MeV_Si5(0.),
   Edep_MeV_Abs1(0.),
   Edep_MeV_Abs2(0.),
   Edep_MeV_Abs3(0.),
   Edep_MeV_Abs4(0.),
   Edep_MeV_ScintVeto(0.),
   runID(-1), eventID(-1),
   photonLastTrackID(-1),gammaLastTrackID(-1), neutronLastTrackID(-1),muonLastTrackID(-1),
   //tankDistance(0.),
   gammaOutScintillator(false),
   muonTrig(false),
   scintToPMT(false),
   energyEnterScinti_MeV(0.),energyExitScinti_MeV(0.),
   barHit(0)
{
}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
brUserEventInformation::~brUserEventInformation()
{
	this->Reset();
}
void brUserEventInformation::Initialize() {

}
void brUserEventInformation::Finalize() {


	// Sort the track collection, so that time(track_n)<time(track_n+1), because this ordering is needed in the offline analysis
	std::sort(PhotonTracks.begin(), PhotonTracks.end(),
				brPhotonTrack::compareHits);

	std::sort(GammaTracks.begin(), GammaTracks.end(),
				brGammaTrack::compareHits);

	std::sort(NeutronTracks.begin(), NeutronTracks.end(),
				brNeutronTrack::compareHits);

	std::sort(MuonTracks.begin(), MuonTracks.end(),
				brMuonTrack::compareHits);
	
	// Sort the hit collection, so that time(hit_n)<time(hit_n+1), because this ordering is needed in the offline analysis
	std::sort(PMTHits.begin(), PMTHits.end(),
			brPMTHit::compareHits);

	// Sort the hit collection, so that time(hit_n)<time(hit_n+1), because this ordering is needed in the offline analysis
	std::sort(ScintHits.begin(), ScintHits.end(),
			brScintHit::compareHits);

	NbOfNeutronTracks = NeutronTracks.size();
	NbOfGammaTracks = GammaTracks.size();
	NbOfPhotonTracks = PhotonTracks.size();
	NbOfMuonTracks = MuonTracks.size();
	NbOfPMTHits = PMTHits.size();
	NbOfScintHits = ScintHits.size();
}

void brUserEventInformation::Reset() {
	//Calls the destructor of the elements of the vector. Afterwards the elements are removed from the vector

	DeleteAll(GammaTracks);
	DeleteAll(NeutronTracks);
	DeleteAll(PhotonTracks);
	DeleteAll(MuonTracks);

	PMTHits.clear(); // G4VHit takes care of the delete
	ScintHits.clear();// G4VHit takes care of the delete

	NbOfNeutronTracks = 0;
	NbOfGammaTracks   = 0;
	NbOfPhotonTracks = 0;
	NbOfMuonTracks   = 0;
	NbOfPMTHits      = 0;
	NbOfScintHits     = 0;
}

void brUserEventInformation::SetEventID(G4int EventID) {
	this->eventID = EventID;
}

G4int brUserEventInformation::GetEventID()const{
	return this->eventID;
}

void brUserEventInformation::SetRunID(G4int RunID) {
	this->runID = RunID;
}

G4int brUserEventInformation::GetRunID()const{
	return this->runID;
}

//////////////////////gamma//////////////////////////////////

void brUserEventInformation::AddGammaTrack(brGammaTrack *mtrack){
	this->GammaTracks.push_back(mtrack);
}

brGammaTrack* brUserEventInformation::GetGammaTrack(G4int trackID){

	G4int ID = -1;

	for (G4int i = 0; i < GammaTracks.size(); i++){
		 if (this->GammaTracks.at(i)->GetTrackID() == trackID)

			 ID = i;

	}
	return this->GammaTracks.at(ID);

}


brGammaTrackVector* brUserEventInformation::GetGammaTracks(){
	return &GammaTracks;
}

///////////////////////Neutron/////////////////////////////

void brUserEventInformation::AddNeutronTrack(brNeutronTrack *ntrack) {

	this->NeutronTracks.push_back(ntrack);
}

brNeutronTrack* brUserEventInformation::GetNeutronTrack(G4int trackID){

	G4int ID = -1;
	for (G4int i = 0; i < NeutronTracks.size(); i++){
		 if (this->NeutronTracks.at(i)->GetTrackID() == trackID)

			 ID = i;

	}
	return this->NeutronTracks.at(ID);

}

brNeutronTrackVector* brUserEventInformation::GetNeutronTracks(){
	return &NeutronTracks;
}

////////////////////////muon///////////////////////////

void brUserEventInformation::AddMuonTrack(brMuonTrack *ntrack) {

	this->MuonTracks.push_back(ntrack);
}

brMuonTrack* brUserEventInformation::GetMuonTrack(G4int trackID){

	G4int ID = -1;
	for (G4int i = 0; i < MuonTracks.size(); i++){
		 if (this->MuonTracks.at(i)->GetTrackID() == trackID)

			 ID = i;

	}
	return this->MuonTracks.at(ID);

}

brMuonTrackVector* brUserEventInformation::GetMuonTracks(){
	return &MuonTracks;
}


////////////////////photon////////////////////////////

void brUserEventInformation::AddPhotonTrack(brPhotonTrack *ptrack) {

	this->PhotonTracks.push_back(ptrack);

}

brPhotonTrack* brUserEventInformation::GetPhotonTrack(G4int trackID){

	G4int ID = -1;
	for (G4int i = 0; i < PhotonTracks.size(); i++){
		 if (this->PhotonTracks.at(i)->GetTrackID() == trackID)

			 ID = i;

	}
	return this->PhotonTracks.at(ID);

}


brPhotonTrackVector* brUserEventInformation::GetPhotonTracks(){
	return &PhotonTracks;
}

//////////////////////PMTHit////////////////////////

void brUserEventInformation::AddPMTHit(brPMTHit *hit) {
	this->PMTHits.push_back(hit);
}

brPMTHitVector* brUserEventInformation::GetPMTHits(){
	return &PMTHits;
}

//////////////////ScintHit////////////////////////////

void brUserEventInformation::AddScintHit(brScintHit *hit) {
	this->ScintHits.push_back(hit);
}

brScintHitVector* brUserEventInformation::GetScintHits(){
	return &ScintHits;
}







////////////////////Store Data in ROOT//////////////////////

brROOTEvent* brUserEventInformation::ConvertToROOTEvent(){

	//convert information stored in UserEventInformation into TObject

	brROOTEvent *myROOTEvent = new brROOTEvent();
	myROOTEvent->SetAbsorptionCount(this->GetAbsorptionCount());
	myROOTEvent->SetBoundaryAbsorption(this->GetBoundaryAbsorptionCount());
	myROOTEvent->SetEventID(this->GetEventID());
	myROOTEvent->SetGammaTracks(this->GetGammaTracks());
	myROOTEvent->SetNeutronTracks(this->GetNeutronTracks());
	myROOTEvent->SetMuonTracks(this->GetMuonTracks());
	myROOTEvent->SetPMTHitCount(this->GetPECountPMT());
	//convert G4hits into ROOT hits:

	for (Int_t i = 0; i < this->PMTHits.size(); i++){

		 myROOTEvent->AddPMTRHit(this->PMTHits.at(i)->ConvertToROOTHit());
	}


	//convert G4hits into ROOT hits:

	for (Int_t i = 0; i < this->ScintHits.size(); i++){

		 myROOTEvent->AddScintRHit(this->ScintHits.at(i)->ConvertToROOTHit());
	}
	myROOTEvent->SetPMTSAboveThreshold(this->GetPMTSAboveThreshold());
	myROOTEvent->SetPhotonCountCeren(this->GetPhotonCount_Cheren());
	myROOTEvent->SetPhotonCountScint(this->GetPhotonCount_Scint());
	myROOTEvent->SetPhotonTracks(this->GetPhotonTracks());
	myROOTEvent->SetGammaOutScintillator(this->GetGammaOutScintillator());
	myROOTEvent->SetMuonTrigger(this->GetMuonTrigger());
	myROOTEvent->SetScintToPMT(this->GetScintToPMT());
	myROOTEvent->SetEnergyEnterScinti(this->GetEnergyEnterScinti());
	myROOTEvent->SetEnergyExitScinti(this->GetEnergyExitScinti());
	myROOTEvent->SetProtonScatter(this->GetProtonScatter());
	myROOTEvent->SetEventEnergyDepositSi1(this->GetEventEnergyDepositSi1());
	myROOTEvent->SetEventEnergyDepositSi2(this->GetEventEnergyDepositSi2());
	myROOTEvent->SetEventEnergyDepositSi3(this->GetEventEnergyDepositSi3());
	myROOTEvent->SetEventEnergyDepositSi4(this->GetEventEnergyDepositSi4());
	myROOTEvent->SetEventEnergyDepositSi5(this->GetEventEnergyDepositSi5());
	myROOTEvent->SetEventEnergyDepositAbs1(this->GetEventEnergyDepositAbs1());
	myROOTEvent->SetEventEnergyDepositAbs2(this->GetEventEnergyDepositAbs2());
	myROOTEvent->SetEventEnergyDepositAbs3(this->GetEventEnergyDepositAbs3());
	myROOTEvent->SetEventEnergyDepositAbs4(this->GetEventEnergyDepositAbs4());
	myROOTEvent->SetEventEnergyDepositScintVeto(this->GetEventEnergyDepositScintVeto());
	myROOTEvent->SetBarHit(this->GetBarHit());
  return myROOTEvent;

}



