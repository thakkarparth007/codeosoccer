#pragma once
#include "skills.h"
#include "GoalKeeper.hpp"

namespace MyStrategy
{
	
  // Naive example for defender
  void defender(BeliefState *state,int botID)
  {
	  print("DEFENDER!\n");
	  if (isBallBlockedAndSafeToSpin(state, botID)) {
		  spinSafely(state, botID);
		  return;
	  }

	  int dist = Vec2D::distSq(state->ballPos, homeGoal);

	  if (dist < DBOX_WIDTH*DBOX_WIDTH * 4) {
		  print("Sparta!!!!!!!!\n");
		  if (state->homePos[botID].x < state->ballPos.y)
			  shoot(botID, state, floatV(state->ballPos), true);
		  else
			  block(state, botID, homeGoal, true, -1);
		  return;
	  }
	  block(state, botID, homeGoal, true, -1);
	  return;

	  Vec2D pos = state->homePos[botID];

	  if (abs(pos.x - (OUR_GOAL_X + 3*DBOX_HEIGHT)) > 100) {
		  print("DEFENDER: MOVE BACK TO BASE %d\t%d\t%d\n", pos.x, OUR_GOAL_X + DBOX_HEIGHT, abs(pos.x - (OUR_GOAL_X + DBOX_HEIGHT)));
		  Vec2D dpoint(OUR_GOAL_X + 3*DBOX_HEIGHT, state->ballPos.y);

		  if (dpoint.y > OUR_GOAL_MAXY)
			  dpoint.y = OUR_GOAL_MAXY;
		  if (dpoint.y < OUR_GOAL_MINY)
			  dpoint.y = OUR_GOAL_MINY;
		  GoToPoint(botID, state, dpoint, PI / 2, true, true);
		  return;
	  }
	  if (fabs(state->homeAngle[botID] - PI / 2) > 0.1) {
		  print("DEFENDER TURNING %f\n", state->homeAngle[botID]);
		  TurnToAngle(botID, state, PI / 2);
	  }
	  else {
		  print("DEFENDER RUNNING\n");
		  if (state->homePos[botID].y > OUR_GOAL_MAXY) {
			  Velocity(botID, -MAX_BOT_SPEED, -MAX_BOT_SPEED);
		  }
		  else if (state->homePos[botID].y < -OUR_GOAL_MAXY) {
			  Velocity(botID, MAX_BOT_SPEED, MAX_BOT_SPEED);
		  }
		  else if (state->homePos[botID].y > state->ballPos.y) {
			  Velocity(botID, MAX_BOT_SPEED, MAX_BOT_SPEED);
		  }
		  else {
			  Velocity(botID, -MAX_BOT_SPEED, -MAX_BOT_SPEED);
		  }
	  }
	  return;

	  Vec2D dpoint(OUR_GOAL_X + DBOX_HEIGHT, -state->ballPos.y);
	  if (dpoint.y > OUR_GOAL_MAXY)
		  dpoint.y = OUR_GOAL_MAXY;
	  if (dpoint.y < OUR_GOAL_MINY)
		  dpoint.y = OUR_GOAL_MINY;
	  //TurnToAngle(botID, state, Vec2D::angle(state->ballPos, state->homePos[botID]));
	  //if (dist > 4*DBOX_WIDTH*DBOX_WIDTH) {//4 * DBOX_HEIGHT*DBOX_HEIGHT) {

	  GoToPointStraight(botID, state, dpoint, state->homeAngle[botID], true, true);
    //print("Defender\n");
	//It follows the ball
	/*Vec2D dpoint;
	dpoint.x = state->ballPos.x;
	dpoint.y = state->ballPos.y;
    //if(dpint.x < state->homePos[botID].x)
	GoToBall(botID,state,true);*/
	  //GoToPointStraight(botID, state, state->ballPos, PI, true, true);
	
  }
}