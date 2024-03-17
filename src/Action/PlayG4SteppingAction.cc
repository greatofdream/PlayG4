#include "PlayG4SteppingAction.hh"
#include "PlayG4EventAction.hh"
#include "PlayG4DetectorConstruction.hh"
#include "PlayG4UserEventInformation.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
// analysis
#include "G4AnalysisManager.hh"
#include "G4AntiNeutrinoE.hh"
#include "G4NeutrinoMu.hh"
#include "G4Electron.hh"
#include "G4Proton.hh"
#include "G4Neutron.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PlayG4SteppingAction::PlayG4SteppingAction(PlayG4EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolume(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PlayG4SteppingAction::~PlayG4SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PlayG4SteppingAction::UserSteppingAction(const G4Step* step)
{
  if (!fScoringVolume) { 
    const PlayG4DetectorConstruction* detectorConstruction
      = static_cast<const PlayG4DetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detectorConstruction->GetScoringVolume();   
  }

  // get volume of the current step
  G4LogicalVolume* volume 
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();
      
  // check if we are in scoring volume
  //if (volume != fScoringVolume) return;
  G4Track* track = step->GetTrack();
  auto particle = track->GetDefinition()->GetParticleName();
  auto PrePoint = step->GetPreStepPoint();
  auto PostPoint = step->GetPostStepPoint();
  auto theProcess = PostPoint->GetProcessDefinedStep();
  auto PrePos = PrePoint->GetPosition();
  auto PostPos = PostPoint->GetPosition();
  auto P = PrePoint->GetMomentum();
  PlayG4UserEventInformation *eventInformation
	= (PlayG4UserEventInformation*)G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetUserInformation();
  if(particle !="opticalphoton"){
    // store the step information, default without photon
    eventInformation->StoreStep(step);
    }
/*  if(fEventAction->nFlag && track->GetDefinition() == G4Neutron::Neutron()){
    fEventAction->nEnergy = track->GetKineticEnergy();
    fEventAction->nFlag = false;
  } 
  if (fEventAction->pFlag && track->GetDefinition() == G4Proton::Proton())
  {
    fEventAction->pEnergy = track->GetKineticEnergy();
    fEventAction->proton_x = track->GetPosition().x();
    fEventAction->proton_y = track->GetPosition().y();
    fEventAction->proton_z = track->GetVertexPosition().z();//step->GetPreStepPoint()->GetPosition().z();//track->GetPosition().z();
    fEventAction->pFlag = false;
  }
*/
  //if (track->GetDefinition() != G4Neutron::Neutron())
/*  if (track->GetDefinition() == G4Proton::Proton())
  {
    fEventAction->pAniEnergy += step->GetTotalEnergyDeposit();
  }
*/ 
  // collect energy deposited in this step
  // G4double edepStep = step->GetTotalEnergyDeposit();
  // fEventAction->AddEdep(edepStep);  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

