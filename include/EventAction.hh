#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "TrackerIonSD.hh"
#include "TrackerCsISD.hh"
#include "G4Event.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "globals.hh"
#include "G4UnitsTable.hh"
#include "Results.hh"
#include <sys/time.h>
#include "RunAction.hh"
#include "DetectorConstruction.hh"

using namespace CLHEP;

/*

  Trigger settings notes:
  No trigger                         0
  Gamma singles                      1
  CsI recoil singles                 2
  gamma-CsI recoil coinc             3
  CsI projectile singles             4
  gamma-CsI projectile coinc         5
  CsI recoil-CsI projectile coinc    6
  gamma-CsI recoil-CsI projectile    7
  CsI system                         8
  gamma-CsI system                   9

 */

class EventAction : public G4UserEventAction
{
  public:
  EventAction(Results*,RunAction*,Projectile*,Recoil*,DetectorConstruction*);
   ~EventAction();
  void BeginOfEventAction(const G4Event*);
  void EndOfEventAction(const G4Event*);
  void AddGriffinCrystDet(G4double, G4double,G4ThreeVector, G4int, G4int);
  void SetNoTrigger(){setTrigger=0;};
  void SetTriggerGammaSing(){setTrigger=1;};
  void SetTriggerPinRecoilSing(){setTrigger=2;};
  void SetTriggerPinProjSing(){setTrigger=4;};
  void SetTriggerPinSing(){setTrigger=8;};
  void SetTriggerGammaPinRecoilCoinc(){setTrigger=3;};
  void SetTriggerGammaPinProjCoinc(){setTrigger=5;};
  void SetTriggerGammaPinCoinc(){setTrigger=9;};
  void SetCsIThreshold(double th){CsIThreshold=th;};


  private:
  Results*      results;
  G4int         ionCollectionID;
  G4int         CsICollectionID;
  G4int         CollectionGriffinGe;
  timeval       tc,ts,td;
  double        t,rate;
  RunAction*    run_action;
  G4double      GriffinCrystEnergyDet[16][4];
  G4double      GriffinCrystWeightDet[16][4];
  G4ThreeVector GriffinCrystPosDet[16][4];
  G4int         GriffinFold;
  size_t        soa,sov,soc,soi;
  G4int         eventTrigger,setTrigger,systemTrigger;
  G4double      CsIThreshold;

  // Info for CsI trigger
  Projectile* theProjectile;
  Recoil*     theRecoil;
  DetectorConstruction* theDetector;
  Int_t       Ap,Zp,Ar,Zr;

  // global scope
  TrackerCsIHitsCollection* CsI;
  TrackerIonHitsCollection* HI;

  //static Decay decay;

};

#endif //EVENTACTION_H

    
