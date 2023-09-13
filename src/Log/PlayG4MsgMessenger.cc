// For Geant4
#include "G4Scintillation.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcommand.hh"
#include "G4UIdirectory.hh"

// For PlayG4
#include "PlayG4Msg.hh"
#include "PlayG4MsgMessenger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
PlayG4MsgMessenger::PlayG4MsgMessenger(PlayG4Msg* PlayG4msg)
:PlayG4Error(PlayG4msg)
{
	// Setup a command directory for error message controls with guidance
	fErrorDir = new G4UIdirectory("/PlayG4/ErrorVerbose/");
	
	fPrimaryCmd = new G4UIcmdWithAnInteger("/PlayG4/ErrorVerbose/Primary",this);
	fPrimaryCmd->SetGuidance("Set verbose level of PlayG4PrimaryGeneratorAction");
	fPrimaryCmd->SetGuidance(" 0 : Silent");
	fPrimaryCmd->SetGuidance(" 1 : Debug mode, but currently the same as silent");
	fPrimaryCmd->SetGuidance(" 2 : Debug mode");
	fPrimaryCmd->SetDefaultValue(0);

	fRunCmd = new G4UIcmdWithAnInteger("/PlayG4/ErrorVerbose/Run",this);
	fRunCmd->SetGuidance("Set verbose level of PlayG4RunAction");
	fRunCmd->SetGuidance(" 0 : Silent");
	fRunCmd->SetGuidance(" 1 : Debug mode, but currently the same as silent");
	fRunCmd->SetGuidance(" 2 : Debug mode");
	fRunCmd->SetDefaultValue(0);

	fEventCmd = new G4UIcmdWithAnInteger("/PlayG4/ErrorVerbose/Event",this);
	fEventCmd->SetGuidance("Set verbose level of PlayG4EventAction");
	fEventCmd->SetGuidance(" 0 : Silent");
	fEventCmd->SetGuidance(" 1 : Debug mode, but currently the same as silent");
	fEventCmd->SetGuidance(" 2 : Debug mode");
	fEventCmd->SetDefaultValue(0);
	
	fTrackCmd = new G4UIcmdWithAnInteger("/PlayG4/ErrorVerbose/Track",this);
	fTrackCmd->SetGuidance("Set verbose level of PlayG4TrackingAction");
	fTrackCmd->SetGuidance(" 0 : Silent");
	fTrackCmd->SetGuidance(" 1 : Debug mode, but currently the same as silent");
	fTrackCmd->SetGuidance(" 2 : Debug mode");
	fTrackCmd->SetDefaultValue(0);
	
	fStepCmd = new G4UIcmdWithAnInteger("/PlayG4/ErrorVerbose/Step",this);
	fStepCmd->SetGuidance("Set verbose level of PlayG4SteppingAction");
	fStepCmd->SetGuidance(" 0 : Silent");
	fStepCmd->SetGuidance(" 1 : Debug mode, but currently the same as silent");
	fStepCmd->SetGuidance(" 2 : Debug mode");
	fStepCmd->SetDefaultValue(0);
	
	fStackCmd = new G4UIcmdWithAnInteger("/PlayG4/ErrorVerbose/Stack",this);
	fStackCmd->SetGuidance("Set verbose level of PlayG4StackingAction");
	fStackCmd->SetGuidance(" 0 : Silent");
	fStackCmd->SetGuidance(" 1 : Debug mode, but currently the same as silent");
	fStackCmd->SetGuidance(" 2 : Debug mode");
	fStackCmd->SetDefaultValue(0);
	
	fConstCmd = new G4UIcmdWithAnInteger("/PlayG4/ErrorVerbose/Construct",this);
	fConstCmd->SetGuidance("Set verbose level of PlayG4DetectorConstruction");
	fConstCmd->SetGuidance(" 0 : Silent");
	fConstCmd->SetGuidance(" 1 : Debug mode, but currently the same as silent");
	fConstCmd->SetGuidance(" 2 : Debug mode");
	fConstCmd->SetDefaultValue(0);
	
	fPhysCmd = new G4UIcmdWithAnInteger("/PlayG4/ErrorVerbose/Physics",this);
	fPhysCmd->SetGuidance("Set verbose level of PlayG4PhysicsList");
	fPhysCmd->SetGuidance(" 0 : Silent");
	fPhysCmd->SetGuidance(" 1 : Debug mode, but currently the same as silent");
	fPhysCmd->SetGuidance(" 2 : Debug mode");
	fPhysCmd->SetDefaultValue(0);
	
	fDigitCmd = new G4UIcmdWithAnInteger("/PlayG4/ErrorVerbose/Digitizer",this);
	fDigitCmd->SetGuidance("Set verbose level of PlayG4Digitizer");
	fDigitCmd->SetGuidance(" 0 : Silent");
	fDigitCmd->SetGuidance(" 1 : Debug mode, but currently the same as silent");
	fDigitCmd->SetGuidance(" 2 : Debug mode");
	fDigitCmd->SetDefaultValue(0);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
PlayG4MsgMessenger::~PlayG4MsgMessenger()
{
	delete fErrorDir;

	delete fPrimaryCmd;
	delete fRunCmd;
	delete fEventCmd;
	delete fTrackCmd;
	delete fStepCmd;
	delete fStackCmd;

	delete fConstCmd;
	delete fPhysCmd;
	delete fDigitCmd;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void PlayG4MsgMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 
	if (command==fPrimaryCmd)	PlayG4Error->SetVerbosePrimary(fPrimaryCmd->GetNewIntValue(newValue));
	
	if (command==fRunCmd)   PlayG4Error->SetVerboseRun     (fRunCmd->GetNewIntValue(newValue));
	if (command==fEventCmd) PlayG4Error->SetVerboseEvent   (fEventCmd->GetNewIntValue(newValue));
	if (command==fTrackCmd) PlayG4Error->SetVerboseTrack   (fTrackCmd->GetNewIntValue(newValue));
	if (command==fStepCmd)  PlayG4Error->SetVerboseStep    (fStepCmd->GetNewIntValue(newValue));
	if (command==fStackCmd) PlayG4Error->SetVerboseStack   (fStackCmd->GetNewIntValue(newValue));
	if (command==fConstCmd) PlayG4Error->SetVerboseConst   (fConstCmd->GetNewIntValue(newValue));
	if (command==fPhysCmd)  PlayG4Error->SetVerbosePhysics (fPhysCmd->GetNewIntValue(newValue));
	if (command==fDigitCmd) PlayG4Error->SetVerboseDigit   (fDigitCmd->GetNewIntValue(newValue));
}
