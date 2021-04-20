#include "RunAction.hh"
#include "EventAction.hh"
#include "G4Run.hh"

RunAction::RunAction(EventAction * theEventAction)
    : eventAction(theEventAction)
{
    eventAction->SetRootSaver(&saver);
}

void RunAction::BeginOfRunAction(const G4RUn* aRun)
{
    G4cout << "Starting Run: " << aRun->GetRunId() << G4endl;
    G4cout << " Creating Root Tree" << G4endl;

    saver.CreateTree();
    out_root_f = new TFile("histoEnergy.root", "RECREATE");

    hrun = new TH1F("EnDis", "Energy Distribution", 1000, 0, 1000);
    hrun -> GetXaxis()->SetTitle("Deposited Energy (kev)");

    eventAction -> AssignHisto(hrun);
}

void RunAction::EndOfRunAction(const G4RUn* aRun)
{
    G4cout << "Ending Run: " << aRun -> GetRunId() << G4endl;
    G4cout << "Numeber of events: " << aRun->GetNumberOfEvents() << G4endl;
    hrun->Write();
    out_root_f ->Close();

    saver.CloseTree();
}
