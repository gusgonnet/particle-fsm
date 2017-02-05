# particle-fsm

This is a library for the [Particle dev kits](https://www.particle.io/).

Ported from the [Arduino Finite State Machine library](http://playground.arduino.cc/Code/FiniteStateMachine) by [Gustavo Gonnet](gusgonnet@gmail.com).

All credit goes to the original author: [Alexander Brevig](alexanderbrevig@gmail.com).

# Finite State Machine Description

A FSM serves as a manager that organizes a set of states, or behaviors.

It manages the transition between states, and the state itself.
The transitions might be caused by the user, a wall or something other that is external, and they might be caused by some internal logic. Transitions either happen immediately, or they are deferred to the next update. The latter is the most common. It's used because that way you'll know that all code related to the current state, will have executed on the same state.

You can read more about finite state machines in this [write-up](https://www.hackster.io/gusgonnet/using-finite-state-machines-fdba04).

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


Every 5 seconds the FSM will advance to the next State in the diagram above.

This FSM translates into this sketch:

```
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

```

---
# Real-world implementations

You can refer to this [pool and sauna controller](https://www.hackster.io/gusgonnet/pool-and-sauna-controller-b24a9a?team=34278).
