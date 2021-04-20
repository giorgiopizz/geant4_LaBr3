#include "G4UserEventAction.hh"
#include "G4String.hh"
#include "Hit.hh"
#include "SensitiveDetector.hh"
#include "TrackParticle.hh"
#include "RootSaver.hh"
#include "TrackParentParticle.hh"
#include "G4SystemOfUnits.hh"

#include "TH1F.h"
#include "TFile.h"

class EventAction: public G4UserEventAction
{
public:
    EventAction();
    ~EventAction();

    void BeginOfEventAction(const G4Event * anEvent);
    void EndOfEventAction(const G4Event * anEvent);

    inline void SetRootSaver( RootSaver * saver) {rootSaver = saver;}


    G4double edep;
    G4int layer;

    TH1F * hene;

    inline void AssignHisto( TH1F* histo=0) {hene = histo;}

    SensitiveDetector * GetSensitiveDetector(G4String detname);
private:
    RootSaver * rootSaver;
    G4String hitsCollName;
    G4int hitsCollID;
    typedef std::map<G4int, TrackParticle*> trackMap_t;

};
