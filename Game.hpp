// For adding header files define your includes here and add the headers in Game folder.
// For example, You may see these files - Attacker.hpp,Defender.hpp and Goalkeeper.hpp
// For checking out the skills you may see skills.h placed in Skills folder.
#pragma once
#include "skills.h"
#include "Attacker.hpp"
#include "Defender.hpp"
#include "AttackSupporter.hpp"
#include "GoalKeeper.hpp"

// Change your team color here (BLUE_TEAM/YELLOW_TEAM)face

Simulator::TeamColor teamColor = Simulator::BLUE_TEAM;

// Make usingDebugger is false when playing against an opponent
bool usingDebugger = true;

namespace MyStrategy
{
	int attacker_id = 1;
	int supporter_id = 2;

  // Write your strategy here in game function.
  // You can also make new functions and call them from game function.
  void game(BeliefState *state)
  {
	  //storePositions(state);
	  //attacker(state,2);
	  
	  for (int i = 0; i < 5; i++) {
		  //state->homeAngle[i] = acos(state->homeVel[i].dot(Vector2D<float>(0, 1)) / state->homeVel[i].abs());
		  print("%d\t%f\n", i, state->homeAngle[i]);
	  }

	  if (state->ballPos.x >= -100) {
		  if (Vec2D::dist(state->homePos[2], state->ballPos) < Vec2D::dist(state->homePos[1], state->ballPos)) {
			  attacker_id = 2;
			  supporter_id = 1;
		  }
		  else {
			  attacker_id = 1;
			  supporter_id = 2;
		  }
		  attacker(state, attacker_id);
		  attacksupporter(state, supporter_id);
	  }
	  else {
		  if (Vec2D::dist(state->homePos[2], state->ballPos) < Vec2D::dist(state->homePos[1], state->ballPos)) {
			  defender(state, 1);
			  attacker(state, 2);
		  }
		  else {
			  defender(state, 2);
			  attacker(state, 1);
		  }
	  }
	  goalkeeper(state,0);

	  Vec2D bp = state->ballPos;
	 /* if (state->pr_balInOurCorner) {
		  int closestBotId = state->ourBotNearestToBall;
		  GoToPoint(1, state, state->homePos[0], 0, true, true);
	  }

	  if (Vec2D::dist(prevPos[2], state->homePos[2]) < 2) {
		  Vec2D newPos = state->homePos[2];
		  newPos.x += rand() % 5;
		  newPos.y += rand() % 5;
		  GoToPoint(2, state, newPos, 0, true, true);
	  }
	  if (Vec2D::dist(prevPos[1], state->homePos[1]) < 2) {
		  Vec2D newPos = state->homePos[1];
		  newPos.x += rand() % 5;
		  newPos.y += rand() % 5;
		  GoToPoint(1, state, newPos, 0, true, true);
	  }
	  */
  }
}