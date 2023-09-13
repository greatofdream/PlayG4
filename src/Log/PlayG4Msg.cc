// For C++
#include <iostream>
#include <sstream>
#include <iomanip>

// For Geant4
#include "G4UImanager.hh"

#include "PlayG4Msg.hh"

using namespace std;
PlayG4Msg* PlayG4Msg::instance = NULL;

PlayG4Msg* PlayG4Msg::GetInstance()
{
	if(!instance) instance = new PlayG4Msg();
	return instance;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
PlayG4Msg::PlayG4Msg()
:fVerbosity(OnlyPlayG4Error),fVerbosePrimary(0),
  fVerboseRun(0),
  fVerboseEvent(0),
  fVerboseTrack(0),
  fVerboseStep(0),
  fVerboseStack(0),
	fVerboseConst(0),
	fVerbosePhysics(0),
	fVerboseDigit(0)
{
	fMessenger = new PlayG4MsgMessenger(this);

	fComment.clear();	
	
	AddMember("greatofdream", "greatofdream@gmail.com", "NULL");
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
PlayG4Msg::~PlayG4Msg()
{}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void PlayG4Msg::PrintMessage(G4String file_name, G4int line_number, G4bool flag)
{
	G4String type = "";
	if (flag) {
		type = "PlayG4 ERROR";
	} else {
		type = "PlayG4 WARNING";
	}
	
	G4int size = GetMessageSize();

	G4cerr<<G4endl;
	if (flag) G4cerr<<"\033[1;31m";
	G4cerr<<"============= "<<type<<" !! ============="<<G4endl;
	G4cerr<<"\033[m"<<"== "<<G4endl;
	G4cerr<<"== File : "<<file_name<<G4endl;
	G4cerr<<"== Line : "<<line_number<<G4endl;
	G4cerr<<"== "<<G4endl;
	G4cerr<<"== Comments "<<G4endl;
	for (auto i=0;i<size;i++) {
		G4cerr<<"== "<<GetMessage(i)<<G4endl;
	}
	G4cerr<<"== "<<G4endl;
	if (flag) G4cerr<<"\033[1;31m";
	G4cerr<<"============= "<<type<<" !! ============="<<G4endl;
	G4cerr<<"\033[m"<<G4endl;
	
	ClearMessage();
	if (flag) PrintMember();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void PlayG4Msg::PrintOneLine(G4String str)
{	
	G4cerr <<" ### "<<"\033[34m"<<"PlayG4"<<"\033[m"<<" ###--> " << str << G4endl;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void PlayG4Msg::PrintOneLine(vector<G4String> str)
{
	G4int size = str.size();
	for (auto i=0;i<size;i++) {
		G4cerr <<" ### "<<"\033[34m"<<"PlayG4"<<"\033[m"<<" ###--> "<<str.at(i)<<G4endl;
	}
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void PlayG4Msg::PrintDebug(G4String str, G4int verb, G4int thr)
{
	if (verb > thr) {
		G4cerr <<" ### "<<"\033[31m"<<"DEBUG"<<"\033[m"<<" ###--> " << str << G4endl;
	}
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void PlayG4Msg::PrintDebug(vector<G4String> str, G4int verb, G4int thr)
{
	if (verb > thr) {
		G4int size = str.size();
		for (auto i=0;i<size;i++) {
			G4cerr <<" ### "<<"\033[31m"<<"DEBUG"<<"\033[m"<<" ###--> " << str.at(i) << G4endl;
		}
	}
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void PlayG4Msg::PrintMember()
{
	G4cerr<<"\033[1;31m"<<"....oooOO0OOooo........oooOO0OOooo... PlayG4 Group Member ....oooOO0OOooo........oooOO0OOooo... "<<G4endl;
	G4cerr<<" If you cannot solve the problem yourself, please contact PlayG4 Group. "<<G4endl<<G4endl;
	for (auto itr=fmember.begin(); itr!=fmember.end(); ++itr) {
		G4cerr<<setw(20)<<itr->first<<" ("<<setw(20)<<itr->second.second<<") : "<<itr->second.first<<G4endl;
	}
	G4cerr<<G4endl<<"....oooOO0OOooo........oooOO0OOooo... PlayG4 Group Member ....oooOO0OOooo........oooOO0OOooo... "<<"\033[m"<<G4endl<<G4endl;
	exit(1);
}
