#pragma once
#include "skills.h"

namespace MyStrategy
{
	extern int attacker_id;
	extern int supporter_id;

	void moveToPointSpl(BeliefState *state, int botID, Vec2D dpoint) {
		Vec2D mypos = state->homePos[botID];
		float myrot = Vec2D::angle(state->homePos[botID], Vec2D(0,0));
		if (myrot < 0)
			myrot += 2 * PI;

		int vl = 0, vr = 0;
		int dx = dpoint.x - mypos.x;
		int dy = dpoint.y - mypos.y;

		float angleToPoint = atan2((float)dpoint.y - mypos.y, (float)dpoint.x - mypos.x);
		//if (angleToPoint < 0)
		//	angleToPoint += 2 * PI;
		myrot = 0;
		if (myrot > angleToPoint) {
			//print("NYOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n");
			vl = (myrot - angleToPoint) * 40 / PI;
		}
		if (myrot < angleToPoint) {
			//print("YUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUS\n");
			vr = (myrot - angleToPoint) * 40 / PI;
		}

		print("ATTACKER:\t%d\t%d\t%f\n", (int)(myrot * 180 / PI), (int)(angleToPoint * 180 / PI), angleToPoint);

		if (fabs(myrot - angleToPoint)*180/PI < 40) {
			print("AWWWWWWWWWWWWWWWWWWWWWSOOOOOOOOOOOOOMe");
			vl = vr = MAX_BOT_SPEED;
			if (myrot < angleToPoint) vl -= angleToPoint*40/PI;
			else if (myrot > angleToPoint) vr -= -angleToPoint*40/PI;
		}

		// slow down near boundaries
		Velocity(botID, vl, vr);
	}

	void shoot(int botID, BeliefState *state, Vector2D<float> point) {
		int botx = state->homePos[botID].x;
		int boty = state->homePos[botID].y;

		int ballx = state->ballPos.x;
		int bally = state->ballPos.y;
		if (Vec2D::dist(state->homePos[botID], state->ballPos) < 340) {
			if (botx < ballx) {
				if (boty > 0 && boty < bally)		// ahead and above
					Spin(botID, MAX_BOT_OMEGA);
				else if (boty > 0 && boty > bally)
					Spin(botID, -MAX_BOT_OMEGA);
				else if (boty < 0 && boty > bally)		// ahead and above
					Spin(botID, -MAX_BOT_OMEGA);
				else
					Spin(botID, MAX_BOT_OMEGA);
			}
			else {
				if (boty > 0 && boty < bally)		// behind and above
					Spin(botID, MAX_BOT_OMEGA/10);
				else if (boty > 0 && boty > bally)
					Spin(botID, -MAX_BOT_OMEGA/10);
				else if (boty < 0 && boty > bally)		// behind and above
					Spin(botID, MAX_BOT_OMEGA/10);
				else
					Spin(botID, -MAX_BOT_OMEGA/10);
			}
			return;
		}
		Vec2D::dist(state->ballPos, state->homePos[botID]);
		double time = Vec2D::dist(state->ballPos, state->homePos[botID]) / (state->ballVel.abs() + state->homePos[botID].abs());
		Vector2D<float> ppos = Vector2D<float>(state->ballPos.x, state->ballPos.y) + time*state->ballVel;
		GoToPoint(botID, state, Vec2D(ppos.x, ppos.y), Vector2D<float>::angle(point, ppos), true, true);
		Vec2D v = state->homePos[botID];
		v.x -= state->ballPos.x;
		v.y -= state->ballPos.y;
		float angle = acos(-v.dot(Vec2D(1, 0)) / v.abs());

		//GoToPoint(botID, state, state->ballPos, angle, false, true);
		//GoToBall(botID, state, true);
		//maingotopoint(botID, state, state->ballPos, MAX_BOT_SPEED, Vector2D<float>::angle(point, Vector2D<float>(state->ballPos.x, state->ballPos.y)), CLEARANCE_PATH_PLANNER, true, true);
		//realshoot(botID, state, point);
		//moveToPointSpl(state, botID, point);
	}

	void attacksupporter(BeliefState *state, int botID)
	{
		print("Attack Supporter\n");
		Vector2D<float> opp_goal(OPP_GOAL_X, 0);

		int dist = Vec2D::distSq(state->ballPos, Vec2D(OPP_GOAL_X, 0));
		if (dist < DBOX_WIDTH*DBOX_WIDTH * 3) {
			shoot(botID, state, opp_goal);
		}
		else {
			float align_angle;
			Vec2D fpoint(OPP_GOAL_X - DBOX_WIDTH, 0);
			if (state->homePos[attacker_id].y > 0) {
				fpoint.y = -DBOX_HEIGHT;
				align_angle = 3 * PI / 4;
			}
			else {
				fpoint.y = DBOX_HEIGHT;
				align_angle = PI / 4;
			}
			//fpoint.x = min(fpoint.x, state->ballPos.x - BOT_BALL_THRESH*3);

			//float align_angle = PI / 2;
			GoToPoint(botID, state, fpoint, align_angle, true, true);
		}

		//Vec2D ballPoint(state->ballPos.x, state->ballPos.y);
		// Go to ball if ball is far
		// Take ball to the goal
		//if (Vec2D::distSq(state->homePos[botID], state->ballPos) < BOT_BALL_THRESH)
		//	GoToPoint(botID, state, fpoint, PI / 2, true, true);
		//else
		//	GoToBall(botID, state, true);// GoToPointStraight(botID, state, ballPoint, 0, true, true);
	}


  // Naive example for attacker
  void attacker(BeliefState *state,int botID)
  {
    print("Attacker\n");

	Vec2D dpoint(OPP_GOAL_X, 0);
	//if (Vec2D::dist(state->homePos[botID], dpoint) > DBOX_WIDTH && Vec2D::dist(state->homePos[1], dpoint) < Vec2D::dist(state->homePos[botID], dpoint))
	//	shoot(botID, state, Vector2D<float>(state->homePos[1].x, state->homePos[1].y));
	//else
		shoot(botID, state, Vector2D<float>(OPP_GOAL_X, 0));
	return;

	Vec2D fpoint(OPP_GOAL_X,0);
	Vec2D ballPoint(state->ballPos.x, state->ballPos.y);
	// Go to ball if ball is far
	// Take ball to the goal
	if (Vec2D::distSq(state->homePos[botID], state->ballPos) < BOT_BALL_THRESH)
		GoToPoint(botID, state, fpoint, PI / 2, true, true);
	else
		GoToBall(botID, state, true);// GoToPointStraight(botID, state, ballPoint, 0, true, true);
  }
  
}