#pragma once
#include <list>
#include <unordered_map>
#include "TTT_StateAction.h"
#include "TTT_TicTacToe.h"

class TTT_Trainer
{
public:
	enum Res {
		WIN,
		LOSS,
		TIE
	};
	struct Episode {
		std::list<TTT_StateAction> sas;
		Res result;
	};

	const double GAMMA = 0.99;
	const double WIN_WEIGHT = -1;
	const double TIE_WEIGHT = 0;
	const double LOSS_WEIGHT = -1;

	std::unordered_map<TTT_StateAction, double, TTT_StateAction::Hash, TTT_StateAction::Pred> Q;
	std::unordered_map<TTT_StateAction, int, TTT_StateAction::Hash, TTT_StateAction::Pred> Q_count;

	static void runIterations(int n, TTT_Trainer& a, TTT_Trainer& b);

	void updateQ(const TTT_StateAction& sa, double ret);
	int pick_random(std::vector<std::pair<int, double>>& probs);

	double random_start();
	int random_action();

	int Pi(TTT_TicTacToe& b);

	static std::pair<TTT_Trainer::Episode, TTT_Trainer::Episode> genEpisode(TTT_Trainer& p1, TTT_Trainer& p2);

	void updateQFromEpisode(Episode e);
};