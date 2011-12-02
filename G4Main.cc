//
// $Id: teste.cc,v 0.1 2010/11/30 22:31:00  $
// GEANT4 tag $Name: geant4-09-03-patch-02 $
//
// 
// --------------------------------------------------------------
//      GEANT 4 - teste.cc
// --------------------------------------------------------------


#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "SrBDetectorConstruction.hh"
//#include "SrBPhysicsList.hh"
#include "ExN02PhysicsList.hh"
#include "SrBPrimaryGeneratorAction.hh"

#include "ExN07RunAction.hh"
//#include "ExN07SteppingVerbose.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

//for sleep(seconds) function
//#include <pthread.h>

//#include "SrBRandom.hh"

int main(G4int argc, char** argv) {

	// G4RunManager has a pointer to G4VHitsCollection. Esse est‡ associando com Sensitive Detectors
	// E Singleton e pode ser obtido por getRunManager()
	G4RunManager* runManager = new G4RunManager;
	//runManager->SetUserAction(new BeamTestEventAction);

	// set mandatory user initialization classes
	// G4VUserDetectorConstruction* detector = new SrBDetectorConstruction;
	SrBDetectorConstruction* detector = new SrBDetectorConstruction;
	detector->setEspessura(1.0*mm);
	runManager->SetUserInitialization(detector);
	G4VUserPhysicsList* physics = new ExN02PhysicsList;
	runManager->SetUserInitialization(physics);

/***** Instantiation and initialization of the Visualization Manager *****/
#ifdef G4VIS_USE
  // Visualization manager construction
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
#endif

	// set mandatory user action class
	G4VUserPrimaryGeneratorAction* gen_action = new SrBPrimaryGeneratorAction;
	runManager->SetUserAction(gen_action);

	// Adicionando acao de usuario
	G4UserRunAction* run_action = new ExN07RunAction;
	runManager->SetUserAction(run_action);

	// Initialize G4 kernel
	runManager->Initialize();


//  // I think this is used with macros
//  G4UIExecutive* session = new G4UIExecutive(argc, argv);


/******* Get the pointer to the UI manager and set verbosities *******/
/*
	G4UImanager* UI = G4UImanager::GetUIpointer();
	UI->ApplyCommand("/vis/open OGLIX");
	//UI->ApplyCommand("/vis/drawView");
	UI->ApplyCommand("/vis/drawVolume");
	//UI->ApplyCommand("/vis/scene/add/volume");
	UI->ApplyCommand("/vis/scene/add/trajectories");
	//UI->ApplyCommand("/vis/scene/add/trajectories smooth");
	UI->ApplyCommand("/vis/scene/add/hits");
	//UI->ApplyCommand("/vis/viewer/set/hiddenEdge 0");
	UI->ApplyCommand("/vis/viewer/set/viewpointThetaPhi 50 20");
	//UI->ApplyCommand("/vis/scene/endOfEventAction accumulate 20");
	//UI->ApplyCommand("/vis/scene/add/axes 0 0 0 5 m"); // x, y, z, comprimento, unidade
	UI->ApplyCommand("/vis/viewer/zoom 1.3");
	//UI->ApplyCommand("/run/verbose 1");
	//UI->ApplyCommand("/event/verbose 1");
	//UI->ApplyCommand("/tracking/verbose 1");
	//UI->ApplyCommand("/vis/viewer/list");
	//UI->ApplyCommand("/vis/drawView");
	//UI->ApplyCommand("/vis/scene/add/trajectories smooth");
	//UI->ApplyCommand("/vis/scene/add/hits");
	//UI->ApplyCommand("/tracking/storeTrajectory");
	//UI->ApplyCommand("/vis/viewer/set/style surface"); //wireframe or surface
	//UI->ApplyCommand("/tracking/storeTrajectory 20");
	//UI->ApplyCommand("/vis/scene/endOfEventAction accumulate 30");
*/

	G4int numberOfEvent = 300;

	for (int i = 10; i > 0; --i){
	//	  detector->setEspessura( (G4double)(10.0*mm / i) );
	//	  runManager->GeometryHasBeenModified();
	  runManager->BeamOn(numberOfEvent);
	}

	//  session->SessionStart();
	//  delete session;

#ifdef G4VIS_USE
	delete visManager;
#endif

	delete runManager;

	return 0;
}



//void teste(){
//
//	SrBRandom *teste = new SrBRandom();
//
//	for (int i=0; i<10; i++){
//		//G4cout << "Numero aleatorio: " << G4UniformRand() << G4endl;
//		G4cout << "Numero aleatorio: " << teste->getRandomNumber() <<  G4endl;
//	}
//}


