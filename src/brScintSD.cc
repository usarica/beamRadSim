/*
 * brScintSD.cc
 *
 *  Created on: 11.04.2013
 *      Author: heuermann
 */


#include "brScintSD.hh"
#include "brScintHit.hh"


#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include <G4StepPoint.hh>
#include "G4TouchableHistory.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4VProcess.hh"
#include "G4ios.hh"
#include <fstream>
#include <iostream>
#include "Randomize.hh"

using namespace::std;


brScintSD::brScintSD(G4String name)
:G4VSensitiveDetector(name),scintCollection(0), verbose(0)
{
  G4String HCname;
  collectionName.insert(HCname = "scintCollection");

  HCID= -1;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

brScintSD::~brScintSD(){

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void brScintSD::Initialize(G4HCofThisEvent* HCE)
{
  scintCollection = new brScintHitsCollection
                          (SensitiveDetectorName,collectionName[0]);


static G4int HCID = -1;
  if(HCID < 0)
  { HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]); }
  HCE->AddHitsCollection( HCID, scintCollection );

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool brScintSD::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{
return false;
}

G4bool brScintSD::ProcessHits2(const G4Step* aStep,G4TouchableHistory*)
{
      	G4TouchableHandle touchable = aStep->GetPreStepPoint()->GetTouchableHandle();
	G4String startVolume = aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName();
	G4String endVolume = aStep->GetPostStepPoint()->GetPhysicalVolume()->GetName();
        G4ThreeVector myEndDirection = aStep->GetPostStepPoint()->GetMomentumDirection();
	G4double theta=-1;
	if(aStep->GetTrack()->GetTrackID()!=1 && !startVolume.contains("Bulk") && endVolume.contains("Bulk")){
              theta = acos(std::abs(myEndDirection.dot(G4ThreeVector(-1,0,0)))); 
	      //eta = -log(tan(acos(std::abs(myEndDirection.dot(G4ThreeVector(-1,0,0))))/2));

//	      cout << theta << endl;
	}


//  const G4VProcess* process = aStep->GetPostStepPoint()->GetProcessDefinedStep();
  G4int npixel=10;
  G4int pixtot=npixel*npixel;
  G4int copyNo1=
    touchable->GetCopyNumber();
  G4int copyNo2=
    touchable->GetCopyNumber(1);

  G4int copyNo = copyNo1+copyNo2*pixtot;
//  if(copyNo2==1) copyNo+=copyNo2*1000;

  G4double edep = aStep->GetTotalEnergyDeposit();

  if(edep == 0.) return false;

//  G4ThreeVector point1 = aStep->GetPreStepPoint()->GetPosition();
//  G4ThreeVector point2 = aStep->GetPostStepPoint()->GetPosition();
//  G4ThreeVector pointE = point1 + G4UniformRand()*(point2 - point1);

//  const G4VProcess* creaProc= aStep->GetTrack()->GetCreatorProcess();
//  G4String procName;
//  G4String creaProcName;

//  if (process) procName = process->GetProcessName();
//  else procName = "0";

//  if (creaProc) creaProcName = creaProc->GetProcessName();
//  else creaProcName = "0";

  brScintHit* hit = new brScintHit();


	  hit = new brScintHit(); //so create new hit
      //
	  hit->SetTrackID  (aStep->GetTrack()->GetTrackID());          // trackID
	  hit->SetParentID (aStep->GetTrack()->GetParentID());         // parentID
	  hit->SetCopyNo(copyNo);
	  // hit->SetVtxPos   (aStep->GetTrack()->GetVertexPosition());
	  //hit->SetProcName (procName);
	  //hit->SetVtxProcName(creaProcName);
	  //hit->SetStripNo(  touchable->GetReplicaNumber(0) );
	  //hit->SetEkin     (aStep->GetPreStepPoint()->GetKineticEnergy()); // kinetic Energy
	  //hit->SetEdep     (edep);                         // set initial value of energy deposit
	  //hit->SetEvtx     (aStep->GetTrack()->GetVertexKineticEnergy());
//	  hit->SetInitialHitTime(aStep->GetPreStepPoint()->GetGlobalTime());// Global Time
	  //hit->SetLocal    (aStep->GetPreStepPoint()->GetLocalTime());  // Local Time
	  //hit->SetLocalPos (localPointE); // local position
	  //hit->SetMomentum( aStep->GetPreStepPoint()->GetMomentum());
	  hit->SetParticleName( aStep->GetTrack()->GetDefinition()->GetParticleName() );
	  //hit->SetVtxVolName (touchable->GetVolume()->GetLogicalVolume()->GetName());
	  //hit->SetProcName (process->GetProcessName());
//	  hit->SetHitPosition(aStep->GetPreStepPoint()->GetPosition());
	  //hit->SetPosLocal (touchable->GetHistory()->GetTopTransform().TransformPoint(pointE));
	  //hit->SetpName (aStep->GetTrack()->GetDefinition()->GetParticleName()); //particle name
	  hit->SetEDep(edep); //energy deposit
	  hit->SetScatterAngle(theta); //energy deposit
	  //hit->SetWeight(aStep->GetTrack()->GetWeight());
	  //if (aStep->GetTrack()->GetDefinition()->GetParticleName().contains("neutron")){
		  //const G4TrackVector *mySecondaries = aStep->GetSecondary();
          //
		  //for (size_t i = 0; i < mySecondaries->size(); i++) {
          //
	  	  //		G4String secParticle =
	  	  //				(*mySecondaries)[i]->GetDefinition()->GetParticleName();
          //
	  	  //		if (secParticle.contains("Ge")) {
	  	  //			G4cout << aStep->GetTrack()->GetDefinition()->GetParticleName() << ": Secondary Ge" << G4endl;
	  	  //			G4cout << "Track ID: " << aStep->GetTrack()->GetTrackID() << G4endl;
	  	  //			G4cout << "Step length: " << aStep->GetStepLength() << G4endl;
	  	  //			G4cout << "Non Ionizing Energy Deposit: " << aStep->GetNonIonizingEnergyDeposit() << G4endl;
	  	  //			G4cout << "Ge Track ID: " << (*mySecondaries)[i]->GetTrackID() << G4endl;
	  	  //		}
          //
	  	  //}
	  scintCollection->insert(hit);

  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void brScintSD::EndOfEvent(G4HCofThisEvent*)
{
  if (verbose>0) {

     G4int NbHits = scintCollection->entries();
     G4cout << "\n-------->Hits Collection: in this event they are " << NbHits
            << " hits in the scint : " << G4endl;
     for (G4int i=0;i<NbHits;i++){
    	 //if ((*scintCollection)[i]->GetCopyNo() > 0)
    	 (*scintCollection)[i]->Print();
     }

   }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

