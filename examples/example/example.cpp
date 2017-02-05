#include <FiniteStateMachine.h>

//how many states are we cycling through?
const byte NUMBER_OF_STATES = 4;

//utility functions
void ledOn() { /*action to turn the led on*/ }
void ledOff() { /*action to turn the led off*/ }
void ledFadeIn() { /*action to fade in the led*/ }
void ledFadeOut() { /*action to fade out the led*/ }
//end utility functions
 
// initialize states
State On = State(ledOn);
State Off = State(ledOff);
State FadeIn = State(ledFadeIn);
State FadeOut = State(ledFadeOut);
 
// initialize state machine, start in state: On
FSM ledStateMachine = FSM(On);
 
// counter variable
byte counter = 0;

void setup()
{ /* nothing to setup */ }
 
void loop()
{
  // increment counter and constrain it to [ 0, 1, 2, 3 ]
  counter = ++counter % NUMBER_OF_STATES;
  switch (counter){
    case 0: ledStateMachine.transitionTo(On); break;
    case 1: ledStateMachine.transitionTo(Off); break;
    case 2: ledStateMachine.transitionTo(FadeIn); break;
    case 3: ledStateMachine.transitionTo(FadeOut); break;
  }
 
  ledStateMachine.update();

  // advance to next state every 5 seconds
  delay(5000);

}
