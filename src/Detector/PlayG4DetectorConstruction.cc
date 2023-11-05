//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file PlayG4DetectorConstruction.cc
/// \brief Implementation of the PlayG4DetectorConstruction class
 
#include "PlayG4DetectorConstruction.hh"
#include "PlayG4DetectorMessenger.hh"
#include "PlayG4ChamberParameterisation.hh"
#include "PlayG4TrackerSD.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4SDManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"

#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"

#include "G4UserLimits.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal 
G4GlobalMagFieldMessenger* PlayG4DetectorConstruction::fMagFieldMessenger = 0;
 
PlayG4DetectorConstruction::PlayG4DetectorConstruction()
:G4VUserDetectorConstruction(),
 fLogicTarget(NULL), labLV(NULL), 
 fTargetMaterial(NULL), fChamberMaterial(NULL), 
 fStepLimit(NULL), 
 fCheckOverlaps(true), fWaterPropertyFile("data/Water.dat")
{
  fMessenger = new PlayG4DetectorMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
PlayG4DetectorConstruction::~PlayG4DetectorConstruction()
{
  delete fStepLimit;
  delete fMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
G4VPhysicalVolume* PlayG4DetectorConstruction::Construct()
{
  // Define materials
  DefineMaterials();

  // Define volumes
  return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PlayG4DetectorConstruction::DefineMaterials()
{
  // Material definition 

  G4NistManager* nistManager = G4NistManager::Instance();

  // Air defined using NIST Manager
  nistManager->FindOrBuildMaterial("G4_AIR");
  
  // Lead defined using NIST Manager
  fTargetMaterial  = nistManager->FindOrBuildMaterial("G4_Pb");
  fShieldMaterial = nistManager->FindOrBuildMaterial("G4_WATER");
  // LAB material
  G4bool isotopes = false;
  G4Element* H = nistManager->FindOrBuildElement("H", isotopes);
  G4Element* C = nistManager->FindOrBuildElement("C", isotopes);
  G4double density = 0.863*g/cm3;
  // fChamberMaterial = new G4Material("LAB", density, 2);
  // fChamberMaterial->AddElement(H, 30);
  // fChamberMaterial->AddElement(C, 18);
  fChamberMaterial = nistManager->FindOrBuildMaterial("G4_WATER");
  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
  auto* Water_MPT = GetPropertyTable(fWaterPropertyFile);
  // SetWaterMaterial(Water_MPT);
  // SetMaterialPropertyMap("Water",  fWaterPropertyFile);
  fChamberMaterial->SetMaterialPropertiesTable(Water_MPT);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* PlayG4DetectorConstruction::DefineVolumes()
{
  G4Material* air  = G4Material::GetMaterial("G4_AIR");
  G4Material* pmtMaterial = G4Material::GetMaterial("G4_Fe");
  // Sizes of the principal geometrical components (solids)
  
  G4int NbOfChambers = 5;
  G4double chamberSpacing = 80*cm; // from chamber center to center!

  G4double chamberWidth = 20.0*cm; // width of the chambers
  G4double targetLength =  5.0*cm; // full length of Target
  
  G4double trackerLength = (NbOfChambers+1)*chamberSpacing;

  G4double labRadius = 14.1*m;
  G4double waterRadius = 15*m;
  G4double waterHeight = 2*waterRadius;
  G4double pbRadius1 = 15.1*m;
  G4double pbRadius2 = 15.2*m; 
  G4double pbHeight = waterHeight+20*cm;
  G4double worldLength = 2.5 * 2 * pbRadius2;


  G4double targetRadius  = 0.5*targetLength;   // Radius of Target
  targetLength = 0.5*targetLength;             // Half length of the Target  
  G4double trackerSize   = 0.5*trackerLength;  // Half length of the Tracker

  // Definitions of Solids, Logical Volumes, Physical Volumes

  // World

  G4GeometryManager::GetInstance()->SetWorldMaximumExtent(worldLength);

  G4cout << "Computed tolerance = "
         << G4GeometryTolerance::GetInstance()->GetSurfaceTolerance()/mm
         << " mm" << G4endl;

  G4Box* worldS
    = new G4Box("world",                                    //its name
                worldLength/2,worldLength/2,worldLength/2); //its size
  G4LogicalVolume* worldLV
    = new G4LogicalVolume(
                 worldS,   //its solid
                 air,      //its material
                 "World"); //its name
  
  //  Must place the World Physical volume unrotated at (0,0,0).
  // 
  G4VPhysicalVolume* worldPV
    = new G4PVPlacement(
                 0,               // no rotation
                 G4ThreeVector(), // at (0,0,0)
                 worldLV,         // its logical volume
                 "World",         // its name
                 0,               // its mother  volume
                 false,           // no boolean operations
                 0,               // copy number
                 fCheckOverlaps); // checking overlaps 

  // pb sheild

  G4Tubs* targetS
    = new G4Tubs("target",pbRadius1,pbRadius2,pbHeight/2,0.*deg,360.*deg);
  fLogicTarget
    = new G4LogicalVolume(targetS, fTargetMaterial,"Target",0,0,0);
  new G4PVPlacement(0,              // no rotation
                    G4ThreeVector(), // at (x,y,z)
                    fLogicTarget,   // its logical volume
                    "Target",       // its name
                    worldLV,        // its mother volume
                    false,          // no boolean operations
                    0,              // copy number
                    fCheckOverlaps); // checking overlaps 

  G4cout << "Target is " << 2*pbHeight/cm << " cm of "
         << fTargetMaterial->GetName() << G4endl;
  // water sheild

  G4Tubs* waterS
    = new G4Tubs("watersheild",labRadius,waterRadius,waterHeight/2,0.*deg,360.*deg);
  G4LogicalVolume* fLogicWater
    = new G4LogicalVolume(waterS, fShieldMaterial,"Watershield",0,0,0);
  
  new G4PVPlacement(0,              // no rotation
                    G4ThreeVector(), // at (x,y,z)
                    fLogicWater,   // its logical volume
                    "WaterPv",       // its name
                    worldLV,        // its mother volume
                    false,          // no boolean operations
                    0,              // copy number
                    fCheckOverlaps); // checking overlaps 

  G4cout << "Water is " << 2*waterHeight/cm << " cm of "
         << fShieldMaterial->GetName() << G4endl;

  // Tracker
 
  G4ThreeVector positionLab = G4ThreeVector(0,0,0);

  G4Sphere* labS
    = new G4Sphere("lab",0, labRadius, 0.*deg, 360.*deg, 0.*deg, 180.*deg);
  labLV
    = new G4LogicalVolume(labS, fChamberMaterial, "Lab",0,0,0);  
  new G4PVPlacement(0,               // no rotation
                    positionLab, // at (x,y,z)
                    labLV,       // its logical volume
                    "Lab",       // its name
                    worldLV,         // its mother  volume
                    false,           // no boolean operations
                    0,               // copy number
                    fCheckOverlaps); // checking overlaps 

  // Tracker segments
  
  // An example of Parameterised volumes
  // Dummy values for G4Tubs -- modified by parameterised volume

  G4Tubs* chamberS
    = new G4Tubs("tracker",0, 100*cm, 100*cm, 0.*deg, 360.*deg);
  G4LogicalVolume* pmtLV 
    = new G4LogicalVolume(chamberS,fChamberMaterial,"Chamber",0,0,0);
  
  G4double firstPosition = -trackerSize + chamberSpacing;
  G4double firstLength   = trackerLength/10;
  G4double lastLength    = trackerLength;

  G4VPVParameterisation* chamberParam =
    new PlayG4ChamberParameterisation(
                                  NbOfChambers,   // NoChambers
                                  firstPosition,  // Z of center of first
                                  chamberSpacing, // Z spacing of centers
                                  chamberWidth,  // chamber width
                                  firstLength,    // initial length 
                                  lastLength);    // final length
                           
  // dummy value : kZAxis -- modified by parameterised volume
/*
  new G4PVParameterised("Chamber",       // their name
                        labLV,   // their logical volume
                        trackerLV,       // Mother logical volume
                        kZAxis,          // Are placed along this axis 
                        NbOfChambers,    // Number of chambers
                        chamberParam,    // The parametrisation
                        fCheckOverlaps); // checking overlaps 

  G4cout << "There are " << NbOfChambers << " chambers in the tracker region. "
         << G4endl
         << "The chambers are " << chamberWidth/cm << " cm of "
         << fChamberMaterial->GetName() << G4endl
         << "The distance between chamber is " << chamberSpacing/cm << " cm" 
         << G4endl;
*/
  // Visualization attributes

  G4VisAttributes* boxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  worldLV   ->SetVisAttributes(boxVisAtt);  
  fLogicTarget ->SetVisAttributes(boxVisAtt);
  fLogicWater ->SetVisAttributes(boxVisAtt);

  G4VisAttributes* chamberVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,0.0));
  labLV->SetVisAttributes(chamberVisAtt);
  
  // Example of User Limits
  //
  // Below is an example of how to set tracking constraints in a given
  // logical volume
  //
  // Sets a max step length in the tracker region, with G4StepLimiter

  G4double maxStep = 0.5*chamberWidth;
  fStepLimit = new G4UserLimits(maxStep);
  labLV->SetUserLimits(fStepLimit);
  
  /// Set additional contraints on the track, with G4UserSpecialCuts
  ///
  /// G4double maxLength = 2*trackerLength, maxTime = 0.1*ns, minEkin = 10*MeV;
  /// trackerLV->SetUserLimits(new G4UserLimits(maxStep,
  ///                                           maxLength,
  ///                                           maxTime,
  ///                                           minEkin));

  // Always return the physical world

  return worldPV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PlayG4DetectorConstruction::ConstructSDandField()
{
  // Sensitive detectors

  G4String trackerChamberSDname = "PlayG4/TrackerChamberSD";
  PlayG4TrackerSD* aTrackerSD = new PlayG4TrackerSD(trackerChamberSDname,
                                            "TrackerHitsCollection");
  G4SDManager::GetSDMpointer()->AddNewDetector(aTrackerSD);
  SetSensitiveDetector( labLV,  aTrackerSD );

  // Create global magnetic field messenger.
  // Uniform magnetic field is then created automatically if
  // the field value is not zero.
  G4ThreeVector fieldValue = G4ThreeVector();
  fMagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
  fMagFieldMessenger->SetVerboseLevel(1);
  
  // Register the field messenger for deleting
  G4AutoDelete::Register(fMagFieldMessenger);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PlayG4DetectorConstruction::SetTargetMaterial(G4String materialName)
{
  G4NistManager* nistManager = G4NistManager::Instance();

  G4Material* pttoMaterial =
              nistManager->FindOrBuildMaterial(materialName);

  if (fTargetMaterial != pttoMaterial) {
     if ( pttoMaterial ) {
        fTargetMaterial = pttoMaterial;
        if (fLogicTarget) fLogicTarget->SetMaterial(fTargetMaterial);
        G4cout
          << G4endl 
          << "----> The target is made of " << materialName << G4endl;
     } else {
        G4cout
          << G4endl 
          << "-->  WARNING from SetTargetMaterial : "
          << materialName << " not found" << G4endl;
     }
  }
}
 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PlayG4DetectorConstruction::SetChamberMaterial(G4String materialName)
{
  G4NistManager* nistManager = G4NistManager::Instance();

  G4Material* pttoMaterial =
              nistManager->FindOrBuildMaterial(materialName);

  if (fChamberMaterial != pttoMaterial) {
     if ( pttoMaterial ) {
        fChamberMaterial = pttoMaterial;
        if (labLV) labLV->SetMaterial(fChamberMaterial);
        G4cout
          << G4endl 
          << "----> The chambers are made of " << materialName << G4endl;
     } else {
        G4cout
          << G4endl
          << "-->  WARNING from SetChamberMaterial : "
          << materialName << " not found" << G4endl;
     }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void PlayG4DetectorConstruction::SetMaxStep(G4double maxStep)
{
  if ((fStepLimit)&&(maxStep>0.)) fStepLimit->SetMaxAllowedStep(maxStep);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4int PlayG4DetectorConstruction::CountNumbersOfTextLines(const char* filePath)
{
  G4long i = 0;
  ifstream ifs(filePath);
  if (ifs) {
    G4String line;
    while (true) {
      getline(ifs, line);
      i++;
      if (ifs.eof()) break;
    }
  }

  return i-2;	//Header and EOF
}

G4MaterialPropertiesTable* PlayG4DetectorConstruction::GetPropertyTable(G4String FileName)
{
  // #----------------------------------------#
  // Open the Property Table 
  // #----------------------------------------#
  // FileName = PlayG4::ParseEnv(FileName);
  ifstream Data(FileName.c_str(),ios_base::in);
  if (!Data) {
    fMessage->AddMessage("Material Property File couldn't open : ");
    fMessage->AddMessage(FileName);
    fMessage->PrintErr(true);
  }

  // #----------------------------------------#
  // Counting the Column in the File
  // #----------------------------------------#
  G4String str;
  G4String tmp;
  G4int Column = 0;
  getline(Data,str);
  istringstream stream(str);
  while (getline(stream,tmp,' ')) Column++;
  const G4int Entries = CountNumbersOfTextLines(FileName.c_str());
  G4double *Energy = new G4double[Entries];
  G4double *RefIndex = new G4double[Entries];
  G4double *Absorption = new G4double[Entries];
  G4double *Rayleigh = new G4double[Entries];
  G4double *MieScat = new G4double[Entries];
  G4double *MieForward = new G4double[Entries];
  G4double *MieBackward =	new G4double[Entries];
  G4double *MieForwardRatio =	new G4double[Entries];

  // #----------------------------------------#
  // Fill the Property Table to Array
  // #----------------------------------------#
  G4int index = 0;
  G4bool forward_flag = false;
  G4bool backward_flag = false ;
  G4bool ratio_flag = false;
  if (Column==8) {
    Data>>Energy[0]>>RefIndex[0]>>Absorption[0]>>Rayleigh[0]>>MieScat[0]>>MieForward[0]>>MieBackward[0]>>MieForwardRatio[0];
    while (!Data.eof()) {
      Energy[index] = Energy[index]*eV;
      Absorption[index] = Absorption[index]*m;
      Rayleigh[index] = Rayleigh[index]*m;
      MieScat[index] = MieScat[index]*m;
      if (MieForward[0]!=MieForward[index]) forward_flag = true;
      if (MieBackward[0]!=MieBackward[index]) backward_flag = true;
      if (MieForwardRatio[0]!=MieForwardRatio[index]) ratio_flag = true;
      index++;

      Data>>Energy[index]>>RefIndex[index]>>Absorption[index]>>Rayleigh[index]>>MieScat[index]>>MieForward[index]>>MieBackward[index]>>MieForwardRatio[index];
    }
  } else if (Column==3) {
    Data>>Energy[0]>>RefIndex[0]>>Absorption[0];
    while (!Data.eof()) {
      Energy[index] = Energy[index]*eV;
      Absorption[index] = Absorption[index]*m;
      index++;

      Data>>Energy[index]>>RefIndex[index]>>Absorption[index];
    }
  } else if (Column==2) {
    Data>>Energy[0]>>RefIndex[0];
    while (!Data.eof()) {
      Energy[index] = Energy[index]*eV;
      index++;

      Data>>Energy[index]>>RefIndex[index];
    }
  } else {
    fMessage->AddMessage("Material Property File isn't much data table");
    fMessage->AddMessage(FileName);
    fMessage->PrintErr(true);
  }

  // #----------------------------------------#
  // Fill the Property Table to G4 Class
  // #----------------------------------------#
  auto* MPT = new G4MaterialPropertiesTable();
  if (Column>1) MPT->AddProperty("RINDEX",	Energy, RefIndex,	Entries);
  if (Column>2) MPT->AddProperty("ABSLENGTH",	Energy, Absorption,	Entries);
  if (Column>3) MPT->AddProperty("RAYLEIGH",	Energy, Rayleigh,	Entries);
  if (Column>4) {
    MPT->AddProperty("MIEHG", Energy, MieScat, Entries);
    if (!forward_flag) MPT->AddConstProperty("MIEHG_FORWARD", MieForward[0]);
    if (forward_flag) MPT->AddProperty("MIEHG_FORWARD", Energy, MieForward, Entries);
    if (!backward_flag) MPT->AddConstProperty("MIEHG_BACKWARD", MieBackward[0]);
    if (backward_flag) MPT->AddProperty("MIEHG_BACKWARD", Energy, MieBackward, Entries);
    if (!ratio_flag) MPT->AddConstProperty("MIEHG_FORWARD_RATIO", MieForwardRatio[0]);
    if (ratio_flag) MPT->AddProperty("MIEHG_FORWARD_RATIO", Energy, MieForwardRatio, Entries);
  }
  MPT->AddConstProperty("SCINTILLATIONYIELD", 0./MeV);

  Data.close();
  return MPT;
}

