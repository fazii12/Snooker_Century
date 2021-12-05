#include "Century.h"

bool isNumber(const string& str)
{
	int i = 0;
	if(str[0] == '-'){
		i = 1; 
	}
    
	for (; str[i] != '\0' ; i++)
		if (isdigit(str[i]) == 0) return false;
    
    return true;
}

string style(char a, int n) {
	string s = "";
	if (n > 0) {

		for (int i = 0; i < n; i++)
			s += a;
	}
	return s;
}

void Sort(Game& g) {
	if (g.players_array != nullptr) {
		Player temp;
		int len = g.players.get_no_of_players();


		for (int i = 0; i < len; i++) {
			for (int j = 0; j < len; j++) {
				if (g.players_array[i].getscore() > g.players_array[j].getscore()) {
					temp = g.players_array[i];
					g.players_array[i] = g.players_array[j];
					g.players_array[j] = temp;
				}
			}
		}
	}
}

Player::Player() {
	fname = lname = "";
	next = prev = nullptr;
	id = score = prev_score = strikes_taken = age = bestbreak = worstbreak = 0;
}

void Player::allot_id() {
	this->id = rand() % 101;
}

string Player::get_fullname() {
	return (fname + ' ' + lname);
}

void Player::info() {
	cout << style(' ', 26) << "| " << id << style(' ', 7) << fname << " " << lname << style(' ', 20 - (fname + " " + lname).length()) << score << style(' ', 15 - (to_string(score).length())) << prev_score << style(' ', 17 - (to_string(prev_score).length())) << strikes_taken << style(' ', 6 - (to_string(strikes_taken).length())) << "|\n";
}

void Player::input_info() {
	if (fname.length() == 0) {
		cout << "\nFirst Name\t:\t";
		cin >> fname;

	}
	if (lname.length() == 0) {
		cout << "\nLast Name\t:\t";
		cin >> lname;
	}
	if (age == 0) {
		cout << "\nAge\t:\t";
		cin >> age;
	}
	if (id == 0) {
		allot_id();
	}
	cout << endl;
}

void Player::set_name(string _fname, string _lname) {
	fname = _fname;
	lname = _lname;
}

int Player::getscore() {
	return score;
}

int Player::getstrikes() {
	return strikes_taken;
}

void Player::update_scores(int turn_score) {
	prev_score = score;
	score += turn_score;
	strikes_taken++;
}



void Player::set_next(Player* p) {
	next = p;
}
void Player::set_prev(Player* p) {
	prev = p;
}

Player* Player::get_next() {
	return next;
}

Player* Player::get_prev() {
	return prev;
}

void Player::set_isfinished(bool x) {
	finished = x;
}

bool Player::get_finish_status() {
	return finished;
}

void Player::set_bestbreak(int x) {
	bestbreak = x;
}

void Player::set_worstbreak(int x) {
	worstbreak = x;
}

int Player::getbestbreak() {
	return bestbreak;
}

int Player::getworstbreak() {
	return worstbreak;
}

int Player::get_id() {
	return id;
}

int Player_list::get_no_of_players() {
	return no_of_players;
}

Player_list::Player_list() {
	front = nullptr;
	no_of_players = 0;
}

void Player_list::operator=(const Player_list& p) {
	if (p.front != nullptr) {
		Player* temp = p.front;

		do {
			add_new_Player(temp);
			temp = temp->get_next();
		} while (temp != p.front);
	}
}

Player* Player_list::get_front() {
	return front;
}

void Player_list::add_new_Player(Player* p = nullptr) {
	Player* new_player = new Player();

	if (p != nullptr)
		*new_player = *p;
	else
		new_player->input_info();

	if (front == nullptr) {
		new_player->set_next(new_player);
		new_player->set_prev(new_player);
		front = new_player;
	}

	else {
		front->get_prev()->set_next(new_player);
		new_player->set_next(front);
		new_player->set_prev(front->get_prev());
		front->set_prev(new_player);
	}

	no_of_players++;
}

void Player_list::del_Player(Player*& p) {
	if (p != nullptr && no_of_players != 0) {
		Player* temp = p->get_next();
		if (no_of_players == 1) {
			delete p;
			front = nullptr;
		}
		else if (p == front)
		{
			front = front->get_next();
			front->set_prev(p->get_prev());
			p->get_prev()->set_next(front);
			delete p;
		}
		else {
			p->get_next()->set_prev(p->get_prev());
			p->get_prev()->set_next(p->get_next());
			delete p;
		}
		p = temp;
		no_of_players--;
	}
}

Player_list::~Player_list() {
	if (front != nullptr) {
		Player* temp = front->get_next();

		while (temp != front) {
			del_Player(temp);
		}

		delete temp;
		front = nullptr;
	}
}

Game::Game() {
	players_array = nullptr;
	winners_list = nullptr;
}

void Game::list_to_arr() {
	Player* temp = players.get_front();
	if (temp != nullptr) {
		if (players_array != nullptr)
			delete[] players_array;

		int length = players.get_no_of_players();
		players_array = new Player[length];

		for (int i = 0; i < length; i++) {
			players_array[i] = *temp;
			temp = temp->get_next();
		}
	}
}

void Game::show_Scorecard() {
	if (players_array != nullptr) {
		Sort(*this);

		cout << style(' ', 26) << style('-', 70) << endl;
		cout << style(' ', 26) << "| ID" << style(' ', 7) << "Name" << style(' ', 15) << "Score" << style(' ', 8) << "last Score" << style(' ', 8) << "Strikes |\n";
		cout << style(' ', 26) << style('-', 70) << endl;
		for (int i = 0; i < players.get_no_of_players(); i++) {
			players_array[i].info();
		}
		cout << style(' ', 26) << style('-', 70) << endl;
		cout << endl;
	}
}



