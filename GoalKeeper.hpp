#pragma once
#include "skills.h"

/*
	Vec2D can be used to make variables that can store points as (x,y) and provide utility functions.
	Vec2D point1;
	Vec2D point2;
	point1.x = HALF_FIELD_MAXX;
	point1.y = 0;
	similarly for point2 can be specified
	Some utility functions:
	These will appear automatically as you type Vec2D::
	float angle = Vec2D::angle(point1,point2);   
	int distance = Vec2D::distSq(point1,point2);
*/

namespace MyStrategy
{
	Vec2D homeGoal(OUR_GOAL_X, 0);
  // Naive Example for GoalKeeper
	void goalkeeper(BeliefState *state, int botID)
	{
		/*int vr = 0, vl = 0;
		int Tx = GRIGHT - state->ballPos.x;
		int Ty = FTOP - state->ballPos.y;

		Vec2D A = state->homePos[botID];
		A.x = GRIGHT - A.x;
		A.y = FTOP - A.y;

		if (A.y > Ty + 0.9 && A.y > 27) {
			vr = -100;
			vl = -100;
		}
		if (A.y < Ty - .9 && A.y < 43) {
			vr = 100;
			vl = 100;
		}
		if (A.y < 27) {
			vr = 100;
			vl = 100;
		}
		if (A.y > 43) {
			vr = -100;
			vl = -100;
		}
		float tR = 180/PI * state->homeAngle[botID];
		if (tR > 270.5)
			vl += abs(tR - 270);
		else if (tR < 269.5)
			vr += abs(tR - 270);

		Velocity(botID, vl, vr);
	  
		return;*/
	  int dist = Vec2D::distSq(state->ballPos, homeGoal);
	//print("GoalKeeper\n%d\t%d\t%d\t%d\n", state->ballPos.x, state->ballPos.y, OUR_GOAL_X, dist);

	  if (dist < DBOX_WIDTH*DBOX_WIDTH * 4) {
		  print("Sparta!!!!!!!!\n");
		  shoot(botID, state, Vector2D<float>(state->ballPos.x, state->ballPos.y));
		  //float ball_angle = state->ballVel.dot(Vector2D<float>)
		  //GoToPoint(botID, state, state->ballPos, Vector2D<float>::angle(point, Vector2D<float>(state->ballPos.x, state->ballPos.y)), false, true);
		  return;
	  }
	  /*
	  if (is_stuck(state, botID)) {
		  GoToPoint(botID, state, Vec2D(OUR_GOAL_X + DBOX_HEIGHT, 0), PI / 2, true, true);
		  return;
	  }*/
	Vec2D pos = state->homePos[botID];

	if (abs(pos.x - (OUR_GOAL_X + DBOX_HEIGHT) > 220)) {
		print("GOALKEEPER: MOVE BACK TO BASE %d\t%d\t%d\n", pos.x, OUR_GOAL_X + DBOX_HEIGHT, abs(pos.x - (OUR_GOAL_X + DBOX_HEIGHT)));
		Vec2D dpoint(OUR_GOAL_X + DBOX_HEIGHT, state->ballPos.y);

		if (dpoint.y > OUR_GOAL_MAXY - 300)
			dpoint.y = OUR_GOAL_MAXY - 300;
		if (dpoint.y < OUR_GOAL_MINY + 300)
			dpoint.y = OUR_GOAL_MINY + 300;
		GoToPoint(botID, state, dpoint, PI / 2, true, true);
		return;
	}
	if (fabs(state->homeAngle[botID] - PI/2) > 0.2) {
		print("Goalkeeper TURNING %f\n", state->homeAngle[botID]);
		TurnToAngle(botID, state, PI / 2);
	}
	else {
		print("Goalkeeper RUNNING\n");
		if (state->homePos[botID].y > OUR_GOAL_MAXY) {
			Velocity(botID, -MAX_BOT_SPEED, -MAX_BOT_SPEED);
		}
		else if (state->homePos[botID].y < -OUR_GOAL_MAXY) {
			Velocity(botID, MAX_BOT_SPEED, MAX_BOT_SPEED);
		}
		else if (state->homePos[botID].y > state->ballPos.y) {
			Velocity(botID, -MAX_BOT_SPEED, -MAX_BOT_SPEED);
		}
		else {
			Velocity(botID, MAX_BOT_SPEED, MAX_BOT_SPEED);
		}
	}
	/*Vec2D dpoint(OUR_GOAL_X+DBOX_HEIGHT,state->ballPos.y);
    if(dpoint.y > OUR_GOAL_MAXY)
      dpoint.y = OUR_GOAL_MAXY;
    if(dpoint.y < OUR_GOAL_MINY)
      dpoint.y = OUR_GOAL_MINY;*/
	//TurnToAngle(botID, state, Vec2D::angle(state->ballPos, state->homePos[botID]));
	//if (dist > 4*DBOX_WIDTH*DBOX_WIDTH) {//4 * DBOX_HEIGHT*DBOX_HEIGHT) {
	//GoToPoint(botID, state, dpoint, PI/2, true, true);
	//}
	//else {
	//	print("INSIDE!!!!!!!!!!!!!*\n*\n*\n*\n*\n*\n*\n*\n");
		//GoToPointStraight(botID, state, state->ballPos, PI, true, true);
		//GoToBall(botID, state, true);
	//}
  }
}