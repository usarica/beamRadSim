/*
 * brROOTEvent.cc
 *
 *  Created on: 22.04.2019
 *      Author: schmitz
 */

#include "brROOTEvent.hh"
#include "brPhotonTrack.hh"
#include "brGammaTrack.hh"
#include "brNeutronTrack.hh"
#include "brMuonTrack.hh"
#include "brPMTRHit.hh"
#include "brScintRHit.hh"
#include <algorithm>
#include <vector>

template<class SequenceType>
void DeleteAll(SequenceType& sequence) {
	for (typename SequenceType::iterator it = sequence.begin(); it != sequence.end(); ++it) {
		delete (*it);
	}
	sequence.clear();
}
ClassImp(brROOTEvent)
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
brROOTEvent::brROOTEvent()
  : eventID(-1),
   GammaTracks(0),NbOfGammaTracks(0),
   NeutronTracks(0),NbOfNeutronTracks(0),
   PhotonTracks(0),NbOfPhotonTracks(0),
   MuonTracks(0),NbOfMuonTracks(0),
   PMTHits(0),NbOfPMTHits(0),
   totalNbOfPEPMT(0),
   ScintRHits(0), NbOfScintRHits(0),
   nbOfCerenkovPhotons(0),nbOfScintillationPhotons(0),absorptionCount(0),
   boundaryAbsorptionCount(0),
   pmtsAboveTrigger(0),
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
   gammaOutScintillator(false),
   scintToPMT(false), muonTrig(false),
   energyEnterScinti_MeV(0.), energyExitScinti_MeV(0.),
   barHit(0)
{
}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
brROOTEvent::~brROOTEvent()
{
	this->Reset();
}
void brROOTEvent::Initialize() {

}
void brROOTEvent::Finalize() {


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
			brPMTRHit::compareHits);

	//Sort the hit collection, so that time(hit_n)<time(hit_n+1), because this ordering is needed in the offline analysis
	std::sort(ScintRHits.begin(), ScintRHits.end(),
			brScintRHit::compareHits);

	NbOfNeutronTracks = NeutronTracks.size();
	NbOfGammaTracks = GammaTracks.size();
	NbOfPhotonTracks = PhotonTracks.size();
	NbOfMuonTracks = MuonTracks.size();
	NbOfPMTHits = PMTHits.size();
	NbOfScintRHits = ScintRHits.size();
}

void brROOTEvent::Reset() {
	//Calls the destructor of the elements of the vector. Afterwards the elements are removed from the vector

	DeleteAll(GammaTracks);
	DeleteAll(NeutronTracks);
	DeleteAll(PhotonTracks);
	DeleteAll(MuonTracks);
	DeleteAll(PMTHits);
	DeleteAll(ScintRHits);


	NbOfNeutronTracks = 0;
	NbOfGammaTracks    = 0;
	NbOfPhotonTracks  = 0;
	NbOfMuonTracks    = 0;
	NbOfPMTHits       = 0;
	NbOfScintRHits   = 0;
}


//////////////////////gamma/////////////////////////////////////

void brROOTEvent::AddGammaTrack(brGammaTrack *mtrack) {

	this->GammaTracks.push_back(mtrack);
}

void brROOTEvent::SetGammaTracks(brGammaTrackVector *trackVec){
	this->GammaTracks = *trackVec;
}


brGammaTrack* brROOTEvent::GetGammaTrack(Int_t trackID) {

	Int_t ID = -1;
	for (Int_t i = 0; i < GammaTracks.size(); i++){
		 if (this->GammaTracks.at(i)->GetTrackID() == trackID)

			 ID = i;

	}
	return this->GammaTracks.at(ID);

}


brGammaTrackVector* brROOTEvent::GetGammaTracks() {
	return &GammaTracks;
}

/////////////////////////Neutron/////////////////////////////////////////////

void brROOTEvent::SetNeutronTracks(brNeutronTrackVector *trackVec){
	this->NeutronTracks = *trackVec;
}



void brROOTEvent::AddNeutronTrack(brNeutronTrack *ntrack) {

	this->NeutronTracks.push_back(ntrack);
}

brNeutronTrack* brROOTEvent::GetNeutronTrack(Int_t trackID) {

	Int_t ID = -1;
	for (Int_t i = 0; i < NeutronTracks.size(); i++){
		 if (this->NeutronTracks.at(i)->GetTrackID() == trackID)

			 ID = i;

	}
	return this->NeutronTracks.at(ID);

}


brNeutronTrackVector* brROOTEvent::GetNeutronTracks() {
	return &NeutronTracks;
}

//////////////////Muon////////////////////////


void brROOTEvent::SetMuonTracks(brMuonTrackVector *trackVec){
	this->MuonTracks = *trackVec;
}



void brROOTEvent::AddMuonTrack(brMuonTrack *ntrack) {

	this->MuonTracks.push_back(ntrack);
}

brMuonTrack* brROOTEvent::GetMuonTrack(Int_t trackID) {

	Int_t ID = -1;
	for (Int_t i = 0; i < MuonTracks.size(); i++){
		 if (this->MuonTracks.at(i)->GetTrackID() == trackID)

			 ID = i;

	}
	return this->MuonTracks.at(ID);

}


brMuonTrackVector* brROOTEvent::GetMuonTracks() {
	return &MuonTracks;
}
////////////////Photon/////////////////////////

void brROOTEvent::AddPhotonTrack(brPhotonTrack *ptrack) {

	this->PhotonTracks.push_back(ptrack);

}

brPhotonTrack* brROOTEvent::GetPhotonTrack(Int_t trackID) {

	Int_t ID = -1;
	for (Int_t i = 0; i < PhotonTracks.size(); i++){
		 if (this->PhotonTracks.at(i)->GetTrackID() == trackID)

			 ID = i;

	}
	return this->PhotonTracks.at(ID);

}

void brROOTEvent::SetPhotonTracks(brPhotonTrackVector *trackVec){
	this->PhotonTracks = *trackVec;
}


brPhotonTrackVector* brROOTEvent::GetPhotonTracks() {
	return &PhotonTracks;
}

////////////////PMTHit//////////////////////////////////

void brROOTEvent::AddPMTRHit(brPMTRHit *hit) {
	this->PMTHits.push_back(hit);
}

void brROOTEvent::SetPMTRHits(brPMTRHitVector *hitVec){
	this->PMTHits = *hitVec;
}

brPMTRHitVector* brROOTEvent::GetPMTRHits() {
	return &PMTHits;
}

//////////////////ScintHit///////////////////////////////

void brROOTEvent::AddScintRHit(brScintRHit *hit) {
	this->ScintRHits.push_back(hit);
}

brScintRHitVector* brROOTEvent::GetScintRHits() {
	return &ScintRHits;
}


