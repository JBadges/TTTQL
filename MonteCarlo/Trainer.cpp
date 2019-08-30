#include <random>
#include <iostream>
#include "Trainer.h"
#include <time.h>



void Trainer::runIterations(int n, Trainer& a, Trainer& b) {
	int winCount = 0;
	int p1winCount = 0;
	int p1tieCount = 0;
	int p1lossCount = 0;
	int p2winCount = 0;
	int p2tieCount = 0;
	int p2lossCount = 0;
	for (int i = 0; i < n; ++i) {
		if (i % 100 == 0) {
			srand(time(nullptr));
		}
		//std::cout << i << "\r";
		std::pair<Trainer::Episode, Trainer::Episode> e = genEpisode(a, b);
		if (e.first.result == WIN)
			p1winCount++;
		if (e.first.result == TIE)
			p1tieCount++;
		if (e.first.result == LOSS)
			p1lossCount++;
		if (e.second.result == WIN)
			p2winCount++;
		if (e.second.result == TIE)
			p2tieCount++;
		if (e.second.result == LOSS)
			p2lossCount++;
		a.updateQFromEpisode(e.first);
		b.updateQFromEpisode(e.second);
		int sizeStep = 25000;
		if (i >= sizeStep && i % sizeStep == 0) {
			std::cout << "P1 Iteration: " << i << "\tWin %: " << ((double)p1winCount / (double)(sizeStep)) * 100 << "\tTie %: " << ((double)p1tieCount / (double)(sizeStep)) * 100 << "\tLoss %: " << ((double)p1lossCount / (double)(sizeStep)) * 100 << "\tState/Action Pairs Tracked: " << a.Q.size() << "\n";
			std::cout << "P2 Iteration: " << i << "\tWin %: " << ((double)p2winCount / (double)(sizeStep)) * 100 << "\tTie %: " << ((double)p2tieCount / (double)(sizeStep)) * 100 << "\tLoss %: " << ((double)p2lossCount / (double)(sizeStep)) * 100 << "\tState/Action Pairs Tracked: " << b.Q.size() << "\n";
			p1winCount = 0;
			p1tieCount = 0;
			p1lossCount = 0;
			p2winCount = 0;
			p2tieCount = 0;
			p2lossCount = 0;
		}

	}

	std::cout << "Done" << std::endl;
}

void Trainer::updateQ(const StateAction& sa, double ret) {
	if (Q.find(sa) == Q.end()) {
		Q[sa] = ret;
		Q_count[sa] = 1;
		return;
	}

	Q[sa] = (Q_count[sa] * Q[sa] + ret) / (Q_count[sa] + 1);
	Q_count[sa] = Q_count[sa] + 1;
}

double Trainer::random_start() {
	return ((rand() % 1000000) / 1000000.0) * 0.1;
}

int Trainer::Pi(TicTacToe& b) {
	int bestCell = -1;
	double bestWeight = -1;
	for (int i = 0; i < 9; ++i) {
		StateAction sa(b, i);
		double weight = (Q.find(sa) == Q.end()) ? random_start() : Q[sa];
		if (weight > bestWeight) {
			bestCell = i;
			bestWeight = weight;
		}
	}

	std::vector<std::pair<int, double> > probs(9);
	double sum = 0;
	for (int i = 0; i < 9; ++i) {
		if (b.isValidMove(i / 3, i % 3)) {
			if (i == bestCell) {
				probs[i] = std::pair<int, double>(i, 0.99);
				sum += 0.99;
			} else {
				probs[i] = std::pair<int, double>(i, 0.000125);
				sum += 0.000125;
			}
		} else {
			probs[i] = std::pair<int, double>(i, 0);
		}
	}

	for (int i = 0; i < 9; i++) {
		probs[i].second /= sum;
	}

	return pick_random(probs);
}

std::pair<Trainer::Episode, Trainer::Episode> Trainer::genEpisode(Trainer& p1, Trainer& p2)
{
	struct Episode e1, e2;
	TicTacToe b;
	int i = 0;
	for (;;) {
		bool validMove = false;
		do {			
			int a = p1.Pi(b);
			if (b.isValidMove(a / 3, a % 3)) {
				validMove = true;
				StateAction sa = StateAction(b, a);
				b.place(a / 3, a % 3);
				e1.sas.push_back(sa);
			}
		} while (!validMove);

		if (b.getAllValidMoves().size() == 0) {
			if (b.getWinner() != NONE) {
				e1.result = WIN;
				e2.result = LOSS;
			}
			else {
				e1.result = TIE;
				e2.result = TIE;
			}
			return { e1, e2 };
		}

		validMove = false;
		do {
			int a = p2.Pi(b); 
			if (b.isValidMove(a / 3, a % 3)) {
				validMove = true;
				StateAction sa = StateAction(b, a);
				b.place(a / 3, a % 3);
				e2.sas.push_back(sa);
			}
		} while (!validMove);

		if (b.getAllValidMoves().size() == 0) {
			if (b.getWinner() != NONE) {
				e1.result = LOSS;
				e2.result = WIN;
			} else {
				e1.result = TIE;
				e2.result = TIE;
			}
			return { e1, e2 };
		}

	}
}

int Trainer::pick_random(std::vector<std::pair<int, double> >& probs) {
	double roll = ((rand() % 1000000) / 1000000.0);

	std::vector<std::pair<int, double> >::reverse_iterator iter = probs.rbegin();
	double total_prob = 1.0;
	for (; iter != probs.rend(); ++iter) {
		total_prob -= iter->second;
		if (roll >= total_prob)
			return iter->first;
	}

	return probs[0].first;
}
int Trainer::random_action() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 9 - 1);
	return dis(gen);
}


void Trainer::updateQFromEpisode(struct Episode e) {
	int i = 0;
	for (std::list<StateAction>::iterator it = e.sas.begin(); it != e.sas.end(); ++it) {
		double weight = 0;
		if (e.result == WIN)
			weight = WIN_WEIGHT;
		else if (e.result == LOSS)
			weight = LOSS_WEIGHT;
		else if (e.result == TIE)
			weight = TIE_WEIGHT;

		double futureDiscountedReturn = weight * std::pow(GAMMA, i);
		updateQ(*it, futureDiscountedReturn);
		i++;
	}
}