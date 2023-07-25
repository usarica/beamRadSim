/*
 * brScintHit.cc
 *
 *  Created on: 22.04.2019
 *      Author: schmitz
 */

#include "brScintHit.hh"
// Includes Physical Constants and System of Units
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4THitsCollection.hh"

G4Allocator<brScintHit> brScintHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

brScintHit::brScintHit():
	trackID(-1), parentID(-1), copyNo(-1),
	EDep(0.),
	EDepRecoil(0.),
	particleName(""),
	initialHitTime(0.),//finalHitTime(0.),
	hitPosition(0.,0.,0.)

{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

brScintHit::~brScintHit() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

brScintHit::brScintHit(const brScintHit& right)
  : G4VHit()
{
	trackID         = right.trackID        ;
    parentID        = right.parentID       ;
    copyNo        = right.copyNo       ;
    EDep            = right.EDep           ;
    EDepRecoil      = right.EDepRecoil     ;
    particleName    = right.particleName   ;
    initialHitTime  = right.initialHitTime ;
    //finalHitTime  = right.finalHitTime ; //ToDo
    hitPosition     = right.hitPosition    ;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const brScintHit& brScintHit::operator=(const brScintHit& right)
{
	trackID         = right.trackID        ;
    parentID        = right.parentID       ;
    copyNo        = right.copyNo       ;
    EDep            = right.EDep           ;
    EDepRecoil      = right.EDepRecoil     ;
    particleName    = right.particleName   ;
    initialHitTime  = right.initialHitTime ;
    //finalHitTime  = right.finalHitTime ; TODO
    hitPosition     = right.hitPosition    ;

    return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4int brScintHit::operator==(const brScintHit& right) const
{
  return (this==&right) ? 1 : 0;
}


//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
bool brScintHit::compareHits(brScintHit* const &a, brScintHit* const &b){
	G4double aTime = a->initialHitTime;
	G4double bTime = b->initialHitTime;
	return (aTime < bTime);
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void brScintHit::Draw()
{
  //G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  //if(pVVisManager)
  //{
  //  G4Circle circle(pos);
  //  circle.SetScreenSize(2.);
  //  circle.SetFillStyle(G4Circle::filled);
  //  G4Colour colour(1.,0.,0.);
  //  G4VisAttributes attribs(colour);
  //  circle.SetVisAttributes(attribs);
  //  pVVisManager->Draw(circle);
  //}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void brScintHit::Print()
{
	//if(pName.contains("Ge")){ //only print info if it is a Ge
		G4cout  << "  trackID  : " << trackID
				<< "  Particle : " << particleName
				<< "  Parent ID: " << parentID
				<< "  Energy   : " << G4BestUnit(EDep,"Energy")
				//<< "  Nuclear recoil deposit: " << G4BestUnit(EDepRecoil,"Energy")
				<< "  Position : " << G4BestUnit(hitPosition,"Length") << G4endl;
	//}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

brScintRHit* brScintHit::ConvertToROOTHit() const{

  brScintRHit *myROOTHit = new brScintRHit();

  myROOTHit->SetEDep(this->GetEDep());
  myROOTHit->SetScatterAngle(this->GetScatterAngle());
  myROOTHit->SetCopyNo(this->GetCopyNo());
  //myROOTHit->SetEDepRecoil(this->GetEDepRecoil()/keV);
  myROOTHit->SetHitPositionX(this->GetHitPosition().getX()/cm);
  myROOTHit->SetHitPositionY(this->GetHitPosition().getY()/cm);
  myROOTHit->SetHitPositionZ(this->GetHitPosition().getZ()/cm);
  myROOTHit->SetInitialHitTime(this->GetInitialHitTime()/ns);
  //myROOTHit->SetFinalHitTime(this->GetFinalHitTime());
  myROOTHit->SetParentID(this->GetParentID());
  myROOTHit->SetParticleName(this->GetParticleName());
  myROOTHit->SetTrackID(this->GetTrackID());


  return myROOTHit;

}


