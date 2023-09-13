#ifndef PlayG4MSGMESSENGER_HH
#define PlayG4MSGMESSENGER_HH 1

// For Geant4
#include "G4UImessenger.hh"
#include "globals.hh"

class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithAnInteger;
class G4UIcommand;
class G4UIcmdWithABool;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADouble;
class G4UIcmdWithAString;

class PlayG4Msg;


class PlayG4MsgMessenger: public G4UImessenger
{
public:
  PlayG4MsgMessenger(PlayG4Msg*);
  ~PlayG4MsgMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
    
private:
	PlayG4Msg* PlayG4Error;
	
	G4UIdirectory*			fErrorDir;
	
	G4UIcmdWithAnInteger*	fPrimaryCmd;
	G4UIcmdWithAnInteger*	fRunCmd;
	G4UIcmdWithAnInteger*	fEventCmd;
	G4UIcmdWithAnInteger*	fTrackCmd;
	G4UIcmdWithAnInteger*	fStepCmd;
	G4UIcmdWithAnInteger*	fStackCmd;

	G4UIcmdWithAnInteger*   fConstCmd;
	
	G4UIcmdWithAnInteger*   fPhysCmd;
	G4UIcmdWithAnInteger*   fDigitCmd;
};

#endif

