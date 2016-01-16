#pragma once
#include "skills.h"

namespace MyStrategy {
	const float BOT_Y_STRIP = -(float) HALF_FIELD_MAXY / 3.0;
	const float MID_Y_STRIP = 0.0;
	const float TOP_Y_STRIP = (float) HALF_FIELD_MAXY / 3.0;

	float whichLane(Vector2D<int> point) {
		float lanes[] = { BOT_Y_STRIP, MID_Y_STRIP, TOP_Y_STRIP };
		int i, min = 0;
		float tempDist = fabs(point.y - lanes[0]);
		float minDist = tempDist;
		for (i = 1; i < 3; ++i) {
			tempDist = fabs(point.y - lanes[i]);
			if (tempDist < minDist) {
				minDist = tempDist;
				min = i;
			}
		}
		return lanes[min];
	}

	class TeamSt;
	class GrabSt;
	class PlayerSt;
	class GrabberSt;
	class GrabSupSt;

	void changePlayerState(std::vector<PlayerSt *> &curPlayerStates, int Id, PlayerSt * newState);
	int otherId(int Id);

	class TeamSt {
	public:
		virtual void Enter(std::vector<PlayerSt *> &curPlayerStates) {}
		virtual TeamSt * Act(BeliefState * state, std::vector<PlayerSt * > curPlayerStates) { return NULL; }
		static GrabSt * grab;
	};

	class GrabSt : public TeamSt {
	public:
		std::string stateName = "Grab";
		float ballLaneY;
		float botLanesY[3];
		int nearestHomeId;

		GrabSt();
		virtual TeamSt * Act(BeliefState * state, std::vector<PlayerSt *> curPlayerStates);
		virtual void Enter(std::vector<PlayerSt *> &curPlayerStates);
	};

	GrabSt * TeamSt::grab = new GrabSt;

	class PlayerSt {
	public:
		virtual ~PlayerSt() {}
		virtual PlayerSt * Act(BeliefState * state) { return NULL; }
		virtual std::string StateName() { return ""; }
	};

	class GrabberSt : public PlayerSt {
	public:
		std::string stateName = "Grabber";
		int Id;

		GrabberSt(int);
		virtual PlayerSt * Act(BeliefState * state);
		virtual std::string StateName();
	};

	class GrabSupSt : public PlayerSt {
	public:
		std::string stateName = "GrabSupporter";
		float curLaneY;
		int Id;

		GrabSupSt(int);
		virtual PlayerSt * Act(BeliefState * state);
		virtual std::string StateName();
	};

	GrabSt::GrabSt() : TeamSt() {
		return;
	}

	TeamSt * GrabSt::Act(BeliefState * state, std::vector<PlayerSt *> curPlayerStates) {
		ballLaneY = whichLane(state->ballPos);
		if (Vec2D::dist(state->homePos[2], state->ballPos) < Vec2D::dist(state->homePos[1], state->ballPos)) {
			nearestHomeId = 2;
		}
		else
			nearestHomeId = 1;
		return NULL;
	}

	void GrabSt::Enter(std::vector<PlayerSt *> &curPlayerStates) {
		curPlayerStates[1] = new GrabberSt(1);
		curPlayerStates[2] = new GrabSupSt(2);
	}

	GrabberSt::GrabberSt(int Id) : PlayerSt() {
		this->Id = Id;
		stateName = "Grabber";
	}

	PlayerSt * GrabberSt::Act(BeliefState * state) {
		//print("nearestHomeId: %d\n", TeamSt::grab->nearestHomeId);
		print("%s", "Grabber");
		if (TeamSt::grab->nearestHomeId != Id) {
			return new GrabSupSt(Id);
		}

		TeamSt::grab->botLanesY[Id] = whichLane(state->homePos[Id]);
		print("Going to ball");
		GoToBall(Id, state, true);
		//GoToPoint(Id, state, state->ballPos, PI / 2, true, true);
		return NULL;
	}

	std::string GrabberSt::StateName() {
		std::string s = "Grabber";
		return s;
	}

	GrabSupSt::GrabSupSt(int Id) : PlayerSt() {
		this->Id = Id;
		stateName = "GrabSupporter";
	}

	PlayerSt * GrabSupSt::Act(BeliefState * state) {
		if (TeamSt::grab->nearestHomeId == Id) {
			return new GrabberSt(Id);
		}

		curLaneY = whichLane(state->homePos[Id]);
		if (whichLane(state->ballPos) == 0.0) {
			if (curLaneY == 0.0) {
				int lanePopCount[] = { 0, 0 };
				int i;
				for (i = 1; i <= 2; ++i) {
					float tempLaneY = whichLane(state->awayPos[i]);
					if (state->awayPos[i].x > state->homePos[Id].x) {
						if (tempLaneY >= 0.0)
							lanePopCount[0] ++;
						else
							lanePopCount[1]++;
					}
				}
				if (lanePopCount[0] >= lanePopCount[1])
					curLaneY = TOP_Y_STRIP;
				else
					curLaneY = BOT_Y_STRIP;
			}
		}
		else {
			if (curLaneY != 0.0)
				curLaneY = 0.0;
		}
		TeamSt::grab->botLanesY[Id] = curLaneY;
		GoToPoint(Id, state, Vector2D<int>(state->homePos[otherId(Id)].x, curLaneY), PI / 2, true, true);
		return NULL;
	}

	std::string GrabSupSt::StateName() {
		std::string s = "GrabSupporter";
		return s;
	}

	void changePlayerState(std::vector<PlayerSt *> &curPlayerStates, int Id, PlayerSt * newState) {
		curPlayerStates[Id] = newState;
	}

	int otherId(int Id) {
		return (Id == 1) ? 2 : 1;
	}
}