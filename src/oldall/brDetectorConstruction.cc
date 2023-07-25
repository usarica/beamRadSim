// created 22-04-2019
// author: Ryan Schmitz (UCSB)

//==============================================================================
#include "brDetectorConstruction.hh"
#include "brScintSD.hh"
#include "brPMTSD.hh"
#include "brUserEventInformation.hh"
#include "brPixelParameterisation.hh"

#include <sstream>
#include <math.h>
#include "globals.hh"
// Includes Physical Constants and System of Units
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4ios.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4Trd.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4RunManager.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4MultiUnion.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4EllipticalTube.hh"
#include "G4Trap.hh"
#include "G4Polycone.hh"
#include "G4Polyhedra.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4PVReplica.hh"

#include "G4RunManager.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4MaterialTable.hh"
#include "G4NistManager.hh"
#include "G4PhysicsVector.hh"

#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolume.hh"

#include "G4PVPlacement.hh"
#include "G4VPVParameterisation.hh"
#include "G4PVParameterised.hh"
#include "globals.hh"
#include "G4SolidStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4GeometryManager.hh"

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4AssemblyVolume.hh"


#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4SDManager.hh"
#include "G4UImanager.hh"

const G4int nLayers = 1; //number of layers in detector. Up here since it defines an array

//==============================================================================
brDetectorConstruction::brDetectorConstruction() :
    verbose(1)//,solidWorld(0), logicWorld(0), physicWorld(0)
{
	SetDefaults();
}

//==============================================================================
brDetectorConstruction::~brDetectorConstruction() {

}
//==============================================================================

//==============================================================================

G4VPhysicalVolume* brDetectorConstruction::Construct() {

	return SetupGeometry();
}

//==============================================================================

G4VPhysicalVolume* brDetectorConstruction::SetupGeometry() {

	if (verbose >= 0) {
		G4cout << "BeamRad> Construct geometry." << G4endl;
	}
	G4double fWorld_x = 20.0 * m;
	G4double fWorld_y = 20.0 * m;
	G4double fWorld_z = 20.0 * m;

	G4Material* worldMaterial = G4NistManager::Instance()->FindOrBuildMaterial(
				"G4_Galactic");
	//			"G4_AIR");

	const G4int nEntriesAir = 2;
	G4double photonEnergyAir[nEntriesAir]={ 6.3 * eV,1.5 * eV};
	G4double Air_RIND[nEntriesAir];

	for (int i = 0; i < nEntriesAir; i++) {
		Air_RIND[i]= 1.0;
	}// max value at 440 nm

	G4MaterialPropertiesTable* mptAir = new G4MaterialPropertiesTable();
	mptAir->AddProperty("RINDEX",photonEnergyAir, Air_RIND, nEntriesAir);//->SetSpline(true);
	worldMaterial->SetMaterialPropertiesTable(mptAir);

	G4Box* solidWorld = new G4Box("world", fWorld_x / 2, fWorld_y / 2, fWorld_z / 2);
	G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, worldMaterial, "World", 0, 0,
			0);

	G4VisAttributes* visAttWorld = new G4VisAttributes();
	visAttWorld->SetVisibility(false);
	logicWorld->SetVisAttributes(visAttWorld);

	//Must place the World Physical volume unrotated at (0,0,0).
	G4PVPlacement* physicWorld = new G4PVPlacement(0, // no rotation
			G4ThreeVector(), // at (0,0,0)
			logicWorld, // its logical volume
		"World", // its name
			0, // its mother  volume
			false, // no boolean operations
			0); // copy number

///////////////////////////////    End world //////////////////////////////////////////////////
///////////////////////////////   Start Scintillator/Wrapping  ///////////////////////////////////////////
	//==============================================================================
	// size of Scintillator and wrapping
	//==============================================================================

	//G4double absThickness = 50*um;

	G4double layerSpacing = 1*mm;

	G4double absThickness1 = 50*um;
	G4double absThickness2 = 50*um;
	G4double absThickness3 = 50*um;
	G4double absThickness4 = 2000*um;
	
	G4double scintVetoThickness = 5*cm;

	G4double measurementPos=10*mm;
	//G4double measurementPos=243*mm;
	//G4double measurementPos=0*mm;
	G4double wrapRefl = 0;//0.97;
	G4double scintX = 50/2*mm;
	G4double scintY = 50/2*mm;
	G4double scintZ  = 50/2*mm;//(each of these dimensions represents the half-width; e.g. this is 600mm long)
	//G4double scintX = 130/2*um;
	//G4double scintY = 130/2*um;
	//G4double scintZ  = 130/2*um;//(each of these dimensions represents the half-width; e.g. this is 600mm long)

	G4double SiBulkX = 49.0/2*um;
	G4double FR4X = 10/2*um;
	G4double detX = 1.0/2*um;

	G4double airGapThickness = 0.1*um; //1*mm
	G4double wrapThickness = 0.1*um; //3*mm
	G4double airgapX = scintX+airGapThickness;	
	G4double airgapY = scintY+airGapThickness;	
	G4double airgapZ = scintZ+airGapThickness;
	G4double wrapX=airgapX+wrapThickness;
	G4double wrapY=airgapY+wrapThickness;
	G4double wrapZ=airgapZ+wrapThickness;

        G4double frontLayerMid = -132*cm;
        G4double midLayerMid = -10*cm;
        G4double backLayerMid = 115*cm;

	//this is here because the entire geometry is shifted 6cm upwards
        G4double centerOffsetX = 6*cm;

	//measured from the centers; the gap between the bars
	G4double barSpacingXY = 60*mm;
	//G4double layerSpacing = 1000*mm; 
	//in visualization this gets swapped, so this is actually 3x2 rather than 2x3
        G4int nPixelYCount = 13; //number of bars in grid, so this is NxN
        G4int nPixelZCount = 13; //number of bars in grid, so this is NxN
	this->SetNBarPerLayer(nPixelZCount*nPixelYCount);
	this->SetNLayer(nLayers);
 
	 G4double outerRadius_pmt   = 52* mm /2.; //26 //52
	 G4double outerRadius_cath  = 52* mm /2.; //26 //52
	 G4double height_pmt        = 200* mm; //142.*mm;
	 G4double height_cath       = 2.0 * mm; //2mm
	 G4double pmtYoffset        = 0*mm;
	 G4double muMetalThickness = 0.1*mm;

	 //G4double worldRotation = -43.1*deg;
	 G4double worldRotation = 0*deg;
	
	//overallX = bottom half of detector below 3rd Si Layer
	G4double overallBotX = layerSpacing*5+absThickness3+absThickness4+scintVetoThickness+2.5*2*scintX+1*mm;
	G4double overallY = scintY;
	G4double overallZ = scintZ;

	//overallTopX = top half of detector above 3rd Si layer
	G4double overallTopX = layerSpacing*4+absThickness2+absThickness1+2.5*2*scintX+1*mm;
	

	G4double steelThickness = 0.5*cm;
	G4double steelY = scintY*3;
	G4double steelZ = scintZ*3;

	G4double cuRodRadius = 0.5*2.54*cm;
	G4double cuSpacing = 5*cm;
	
	G4NistManager* nistMan = G4NistManager::Instance();

