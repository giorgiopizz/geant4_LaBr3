#include "EventAction.hh"
#include "Hit.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4DigiManager.hh"
#include "G4Event.hh"
#include "SensitiveDetector.hh"

EventAction::EventAction()
    :hene(0),
    rootSaver(0),
    hitsCollName("HitCollection"),
    hitsCollID(-1)
{
}


EventAction::~EventAction()
{}

// void EventAction::AssignHisto(TH1F* histo)
// {
//     hene = histo;
// }

SensitiveDetector * GetSensitiveDetector(G4String detname)
{
    G4SDManager * SDMan = G4SDManager::GetSDMpointer();
    SensitiveDetector * sens = static_cast<SensitiveDetector*>(SDman->FindSensitiveDetector(detname));
}

void EventAction::BeginOfEventAction(const G4Event * anEvent)
{
    if (anEvent->GetEventID() %10 ==0) G4cout << "starting event: " << anEvent->GetEventID() << G4endl;
    if (hitsCollID==-1)
    {
        G4SDManager * SDman = G4SDManager::GetSDMpointer();
        hitsCollID = SDman ->GetCollectionID(hitsCollName);
    }
}

void EventAction::EndOfEventAction(const G4Event * anEvent)
{
    //retrieve hits collection
    G4HCofThisEvent * hitsCollection = anEvent->GetHCofThisEvent();
    HitCollection* hits = 0;
    if(hitsCollection)
    {
        hits = static_cast<HitCollection*>(hitsCollection->GetHC(hitsCollID));
    }

    if (hits)
    {
        typedef std::vector<Hit*>::const_iterator hitsVector_it;
        hitsVector_it hit = hits->GetVector()->begin();
        hitsVector_it end = hits->GetVector()->end();
        for( ; hit!=end;++hit){
            layer = (*hit) -> GetLayerNumber();
            edep = (*hit) -> GetEdep();
        }
        // for (auto it: hits){
        //
        // }

        // fill the histogram of the deposited energy
        int check = 0;
        if (hene) check = hene->Fill(edep/keV);

        //retrieve the map corresponding too SensitiveDetector

        G4String sdname = "/myDet/SD";
        SensitiveDetector * sensitive = this->GetSensitiveDetector(sdname);

        trackMap_t trackMap = sensitive->GetTrackMap(); 
    }
}
