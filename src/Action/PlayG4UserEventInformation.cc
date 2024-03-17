// For Geant4
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"
// For PlayG4
#include "PlayG4UserEventInformation.hh"
PlayG4UserEventInformation::PlayG4UserEventInformation()
	:fCeren_PhotonCount(0)
{
    // release the space using swap
    vector<Int_t>().swap(SimTrack.ParentTrackId);

}
PlayG4UserEventInformation::~PlayG4UserEventInformation()
{}

void PlayG4UserEventInformation::StoreStep(const G4Step* step)
{
  G4Track* track = step->GetTrack();
  auto particle = track->GetDefinition()->GetParticleName();
  auto PrePoint = step->GetPreStepPoint();
  auto PostPoint = step->GetPostStepPoint();
  auto theProcess = PostPoint->GetProcessDefinedStep();
  auto PrePos = PrePoint->GetPosition();
  auto PostPos = PostPoint->GetPosition();
  auto P = PrePoint->GetMomentum();
  SimStep.TrackId.emplace_back(track->GetTrackID());
  SimStep.StepId.emplace_back(track->GetCurrentStepNumber());
  SimStep.PdgId.emplace_back(track->GetDefinition()->GetPDGEncoding());
  SimStep.nProcessType.emplace_back(theProcess->GetProcessType());
  SimStep.nProcessSubType.emplace_back(theProcess->GetProcessSubType());
  SimStep.StepPoint_Pre_x.emplace_back(PrePos.x());
  SimStep.StepPoint_Pre_y.emplace_back(PrePos.y());
  SimStep.StepPoint_Pre_z.emplace_back(PrePos.z());
  SimStep.StepPoint_Post_x.emplace_back(PostPos.x());
  SimStep.StepPoint_Post_y.emplace_back(PostPos.y());
  SimStep.StepPoint_Post_z.emplace_back(PostPos.z());
  SimStep.StepLength.emplace_back(step->GetStepLength());
  SimStep.dE.emplace_back(step->GetTotalEnergyDeposit());
  SimStep.Px.emplace_back(P.x());
  SimStep.Py.emplace_back(P.y());
  SimStep.Pz.emplace_back(P.z());
  SimStep.E_k.emplace_back(PrePoint->GetKineticEnergy());
  SimStep.T.emplace_back(PrePoint->GetGlobalTime());
  const std::vector<const G4Track*>* secondary = step->GetSecondaryInCurrentStep();
  for(size_t lp=0; lp<(secondary->size()); lp++){
      SimTrackStep.TrackId.emplace_back(track->GetTrackID());
      SimTrackStep.StepId.emplace_back(track->GetCurrentStepNumber());
      // SimTrackStep.ChildTrackId.emplace_back((*secondary)[lp]->GetTrackID());
      auto startPos = (*secondary)[lp]->GetPosition(); // The vertex position is not set until it is handled by step manager, G4SteppingManager::SetInitialStep
      SimTrackStep.StartPoint_x.emplace_back(startPos.x());
      SimTrackStep.StartPoint_y.emplace_back(startPos.y());
      SimTrackStep.StartPoint_z.emplace_back(startPos.z());
      SimTrackStep.T.emplace_back((*secondary)[lp]->GetGlobalTime()); //Time since the event is created 
      SimTrackStep.PdgId.emplace_back((*secondary)[lp]->GetDefinition()->GetPDGEncoding());
  }
}

void PlayG4UserEventInformation::StoreTrack(const G4Track* aTrack)
{
    auto P = aTrack->GetVertexMomentumDirection();
    auto startPos = aTrack->GetVertexPosition();
      SimTrack.TrackId.emplace_back(aTrack->GetTrackID());
      SimTrack.ParentTrackId.emplace_back(aTrack->GetParentID());
      SimTrack.PdgId.emplace_back(aTrack->GetDefinition()->GetPDGEncoding());
  SimTrack.Px.emplace_back(P.x());
  SimTrack.Py.emplace_back(P.y());
  SimTrack.Pz.emplace_back(P.z());
  SimTrack.E_k.emplace_back(aTrack->GetVertexKineticEnergy());
  SimTrack.StartPoint_x.emplace_back(startPos.x());
  SimTrack.StartPoint_y.emplace_back(startPos.y());
  SimTrack.StartPoint_z.emplace_back(startPos.z());
  SimTrack.T.emplace_back(aTrack->GetGlobalTime()); //Time since the event is created 
  SimTrack.Velocity.emplace_back(aTrack->GetVelocity());
      // SimTrack.TrackLength.emplace_back(aTrack->GetTrackLength());
      auto theProcess = aTrack->GetCreatorProcess();
	if(theProcess){
          SimTrack.nProcessType.emplace_back(aTrack->GetCreatorProcess()->GetProcessType());
          SimTrack.nProcessSubType.emplace_back(aTrack->GetCreatorProcess()->GetProcessSubType());
	} else {
          SimTrack.nProcessType.emplace_back(-1);
          SimTrack.nProcessSubType.emplace_back(-1);
	}

}

