#include "DetectorConstruction.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#inlcude "G4PVPlacement.hh"
#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "SensitiveDetector.hh"
#include "G4SDManager.hh"

DetectorConstruction::DetectorConstruction()
    : vacuum(0)
    , LaBr3_Mat(0)
    , logicWorld(0)
    , halfWorldLength(0.5*km)
{
//---------------Material definition ---------------
DefineMaterials();
//--------------Size of the principal geometrical components-----------
ComputeParameters();

}

DetectorConstruction::~DetectorConstruction()
{
    delete LaBr3_Mat;
}

void DetectorConstruction::DefineMaterials()
{
    // get materials from list database
    G4NistManager * man = G4NistManager::Instance();
    man->SetVerbose(10);
    //define NIST material
    // 1- Lantanio (L)
    // retrieving lantanum from G4Nist database
    G4int LantanumZ = 57;
    G4Element* L = man->FindOrBuildElement(LantanumZ);
    if(L) G4cout << "Lantanum correcly retrieved" << G4endl;

    //2- Bromide (Br)
    G4int BromideZ = 35;
    G4Element * Br = man->FindOrBuildElement(BromideZ);
    if(Br) G4cout << "Bromide correcly retrieved" << G4endl;

    G4cout << "Building LaBr3 material" <<G4endl;

    G4double LaBr3_density = 5.08*g/cm3;
    G4int LaBr3_comp_Atoms = 2;
    G4int n_La_atoms = 1;
    G4Int n_Br_atoms = 3;
    LaBr3_Mat = new G4Material("LaBr3Mat", LaBr3_density, LaBr3_comp_Atoms);
    LaBr3_Mat->AddElement(L, n_La_atoms);
    LaBr3_Mat->AddElement(Br, n_Br_atoms);

    if(!LaBr3_Mat) G4cout << "Problems making LaBr3 material" << G4endl;

    vacuum = man->FindOrBuildMaterial("G4_Galactic");

}

void DetectorConstruction::ComputerParameters()
{
    halfWorldLength = 500*m;
    halfLaBr3Det_x = 3.81*cm; //radius
    halfLaBr3Det_y = 1.5*2.540*cm;
    haldLaBr3Det_z = 7.762*cm;
}


G4VPhysicalVolume * DetectorConstruction::Construct()
{
    G4GeometryManager::GetInstance()->SetWorldMaximumExtent(2*halfWorldLength);

    G4cout << "Computed tolerance = " << G4GeometryTolerance::GetInstance()->GetTolerance/mm << " mm " <<G4endl;

    //define the box World

    G4Box * solidWorld = new G4Box ("world",
                                    halfWorldLength,   //dim in x
                                    halfWorldLength,    //dim in y
                                    halfWorldLength);    //dim in z
    logicWorld = new G4LogicalVolume(soldiWorld, //corresponding G4Solid
                                    vacuum,     //corresponding G4Material
                                    "World",    //nome
                                    0,          //field manager
                                    0,          //sensitive detector
                                    0,          //user limits
                                    0);          //optimise
    //must place the physical world unrotated at 0, 0, 0
    G4VPhysicalVolume * phisiWorld = new G4PVPlacement(0,   //no rot.
                                                        G4ThreeVector() //place at 0,0,0
                                                        logicWorld,     //its logical volume
                                                        "World",        //its name
                                                        0,              //its mother logical volume (world è l'unico che può avere come madre 0!)
                                                        false,          // no boolean operations
                                                        0);             //copy number
    G4Colour
            green(0.0,1.0,0.0),
            blue(0.0,0.0,1.0),
            brown(0.4,0.4,0.1),
            white(1.0,1.0,1.0);
    logicWorld ->SetVisAttributes(new G4VisAttributes(white));
    logicWorld->SetVisAttributes(G4VisAttributes::Invisible);

    // Call the method to consturct all the rest
    Construct_LaBr3Detector();
    return physiWorld;
}

G4VPhysicalVolume * DetectorConstruction::Construct_LaBr3Detector()
{
    G4Colour
            green(0.0,1.0,0.0),
            blue(0.0,0.0,1.0),
            brown(0.4,0.4,0.1),
            white(1.0,1.0,1.0);
    G4Tubs* solidLaBr3Det = new G4Tubs("solid_LaBr3",
                                        0,
                                        halfLaBr3Det_x,
                                        0.5*halfLaBr3Det_z,
                                        0*deg,
                                        360*deg);
    logicLaBr3 = new G4LogicalVolume(solidLaBr3Det, //its solid
                                    LaBr3_Mat,      //its material
                                    "logic_LaBr3");
    G4int LaBr3_copynum =1;
    physiLaBr3 = new G4PVPlacement(0,    // no rot
                                    G4ThreeVector(), //at 0,0,0
                                    logicLaBr3,     //its logical volume
                                    "physical_LaBr3",   //its name
                                    logicWorld,     //its mother logical world
                                    false,
                                    LaBr3_copynum); //copynumber
    logicLaBr3->SetVisAttributes(new G4VisAttributes(green));

    //Define the LaBr3 as Sensitive detector
    static SensitiveDetector * sensitive = 0;
    if( !sensitive )
    {
        G4cout << " Declaring Sensitive Detector " << G4endl;
        sensitive = new SensitiveDetector("/myDet/SD"); // lo metto nella directory del bash
        // we register the SD with the mangare
        G4SDManager::GetSDMPointer()->AddNewDetector(sensitive);
        G4cout << "Sensitive Detector added " << G4endl;
    }
    logicLaBr3->SetSensitiveDetector(sensitive);

    return physiLaBr3;
}