///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
	//==========================================================================
	//Scintillator Materials
	//==========================================================================

	//==========================================================================
	// Elements
	//
	//*******************************************************************************************************************************
	G4Element* elH = nistMan->FindOrBuildElement("H");
	G4Element* elC = nistMan->FindOrBuildElement("C");
	G4Element* elO = nistMan->FindOrBuildElement("O");
	G4Element* elK = nistMan->FindOrBuildElement("K");
	G4Element* elNa = nistMan->FindOrBuildElement("Na");
	G4Element* elSi = nistMan->FindOrBuildElement("Si");
	G4Element* elAl = nistMan->FindOrBuildElement("Al");
	G4Element* elAu = nistMan->FindOrBuildElement("Au");
        G4Element* elCs = nistMan->FindOrBuildElement("Cs"); // Cesium;
        G4Element* elSb = nistMan->FindOrBuildElement("Sb"); // Antimony;
        G4Element* elB = nistMan->FindOrBuildElement("B"); // Boron;
        G4Element* elLa = nistMan->FindOrBuildElement("La");
        G4Element* elRh = nistMan->FindOrBuildElement("Rh");
        G4Element* elTe = nistMan->FindOrBuildElement("Te");
	
	//mu metal materials	
	G4Element* elNi = nistMan->FindOrBuildElement("Ni"); //Nickel;
	G4Element* elFe = nistMan->FindOrBuildElement("Fe"); //Iron;
	
	//there are other parts, but to first order this is 80% Ni, 15% Fe, 5% other stuff, so I'm just going to lump that into Fe
	G4Material* muMetal = new G4Material("muMetal",8.7*g/cm3, 2);
	muMetal->AddElement(elNi,0.8); //80% mass fraction
	muMetal->AddElement(elFe,0.2); //20% mass fraction


	G4Element* elPlastic = nistMan->FindOrBuildElement("G4_POLYSTYRENE");
	//==========================================================================
	// BC-400 plastic scintillator; according to datasheet, elH = 1.103 *elC, elH + elC = 1
	//For the references for the optical properties see ../ref/EmissionSpectrum_BC-400.pdf

	G4Material* matPlScin = new G4Material("SiDettillator", 1.032 * g / cm3, 2);
	//matPlScin->AddElement(elC, .4755);
	//matPlScin->AddElement(elH, .5245);
	matPlScin->AddElement(elC, 10);
	matPlScin->AddElement(elH, 11);
	matPlScin->SetMaterialPropertiesTable(SetOpticalPropertiesOfPS());
	matPlScin->GetIonisation()->SetBirksConstant(0.149*mm/MeV); // according to L. Reichhart et al., Phys. Rev instedad of(0.126*mm/MeV);
	
	//==========================================================================
	G4Material* wrapMat = nistMan->FindOrBuildMaterial("G4_POLYETHYLENE");
	//G4Material* airgapMat = worldMaterial; //The air gap mat should be air, change this if you change worldmat to be vacuum/galactic		
	G4Material* AlMat = nistMan->FindOrBuildMaterial("G4_Al");
	G4Material* CuMat = nistMan->FindOrBuildMaterial("G4_Cu");
	G4Material* AgMat = nistMan->FindOrBuildMaterial("G4_Ag");
	G4Material* AuMat = nistMan->FindOrBuildMaterial("G4_Au");
	G4Material* FeMat = nistMan->FindOrBuildMaterial("G4_Fe");
	
	G4Material* NiMat = nistMan->FindOrBuildMaterial("G4_Ni");
	G4Material* PbMat = nistMan->FindOrBuildMaterial("G4_Pb");
	
	G4Material* SiMat = nistMan->FindOrBuildMaterial("G4_Si");
	
	G4Material* RhMat = nistMan->FindOrBuildMaterial("G4_Rh");
	G4Material* TeMat = nistMan->FindOrBuildMaterial("G4_Te");

	G4Material* steelMat = nistMan->FindOrBuildMaterial("G4_STAINLESS-STEEL");
	//going to use concrete as a first order approximation to rock, since it's close and we just want something dense
	G4Material* concreteMat = nistMan->FindOrBuildMaterial("G4_CONCRETE");
/*	
	G4Material* silicaMat = new G4Material("SiO2", 2.65 * g / cm3, 2);
	silicaMat->AddElement(elSi, 1);
	silicaMat->AddElement(elO, 2);
*/
	G4Material* LaOMat = new G4Material("La2O3", 6.51 * g / cm3, 2);
	LaOMat->AddElement(elLa, 2);
	LaOMat->AddElement(elO, 3);

