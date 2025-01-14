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
/// \file PlayG4RunAction.cc
/// \brief Implementation of the PlayG4RunAction class

#include "PlayG4RunAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
// analysis
#include "G4AnalysisManager.hh"
#include "PlayG4Storage.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PlayG4RunAction::PlayG4RunAction()
 : G4UserRunAction()
{ 
  fMessage->PrintOneLine("Constructor < Run Action >");
  // set printing event number per each 100 events
  G4RunManager::GetRunManager()->SetPrintProgress(1000);     
  // auto analysisManager = G4AnalysisManager::Instance();
  // G4cout << "Using " << analysisManager->GetType() <<G4endl;
  // analysisManager->SetVerboseLevel(1);
  //analysisManager->SetNtupleMerging(true);

  // Creating ntuple
  // analysisManager->CreateNtuple("Energy", "Energy of nu or n");
  // analysisManager->CreateNtupleDColumn("nEnergy");
  // analysisManager->CreateNtupleDColumn("pEnergy");
  // analysisManager->CreateNtupleDColumn("pAniEnergy");
  // analysisManager->CreateNtupleDColumn("proton_x");
  // analysisManager->CreateNtupleDColumn("proton_y");
  // analysisManager->CreateNtupleDColumn("proton_z");
  // analysisManager->FinishNtuple();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PlayG4RunAction::~PlayG4RunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PlayG4RunAction::BeginOfRunAction(const G4Run*)
{ 
  //inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
  // auto analysisManager = G4AnalysisManager::Instance();
  // G4String fileName = "background";
  // analysisManager->OpenFile(fileName);
  auto RootFile = PlayG4Storage::GetInstance();

  fMessage->PrintOneLine(":====== Run Info ======:");
  fMessage->PrintOneLine("Output Root File name: "+RootFile->fileName);
  fMessage->PrintOneLine(":====== Run Info ======:\n");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PlayG4RunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if(nofEvents == 0) return;
  fMessage->PrintOneLine(" Events num of This Run:" + nofEvents);
  // auto analysisManager = G4AnalysisManager::Instance();
  // analysisManager->Write();
  // analysisManager->CloseFile();
  auto RootFile = PlayG4Storage::GetInstance();
  RootFile->WriteData();
  fMessage->PrintOneLine("~~~~~~~~ End of This Run ~~~~~~~");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
