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
/// \file PlayG4EventAction.cc
/// \brief Implementation of the PlayG4EventAction class

#include "PlayG4EventAction.hh"
#include "PlayG4UserEventInformation.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
// analysis
#include "g4root.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PlayG4EventAction::PlayG4EventAction()
: G4UserEventAction()
{
	fMessage->PrintOneLine("Constructor < Event Action >");
	StartTime = clock();
	// Following: initilize other settings
  nEnergy = 0.;
  nFlag = true;
  pEnergy = 0.;
  pFlag = true;
  pAniEnergy = 0.;
  proton_x = 0.;
  proton_y = 0.;
  proton_z = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PlayG4EventAction::~PlayG4EventAction()
{
	fMessage->PrintOneLine("Destructor < Event Action >");
	// Following: delete other settings

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PlayG4EventAction::BeginOfEventAction(const G4Event* event)
{
  nEnergy = 0.;
  nFlag = true;
  pEnergy = 0.;
  pFlag = true;
  pAniEnergy = 0.;
  proton_x = 0.;
  proton_y = 0.;
  proton_z = 0.;
	auto evID = event->GetEventID();
	EndTime = clock();

	if (evID==0) {
		fMessage->PrintOneLine("==============================================");
		fMessage->PrintOneLine("=====                                         ");
		fMessage->PrintOneLine("==                                            ");
		fMessage->PrintOneLine("               Start Simulating               ");
		fMessage->PrintOneLine("                                            ==");
		fMessage->PrintOneLine("                                         =====");
		fMessage->PrintOneLine("==============================================");
	}
	auto RootFile = PlayG4Storage::GetInstance();
	
	G4EventManager::GetEventManager()->SetUserInformation(new PlayG4UserEventInformation);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PlayG4EventAction::EndOfEventAction(const G4Event* event)
{
	if ( event->IsAborted() ) return;
	auto evtID = event->GetEventID();
	if (evtID%100==0){
		 G4cerr<<" Current Event No. is "<<evtID<<" ("<<(double)(EndTime-StartTime) / CLOCKS_PER_SEC<<" sec)"<< G4endl;
	}
	SaveTruthInfo(event);
	PlayG4UserEventInformation* eventInformation = (PlayG4UserEventInformation*)event->GetUserInformation();
	PlayG4Storage::GetInstance()->FillMCTrack(eventInformation->SimTrack);
	PlayG4Storage::GetInstance()->FillMCStep(eventInformation->SimStep);
	// auto Parameters = PlayG4Parameters::GetME();

	// if(RootFile->GetSecondaryTreeFlag()){
	// 	G4cout << "\n| Event " << evID   << G4endl;
	// 	G4cout << "--------------------\n" << G4endl;
	// }

	
  // analysisManager
  // auto analysisManager = G4AnalysisManager::Instance();
  // analysisManager->FillNtupleDColumn(0, nEnergy);
  // analysisManager->FillNtupleDColumn(1, pEnergy);
  // analysisManager->FillNtupleDColumn(2, pAniEnergy);
  // analysisManager->FillNtupleDColumn(3, proton_x);
  // analysisManager->FillNtupleDColumn(4, proton_y);
  // analysisManager->FillNtupleDColumn(5, proton_z);
  // analysisManager->AddNtupleRow();
  // get number of stored trajectories
//   G4TrajectoryContainer* trajectoryContainer = event->GetTrajectoryContainer();
//   G4int n_trajectories = 0;
//   if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();

  // periodic printing

//   if ( eventID < 100 || eventID % 100 == 0) {
//     G4cout << ">>> Event: " << eventID  << G4endl;
//     if ( trajectoryContainer ) {
//       G4cout << "    " << n_trajectories
//              << " trajectories stored in this event." << G4endl;
//     }
//     G4VHitsCollection* hc = event->GetHCofThisEvent()->GetHC(0);
//     G4cout << "    "  
//            << hc->GetSize() << " hits stored in this event" << G4endl;
//   }
  	// fTruthList.clear();
	// fTrackContainer.clear();
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void PlayG4EventAction::SaveTruthInfo(const G4Event* event)
{
	auto evtID = event->GetEventID();
	G4int NumberOfVertex = event->GetNumberOfPrimaryVertex();
	G4int NumberOfParticles = 0;
	for(Int_t i=0; i<NumberOfVertex; i++)
		NumberOfParticles += event->GetPrimaryVertex(i)->GetNumberOfParticle();

	// std::vector<TimeStamp>::iterator iter = globalTimeList.begin();

	for(Int_t i=0; i<NumberOfVertex; i++)
	{
		PlayG4SimTruthTree_t vertexTruth;
		G4PrimaryVertex* gpVertex = event->GetPrimaryVertex(i);
		vertexTruth.RunId = 0;
		vertexTruth.EventId = evtID;
		vertexTruth.VertexId = i;

		vertexTruth.nParticle = gpVertex->GetNumberOfParticle();
		vertexTruth.x = gpVertex->GetX0()/CLHEP::mm;	
		vertexTruth.y = gpVertex->GetY0()/CLHEP::mm;
		vertexTruth.z = gpVertex->GetZ0()/CLHEP::mm;
                vertexTruth.Sec = gpVertex->GetT0()/CLHEP::second;//+iter->GetSec();
		vertexTruth.NanoSec = gpVertex->GetT0()/CLHEP::ns;//+iter->GetNanoSec();
	
		// vertexTruth.dEList.resize(fDetConstruction->ndE);

		for(Int_t j=0; j<event->GetPrimaryVertex(i)->GetNumberOfParticle(); j++)
		{
				
		
			G4PrimaryParticle* gpParticle = gpVertex->GetPrimary(j);
			G4int nTrack = gpParticle->GetTrackID();
			// TrackMap[nTrack] = i;
			
			//G4cout<<gpParticle->GetParticleDefinition()->GetParticleName()<<"\t"<<gpVertex->GetT0()<<G4endl;

			PlayG4PrimaryParticle_t jpParticle;
			jpParticle.TrackId = nTrack;
			jpParticle.PdgId = gpParticle->GetPDGcode();
			jpParticle.px = gpParticle->GetPx()/CLHEP::MeV;
			jpParticle.py = gpParticle->GetPy()/CLHEP::MeV;
			jpParticle.pz = gpParticle->GetPz()/CLHEP::MeV;
			jpParticle.Ek = gpParticle->GetKineticEnergy()/CLHEP::MeV;

			// iter++;

			vertexTruth.EkMerged += jpParticle.Ek;
			//G4cout<<jpParticle.Ek<<"\t";
			
			// for(size_t k=0; k<vertexTruth.dEList.size(); k++)
			// {
			// 	if(k<fdEList[nTrack].size())
			// 		vertexTruth.dEList[k] += fdEList[nTrack][k];
			// }

			vertexTruth.PrimaryParticleList.emplace_back(jpParticle);
			// for(auto iter = fTrackContainer.begin(); iter != fTrackContainer.end(); )
			// {
			// 	if(iter->second.nPrimaryId==nTrack)
			// 	{
			// 		vertexTruth.trackList.emplace_back(iter->second);
			// 		iter = fTrackContainer.erase(iter);
			// 	}
			// 	else 
			// 	  ++iter;
			// }

		}

		fTruthList[i] = vertexTruth;
		PlayG4Storage::GetInstance()->FillMCTruth(vertexTruth);
	}
}
