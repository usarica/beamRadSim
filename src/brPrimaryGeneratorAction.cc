#include "brPrimaryGeneratorAction.hh"
#include "brDetectorConstruction.hh"
#include "brPrimaryGeneratorActionMessenger.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"
#include "G4UnitsTable.hh"
// Includes Physical Constants and System of Units
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

brPrimaryGeneratorAction::brPrimaryGeneratorAction(brDetectorConstruction* myDC) :
  	  myDetector(myDC), myParticleGun(NULL), myGeneralParticleSource(NULL),
  	  verbosity(1), MsgPrefix(""), sourceID(0),
  	  useGeantinos(false), myParticleTable(NULL),
  	  UseDefaultSeeds(true){

    MsgPrefix = "brPrimaryGeneratorAction> ";
    myMessenger = new brPrimaryGeneratorActionMessenger(this);
    this->InitPGA();
    myParticleTable = G4ParticleTable::GetParticleTable();
}

brPrimaryGeneratorAction::~brPrimaryGeneratorAction() {
	if (myGeneralParticleSource != NULL) {
		delete myGeneralParticleSource;
		myGeneralParticleSource = NULL;
	}

	if (myParticleGun != NULL) {
		delete myParticleGun;
		myParticleGun = NULL;
	}
	delete myMessenger;
}



void brPrimaryGeneratorAction::UseGeantinos(G4bool myGeantinoStatus){
  useGeantinos = myGeantinoStatus;
  if(verbosity>=1){
    G4cout << MsgPrefix << "Use geantino as primary particle: " << useGeantinos << G4endl;
  }
}



void brPrimaryGeneratorAction::InitPGA() {


	  G4cout << MsgPrefix << "Use General Particle Source." << G4endl;
	  myGeneralParticleSource = new G4GeneralParticleSource();


}
//generate neutrons here
void brPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
	ChangeSeeds();
	//StoreSeeds();


	myGeneralParticleSource->GeneratePrimaryVertex(anEvent);


}

/*void brPrimaryGeneratorAction::StoreSeeds(){ //TODO store seeds vie recorder
	std::vector<unsigned long> v;
	v = G4Random::getTheEngine()->put();
	myAnalysisManager->StoreRandomGeneratorState(v);
	//CLHEP::HepRandom::showEngineStatus();
}*/

void brPrimaryGeneratorAction::ChangeSeeds(){
	//Restore seeds
	if(!UseDefaultSeeds){
		G4cout << "/BeamRad> - BeginOfEventAction: Change random number generator seeds from :" << G4endl;
		G4Random::showEngineStatus();
		G4cout << "              to:" << G4endl;
		G4Random::getTheEngine()->get(Seeds);
		G4Random::showEngineStatus();
		UseDefaultSeeds = true;
		Seeds.clear();
	}
}

void brPrimaryGeneratorAction::SetSeeds(const unsigned long seed0,
		const unsigned long seed1, const unsigned long seed2) {
	Seeds.push_back(1878463799);//ID to identify the used random number generator, here it is the RanecuEngine (see BeamRad.cc:28)
	Seeds.push_back(static_cast<unsigned long>(seed0));
	Seeds.push_back(static_cast<unsigned long>(seed1));
	Seeds.push_back(static_cast<unsigned long>(seed2));
	UseDefaultSeeds = false;
	G4cout << "BeamRad/RunAction> SetSeeds" << G4endl;
	for(size_t i = 0; i < Seeds.size(); i++){
		G4cout << " Seeds[" << i << "]: " << Seeds[i] << G4endl;
	}
}

