#include "Player.hh"
#include <vector>
#include <stack>
#include <queue>
#include <complex>
#include <list>
#include <map>
using namespace std;


/**
 * Write the name of your player and save this file
 * as AI<name>.cc
 */
#define PLAYER_NAME Null





struct PLAYER_NAME : public Player {
    /**
     * Factory: returns a new instance of this class.
     * Do not modify this function.
     */
    static Player* factory () {
        return new PLAYER_NAME;
    }

    /*---------------------EDIT FROM HERE--------------------------------------*/

bool initial_control = true;
//A step is an action, which can be a move in dir if (is_move) or a shoot
struct Step {
    bool is_move;
    Dir dir;
};

//A mision consists of a list of steps to reach a position objective
struct Mission {
    list<Step> steps;
    Pos objective;
};

struct Assignament {
    Mission mission;
    Starship_Id sid;
};

//A tactic cell contains the predicted dangers for that cell and auxiliary info used
//by starships to calculate paths
struct TacticalCell{
    //First element indicates the round in which the cell will be inaccesible
    //This danger is only valid if round() equals the second value.
    map<int, int> dangers;

    //Auxiliary values for starship pathing
    int distance;
    Starship_Id updater;
    int round;
};




//Stores me()
Player_Id myId;

//Stores the Starship_Ids of enemoy starships.
set<Starship_Id> enemies;

//Stores round() at the start of each round
int myround;

//Stores the Starships_Ids of allies, along with their current missions.
vector<Assignament> assignament;

//Stores information about the map, distribted in tactical cells.
vector< vector<TacticalCell> > tactical_map;

/**
 * Attributes for your player can be defined here.
 */

//Get allies and game dimensions
void initialize_game();

//Draw danger zones into tactical map;
void draw_dangers();

//Writes into assignament a mission for the specified starship
Mission get_mission(Starship_Id sid);

//Does the action specified by step. If it coudln't be done, returns false
bool do_step(Assignament &assignament);

virtual void play () {
    if (initial_control) initialize_game();
    draw_dangers();
    for (int i = 0; i < assignament.size(); ++i){
        Starship ship = starship(assignament[i]);
        if (ship.alive and not do_step(assignament[i])){
            assignament[i].mission = get_mission(assignament[i].sid);
            do_step(assignament[i]);
        }
    }
}

Mission get_mission(Starship_Id sid){
    Pos pos =
}

void initialize_game(){
    //Get ally Starship_Ids into mission_of
    if (round() == 0){
        myId = me();
        int n_spp = number_starships_per_player();
        mission_of.resize(n_spp);
        Starship_Id bsid = begin(myId);
        Starship_Id esid = end(myId);
        for (Starship_Id sid = bsid; sid < esid; ++sid){
            assignament[sid - bsid].sid = sid;
        }
    }
    //Get map and window dimensions
    //map_dimensions = {number_rows(), number_universe_columns()};
    //win_dimensions = {first(map_dimensions), number_window_columns()};

    //Get enemy Starship_Ids into enemy;
    Pos win_dimensions = {number_rows(), number_window_columns()};
    int n_p = number_players() - enemies.size();
    int i = 0;
    while (i < first(win_dimensions) and n_p > 0){
        int j = 0;
        while (j < second(win_dimensions) and n_p > 0){
            Cell c = cell(Pos{i, j});
            if (c.type == STARSHIP and player_of(c.sid) != myId
            and enemies.find(player_of(c.sid)) != enemies.end()){
                --n_p;
                enemies.insert(player_of(c.sid));
            }
            ++j;
        }
        ++i;
    }
    if (n_p == 0) initial_control = false;
}


void draw_dangers(){
    map<Missile_Id, Missile> mymissiles = missiles();
    map<Missile_Id, Missile>::const_iterator mis_it = mymissiles.begin();
    map<Missile_Id, Missile>::const_iterator mis_fi = mymissiles.end();
    while (mis_it != mis_fi){
        /*!!!!!!!!!!!!!!!!*/
        trace_missile_path(*mis_it);
        ++mis_it;
    }
    set<Starship_Id>::const_iterator ene_it = enemies.begin();
    set<Starship_Id>::const_iterator ene_fi = enemies.end();
    while (ene_it != ene_fi){
        /*!!!!!!!!!!!!!!!*/
        trace_enemy_danger(*ene_it);
        ++ene_it;
    }
}







};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);

