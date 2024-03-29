//
// $Id: ExN01DetectorConstruction.hh,v 1.6 2006/06/29 17:47:13 gunter Exp $
// GEANT4 tag $Name: geant4-09-03-patch-02 $
//

#ifndef SrBDetectorConstruction_H
#define SrBDetectorConstruction_H 1

class G4LogicalVolume;
class G4VPhysicalVolume;

#include "G4VUserDetectorConstruction.hh"


class SrBDetectorConstruction : public G4VUserDetectorConstruction
{
  public:

	SrBDetectorConstruction();
    ~SrBDetectorConstruction();

    G4VPhysicalVolume* Construct();

    inline G4double getEspessura(){
    	return espessura;
    }
    inline void setEspessura(G4double _espessura) {
    	espessura = _espessura;
    }

  private:

    G4double espessura;
    
    // Logical volumes
    //
    G4LogicalVolume* experimentalHall_log;
    G4LogicalVolume* detector_log;
    G4LogicalVolume* cubo_log;


    // Physical volumes
    //
    G4VPhysicalVolume* experimentalHall_phys;
    G4VPhysicalVolume* detector_phys;
    G4VPhysicalVolume* cubo_phys;
};

#endif

