/*
||
|| @file FiniteStateMachine.h
|| @version 1.8.0
|| @original author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
|| @Ported to Particle by Gustavo Gonnet
|| @contact gusgonnet@gmail.com
||
|| @description
|| | Provide an easy way of making finite state machines
|| #
||
|| @license
|| | This library is free software; you can redistribute it and/or
|| | modify it under the terms of the GNU Lesser General Public
|| | License as published by the Free Software Foundation; version
|| | 2.1 of the License.
|| |
|| | This library is distributed in the hope that it will be useful,
|| | but WITHOUT ANY WARRANTY; without even the implied warranty of
|| | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
|| | Lesser General Public License for more details.
|| |
|| | You should have received a copy of the GNU Lesser General Public
|| | License along with this library; if not, write to the Free Software
|| | Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
|| #
---------------------( COPY )---------------------
This libraries .h file has been updated by Terry King to make it compatible with Ardino 1.0x

(Example 1.03) and also earlier versions like 0023

#include "WProgram.h"
...has been replaced by:

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

terry@yourduino.com
02/07/2012
-----------------( END COPY )----------------------
||
*/

#ifndef FINITESTATEMACHINE_H
#define FINITESTATEMACHINE_H

#include "application.h"

#define NO_ENTER (0)
#define NO_UPDATE (0)
#define NO_EXIT (0)

#define FSM FiniteStateMachine

//define the functionality of the states
class State {
	public:
		State( void (*updateFunction)() );
		State( void (*enterFunction)(), void (*updateFunction)(), void (*exitFunction)() );
		//State( byte newId, void (*enterFunction)(), void (*updateFunction)(), void (*exitFunction)() );

		//void getId();
		void enter();
		void update();
		void exit();
	private:
		//byte id;
		void (*userEnter)();
		void (*userUpdate)();
		void (*userExit)();
};

//define the finite state machine functionality
class FiniteStateMachine {
	public:
		FiniteStateMachine(State& current);

		FiniteStateMachine& update();
		FiniteStateMachine& transitionTo( State& state );
		FiniteStateMachine& immediateTransitionTo( State& state );

		State& getCurrentState();
		boolean isInState( State &state ) const;

		unsigned long timeInCurrentState();

	private:
		bool 	needToTriggerEnter;
		State* 	currentState;
		State* 	nextState;
		unsigned long stateChangeTime;
};

#endif

/*
|| @changelog
|| | 1.8.0 2016-01-07- Gustavo Gonnet : Ported to Particle
|| | 1.7 2010-03-08- Alexander Brevig : Fixed a bug, constructor ran update, thanks to Ren? Press?
|| | 1.6 2010-03-08- Alexander Brevig : Added timeInCurrentState() , requested by sendhb
|| | 1.5 2009-11-29- Alexander Brevig : Fixed a bug, introduced by the below fix, thanks to Jon Hylands again...
|| | 1.4 2009-11-29- Alexander Brevig : Fixed a bug, enter gets triggered on the first state. Big thanks to Jon Hylands who pointed this out.
|| | 1.3 2009-11-01 - Alexander Brevig : Added getCurrentState : &State
|| | 1.3 2009-11-01 - Alexander Brevig : Added isInState : boolean, requested by Henry Herman
|| | 1.2 2009-05-18 - Alexander Brevig : enter and exit bug fix
|| | 1.1 2009-05-18 - Alexander Brevig : Added support for cascaded calls
|| | 1.0 2009-04-13 - Alexander Brevig : Initial Release
|| #
*/
