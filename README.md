# particle-fsm

This is a library for the [Particle dev kits](https://www.particle.io/).

Ported from the [Arduino Finite State Machine library](http://playground.arduino.cc/Code/FiniteStateMachine) by [Gustavo Gonnet](gusgonnet@gmail.com).

All credit goes to the original author: [Alexander Brevig](alexanderbrevig@gmail.com).

# Finite State Machine Description

A FSM serves as a manager that organizes a set of states, or behaviors.

It manages the transition between states, and the state itself.
The transitions might be caused by the user, a wall or something other that is external, and they might be caused by some internal logic. Transitions either happen immediately, or they are deferred to the next update. The latter is the most common. It's used because that way you'll know that all code related to the current state, will have executed on the same state.


# FSM Library Description

This library will help you get rid of all your custom switch-case statements.

It is created to help organizing and standardizing the way an FSM could be implemented.

The library expects all functionality to be coded in the sketch, and the State class will simply use callbacks to simulate functionality.

All States expect an enter function, an update function and an exit function. These functions are being called according to this scheme:

```
current.exit();  //exit current state
next.enter();    //enter next state
current = next;
while no transition
  current.update();
```
---

# Creation

## Finite State Machine Creation

_FiniteStateMachine(State& current)_

_FSM(State& current)_

Example:

```FSM ethernetStateMachine = FSM(ethernetDebugState);```

Initializes an FSM object with the current state equal to ethernetDebugState.


## State Creation

_State( enterFunction , updateFunction , exitFunction )_

Example:

```State ethernetDebugState = State( connectToHost , debug , closeConnectionToHost );```

---
# Functions
## State Functions

_void enter()_ : 
This function gets called whenever this state is entered

_void update()_ : 
This function gets called whenever the state machine updates while in this state

_void exit()_ : 
This function gets called whenever this state is exited

## Finite State Machine Functions

_void update()_ : 
This function will trigger update on the current State

_void transitionTo(State& next)_ : 
This function will schedule a state change, the change itself will occur at the beginning of the next update

_void immediateTransitionTo(State& next)_ : 
This function will instantly change the current state to next state

_State& getCurrentState()_ :
Returns the current state

_boolean isInState( State &state )_ : 
Check if state is equal to the current state of the FSM

---

# Example

## LED Finite State Machine

We will implement a state machine for an LED.

From a design point of view we want to make the led go on and off, as well as fade in and out. This translates directly to the states for our example:

On
Off
FadeIn
FadeOut

The states describe themselves:


![alt text](https://github.com/gusgonnet/particle-fsm/blob/master/images/LED_FSM.png)


We will use external transitions, caused by a user and their button presses.

Each button will cause the FSM to advance to the next State in the diagram above.

This translates into this code:

```
//http://playground.arduino.cc/uploads/Code/FSM.zip
#include <FiniteStateMachine.h>
//http://playground.arduino.cc/uploads/Code/Button.zip
#include <Button.h>
//http://playground.arduino.cc/uploads/Code/LED.zip
#include <LED.h>
 
const byte NUMBER_OF_STATES = 4; //how many states are we cycling through?
 
//initialize states
State On = State(ledOn);
State Off = State(ledOff);
State FadeIn = State(ledFadeIn);
State FadeOut = State(ledFadeOut);
 
FSM ledStateMachine = FSM(On);     //initialize state machine, start in state: On
 
Button button = Button(12,PULLUP); //initialize the button (wire between pin 12 and ground)
LED led = LED(11);                 //initialize the LED
byte buttonPresses = 0;            //counter variable, hols number of button presses
 
void setup(){ /*nothing to setup*/ }
 
//poor example, but then again; it's just an example
void loop(){
  if (button.uniquePress()){
    //increment buttonPresses and constrain it to [ 0, 1, 2, 3 ]
    buttonPresses = ++buttonPresses % NUMBER_OF_STATES;
    switch (buttonPresses){
      case 0: ledStateMachine.transitionTo(On); break;
      case 1: ledStateMachine.transitionTo(Off); break;
      case 2: ledStateMachine.transitionTo(FadeIn); break;
      case 3: ledStateMachine.transitionTo(FadeOut); break;
    }
  }
  ledStateMachine.update();
}
 
//utility functions
void ledOn(){ led.on(); }
void ledOff(){ led.off(); }
void ledFadeIn(){ led.fadeIn(500); }
void ledFadeOut(){ led.fadeOut(500); }
//end utility functions
```