//FR4
G4double density = 1.2*g/cm3;
G4int numel;
G4int natoms;
G4double fractionMass;
 G4Material* Epoxy = new G4Material("Epoxy" , density, numel=2);
 Epoxy->AddElement(elH, natoms=2);
 Epoxy->AddElement(elC, natoms=2);
 //SiO2 (Quarz)
 G4Material* SiO2 = new G4Material("SiO2",density= 2.200*g/cm3, numel=2);
 SiO2->AddElement(elSi, natoms=1);
 SiO2->AddElement(elO , natoms=2);
 //FR4 (Glass + Epoxy)
 density = 1.86*g/cm3;
 G4Material* FR4 = new G4Material("FR4" , density, numel=2);
 FR4->AddMaterial(Epoxy, fractionMass=0.472);
 FR4->AddMaterial(SiO2, fractionMass=0.528);
// fr4Material = FR4;



////////////////////////////////////////////////////////////////////////////////
//									     ///
//				Si Base					     ///
//									     ///
////////////////////////////////////////////////////////////////////////////////
/*
        G4Box* SiLayer_solid = new G4Box("SiDet_solid",
                                scintX,
                                scintY,
                                scintZ);

        G4LogicalVolume* SiLayer_logic = new G4LogicalVolume(
                                SiLayer_solid,
                                //matPlScin,
                                SiMat,
                                "SiLayer_logic",
                                0, 0, 0);

        G4PVPlacement* SiLayer_physic = new G4PVPlacement(
                        0,
                        G4ThreeVector(scintX,0,0),
                        SiLayer_logic,
                        "SiLayer_physic",
                        logicWorld,
                        false,
                        0,
                        true);
*/
	/////////// Au plating //////////////////////////////

	G4Box* FR4_solid = new G4Box("FR4Z_solid",
				FR4X, 
				scintY,
				scintZ);

	G4LogicalVolume* FR4_logic = new G4LogicalVolume(
				FR4_solid,
				//matPlScin,
				FR4,
				"FR4_logic",
				0, 0, 0);
        
	G4PVPlacement* FR4_physic = new G4PVPlacement(
                        0,
                        G4ThreeVector(-2*SiBulkX-detX*2-FR4X*2-FR4X-5*um,0,0),
                        FR4_logic,
                        "FR4_physic",
                        logicWorld,
                        false,
                        0,
                        true);

	G4Box* SiDet_solid = new G4Box("SiDet_solid",
				detX, 
				scintY,
				scintZ);

	G4LogicalVolume* SiDet_logic1 = new G4LogicalVolume(
				SiDet_solid,
				//matPlScin,
				worldMaterial,
				"SiDet_logic1",
				0, 0, 0);

	G4Box* SiDet_solid_pixel = new G4Box("SiDet_solid_pixel",
				detX, 
				scintY/130,
				scintZ/130);
	
	G4LogicalVolume* SiDet_logic1_pixel = new G4LogicalVolume(
				SiDet_solid_pixel,
				//matPlScin,
				SiMat,
				"SiDet_logic_pixel",
				0, 0, 0);
	
	G4PVPlacement* SiDet_physic1 = new G4PVPlacement(
                        0,
                        G4ThreeVector(-detX-FR4X*2,0,0),
                        SiDet_logic1,
                        "SiDet_physic1",
                        logicWorld,
                        false,
                        0,
                        true);

        brPixelParameterisation* pixelParam = new brPixelParameterisation(
                        nPixelYCount,
                        nPixelZCount,
                        0,//-detX-FR4X*2, //x offset
                        scintY/nPixelYCount*2, //YZ spacing
                        scintY/nPixelYCount, //half-width
                        scintZ/nPixelZCount //half-length
			);

        G4PVParameterised* pixelDetParamPhys= new G4PVParameterised("pixelDetParamPhys",
                        SiDet_logic1_pixel,
                        SiDet_logic1,
                        kXAxis,
                        nPixelYCount*nPixelZCount,
                        pixelParam,
                        true); //checking overlaps


	//////////////////// Bulk part of Si ////////////////

	G4Box* SiBulk_solid = new G4Box("SiBulk_solid",
				SiBulkX, 
				scintY,
				scintZ);

	G4LogicalVolume* SiBulk_logic1 = new G4LogicalVolume(
				SiBulk_solid,
				//matPlScin,
				worldMaterial,
				"SiBulk_logic1",
				0, 0, 0);
        
	G4Box* SiBulk_solid_pixel = new G4Box("SiBulk_solid_pixel",
				SiBulkX, 
				scintY/130,
				scintZ/130);
	
	G4LogicalVolume* SiBulk_logic1_pixel = new G4LogicalVolume(
				SiBulk_solid_pixel,
				//matPlScin,
				SiMat,
				"SiBulk_logic_pixel",
				0, 0, 0);

	G4PVPlacement* SiBulk_physic = new G4PVPlacement(
                        0,
                        G4ThreeVector(-SiBulkX-detX*2-FR4X*2,0,0),
                        SiBulk_logic1,
                        "SiBulk_physic",
                        logicWorld,
                        false,
                        1,
                        true);
	
        G4PVParameterised* pixelBulkParamPhys= new G4PVParameterised("pixelBulkParamPhys",
                        SiBulk_logic1_pixel,
                        SiBulk_logic1,
                        kXAxis,
                        nPixelYCount*nPixelZCount,
                        pixelParam,
                        false); //checking overlaps


////////////////////////////////////////////////////////////////////////////////
//									     ///
//	         		Steel Wall				     ///
//									     ///
////////////////////////////////////////////////////////////////////////////////


