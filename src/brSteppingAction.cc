/*
 * brSteppingAction.cc
 *
 *  Created on: 18.04.2017
 *      Author: schmitz
 */
#include "brSteppingAction.hh"
#include "brEventAction.hh"
#include "brTrackingAction.hh"
#include "brPMTSD.hh"
#include "brScintSD.hh"
#include "brUserTrackInformation.hh"
#include "brUserEventInformation.hh"
#include "brSteppingMessenger.hh"
#include "brHistoManager.hh"
//#include "brUserRegionInformation.hh"

// Includes Physical Constants and System of Units
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4SteppingManager.hh"
#include "G4SDManager.hh"
#include "G4EventManager.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessType.hh"
#include "G4HadronicProcessType.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4StepPoint.hh"
#include "G4TrackStatus.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4OpBoundaryProcess.hh"
#include "Randomize.hh"
#include "G4RunManager.hh"
#include <math.h>       /* pow */
#include <vector>
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
brSteppingAction::brSteppingAction(brHistoManager* histo)
  :oneStepPrimaries(false), histoManager(histo), killPhoton(false)
  //killPhoton(true)
{
  steppingMessenger = new brSteppingMessenger(this);
}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
brSteppingAction::~brSteppingAction()
{}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void brSteppingAction::UserSteppingAction(const G4Step * theStep){
  G4Track* theTrack = theStep->GetTrack();
  G4int trackID = theTrack->GetTrackID();

  brUserTrackInformation* trackInformation
  	  	  	  	  	  	  	 =(brUserTrackInformation*)theTrack->GetUserInformation();
  brUserEventInformation* eventInformation
    						=(brUserEventInformation*)G4EventManager::GetEventManager()
    						->GetConstCurrentEvent()->GetUserInformation();

  G4StepPoint* thePrePoint     = theStep->GetPreStepPoint();
  G4VPhysicalVolume* thePrePV  = thePrePoint->GetPhysicalVolume();
 // G4VLogicalVolume* thePreLV   = thePrePV->GetLogicalVolume();
  
 // brUserRegionInformation* thePreRInfo
 //						 = (brUserRegionInformation*)(thePreLV->GetRegion()->GetUserInformation());

  G4StepPoint* thePostPoint    = theStep->GetPostStepPoint();
  G4VPhysicalVolume* thePostPV = thePostPoint->GetPhysicalVolume();
 //G4VLogicalVolume* thePostLV  = thePostPV->GetLogicalVolume();

 // brUserRegionInformation* thePostRInfo
 //  						 = (brUserRegionInformation*)(thePostLV->GetRegion()->GetUserInformation());
  
 //G4cout << "Start Volume " << thePrePV->GetName()<< G4endl;
  G4OpBoundaryProcessStatus boundaryStatus = Undefined;
  static G4OpBoundaryProcess* boundary     = NULL;

  //find the boundary process only once
  if(!boundary){
    G4ProcessManager* pm
      = theStep->GetTrack()->GetDefinition()->GetProcessManager();
    G4int nprocesses = pm->GetProcessListLength();
    G4ProcessVector* pv = pm->GetProcessList();
    G4int i;
    for( i=0;i<nprocesses;i++){
      if((*pv)[i]->GetProcessName()=="OpBoundary"){
	boundary = (G4OpBoundaryProcess*)(*pv)[i];
	break;
      }
    }
  }
  G4double myStepLength = 0.0;
  myStepLength = theStep->GetStepLength();
  G4double myEnergyDelta = 0.0;
  G4double myEnergyEDep = 0.0;
  G4double eventTime = 0.0;
  G4double totalEnergy = 0.0;
  G4String particleName = "";

  particleName = theTrack->GetDefinition()->GetParticleName();
  myEnergyEDep = theStep->GetTotalEnergyDeposit();
  myEnergyDelta = theStep->GetDeltaEnergy();
  G4int stepID = theStep->GetTrack()->GetCurrentStepNumber();
  G4int eventID = eventInformation->GetEventID();
  //
  // Get information about the start point of the step
  //
  G4ThreeVector myStartPosition;
  G4ThreeVector myStartDirection;
  G4double myStartXYMagnitude;
  G4String myStartProcessName = "";
  G4String myStartVolumeName = "";
  G4String myEndVolumeName = ""; //using this, so defining it here instead of below

  G4int preCopyNo = thePrePoint->GetTouchable()->GetCopyNumber(); //also using these two
  G4int postCopyNo = thePostPoint->GetTouchable()->GetCopyNumber();
  
  G4double myStartTime = -1.0;
  G4ThreeVector myStartMomentumDirection;
  G4double myStartKineticEnergy = 0.;
  G4String startMat = "";
  G4String myCreatorProcess = "";
  G4double cosDetect= 0;//myStartDirection.dot(G4ThreeVector(0,0,1));
//  G4double pi=3.14159265359; //using this explicitly since 
  G4double angleDetect=0;//acos(cosDetect)*180.0/PI;
  G4double polyAngleFitResult=0;
  //Test if there is a step
  if (thePrePoint != NULL) {
	  if (thePrePoint->GetPhysicalVolume() != NULL)
		  myStartVolumeName = thePrePoint->GetPhysicalVolume()->GetName();
//		  if(myStartVolumeName.contains("pixel")) std::cout << "IN SI: " << myStartVolumeName << std::endl;
	  if (thePrePoint->GetProcessDefinedStep() != NULL)
		  myStartProcessName =
				  thePrePoint->GetProcessDefinedStep()->GetProcessName();
	  startMat = thePrePoint->GetMaterial()->GetName();
	  myStartPosition = thePrePoint->GetPosition();
	  myStartDirection = thePrePoint->GetMomentumDirection();
	  myStartTime = thePrePoint->GetGlobalTime();
	  myStartKineticEnergy = thePrePoint->GetKineticEnergy();
  	  myStartXYMagnitude = sqrt(pow(myStartPosition.x(),2)+pow(myStartPosition.y(),2));
		
  }


  if(theTrack->GetParentID()==0){
    //This is a primary track

    G4TrackVector* fSecondary=fpSteppingManager->GetfSecondary();
    G4int tN2ndariesTot = fpSteppingManager->GetfN2ndariesAtRestDoIt()
      + fpSteppingManager->GetfN2ndariesAlongStepDoIt()
      + fpSteppingManager->GetfN2ndariesPostStepDoIt();

    	//If we havent already found the conversion position and there were
    	//secondaries generated, then search for it


  }
 
  if(!thePostPV){//out of world
    return;
  }

  G4ParticleDefinition* particleType = theTrack->GetDefinition();



  // kill optical photons which are below pmt sensitivity
  // for now kill photons which were created after 10^20 ns
  //if(killPhoton && (particleType==G4OpticalPhoton::OpticalPhotonDefinition()) && theTrack->GetGlobalTime() > pow(10.,15.)* ns)//(theTrack->GetTotalEnergy() < 1.9*eV))
  //	  theTrack->SetTrackStatus(fStopAndKill);

  //if ( trackInformation->GetReflectionCount() > 200) G4cout << "reflection " << trackInformation->GetReflectionCount() << G4endl;
  //if ( trackInformation->GetInternalReflectionCount() > 200) G4cout << "internal reflection " << trackInformation->GetInternalReflectionCount() << G4endl;

  //kill photons which are reflected internally (i.e. dielectric-dielectric) more than 200 times
  //if(trackInformation->GetInternalReflectionCount() > 1000)
  //	  theTrack->SetTrackStatus(fStopAndKill);


  if((particleType==G4OpticalPhoton::OpticalPhotonDefinition())){

          myCreatorProcess = theTrack->GetCreatorProcess()->GetProcessName();

    //Was the photon absorbed by the absorption process
    if(thePostPoint->GetProcessDefinedStep()->GetProcessName()=="OpAbsorption"){
      eventInformation->IncAbsorption();
      trackInformation->AddTrackStatusFlag(absorbed);
    }



    boundaryStatus=boundary->GetStatus();

   //
   // for debugging
   //
   //boundary->DumpInfo();
   //G4cout << "========================================================" << G4endl;
   //G4cout << "TrackID "  <<  trackID << G4endl;
   //boundary->SetVerboseLevel(4);
   //G4cout << "========================================================" << G4endl;


    //Check to see if the particle was actually at a boundary
    //Otherwise the boundary status may not be valid
    //Prior to Geant4.6.0-p1 this would not have been enough to check
    if(thePostPoint->GetStepStatus()==fGeomBoundary){
      switch(boundaryStatus){


      //Undefined
      //FresnelRefraction
      //FresnelReflection
      //TotalInternalReflection
      //LambertianReflection
      //LobeReflection
      //SpikeReflection
      //BackScattering
      //Absorption
      //Detection
      //NotAtBoundary
      //SameMaterial
      //StepTooSmall
      //NoRINDEX


      case Undefined:
      break;
      case NoRINDEX:

      break;
      case Absorption:
   	  trackInformation->AddTrackStatusFlag(boundaryAbsorbed);
    	  eventInformation->IncBoundaryAbsorption();
	  //G4cout << thePostPV->GetName() << G4endl;
	break;
      case Detection: //Note, this assumes that the volume causing detection
                      //is the photocathode because it is the only one with
	                  //non-zero efficiency
	//Trigger sensitive detector manually
/*
	//determine cosine of angle of incidence  
        cosDetect= myStartDirection.dot(G4ThreeVector(0,0,1));
		
	//determine angle of incidence
	angleDetect=acos(cosDetect)*180/M_PI; //should always be less than 90 degrees

        //using a 6th degree polynomial fit based on the data in OpticalData/PMTAngularSpec.txt. Using 6th degree because detections are infrequent compared to total # of steps so it's not that expensive
        polyAngleFitResult=3.93E-11*pow(angleDetect,6)-9.69E-09*pow(angleDetect,5)+9.10E-07*pow(angleDetect,4)-4.26E-05*pow(angleDetect,3)+9.17E-04*pow(angleDetect,2)-8.22E-03*angleDetect+9.98E-01;	

	//if we don't think we're optimally coupled, this second 62 degrees term below is the glass-scintillator critical angle correction. Specifically, it's the correction for silicone oil-to-scintillator. The borosilicate glass-to-scintillator correction is 72.9 degrees. Enabling this cutoff for silicone oil for now since we're doing the optical coupling manually and it could possibly be a poor coupling, but it should mostly not matter for a bar since the detection angles are much sharper than 62 degrees most of the time
	if(G4UniformRand()<polyAngleFitResult && angleDetect<62){

	//G4cout << "hit registered!" << G4endl;
	//G4cout << theStep->GetPostStepPoint()->GetPhysicalVolume()->GetName() << G4endl;
	//if(G4UniformRand()<cosDetect){                               //if we think we did a good job coupling, then just use this relationship (which falls off at high theta anyways)
//		if(G4UniformRand()<0.01) G4cout << "Cosine is " << cosDetect << G4endl;
		myEndVolumeName=theStep->GetPostStepPoint()->GetPhysicalVolume()->GetName();
		if (myEndVolumeName.contains("phCath")){
	  G4String sdPMTName="PMT_SD";
	  //hier

	  brPMTSD* pmtSD = (brPMTSD*)G4SDManager::GetSDMpointer()->FindSensitiveDetector(sdPMTName);
	  //pmtSD->GetCollectionName(1);
	  if(pmtSD){
	    pmtSD->ProcessHits_constStep(theStep,NULL);
	 //   G4cout << "Process Hits PMT" << G4endl;
	    }
	  trackInformation->AddTrackStatusFlag(hitPMT);

		}
		}
*/
          break;
      case FresnelReflection:
	  trackInformation->IncReflections();
	  trackInformation->IncInternalReflections();
    	  
	  break;
      case TotalInternalReflection:
	  trackInformation->IncReflections();
	  trackInformation->IncInternalReflections();
    	  break;

      case SpikeReflection:
	  trackInformation->IncReflections();
	  trackInformation->IncInternalReflections();
    	  
	  break;
      case LambertianReflection: //diffuse surfaces only
	  trackInformation->IncReflections();
	  trackInformation->IncInternalReflections();

    	  break;


      default:
    	  break;
      }
    }
  }


  //
  // search and record

  // 2) interaction of neutrons
  //





	//Get information about the end point of the step

//	G4String myEndVolumeName = "";
	G4String myEndProcessName = "";
	G4double myEndTime = -1.0;
	G4ThreeVector myEndPosition;
	G4ThreeVector myEndDirection;
	G4double myEndKineticEnergy = -1.0;
	G4double sumEnergyDepSi=0;
	G4double sumEnergyDepAbs=0;
	G4double sumEnergyDelta=0;
	G4String endMat = "";
	G4int nbOfInteractions = 0;
	G4int nbOfElastics = 0;


	if (thePostPoint != NULL) {
		myEndKineticEnergy = thePostPoint->GetKineticEnergy();
		if (thePostPoint->GetPhysicalVolume() != NULL) {
			myEndVolumeName = thePostPoint->GetPhysicalVolume()->GetName();
			endMat = thePostPoint->GetMaterial()->GetName();
		//	G4cout << "end vol is " << myEndVolumeName << G4endl;
		}
  

		if (thePostPoint->GetProcessDefinedStep() != NULL) {
			myEndProcessName =
					thePostPoint->GetProcessDefinedStep()->GetProcessName();
		}


		myEndPosition = thePostPoint->GetPosition();
		myEndDirection = thePostPoint->GetMomentumDirection();
		myEndTime = thePostPoint->GetGlobalTime();

//		if(particleName.contains("mu") && myStartVolumeName.contains("World") && myEndVolumeName=="barParam"){G4cout << "leaving world, entering " << myEndVolumeName << G4endl;}
		//count interactions
		nbOfInteractions = 1;
		//flag elastic scattering
		if(myEndProcessName.contains("Elastic") !=0 ) nbOfElastics = 1;

		
//		if(myEndVolumeName.contains("World") && myStartVolumeName=="rockPhysic") G4cout << "Particle " << particleName << " exiting rock" << G4endl;


/*
//////////// neutron interaction manager /////////////
	if( particleName.contains("neutron") ){

		if (eventInformation->GetNeutronTracks()->size() > 0){ //there are neutron tracks
		eventInformation->GetNeutronTrack(theStep->GetTrack()->GetTrackID())->AddNbOfElastics(nbOfElastics);
		eventInformation->GetNeutronTrack(theStep->GetTrack()->GetTrackID())->AddNbOfInteractions(nbOfInteractions);
		}
	}
*/
/*
///////////// gamma interaction manager ///////////////
	if( particleName.contains("gamma") ){
		//sum energy deposit
		sumEnergyDep=eventInformation->GetGammaTrack(theStep->GetTrack()->GetTrackID())->GetEnergyDeposit()+myEnergyEDep;
		eventInformation->GetGammaTrack(theStep->GetTrack()->GetTrackID())->SetEnergyDeposit(sumEnergyDep);
//	if(theTrack->GetCurrentStepNumber()==1) G4cout << "Gamma track creator process is: " << theTrack->GetCreatorProcess()->GetProcessName() << " and energy is " << eventInformation->GetGammaTrack(trackID)->GetInitialEnergy() << G4endl;	
	}
*/
//
/*
	if(particleName.contains("e+") || particleName.contains("e-")){
		if(theTrack->GetCurrentStepNumber()==1) G4cout << "Electron track creator process is: " << theTrack->GetCreatorProcess()->GetProcessName() << " and energy is " << theTrack->GetTotalEnergy() << G4endl;// " *and kinetic energy is* " << theTrack->GetKineticEnergy() << G4endl;
		}

*/
	
	} //end of PostStep loop

//	if(myEndVolumeName.contains("SiDet") && particleName.contains("gamma")){ //absorber
//		if(myEndProcessName!="Transportation") G4cout << "process name in Si: " << myEndProcessName << G4endl;
	
	////// yeah this should probably be a switch statement. I forget what's the least expensive way, will fix later
	if(myStartVolumeName.contains("pixel")){ //si detector
		G4String sdScintName="Scint_SD";
		//G4cout << myStartVolumeName << G4endl;
                brScintSD* scintSD = (brScintSD*)G4SDManager::GetSDMpointer()->FindSensitiveDetector(sdScintName);
                scintSD->ProcessHits2(theStep,NULL);
	}
	if(myStartVolumeName.contains("Det")){ //si detector
		sumEnergyDepSi=eventInformation->GetEventEnergyDepositSi1()+myEnergyEDep;
		eventInformation->SetEventEnergyDepositSi1(sumEnergyDepSi);
//		std::cout << myStartVolumeName << std::endl;
	

		if(myEnergyEDep>4) {std::cout << "in the det with deposit: " << myEnergyEDep << std::endl;
			std::cout << "particle name: " << particleName << " and start process " << myStartProcessName << std::endl;
			std::cout << "particle name: " << particleName << " and end process " << myEndProcessName << std::endl;}
	}
///*
	else if(myStartVolumeName.contains("Bulk")){ //si detector
	//else if(myStartVolumeName.contains("SiBulk")||myEndVolumeName.contains("SiBulk")){ //si detector
		sumEnergyDepSi=eventInformation->GetEventEnergyDepositSi2()+myEnergyEDep;
		eventInformation->SetEventEnergyDepositSi2(sumEnergyDepSi);
		if(eventInformation->GetEventEnergyDepositSi2()>1) {std::cout << "in the bulk with deposit: " << myEnergyEDep << std::endl;
			std::cout << "particle name: " << particleName << " and start process " << myStartProcessName << std::endl;
			std::cout << "particle name: " << particleName << " and end process " << myEndProcessName << std::endl;}
	}
//*/
//	/*
	else if(myStartVolumeName.contains("MIP")){ //si detector
		sumEnergyDepSi=eventInformation->GetEventEnergyDepositSi3()+myEnergyEDep;
		eventInformation->SetEventEnergyDepositSi3(sumEnergyDepSi);
	}
	
//	if(myEndVolumeName.contains("Bulk") && myStartVolumeName.contains("SiDet") && trackID!=1){ //si detector
//		double eta = -log(tan(acos(std::abs(myEndDirection.dot(G4ThreeVector(-1,0,0))))/2));
//		eventInformation->SetProtonScatter(eta);
//	}
//		std::cout << myStartVolumeName << std::endl;
/*
	else if(myStartVolumeName.contains("SiDet_physic4")||myEndVolumeName.contains("SiDet_physic4")){ //si detector
		sumEnergyDepSi=eventInformation->GetEventEnergyDepositSi4()+myEnergyEDep;
		eventInformation->SetEventEnergyDepositSi4(sumEnergyDepSi);
	}

	else if(myStartVolumeName.contains("SiDet_physic5")||myEndVolumeName.contains("SiDet_physic5")){ //si detector
		sumEnergyDepSi=eventInformation->GetEventEnergyDepositSi5()+myEnergyEDep;
		eventInformation->SetEventEnergyDepositSi5(sumEnergyDepSi);
	}

	//if(myEndVolumeName.contains("abs") && particleName.contains("gamma")){ //absorber
	//	if(myEndProcessName!="Transportation") G4cout << "process name in abs: " << myEndProcessName << G4endl;
	else if(myStartVolumeName.contains("abs_physic1")||myEndVolumeName.contains("abs_physic1")){ //absorber
		sumEnergyDepAbs=eventInformation->GetEventEnergyDepositAbs1()+myEnergyEDep;
		eventInformation->SetEventEnergyDepositAbs1(sumEnergyDepAbs);
	}

	else if(myStartVolumeName.contains("abs_physic2")||myEndVolumeName.contains("abs_physic2")){ //absorber
		sumEnergyDepAbs=eventInformation->GetEventEnergyDepositAbs2()+myEnergyEDep;
		eventInformation->SetEventEnergyDepositAbs2(sumEnergyDepAbs);
	}

	else if(myStartVolumeName.contains("abs_physic3")||myEndVolumeName.contains("abs_physic3")){ //absorber
		sumEnergyDepAbs=eventInformation->GetEventEnergyDepositAbs3()+myEnergyEDep;
		eventInformation->SetEventEnergyDepositAbs3(sumEnergyDepAbs);
	}

	else if(myStartVolumeName.contains("abs_physic4")||myEndVolumeName.contains("abs_physic4")){ //absorber
		sumEnergyDepAbs=eventInformation->GetEventEnergyDepositAbs4()+myEnergyEDep;
		eventInformation->SetEventEnergyDepositAbs4(sumEnergyDepAbs);
	}

	else if(myStartVolumeName.contains("scintVeto")||myEndVolumeName.contains("scintVeto")){ //absorber
		sumEnergyDepAbs=eventInformation->GetEventEnergyDepositScintVeto()+myEnergyEDep;
		eventInformation->SetEventEnergyDepositScintVeto(sumEnergyDepAbs);
	}
*/
	/*	
	if(particleName.contains("gamma") && myStartVolumeName=="plScin_physic" && myEndVolumeName.contains("World")){ //gamma exiting scintillator to the world
		eventInformation->GetGammaTrack(theStep->GetTrack()->GetTrackID())->SetGammaOutScintillator(true);
	}
  */
  
}




