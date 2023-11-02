#include "PlayG4Storage.hh"
// For C++ 
#include <iostream>
#include <vector>

// For Geant4
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

// For ROOT 
#include "TBranch.h"
#include "TFile.h"
#include "TStreamerInfo.h"
#include "TTree.h"
#include "TROOT.h"
#include "TSystem.h"



PlayG4Storage* PlayG4Storage::instance = 0;

PlayG4Storage::PlayG4Storage(){

}

PlayG4Storage::~PlayG4Storage(){
    //fPlayG4File->Close();
}
PlayG4Storage* PlayG4Storage::GetInstance()
{
	if (instance == 0) instance = new PlayG4Storage();
	return instance;
}

void PlayG4Storage::CreateFile(G4String name)
{
    fPlayG4File = new TFile(name, "Recreate", "Simulation File");
    std::cout<<"PlayG4File Address: "<<fPlayG4File<<std::endl;
    truthTree = new TTree("SimTruth", "MonteCarloTruth");
    // trackTree = new TTree("SimTrack", "TrackInfo");
    
	
    CreateBranchesForTruthRoot();
	// CreateBranchesForSensorRoot();

}
void PlayG4Storage::CreateBranchesForTruthRoot(){
    truthTree->Branch("RunID", &SimTruth.RunId);
    truthTree->Branch("EventID", &SimTruth.EventId);
    truthTree->Branch("VertexId", &SimTruth.VertexId);
    truthTree->Branch("nParticle", &SimTruth.nParticle);
    truthTree->Branch("x", &SimTruth.x);
	truthTree->Branch("y", &SimTruth.y);
	truthTree->Branch("z", &SimTruth.z);
	truthTree->Branch("Sec", &SimTruth.Sec);
	truthTree->Branch("NanoSec", &SimTruth.NanoSec);
    truthTree->Branch("EkMerged", &SimTruth.EkMerged);
    truthTree->Branch("PrimaryParticleList", &SimTruth.PrimaryParticleList);
    truthTree->Branch("VertexRadA", &SimTruth.VertexRadA);
    truthTree->Branch("testarray", &testarray);

    // TrackTree->Branch("trackList", &SimTrack);
}
void PlayG4Storage::CreateBranchesForSensorRoot(){

}
void PlayG4Storage::FillMCTruth(const PlayG4SimTruthTree_t &truth)
{
    SimTruth = truth;
    truthTree->Fill();
}
void PlayG4Storage::WriteData()
{
    fPlayG4File->cd();
    truthTree->Write("", TObject::kOverwrite); 
    int entries = truthTree->GetEntries();
    std::cout<<"Entries:"<<entries<<" file:"<<truthTree->GetCurrentFile()<<std::endl;
    std::cout<<"PrimaryParticleList"<<SimTruth.PrimaryParticleList[0].PdgId<<std::endl;

	// trackTree->Write("", TObject::kOverwrite);
    //truthTree->AutoSave();
    //fPlayG4File->Write();
    fPlayG4File->Close();
}