//	G4Box* steelWall_solid = new G4Box("steelWall_solid",
//			steelThickness/2,
//			steelY,
//			steelZ);
/*
	G4Tubs* steelWall_solid = new G4Tubs("steelWall_solid",
			10*cm,
			10*cm+steelThickness,
			steelZ*10,
			0*deg,
			360*deg);

	G4LogicalVolume* steelWall_logic = new G4LogicalVolume(
			steelWall_solid,
			steelMat,
			"steelWall_logic",
			0,0,0);

        G4PVPlacement* steelWall_physic = new G4PVPlacement(
                        0,
                        G4ThreeVector(12*cm,0,0),
                        steelWall_logic,
                        "steelWall_physic",
                        logicWorld,
                        false,
                        0,
                        true);

////////////////////////////////////////////////////////////////////////////////
//									     ///
//				Copper Rod				     ///
//									     ///
////////////////////////////////////////////////////////////////////////////////

	G4Tubs* cuRod_solid = new G4Tubs("cuRod_solid",
			0,
			cuRodRadius,
			steelZ,
			0*deg,
			360*deg);

	G4LogicalVolume* cuRod_logic = new G4LogicalVolume(
			cuRod_solid,
			CuMat,
			"CuRod_logic",
			0,0,0);

	G4PVPlacement* cuRod_physic = new G4PVPlacement(
			0,
			G4ThreeVector(cuSpacing,0,0),
			cuRod_logic,
			"cuRod_physic",
			logicWorld,
			false,
			0,
			true);

//////////////////////////////////////////////////////////////////////////
//									//
//			Overall Detector Geometry		     	//
//									//
//////////////////////////////////////////////////////////////////////////

	G4Box* SiOverall_solid = new G4Box("SiOverall_solid",
			overallBotX, //using because it's thicker/sure to contain
			overallY,
			overallZ);

	G4LogicalVolume* SiOverall_logic = new G4LogicalVolume(
			SiOverall_solid,
			worldMaterial,
			"SiOverall_logic",
			0,0,0);

        G4PVPlacement* SiOverall_physic = new G4PVPlacement(
                        0,
                        G4ThreeVector(-overallBotX-steelThickness,0,0),
                        SiOverall_logic,
                        "SiOverall_physic",
                        logicWorld,
                        false,
                        0,
                        true);

	SiOverall_logic->SetVisAttributes(visAttWorld);
*/
/////////////////////////////////////////////////////////////////////////////////
//                            Wrapping Geometry                                //
/////////////////////////////////////////////////////////////////////////////////	
/* //geometry to be used when photocathode is attached to PMT
	G4Box* wrap_solid_total = new G4Box("wrap_solid_total",
			wrapXY,
			wrapXY,
			wrapZ);

	G4Tubs* wrap_PMT_hole = new G4Tubs("wrap_PMT_hole",
			0,
			outerRadius_pmt,
			(wrapThickness+airGapThickness)/2,
			0*deg,
			360*deg);	

//	G4ThreeVector* subVec = new G4ThreeVector(0,0,wrapX-wrapThickness/2);
	G4RotationMatrix* rot = new G4RotationMatrix();
	G4SubtractionSolid* wrap_solid = new G4SubtractionSolid("wrap_solid",
			wrap_solid_total,
			wrap_PMT_hole,
			rot,
			//11 mm is y-axis PMT offset
			G4ThreeVector(0,0,wrapZ-(airGapThickness+wrapThickness)/2));
*/

/*
	G4Box* wrap_solid = new G4Box("wrap_solid",
			wrapXY,
			wrapXY,
			wrapZ);

	G4LogicalVolume* wrap_logic = new G4LogicalVolume(
			wrap_solid,
			wrapMat,
			"wrap_logic",
			0, 0, 0);


	
	G4PVPlacement* wrap_physic = new G4PVPlacement(
			0,
			G4ThreeVector(),
			wrap_logic,
			"wrap_physic",
			logicWorld,
			false,
			0,
			true);
*/

	
/////////////////////////////////////////////////////////////////////////////////
//                            Air Gap Geometry                                //
/////////////////////////////////////////////////////////////////////////////////	
/*
	G4Box* airgap_solid_total = new G4Box("airgap_solid_total",
			airgapX,
			airgapY,
			airgapZ);

	G4Tubs* airgap_PMT_hole = new G4Tubs("airgap_PMT_hole",
			0,
			outerRadius_pmt,
			airGapThickness/2,
			0*deg,
			360*deg);	

	G4RotationMatrix* rot2 = new G4RotationMatrix();
//	G4ThreeVector* subVec = new G4ThreeVector(0,0,wrapX-wrapThickness/2);
	G4SubtractionSolid* airgap_solid = new G4SubtractionSolid("airgap_solid",
			airgap_solid_total,
			airgap_PMT_hole,
			rot2,
			//11 mm is y-axis PMT offset
			G4ThreeVector(0,pmtYoffset,airgapZ-airGapThickness/2));
*/
/*
	G4Box* airgap_solid = new G4Box("airgap_solid",
			airgapX,
			airgapY,
			airgapZ);

	G4LogicalVolume* airgap_logic = new G4LogicalVolume(
			airgap_solid,
			worldMaterial,
			"airgap_logic",
			0, 0, 0);

	G4PVPlacement* airgap_physic = new G4PVPlacement(
			0,
			G4ThreeVector(),
			airgap_logic,
			"airgap_physic",
			wrap_logic,
			false,
			0,
			true);
*/	
/////////////////////////////////////////////////////////////////////////////////
//                            Scintillator Geometry                                //
/////////////////////////////////////////////////////////////////////////////////	
/*
	G4Box* SiDet_solid = new G4Box("SiDet_solid",
				scintX, 
				scintY,
				scintZ);

	G4LogicalVolume* SiDet_logic1 = new G4LogicalVolume(
				SiDet_solid,
				//matPlScin,
				SiMat,
				"SiDet_logic1",
				0, 0, 0);

	G4LogicalVolume* SiDet_logic2 = new G4LogicalVolume(
				SiDet_solid,
				//matPlScin,
				SiMat,
				"SiDet_logic2",
				0, 0, 0);

	G4LogicalVolume* SiDet_logic3 = new G4LogicalVolume(
				SiDet_solid,
				//matPlScin,
				SiMat,
				"SiDet_logic3",
				0, 0, 0);

	G4LogicalVolume* SiDet_logic4 = new G4LogicalVolume(
				SiDet_solid,
				//matPlScin,
				SiMat,
				"SiDet_logic4",
				0, 0, 0);

	G4LogicalVolume* SiDet_logic5 = new G4LogicalVolume(
				SiDet_solid,
				//matPlScin,
				SiMat,
				"SiDet_logic5",
				0, 0, 0);

	G4PVPlacement* SiDet_physic1 = new G4PVPlacement(
			0,
			G4ThreeVector(2*wrapX*2+4*layerSpacing+absThickness1+absThickness2,0,0),
			SiDet_logic1,
			"SiDet_physic1",
			SiOverall_logic,
			false,
			0,
			true);

	G4PVPlacement* SiDet_physic2 = new G4PVPlacement(
			0,
			G4ThreeVector(wrapX*2+2*layerSpacing+absThickness2,0,0),
			SiDet_logic2,
			"SiDet_physic2",
			SiOverall_logic,
			false,
			0,
			true);

	G4PVPlacement* SiDet_physic3 = new G4PVPlacement(
			0,
			G4ThreeVector(),
			SiDet_logic3,
			"SiDet_physic3",
			SiOverall_logic,
			false,
			0,
			true);

	G4PVPlacement* SiDet_physic4 = new G4PVPlacement(
			0,
			G4ThreeVector(-wrapX*2-2*layerSpacing-absThickness3,0,0),
			SiDet_logic4,
			"SiDet_physic4",
			SiOverall_logic,
			false,
			0,
			true);
	G4PVPlacement* SiDet_physic5 = new G4PVPlacement(
			0,
			G4ThreeVector(-2*wrapX*2-4*layerSpacing-absThickness3-absThickness4,0,0),
			SiDet_logic5,
			"SiDet_physic5",
			SiOverall_logic,
			false,
			0,
			true);

	*/


