#include "G4VSensitiveDetector.hh"
#include "Hit.hh"
#include "G4SystemOfUnits.hh"
#include "DetectorConstruction.hh"
#include "RunAction.hh"
#include "G4Step.hh"


// User defined classes, not G4 ones
#include "TrackParticle.hh"
#include "TrackParentParticle.hh"

class DetectorConstruction;
class RunAction;

class G4Step;
class G4TouchableHistory;
class G4HCofThisEvent;
class SensitiveDetector: public G4VSensitiveDetector
{
public:
    SensitiveDetector(G4string SDname);
    ~SensitiveDetector();

public:
    //Mandatory base class method: it must be overloaded
    G4bool ProcessHits(G4Step * step, G4TouchableHistory * ROhist);

    // optional method of base class G4VSensitiveDetector

    void Initialize(G4HCofThisEvent * HCE);

    //optional

    void EndOfEvent(G4HCofThisEvent * HCE);

private:
    // c++ map to store the hits
    typedef std::map<G4int, Hit *> hitMap_t;

    hitMap_t hitMap;

    HitCollection * hitCollection;

    typedef std::map<G4int, TrackParticle*> trackMap_t;
    trackMap_t trackMap;

    typedef std::map<G4int, TrackParentParticle*> trackParentMap_t;
    trackParentMap_t trackParentMap;

    //map getter

public:
    trackMap_t GetTrackMap() { return trackMap;}

};
