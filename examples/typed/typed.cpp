#include <FiniteStateMachine.h>

DECLARE_STATE(CatState);
void restCat();
CatState catRestingState(restCat);
void meow();
CatState meowingState(meow);
FSMT<CatState> catFSM(catRestingState);

DECLARE_STATE(DogState);
void restDog();
DogState dogRestingState(restDog);
void bark();
DogState barkingState(bark);
FSMT<DogState> dogFSM(dogRestingState);

// setting the initial state to a cat state would fail with the compiler error
// no known conversion for argument 1 from 'CatState' to 'DogState&'
// FSMT<DogState> dogFSM(catRestingState);

void setup() {
}

void loop() {
  catFSM.update();
  dogFSM.update();
}

void restCat() {
  catFSM.transitionTo(meowingState);
}

void meow() {
  // meow!
  catFSM.transitionTo(catRestingState);
}

void restDog() {
  dogFSM.transitionTo(barkingState);
  // either asking the cat to bark or the dog to meow would fail with a compiler error
  // catFSM.transitionTo(barkingState);
  // dogFSM.transitionTo(meowingState);
}

void bark() {
  // bark!
  dogFSM.transitionTo(dogRestingState);
}
