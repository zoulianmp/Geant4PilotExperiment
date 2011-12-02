
#ifndef ExN07RunAction_h
#define ExN07RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

class ExN07RunAction : public G4UserRunAction
{
  public:
    ExN07RunAction();
   ~ExN07RunAction();

  public:
    G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);
};

#endif

