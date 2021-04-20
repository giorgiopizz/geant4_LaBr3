#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4Version.hh"
#include "G4VisExecutive.hh"
#if G4VERSION_NUMBER>=930
#include "G4UIExecutive.hh"
#else
#include "G4UIterminal.hh"
#include "G4Uitcsh.hh"
#endif
// queste sotto sono classi mie
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"   //pcelle primarie
#include "QGSP_BERT_HP.hh"              //physics list

#include "EventAction.hh"
#include "RunAction.hh"


int main(int argc, char ** argv)
{
    //the same as TRandom3 di root che ha periodo di 2^19937-1
    CLHEP::HepRandom::setTheEngine(new CLHEP::MTwistEngine());

    //run manager
    G4RunManager * runManager = new G4RunManager();

    //mandatory initialization classes
    // e sono 2
    // classe con metodi virtuali che devono essere implementati nella nostra classe
    G4VUserDetectorConstruction* detector = new DetectorConstruction();
    runManager->SetUserInitialization(detector);

    G4cout << "Setting Physics List" << G4endl;

    G4VUserPhysicsList * physics = new QGSP_BERT_HP(); // quella che simula anche i neutroni
    runManager->SetUserInitialization(physics);

    // mandatory user action classes
    G4VUserPrimaryGeneratorAction * gen_action = new PrimaryGeneratorAction();
    runManager->SetUserAction(gen_action);


    // optional user action classes
    EventAction* event_action = new EventAction();
    RunAction * run_action = new RunAction(event_action);
    runManager->SetUserAction(event_action);
    runManager->SetUserAction(run_action);

    // inizializzazione del G4 Kernel
    runManager->Initialize();



    G4VisManager * visManager = new G4VisExecutive();
    visManager->Initialize();

    // devo prendere puntatore allo user interface manager (è un singleton)
    G4UImanager * UImanager = G4UImanager::GetUIpointer();

    if (argc!=1) //batch mode
    {
        G4String command = "/control/execute ";
        G4String filename = argv[1];
        UImanager->ApplyCommand(command + filename);
    }
    else{
        #if G4VERSION_NUMBER>930
        G4UIExecutive * ui = new G4UIExecutive(argc, argv);
        if (ui->isGUI())
        {
            UImanager->ApplyCommand("/control/execute visQt.mac");
        }
        else{
            UImanager->ApplyCommand("/control/execute vis.mac");
        }
        #else
        G4UIsession * ui = new G4UIterminal();
        #endif
        UImanager ->ApplyCommand("/control/execute ")
        ui->SessionStart();
        delete ui;
    }

    delete runManager;
    return 0;
}