//////////////////////////////////////////////////////////////////////////////////
//                           Absorber						//
//////////////////////////////////////////////////////////////////////////////////
/*

	G4Box* abs_solid1 = new G4Box("abs_solid1",
				absThickness1/2,
				scintY,
				scintZ);

	G4Box* abs_solid2 = new G4Box("abs_solid2",
				absThickness2/2,
				scintY,
				scintZ);

	G4Box* abs_solid3 = new G4Box("abs_solid3",
				absThickness3/2,
				scintY,
				scintZ);

	G4Box* abs_solid4 = new G4Box("abs_solid4",
				absThickness4/2,
				scintY,
				scintZ);

	G4LogicalVolume* abs_logic1 = new G4LogicalVolume(
				abs_solid1,
				AgMat, //AlMat //absMat
				"abs_logic1",
				0, 0, 0);

	G4LogicalVolume* abs_logic2 = new G4LogicalVolume(
				abs_solid2,
				AuMat, //CuMat //absMat
				"abs_logic2",
				0, 0, 0);

	G4LogicalVolume* abs_logic3 = new G4LogicalVolume(
				abs_solid3,
				AgMat, //AgMat or NiMat //absMat
				"abs_logic3",
				0, 0, 0);

	G4LogicalVolume* abs_logic4 = new G4LogicalVolume(
				abs_solid4,
				AuMat, //FeMat //absMat
				"abs_logic4",
				0, 0, 0);

	G4PVPlacement* abs_physic1 = new G4PVPlacement(
			0,
			G4ThreeVector(3*wrapX+3*layerSpacing+absThickness1/2+absThickness2,0,0),
			abs_logic1,
			"abs_physic1",
			SiOverall_logic,
			false,
			0,
			true);
	
	G4PVPlacement* abs_physic2 = new G4PVPlacement(
			0,
			G4ThreeVector(wrapX+1*layerSpacing+absThickness2/2,0,0),
			abs_logic2,
			"abs_physic2",
			SiOverall_logic,
			false,
			0,
			true);
	
	G4PVPlacement* abs_physic3 = new G4PVPlacement(
			0,
			G4ThreeVector(-wrapX-1*layerSpacing-absThickness3/2,0,0),
			abs_logic3,
			"abs_physic3",
			SiOverall_logic,
			false,
			0,
			true);

	G4PVPlacement* abs_physic4 = new G4PVPlacement(
			0,
			G4ThreeVector(-3*wrapX-3*layerSpacing-absThickness3-absThickness4/2,0,0),
			abs_logic4,
			"abs_physic4",
			SiOverall_logic,
			false,
			0,
			true);
*/
////////////////////////////////////////////////////////////////////////////////
//			Scintillator High Energy Xray veto		      //
////////////////////////////////////////////////////////////////////////////////

/*
	G4Box* scintVeto_solid = new G4Box("scintVeto_solid",
				scintVetoThickness/2,
				scintY,
				scintZ);

	G4LogicalVolume* scintVeto_logic = new G4LogicalVolume(
				scintVeto_solid,
				matPlScin,
				"scintVeto_logic",
				0, 0, 0);

	G4PVPlacement* scintVeto_physic = new G4PVPlacement(
			0,
			G4ThreeVector(-5*wrapX-5*mm-absThickness3-absThickness4-scintVetoThickness/2,0,0),
			scintVeto_logic,
			"scintVeto_physic",
			SiOverall_logic,
			false,
			0,
			true);
*/
    //==========================================================================
    //---------------Scintillator Sensitive Detector---------------
    //==========================================================================
/*
	G4SDManager* SDman = G4SDManager::GetSDMpointer();
	G4String SDnameC = "BeamRad/ScintiSensitiveDetector";
	brScintSD* scintSD = new brScintSD(SDnameC);
	SDman->AddNewDetector ( scintSD );
	SiDet_logic1->SetSensitiveDetector(scintSD);

	SiDet_logic2->SetSensitiveDetector(scintSD);
	SiDet_logic3->SetSensitiveDetector(scintSD);
	SiDet_logic4->SetSensitiveDetector(scintSD);
	SiDet_logic5->SetSensitiveDetector(scintSD);
	scintVeto_logic->SetSensitiveDetector(scintSD);
	//abs_logic->SetSensitiveDetector(scintSD);
*/
   G4String SDnameOfScintDetector = "Scint_SD";
   brScintSD* myScintSD = new brScintSD(SDnameOfScintDetector);
   G4SDManager::GetSDMpointer()->AddNewDetector(myScintSD);


