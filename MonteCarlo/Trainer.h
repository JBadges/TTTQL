#pragma once
#include <list>
#include <unordered_map>
#include "StateAction.h"
#include "TicTacToe.h"

class Trainer
{
public:
	enum Res {
		WIN,
		LOSS,
		TIE
	};
	struct Episode {
		std::list<StateAction> sas;
		Res result;
	};

	const double GAMMA = 0.99;
	const double WIN_WEIGHT = -1;
	const double TIE_WEIGHT = 0;
	const double LOSS_WEIGHT = -1;

	std::unordered_map<StateAction, double, StateAction::Hash, StateAction::Pred> Q;
	std::unordered_map<StateAction, int, StateAction::Hash, StateAction::Pred> Q_count;

	static void runIterations(int n, Trainer& a, Trainer& b);

	void updateQ(const StateAction& sa, double ret);
	int pick_random(std::vector<std::pair<int, double>>& probs);

	double random_start();
	int random_action();

	int Pi(TicTacToe& b);

	static std::pair<Trainer::Episode, Trainer::Episode> genEpisode(Trainer& p1, Trainer& p2);

	void updateQFromEpisode(Episode e);
};