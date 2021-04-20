#include "G4UserRunAction.hh"
#include "TFile.h"
#include "TH1F.h"
#include "RootSaver.hh"

class G4Run;
class EventAction;

class RunAction: G4UserRunAction
{
public:
    //constructor
    RunAction(EventAction* evAct);
    ~RunAction();

    void BeginOfRunAction(const G4Run* );

    void EndOfRunAction(const G4Run *);

    TH1F * hrun;
    TFile * out_root_f;

private:
    RootSaver saver;
    EventAction * eventAction;
};