////////////////    G4 Vis attributes        /////////////////////////////
	
	G4VisAttributes* visAttribSiDet = new G4VisAttributes(G4Colour::White());
	visAttribSiDet->SetVisibility(true);
	
//	G4VisAttributes* visAttribAbs = new G4VisAttributes(
//			G4Colour::Gray());
//	visAttribAbs->SetVisibility(true);

	G4VisAttributes* visAttribAbsAl = new G4VisAttributes(
			G4Colour::Gray());
	visAttribAbsAl->SetVisibility(true);

	G4VisAttributes* visAttribAbsCu = new G4VisAttributes(
			G4Colour::Red());
	visAttribAbsCu->SetVisibility(true);

	G4VisAttributes* visAttribAbsFR4 = new G4VisAttributes(
			G4Colour::Green());
	visAttribAbsFR4->SetVisibility(true);

	G4VisAttributes* visAttribAbsNi = new G4VisAttributes(
			G4Colour::Gray());
	visAttribAbsNi->SetVisibility(true);

	G4VisAttributes* visAttribAbsFe = new G4VisAttributes(
			G4Colour::Black());
	visAttribAbsFe->SetVisibility(true);

/*
	G4VisAttributes* visAttribSiDetExt = new G4VisAttributes(G4Colour::Cyan());
	visAttribSiDetExt->SetVisibility(false);
	
	G4VisAttributes* visAttribWrapExt = new G4VisAttributes(
			G4Colour::White());
	visAttribWrapExt->SetColour(0.5,0.5,0.5,0.3);
	visAttribWrapExt->SetVisibility(true);

	G4VisAttributes* visAttribLead = new G4VisAttributes(
			G4Colour::Black());
	visAttribLead->SetVisibility(true);
	
*/
/*	abs_logic1->SetVisAttributes(visAttribAbs);
	abs_logic2->SetVisAttributes(visAttribAbs);
	abs_logic3->SetVisAttributes(visAttribAbs);
	abs_logic4->SetVisAttributes(visAttribAbs);
*/

	//SiLayer_logic->SetVisAttributes(visAttribSiDet);
	SiBulk_logic1->SetVisAttributes(visAttribAbsNi);
	FR4_logic->SetVisAttributes(visAttribAbsFR4);
	SiDet_logic1->SetVisAttributes(visAttribSiDet);

/*
	abs_logic1->SetVisAttributes(visAttribAbsAl);
	abs_logic2->SetVisAttributes(visAttribAbsCu);
	abs_logic3->SetVisAttributes(visAttribAbsNi);
	abs_logic4->SetVisAttributes(visAttribAbsFe);
	SiDet_logic1->SetVisAttributes(visAttribSiDet);
	SiDet_logic2->SetVisAttributes(visAttribSiDet);
	SiDet_logic3->SetVisAttributes(visAttribSiDet);
	SiDet_logic4->SetVisAttributes(visAttribSiDet);
	SiDet_logic5->SetVisAttributes(visAttribSiDet);
	scintVeto_logic->SetVisAttributes(visAttribSiDet);

	cuRod_logic->SetVisAttributes(visAttribAbsCu);
	steelWall_logic->SetVisAttributes(visAttribAbsNi);
*/
////////////////////////////////////////////////////////////////////////////

/*//////////////////////////////////////////////////////////////////////////////////////////////////////
*/
	 //the "photocathode" is a metal slab at the front of the glass that
	 //is only an approximation of the real thing since it only
	 //absorbs or detects the photons based on the efficiency set

//////////////////// moving placement of phCathSolid from PMT to the      ////////////////////////
//////////////////// Pixel volume s.t. there are no logical volume overlaps ///////////////////////

   //sensitive detector is not actually on the photocathode.
   //processHits gets done manually by the stepping action.
   //It is used to detect when photons hit and get absorbed&detected at the
   //boundary to the photocathode (which doesnt get done by attaching it to a
   //logical volume.
   //It does however need to be attached to something or else it doesnt get
   //reset at the begining of events
   //==========================================================================
   //---------------PMT Sensitive Detector---------------
   //==========================================================================
/*
	G4String SDnameOfPMTDetector = "PMT_SD";
   brPMTSD* myPMTSD = new brPMTSD(SDnameOfPMTDetector);

   G4SDManager::GetSDMpointer()->AddNewDetector(myPMTSD);
	myPMTSD->InitPMTs(nbAllPmts);
	myPMTSD->SetR878_QE(GetPMTEff_R878());
	myPMTSD->SetR7725_QE(GetPMTEff_R7725());
	myPMTSD->SetET9814B_QE(GetPMTEff_ET9814B());
	phCathLog->SetSensitiveDetector(myPMTSD); //change HERE for PMT Scenario
//  	G4ThreeVector PMTPosition1 = G4ThreeVector(0,pmtYoffset,scintZ+height_pmt/2+(nLayers-1)*layerSpacing/2);
  //  	G4RotationMatrix rotm1  = G4RotationMatrix();//(G4ThreeVector(0, -1., 0. ), pi / 2.0);
//	G4Transform3D transform = G4Transform3D(rotm1,PMTPosition1);
*/
/*
	G4PVPlacement* pmtPhys = new G4PVPlacement(transform,   //rotation,position
			                     pmtLog,                   //its logical volume
			                     "pmt_physic",                //its name
			                     logicWorld,              //its mother  volume
			                     false,                    //no boolean operation
			                     nbAllPmts,             //copy number
			                     true);           //checking overlaps
*/
/*
	// visual attributes for all PMTs;
	G4VisAttributes* visAttribPMT = new G4VisAttributes(G4Colour::Blue());
	visAttribPMT->SetForceWireframe(false);
	visAttribPMT->SetForceSolid(true);
	visAttribPMT->SetVisibility(true);

	//setting same color so it doesn't look bad in isometric view
	
	//G4VisAttributes* visAttribPhCath = new G4VisAttributes(G4Colour::Blue());
	G4VisAttributes* visAttribPhCath = new G4VisAttributes(G4Colour::Red());
	visAttribPhCath->SetForceWireframe(false);
	visAttribPhCath->SetForceSolid(false);
	visAttribPhCath->SetVisibility(true);

	pmtLog->SetVisAttributes(visAttribPMT);
	phCathLog->SetVisAttributes(visAttribPhCath);
*/
	//==============================================================================
	// Optical Surfaces
	//==============================================================================
	// Optical Properties
	// Note that, as mentioned in HyperNews posts and the G4AppDev Guide, the definition
	// of a logical bordfer surface involves a ordered pair of materials, such that
	// despite there being no clearly defined structure/class in the prototpye, the
	// order in which the surfaces are listed defines the orientation of the surface;
	// particles "see" this surface only when traveling from the first listed physical
	// volume into the second, which is why I have created a pair of complementary
	// surfaces for every interface (producing identical, bidirectional interactions).


