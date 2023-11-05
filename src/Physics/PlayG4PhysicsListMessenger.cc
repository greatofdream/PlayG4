#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIdirectory.hh"
#include "PlayG4PhysicsList.hh"
#include "PlayG4PhysicsListMessenger.hh"

PlayG4PhysicsListMessenger::PlayG4PhysicsListMessenger(PlayG4PhysicsList* pPhys)
:G4UImessenger(),
	fPhysicsList(pPhys),
    fPhysDir(0),fEMListCmd(0){
    fPhysDir = new G4UIdirectory("/PlayG4/Physics/");
	fPhysDir->SetGuidance("physics list commands");

    fEMListCmd = new G4UIcmdWithAString("/PlayG4/Physics/SetPhysicsEM",this);  
	fEMListCmd->SetGuidance("Set Electromagnetic physicsList.");
	fEMListCmd->SetParameterName("fEmName",true);
	fEMListCmd->SetDefaultValue("StandardPhysics");
    fOpListCmd = new G4UIcmdWithAString("/PlayG4/Physics/SetPhysicsOptical",this);  
	fEMListCmd->SetGuidance("Set Optical module physicsList.");
	fEMListCmd->SetParameterName("fOpName",true);
	fEMListCmd->SetDefaultValue("local");
    fDeListCmd = new G4UIcmdWithAString("/PlayG4/Physics/SetPhysicsDecay",this);  
	fEMListCmd->SetGuidance("Set Decay module physicsList.");
	fEMListCmd->SetParameterName("fDeName",true);
	fEMListCmd->SetDefaultValue("on");
}
PlayG4PhysicsListMessenger::~PlayG4PhysicsListMessenger()
{
    delete fPhysDir;
    delete fEMListCmd;
}
void PlayG4PhysicsListMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
	if(command == fEMListCmd) fPhysicsList->SetPhysicsListEM(newValue);
}
