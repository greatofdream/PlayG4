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
    trackTree = new TTree("SimTrack", "MonteCarloTrack");
    stepTree = new TTree("SimStep", "MonteCarloStep");
    trackStepTree = new TTree("SimTrackStep", "StepTrackRelation");
	
    CreateBranchesForTruthRoot();
	// CreateBranchesForSensorRoot();

}
void PlayG4Storage::CreateBranchesForTruthRoot(){
    // truth tree
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
    // track tree
    trackTree->Branch("ParentTrackId", &SimTrack.ParentTrackId);
    trackTree->Branch("TrackId", &SimTrack.TrackId);
    trackTree->Branch("StepId", &SimTrack.StepId);
    trackTree->Branch("PdgId", &SimTrack.PdgId);
    trackTree->Branch("TrackLength", &SimTrack.TrackLength);
    trackTree->Branch("ProcessType", &SimTrack.nProcessType);
    trackTree->Branch("ProcessSubType", &SimTrack.nProcessSubType);
    trackTree->Branch("StartPoint_x", &SimTrack.StartPoint_x);
    trackTree->Branch("StartPoint_y", &SimTrack.StartPoint_y);
    trackTree->Branch("StartPoint_z", &SimTrack.StartPoint_z);
    trackTree->Branch("T", &SimTrack.T);
    trackTree->Branch("Velocity", &SimTrack.Velocity);
    trackTree->Branch("Px", &SimTrack.Px);
    trackTree->Branch("Py", &SimTrack.Py);
    trackTree->Branch("Pz", &SimTrack.Pz);
    trackTree->Branch("E_k", &SimTrack.E_k);
    // steps tree
    stepTree->Branch("TrackId", &SimStep.TrackId);
    stepTree->Branch("StepId", &SimStep.StepId);
    stepTree->Branch("PdgId", &SimStep.PdgId);
    stepTree->Branch("ProcessType", &SimStep.nProcessType);
    stepTree->Branch("ProcessSubType", &SimStep.nProcessSubType);
    stepTree->Branch("StepPoint_Pre_x", &SimStep.StepPoint_Pre_x);
    stepTree->Branch("StepPoint_Pre_y", &SimStep.StepPoint_Pre_y);
    stepTree->Branch("StepPoint_Pre_z", &SimStep.StepPoint_Pre_z);
    stepTree->Branch("StepPoint_Post_x", &SimStep.StepPoint_Post_x);
    stepTree->Branch("StepPoint_Post_y", &SimStep.StepPoint_Post_y);
    stepTree->Branch("StepPoint_Post_z", &SimStep.StepPoint_Post_z);
    stepTree->Branch("StepLength", &SimStep.StepLength);
    stepTree->Branch("dE", &SimStep.dE);
    stepTree->Branch("Px", &SimStep.Px);
    stepTree->Branch("Py", &SimStep.Py);
    stepTree->Branch("Pz", &SimStep.Pz);
    stepTree->Branch("E_k", &SimStep.E_k);
    stepTree->Branch("T", &SimStep.T);
    // step->track relation
    trackStepTree->Branch("TrackId", &SimTrackStep.TrackId);
    trackStepTree->Branch("StepId", &SimTrackStep.StepId);
    trackStepTree->Branch("StartPoint_x", &SimTrackStep.StartPoint_x);
    trackStepTree->Branch("StartPoint_y", &SimTrackStep.StartPoint_y);
    trackStepTree->Branch("StartPoint_z", &SimTrackStep.StartPoint_z);
    trackStepTree->Branch("T", &SimTrackStep.T);
    trackStepTree->Branch("PdgId", &SimTrackStep.PdgId);
    // trackStepTree->Branch("ChildTrackId", &SimTrackStep.ChildTrackId);
}
void PlayG4Storage::CreateBranchesForSensorRoot(){

}
void PlayG4Storage::FillMCTruth(const PlayG4SimTruthTree_t &truth)
{    // invoked after the truth data ready
    SimTruth = truth;
    truthTree->Fill();
}
void PlayG4Storage::FillMCTrack(const PlayG4SimTrack_t &track)
{
    SimTrack = track;
    trackTree->Fill();
    //std::cout<<"Track size"<<SimTrack.ParentTrackId.size()<<std::endl;
}
void PlayG4Storage::FillMCStep(const PlayG4SimStep_t &steps)
{
    SimStep = steps;
    stepTree->Fill();
}
void PlayG4Storage::FillMCTrackStep(const PlayG4SimTrackStep_t &trackSteps)
{
    SimTrackStep = trackSteps;
    trackStepTree->Fill();
}
void PlayG4Storage::WriteData()
{
    fPlayG4File->cd();
    truthTree->Write("", TObject::kOverwrite);
    trackTree->Write("", TObject::kOverwrite);
    stepTree->Write("", TObject::kOverwrite);
    trackStepTree->Write("", TObject::kOverwrite);
    // int entries = truthTree->GetEntries();
    // std::cout<<"Entries:"<<entries<<" file:"<<truthTree->GetCurrentFile()<<std::endl;

    //truthTree->AutoSave();
    //fPlayG4File->Write();
    fPlayG4File->Close();
}