//    G4OpticalSurface* opSDielectricBiAlkali = new G4OpticalSurface("Detector", unified,
//                                                    polished, dielectric_metal);
    //////////////////
//    G4MaterialPropertiesTable* mtphcath =  matBiAlkali->GetMaterialPropertiesTable();
//    opSDielectricBiAlkali->SetMaterialPropertiesTable(mtphcath);
//    opSDielectricBiAlkali->SetMaterialPropertiesTable(SetOpticalPropertiesOfPMT());

//    G4OpticalSurface* opSWrapScintillator = new G4OpticalSurface("Wrapping", unified,
//                              /*ground*/      groundteflonair,
//                                                dielectric_metal);
//	const G4int nEntriesWrap = 2;
//	G4double photonEnergyWrap[nEntriesWrap]={ 1.5 * eV,6.3 * eV};
//	G4double wrap_REFL[nEntriesWrap] = {wrapRefl,wrapRefl};//{0.95,0.95}
//	G4double wrap_RIND[nEntriesWrap];

//	G4MaterialPropertiesTable* mptWrap = new G4MaterialPropertiesTable();
	//mptWrap->AddProperty("TRANSMITTANCE",photonEnergyWrap, foil_REFL, nEntriesWrap);//->SetSpline(true);
//	mptWrap->AddProperty("REFLECTIVITY",photonEnergyWrap, wrap_REFL, nEntriesWrap);
    
//    opSWrapScintillator->SetMaterialPropertiesTable(mptWrap);

//define optical surfaces for each object in the sim, and match the optical properties of each surface to it

//    new G4LogicalSkinSurface("Wrap", wrap_logic, opSWrapScintillator);
//    new G4LogicalSkinSurface("PhCath", phCathLog, opSDielectricBiAlkali);

//Connect detector volume (photocathode) to each surface which is in contact with it
// use this if you want to explicitly define the allowed optical surfaces rather than a wrapping
//        new G4LogicalBorderSurface("Glass->PhCath",
//			pmtPhys,phCathPhys,opSDielectricBiAlkali);
//			PMTParam_phys,phCathPhys,opSDielectricBiAlkali);

//	new G4LogicalBorderSurface("PhCath->Glass",
//			phCathPhys,pmtPhys,opSDielectricBiAlkali);
//			phCathPhys,PMTParam_phys,opSDielectricBiAlkali);
/*
    new G4LogicalBorderSurface("Scinti->PhCath",
			barParamPhys[0], PMTParamPhys[0] ,opSDielectricBiAlkali);
			//SiDet_physic, phCathPhys ,opSDielectricBiAlkali);

    new G4LogicalBorderSurface("PhCath->Scinti",
    			PMTParamPhys[0] ,barParamPhys[0] ,opSDielectricBiAlkali);
    			//phCathPhys ,SiDet_physic ,opSDielectricBiAlkali);
*/
/*
    new G4LogicalBorderSurface("AirGap->PhCath",
			airgap_physic, phCathPhys ,opSDielectricBiAlkali);

    new G4LogicalBorderSurface("PhCath->AirGap",
    			phCathPhys ,airgap_physic ,opSDielectricBiAlkali);
*/
//*/
    return physicWorld;

}

G4MaterialPropertiesTable* brDetectorConstruction::SetOpticalPropertiesOfPS(){


G4MaterialPropertiesTable* mptPlScin = new G4MaterialPropertiesTable();

 const G4int nEntries= 43;//301;//100;

	G4double EJ200_SCINT[nEntries];
	G4double EJ200_RIND[nEntries];
	G4double EJ200_ABSL[nEntries];
	G4double photonEnergy[nEntries];

	std::ifstream ReadEJ200;
	G4int ScintEntry=0;
	G4String filler;
	G4double pEnergy;
	G4double pWavelength;
	G4double pSEff;
	ReadEJ200.open("/media/ryan/Storage/computing/beamRadSim/OpticalData/EJ200ScintSpectrum.txt");
	if(ReadEJ200.is_open()){
	while(!ReadEJ200.eof()){
	ReadEJ200 >> pWavelength >> pSEff;
	pEnergy = (1240/pWavelength)*eV;
	photonEnergy[ScintEntry] = pEnergy;
	EJ200_SCINT[ScintEntry] = pSEff;
	G4cout << "read-in energy scint: " << photonEnergy[ScintEntry] << " eff: " << EJ200_SCINT[ScintEntry] << G4endl;
	ScintEntry++;
	}
	}
	else
	G4cout << "Error opening file: " << "EJ200ScintSpectrum.txt" << G4endl;
	ReadEJ200.close();


	for (int i = 0; i < nEntries; i++) {
		EJ200_RIND[i] = 1.58;//58; // refractive index at 425 nm
		//EJ200_ABSL[i] *= myPSAttenuationLength;
		EJ200_ABSL[i] = 3.8*m;//2.5 * m; // bulk attenuation at 425 nm
	}

	mptPlScin->AddProperty("FASTCOMPONENT", photonEnergy, EJ200_SCINT,
			nEntries);//->SetSpline(true);


	mptPlScin->AddProperty("ABSLENGTH", photonEnergy, EJ200_ABSL,
				nEntries);//->SetSpline(true);

	mptPlScin->AddConstProperty("SCINTILLATIONYIELD", 10000. / MeV); //--- according to EJ200
	mptPlScin->AddConstProperty("RESOLUTIONSCALE", 1.0);
	mptPlScin->AddConstProperty("FASTTIMECONSTANT", 2.1 * ns); //decay time, according to EJ200
	mptPlScin->AddProperty("RINDEX", photonEnergy, EJ200_RIND, nEntries);//->SetSpline(true);

return mptPlScin;
}

