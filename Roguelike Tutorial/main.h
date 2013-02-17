#include <stdio.h>
#include "libtcod.hpp"
// Forward declare the Actor class so that the compiler knows that this class exists before compiling the Actor class and its circular testing.
class Actor;
#include "Attacker.h"
#include "Destructible.h"
#include "Ai.h"
#include "Actor.h"
#include "Map.h"
#include "Engine.h"
#include "BspListener.h"
