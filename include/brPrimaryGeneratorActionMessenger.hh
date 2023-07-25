#ifndef brPrimaryGeneratorActionMessenger_h
#define brPrimaryGeneratorActionMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class brPrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithAnInteger;
class G4UIcmdWithABool;
class G4UIcmdWithoutParameter;

class brPrimaryGeneratorActionMessenger: public G4UImessenger {
public:
	brPrimaryGeneratorActionMessenger(brPrimaryGeneratorAction* PGA);
	~brPrimaryGeneratorActionMessenger();

	void SetNewValue(G4UIcommand*, G4String);
private:
	brPrimaryGeneratorAction* myPGA;
	G4UIdirectory* dirPGA;

	G4UIcmdWithABool *cmdUseGeantinos;


	G4UIcmdWithAnInteger *cmdSeed0;
	G4UIcmdWithAnInteger *cmdSeed1;
	G4UIcmdWithAnInteger *cmdSeed2;
	G4UIcmdWithoutParameter *cmdSetSeeds;
	unsigned long Seed0;
	unsigned long Seed1;
	unsigned long Seed2;

};

#endif