G4MaterialPropertiesTable* brDetectorConstruction::SetOpticalPropertiesOfPMT(){

	G4MaterialPropertiesTable* mptPMT = new G4MaterialPropertiesTable();

	const G4int nEntriesPMT = 41;//27;//36;//2;//37;//15; //just figure out how many entries are in the text file,
								//unless you're not lazy like me and want to dynamically allocate memory
//* PMT QEff read-in (updated Jan 2018)
	G4double photonEnergyPMT[nEntriesPMT];
	G4double photocath_EFF[nEntriesPMT];
	G4double PhCath_REFL[nEntriesPMT]; // to be determined
	
	std::ifstream ReadPMTQEff;
	G4int PMTEntry=0;
	G4String filler;
	G4double pEnergy;
	G4double pWavelength;
	G4double pQEff;
	ReadPMTQEff.open("/media/ryan/Storage/computing/beamRadSim/OpticalData/PMT_R878_QE_orig.txt");
	if(ReadPMTQEff.is_open()){
	while(!ReadPMTQEff.eof()){
	ReadPMTQEff >> pWavelength >> pQEff;
	pQEff=1;
	pEnergy = (1240/pWavelength)*eV;
	photonEnergyPMT[PMTEntry] = pEnergy;
	photocath_EFF[PMTEntry] = pQEff;
	PhCath_REFL[PMTEntry] = 0;
	G4cout << "read-in energy: " << photonEnergyPMT[PMTEntry] << " eff: " << photocath_EFF[PMTEntry] << G4endl;
	PMTEntry++;
	}
	}
	else
	G4cout << "Error opening file: " << "PMT_R878_QE.txt" << G4endl;
	ReadPMTQEff.close();
/*	
	G4double PhCath_REFL[nEntriesPMT] = { // to be determined
			0., 0.,0.,0.,0.,0.,0.,0.,0.,0.,
			0., 0.,0.,0.,0.//,0.,0.,0.,0.,0.,
			//0., 0.,0.,0.,0.,0.,0.//,0.,0.,0.,
			//0., 0.,0.,0.,0.,0.//,0.
			};
*/

	mptPMT->AddProperty("REFLECTIVITY", photonEnergyPMT,PhCath_REFL, nEntriesPMT);//->SetSpline(true);
	mptPMT->AddProperty("EFFICIENCY",photonEnergyPMT,photocath_EFF,nEntriesPMT);//->SetSpline(true);

	G4cout << "successfully at end of PMT optical table" << G4endl;
	
	return mptPMT;

}

G4PhysicsVector brDetectorConstruction::GetPMTEff_R878(){
	
	std::ifstream ReadPMTQEff;
	ReadPMTQEff.open("/media/ryan/Storage/computing/beamRadSim/OpticalData/PMT_R878_QE.txt");
	G4PhysicsVector effVec;
	effVec.Retrieve(ReadPMTQEff,true);
	if (effVec.GetVectorLength()!=0) G4cout << "Quantum Efficiency successfully retrieved for PMT_R878_QE" << G4endl;
	else G4cout << "ERROR: Vector length is zero!" << G4endl;
	return effVec;
}

G4PhysicsVector brDetectorConstruction::GetPMTEff_R7725(){
	
	std::ifstream ReadPMTQEff;
	ReadPMTQEff.open("/media/ryan/Storage/computing/beamRadSim/OpticalData/PMT_R7725_QE.txt");
	G4PhysicsVector effVec;
	effVec.Retrieve(ReadPMTQEff,true);
	if (effVec.GetVectorLength()!=0) G4cout << "Quantum Efficiency successfully retrieved for PMT R7725" << G4endl;
	else G4cout << "ERROR: Vector length is zero!" << G4endl;
	return effVec;
}

G4PhysicsVector brDetectorConstruction::GetPMTEff_ET9814B(){
	
	std::ifstream ReadPMTQEff;
	ReadPMTQEff.open("/media/ryan/Storage/computing/beamRadSim/OpticalData/PMT_ET9814B_QE.txt");
	G4PhysicsVector effVec;
	effVec.Retrieve(ReadPMTQEff,true);
	if (effVec.GetVectorLength()!=0) G4cout << "Quantum Efficiency successfully retrieved for PMT ET9814B" << G4endl;
	else G4cout << "ERROR: Vector length is zero!" << G4endl;
	return effVec;
}

void brDetectorConstruction::UpdateGeometry() {
	if (verbose >= 0) {
		G4cout << "BeamRad> Update geometry." << G4endl;
		G4cout
				<< "               Don't use this command explicitly, it's obsolete and can crash the run."
				<< G4endl;
	}
	// clean-up previous geometry
    G4GeometryManager::GetInstance()->OpenGeometry();
    G4PhysicalVolumeStore::GetInstance()->Clean();
    G4LogicalVolumeStore::GetInstance()->Clean();
    G4SolidStore::GetInstance()->Clean();
    G4LogicalSkinSurface::CleanSurfaceTable();
    G4LogicalBorderSurface::CleanSurfaceTable();
    G4SurfaceProperty::CleanSurfacePropertyTable();
    //define new one
	G4RunManager::GetRunManager()->DefineWorldVolume(Construct());
	G4RunManager::GetRunManager()->GeometryHasBeenModified();
	updated=false;
}


void brDetectorConstruction::SetDefaults(){
  //Resets to default values


  updated=true;
}



