#include "SensitiveDetector.hh"
#include "G4Step.hh"
#include "Randomize.hh"
#include "G4HCofThisEvent.hh"

#include "G4HCtable.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4TouchableHistory.hh"
#include "TrackParticle.hh"
#include "TrackParentParticle.hh"

SensitiveDetector::SensitiveDetector(G4string SDname):
                    G4VSensitiveDetector(SDname)
{
    G4cout << " Creating SD with name " << SDname << G4endl;
    G4string myCollectionName = "HitCollection";

    // collectionName is a protected data member of base class G4VSensitiveDetector
    collectionName.insert(myCollectionName);
}

SensitiveDetector::~SensitiveDetector()
{}

G4bool SensitiveDetector::ProcessHits(G4Step * step, G4TouchableHistory * ROhist)
{
    G4TouchableHandle touchable = step -> GetPreStepPoint() -> GetTouchableHandle();
    G4int copyNo = touchable -> GetVolume(0) -> GetCopyNo(); //layer più profondo quindi voglio il figlio
    G4int index = copyNo;

    TrackParticle * Tparticle = new TrackParticle();
    G4Track *  thistrack = step->GetTrack();

    // ci sono delle info ch evoglio tirar fuori della particella dalla traccia

    G4double trackenergy = thistrack -> GetDynamicParticle() -> GetKineticEnergy();

    // define the key for the trackMat_t

    G4int thistackID = thistrack -> GetTrackID(); // numero univoco della traccia

    G4string trackname = thistrack -> GetDefinition() -> GetParticleName();

    G4int parentID = thistrack -> GetParentiD();

    G4cout << " Track " << thistrackID << " Energy " << G4BestUnit(trackenergy, "Energy")
    << " Type " << trackname << " mum " << parentID << G4endl;

    G4int trackPDGencod = thistrack -> GetDefinition() -> GetPDGEncoding(); // elettroni codice +11, positroni -11 ecc...
    G4double zstartpos = (thistrack->GetVertexPosition() ).getZ();

    G4double starttime = thistrack->GetGlobalTime();

    Tparticle->SetMothPart_ID(parentID);    //l'ho scritto io

    G4double edep = step -> GetTotalEnergyDeposit();
    Tparticle->SetPart_Type(trackPDGencod);

    Tparticle -> SetPart_name(trackname);

    Tparticle -> SetZStart_Pos (zstartpos);

    Tparticle -> SetStart_Time(starttime);

    // HITS PART

    hitMap_t::iterator it = hitMap.find(index);
    Hit * aHit = 0;
    if (it != hitMap.end() ) // se iteratore non è arrivato in fondo alla mappa
    {
        // some hit for this layer already exist
        // ho già riempito la hitMap con delle hits
        aHit = it -> second; // richiamiamo la hit che abbiamo salvato nella mappa (è memorizzata nella seconda entrata della mappa)
    }
    else
    {
        // no hit previously saved
        aHit = new Hit(index);
        hitMap.insert( std::make_pair(index, aHit)); //inserisco nella mappa una coppia (indice, hit)
        HitCollection -> insert(aHit);
    }
    aHit -> AddEdep (edep);

    // altro codice che riguarda la track map
}


void SensitiveDetector::Initialize(G4HCofThisEvent * HCE)
{
    hitCollection = new HitCollection(GetName(), collectionName[0]); //nel nostro caso si chiama "HitCollection"
    static G4int HCID = -1; //inizializzo id della coll. a -1
    if (HCID < 0 ) HCID = GetCollectioID(0); //metto getcollection id a 0 (stesso di due riche sopra)
    HCE -> AddHitsCollection (HCID, hitCollection);

    hitMap.clear();
    trackMap.clear();

}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent * HCE)
{
    hitCollection -> PrintAllHits();
}
