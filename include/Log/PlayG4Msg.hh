#ifndef PlayG4MSG_HH
#define PlayG4MSG_HH

// For C++
#include <vector>

// For Geant4
#include "G4String.hh"
#include "globals.hh"
#include "PlayG4MsgMessenger.hh"
using namespace std;

class PlayG4MsgMessenger;

enum{
	NoError,
	OnlyPlayG4Error,
	AllError
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class PlayG4Msg
{
	public:
		static PlayG4Msg* GetInstance();
		void AddMessage(G4String str) {fComment.push_back(str);}
		void AddMessage(vector<G4String> str) {fComment = str;}
		void ClearMessage() {vector<G4String>().swap(fComment);}
		G4int GetMessageSize() {return (G4int)fComment.size();}
		vector<G4String> GetMessage() {return fComment;}
		G4String GetMessage(G4int i) {return fComment.at(i);}
		void AddMember(G4String name, G4String mail, G4String institute) {
			fmember.push_back(make_pair(name, make_pair(mail, institute)));
		}

		void PrintMember();
		void PrintOneLine(G4String str);
		void PrintOneLine(vector<G4String> str);
		void PrintDebug(G4String str, G4int verb, G4int thr);
		void PrintDebug(vector<G4String> str, G4int verb, G4int thr);
		void PrintMessage(G4String file_name, G4int line_number, G4bool flag=false);
		#define PrintErr(flag) PrintMessage(__FILE__, __LINE__, flag)

		inline G4int GetVerbosity()			{return fVerbosity;}
		inline G4int GetVerbosePrimary()	{return fVerbosePrimary;}
		inline G4int GetVerboseRun()		{return fVerboseRun;}
		inline G4int GetVerboseEvent()		{return fVerboseEvent;}
		inline G4int GetVerboseTrack()		{return fVerboseTrack;}
		inline G4int GetVerboseStep()		{return fVerboseStep;}
		inline G4int GetVerboseStack()		{return fVerboseStack;}
		inline G4int GetVerboseConst()		{return fVerboseConst;}
		inline G4int GetVerbosePhysics()	{return fVerbosePhysics;}
		inline G4int GetVerboseDigit()		{return fVerboseDigit;}

		inline void SetVerbosity(G4int v)		{fVerbosity = v;}
		inline void SetVerbosePrimary(G4int v)	{fVerbosePrimary = v;}
		inline void SetVerboseRun(G4int v)		{fVerboseRun = v;}
		inline void SetVerboseEvent(G4int v)	{fVerboseEvent = v;}
		inline void SetVerboseTrack(G4int v)	{fVerboseTrack = v;}
		inline void SetVerboseStep(G4int v)		{fVerboseStep = v;}
		inline void SetVerboseStack(G4int v)	{fVerboseStack = v;}
		inline void SetVerboseConst(G4int v)	{fVerboseConst = v;}
		inline void SetVerbosePhysics(G4int v)	{fVerbosePhysics = v;}
		inline void SetVerboseDigit(G4int v)	{fVerboseDigit = v;}


	private :
		PlayG4Msg();
		~PlayG4Msg();
		static PlayG4Msg* instance;
		PlayG4MsgMessenger *fMessenger;

		vector<G4String> fComment;
		vector<pair<G4String, pair<G4String, G4String> > > fmember;
		G4int fVerbosity;
		G4int fVerbosePrimary;
		G4int fVerboseRun;
		G4int fVerboseEvent;
		G4int fVerboseTrack;
		G4int fVerboseStep;
		G4int fVerboseStack;
		G4int fVerboseConst;
		G4int fVerbosePhysics;
		G4int fVerboseDigit;
};
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
