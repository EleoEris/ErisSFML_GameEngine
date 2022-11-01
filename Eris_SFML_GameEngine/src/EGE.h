#pragma once

#include "core/WindowComponent.h"

/*	
* Important notes:
*	Always use key(keycode) before key (key function will convert the key through a constexpr to the right key system
*
*	Check the comment standard at the end of this file
*/

//+// make extraMenusState
//+// make gameMenuState
//+// make each states a singleton (except the extraMenusState)

//3//! Required minimum C++17

// Comment standard (so you can look them up very quickly through search solution):
//					- normal comment
// //X				- adding characters after standardized comment means you have to look up the same comment in solution when solving the issue
//I//				- important
//I//!				- very important
//3//!				- important for third-party use
//+//				- to do / to continue
//C++++//			- to do if you upgrade C++ version (please check if the new version supports the feature)
//E//				- edited a part of a 3rd party code
//E//!				- this is where the editing of 3rd party code stopped
//>//				- try optimazing
//>//!				- needs optimization
//X//!				- possible crossplatform issues (this project might not be crossplatform)
//T//				- needs more testing
//?//				- check this thing out
//s//				- security concern
//b//				- harmless bug
//!//				- might break but not under current circumstances
//!//!				- will break in certain possible situations
//!!!//				- NEEDS FIXING OR THE WORLD WILL END
//<3//				- thank you kind stranger

// cool hashing func below
struct Hash {
	const size_t operator()(int x) const
	{
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = (x >> 16) ^ x;
		return x;
	}
};