void Game::startRecording() {

	bool out_of_the_game = false;
	int no_of_players, winning_threshold, winning_score;

	cout << "Enter number of Players\t:\t";
	cin >> no_of_players;

	while (no_of_players < 2 || no_of_players > 10) {
		cout << "Incorrect, Enter number of players again\t:\t";
		cin >> no_of_players;
	}

	cout << "\nEnter winning threshold :\t";
	cin >> winning_threshold;

	while (winning_threshold < 1 || winning_threshold > no_of_players - 1) {
		cout << "\nIncorrect, Enter winning threshold again\t:\t";
		cin >> winning_threshold;
	}

	cout << "\nEnter winning score :\t";
	cin >> winning_score;

	while (winning_score < 10) {
		cout << "\nIncorrect, Enter winning score again\t:\t";
		cin >> winning_score;
	}


	winners_list = new Player[winning_threshold];

	for (int i = 0; i < no_of_players; i++) {
		cout << setw(30) << "Player " << i + 1 << endl;
		players.add_new_Player(0);
	}

	Player* current_player = players.get_front(), *wbp, *bbp;
	int current_players_score, players_won = 0, bb = 0, wb = 0;
	float avg;
	string wbname, bbname;

	int temp = no_of_players - winning_threshold;

	do {
		system("cls");
		if (out_of_the_game) {

			cout << "Winners\n" << style(' ', 30) << "ID\tName" << style(' ', 18) << "Final Score" << style(' ', 10) << "Strikes" << style(' ', 10) << "S/R\n";
			cout << style(' ', 30) << style('-', 74) << endl;
			for (int i = 0; i < players_won; i++) {
				avg = (float)winners_list[i].getscore() / winners_list[i].getstrikes();
				cout << style(' ', 30) << winners_list[i].get_id() << "\t" << winners_list[i].get_fullname() << style(' ', 25 - winners_list[i].get_fullname().length()) << winners_list[i].getscore() << style(' ', 21 - (to_string(winners_list[i].getscore()).length())) << winners_list[i].getstrikes() << style(' ', 14 - (to_string(winners_list[i].getstrikes()).length())) << setprecision(3) << avg << endl;
			}
		}

		//code for displaying worst and bestr breaks here
		if (current_player->getstrikes() >= 1) {
			cout << "\nBest Break\t" << bbname << "\t " << bb << endl;
			cout << "\nWorst Break\t\t" << wbname << "\t " << wb << endl;
		}

		list_to_arr();
		cout << "\n\nOn Going\n\n";
		show_Scorecard();
		
		
		string curr_score;
		cout << current_player->get_fullname() << "'s turn\t:\t";
		cin >> curr_score;

		stringstream _stoi(curr_score);
			
		_stoi >> current_players_score;
	
		while(!isNumber(curr_score) || current_players_score > winning_score+10){
			cout<<"Invalid score entered, enter again\n";
			cout << current_player->get_fullname() << "'s turn\t:\t";
			cin >> curr_score;

			_stoi.clear();
			_stoi.str(curr_score);
			
			_stoi >> current_players_score;
	
		}

		
		

		if (bb <= current_players_score) {
			bb = current_players_score;
			bbname = current_player->get_fullname();
		}
		else if (wb >= current_players_score) {
			wb = current_players_score;
			wbname = current_player->get_fullname();
		}


		current_player->update_scores(current_players_score);
		if (current_player->getbestbreak() < current_players_score)
			current_player->set_bestbreak(current_players_score);
		else if (current_player->getworstbreak() > current_players_score)
			current_player->set_worstbreak(current_players_score);

		if (current_player->getscore() >= winning_score) {
			winners_list[players_won] = *current_player;
			players.del_Player(current_player);
			players_won++;
			if (!out_of_the_game)
				out_of_the_game = true;
		}
		else
			current_player = current_player->get_next();



	} while (players.get_no_of_players() != temp);

	system("cls");
	showFinalResults(players_won);
}


void Game::showFinalResults(int n) {
	if (winners_list != nullptr) {

		cout << "---------------------------------------------------------Final Results---------------------------------------------------------\n\n";
		cout << "Winners\n" << style(' ', 30) << "ID\tName" << style(' ', 18) << "Final Score" << style(' ', 10) << "Strikes" << style(' ', 10) << "S/R\n";
		cout << style(' ', 30) << style('-', 74) << endl;
		for (int i = 0; i < n; i++) {
			cout << style(' ', 30) << winners_list[i].get_id() << "\t" << winners_list[i].get_fullname() << style(' ', 25 - winners_list[i].get_fullname().length()) << winners_list[i].getscore() << style(' ', 21 - (to_string(winners_list[i].getscore()).length())) << winners_list[i].getstrikes() << style(' ', 14 - (to_string(winners_list[i].getstrikes()).length())) << setprecision(3) << (float)winners_list[i].getscore() / winners_list[i].getstrikes() << endl;
		}

		cout << "\nLoser\n";
		Player* temp = players.get_front();
		float avg;
		if (temp != nullptr) {
			do {
				if (temp->getstrikes() == 0)
					avg = 0.00;
				else
					avg = (float)temp->getscore() / temp->getstrikes();

				cout << style(' ', 30) << temp->get_id() << "\t" << temp->get_fullname() << style(' ', 25 - temp->get_fullname().length()) << temp->getscore() << style(' ', 21 - (to_string(temp->getscore()).length())) << temp->getstrikes() << style(' ', 14 - (to_string(temp->getstrikes()).length())) << setprecision(3) << avg << endl;
				temp = temp->get_next();
			} while (temp != players.get_front());
		}
	}
}
