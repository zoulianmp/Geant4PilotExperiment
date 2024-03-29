#include "SrBDetectorConstruction.hh"
#include "G4Material.hh"
#include "G4Box.hh"
//#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh" // usado para pegar materiais j� cadastrados no Geant4
#include "G4VisAttributes.hh"

#include "G4MultiFunctionalDetector.hh"
#include "G4SDManager.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4VSDFilter.hh"
#include "G4PSFlatSurfaceFlux.hh"
#include "G4SDParticleFilter.hh"

//#include "G4VPrimitiveSensitivity.hh"
#include "G4PSDoseDeposit.hh"
#include "G4PSEnergyDeposit.hh"

SrBDetectorConstruction::SrBDetectorConstruction()
 :  experimentalHall_log(0), detector_log(0), cubo_log(0),
    experimentalHall_phys(0), detector_phys(0), cubo_phys(0)//, espessura(0.1*mm)
{;}

SrBDetectorConstruction::~SrBDetectorConstruction()
{
}

G4VPhysicalVolume* SrBDetectorConstruction::Construct()
{

  //------------------------------------------------------ materials

  G4double a;  // atomic mass
  G4double z;  // atomic number
  G4double density;

  G4Material* Ar = new G4Material("ArgonGas", z= 18., a= 39.95*g/mole, density= 1.782*mg/cm3);

  //G4Material* Al = new G4Material("Aluminum", z= 13., a= 26.98*g/mole, density= 2.7*g/cm3);
  G4Material* Pb = new G4Material("Lead", z= 82., a= 207.19*g/mole, density= 11.35*g/cm3);


  /* ++++++++ Inicio da confec��o da �gua ++++++++ */
  /*
       G4Element(Nome, S�mbolo, Z, Massa molecular)
       G4Material(Nome, densidade, n�mero de componentes)
       AddElement(Elemento, n�mero de �tomos)
  */
  a = 1.01*g/mole;
  z = 1.;
  G4Element*  elH = new G4Element("Hydrogen", "H", z, a);
  G4Element*  elO = new G4Element("Oxygen", "O", 8., 16.00*g/mole);
  density = 1.000*g/cm3;
  G4Material* h2o = new G4Material("Water", density, 2);
  h2o->AddElement(elH, 2);
  h2o->AddElement(elO, 1);
  /* ++++++++ Fim da confec��o da �gua ++++++++ */


  /* ++++++++ Inicio da confec��o do Ar ++++++++ */
  /*
       G4Element(Nome, S�mbolo, Z, Massa molecular)
       G4Material(Nome, densidade, n�mero de componentes)
       AddElement(Elemento, percentagem)
  */
  G4Element*  elN = new G4Element("Nitrogen", "N", 7., 14.01*g/mole);
  //G4Element*  elO = new G4Element("Oxygen", "O", 8., 16.00*g/mole);
  density = 1.290*mg/cm3;
  G4Material* air = new G4Material("Air", density, 2);
  air->AddElement(elN, 70*perCent);
  air->AddElement(elO, 30*perCent);
  /* ++++++++ Fim da confec��o do Ar ++++++++ */


  // Outra forma de se obter alguns outros materiais
  //G4NistManager* nistMan = G4NistManager::Instance();
  //G4Material* H2O = nistMan->FindOrBuildMaterial("G4_WATER");
  //G4Material* Air = nistMan->FindOrBuildMaterial("G4_AIR");

  //------------------------------------------------------ volumes

  //------------------------------ experimental hall (world volume)
  //------------------------------ beam line along x axis

  G4double expHall_x = 3.0*m;
  G4double expHall_y = 1.0*m;
  G4double expHall_z = 1.0*m;
  G4Box* experimentalHall_box
    = new G4Box("expHall_box",expHall_x,expHall_y,expHall_z);

  experimentalHall_log = new G4LogicalVolume(experimentalHall_box,
                                             Ar,
                                             "expHall_log",0,0,0);

  experimentalHall_phys = new G4PVPlacement(0,                // Rota��o
		  	  	  	  	  	  	  	  G4ThreeVector(),		  // Origem
                                      experimentalHall_log,   // Seu volume l�gico
                                      "expHall",			  // Seu nome
                                      0,					  // Seu volume m�e. Neste caso o ponteiro � nulo por tratar-se do World Volume
                                      false,				  // Nenhuma opera��o booleana
                                      0);					  // Its copy number

  //------------------------------ a detector block


  G4double block_x = 0.1*mm;
//  G4double block_x = espessura;
  G4double block_y = 50.0*cm;
  G4double block_z = 50.0*cm;
  // Isso � o que se chama de s�lido. Cada s�lido pode necessitar de um
  // conjunto espec�fico de dados para a sua cria��o
  G4Box* detectorBlock_box = new G4Box("detectorBlock_box", block_x, block_y, block_z);
//  G4Box* detectorBlock_box = new G4Box("detectorBlock_box", espessura, block_y, block_z);

  // Volume l�gico
  // Ainda tenho que entender os �ltimos tr�s argumentos
  detector_log = new G4LogicalVolume(detectorBlock_box, Pb, "detector_log", 0, 0, 0);

  //detector_log->SetVisAttributes(G4VisAttributes::Invisible);
  detector_log->SetVisAttributes(G4Colour(1.0, 0.0, 0.0));

  G4double blockPos_x = 1.0*m;
  G4double blockPos_y = 0.0*m;
  G4double blockPos_z = 0.0*m;
  detector_phys = new G4PVPlacement(0,
             	 	 	G4ThreeVector(blockPos_x,blockPos_y,blockPos_z),
             	 	 	detector_log,
             	 	 	"detectorBlock",
             	 	 	experimentalHall_log,  // Volume m�e.
             	 	 	false,
             	 	 	0);

  //------------------------------------------------------------------



  //------------------------------ Cubinho de agua
  G4Box* cubo_box = new G4Box("cubo_box", 10.0*cm, 10.0*cm, 10.0*cm);
  cubo_log = new G4LogicalVolume(cubo_box, h2o, "cubo_log", 0, 0, 0);
  cubo_log->SetVisAttributes(G4Colour(1.0, 0.0, 0.0));
  cubo_phys = new G4PVPlacement(0,
             	 	 	G4ThreeVector( 1.3*m, 0.0*m, 0.0*m),
             	 	 	cubo_log,
             	 	 	"cubo",
             	 	 	experimentalHall_log,  // Volume m�e.
             	 	 	false,
             	 	 	0);
  //------------------------------------------------------------------


  /*
   * Sensitive Detector
   */

//  G4SDParticleFilter* gammaFilter = new G4SDParticleFilter("gammaFilter", "gamma");
  G4VPrimitiveScorer* primitive = new G4PSEnergyDeposit("eDep");

  G4MultiFunctionalDetector* myScorer = new G4MultiFunctionalDetector("mySrBDetector");
  myScorer->RegisterPrimitive(primitive);

  G4SDManager::GetSDMpointer()->AddNewDetector(myScorer);
  cubo_log->SetSensitiveDetector(myScorer);

//  G4SDManager::GetSDMpointer()->SetVerboseLevel(1);
  G4SDManager::GetSDMpointer()->SetVerboseLevel(0);

  return experimentalHall_phys;
}

