#pragma once
#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <iomanip>
using namespace std;


class Player
{
	string fname;
	string lname;
	int id;
	int score;
	int prev_score;
	int strikes_taken;
	int age;
	int bestbreak;
	int worstbreak;

	Player *next, *prev;
	void allot_id();
	bool finished;

public:

	Player();
	void set_name(string, string);
	void set_prev(Player*);
	void set_next(Player*);
	void set_isfinished(bool);
	void set_bestbreak(int);
	void set_worstbreak(int);
	bool get_finish_status();
	Player* get_prev();
	Player* get_next();
	void update_scores(int);
	string get_fullname();
	void info();
	void input_info();
	int getscore();
	int getstrikes();
	void set_start_time();
	int get_id();
	int getbestbreak();
	int getworstbreak();
};


class Player_list
{
	Player* front;
	int no_of_players;

public:

	Player_list();
	void add_new_Player(Player*);
	void del_Player(Player*&);
	~Player_list();
	int get_no_of_players();
	Player* get_front();

	void operator=(const Player_list&);
};



class Game
{
	friend void Sort(Game&);
	int game_id;
	Player_list players;
	Player *players_array;
	Player* winners_list;


public:

	Game();
	void list_to_arr();
	void show_Scorecard();
	void play();
	void show_final_results(int);


};





