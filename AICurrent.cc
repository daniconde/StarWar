#include "Player.hh"
#include <vector>
#include <stack>
#include <queue>
#include <complex>
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
    Dir movez = UP;
    Player_Id myId;
    int n_rocket_plus;
    int n_coins;
    int n_players;
    set<Player_Id>Ids;
    set<Starship_Id> enemies;
    set<Starship_Id> allies;
    complex<int> map_dimensions;
    complex<int> win_dimensions;
    map<int, bool> map_registry;
    /**
     * Attributes for your player can be defined here.
     */
    void get_allies(){
        for (Starship_Id sid = begin(myId); sid < end(myId); ++sid){
            allies.insert(sid);
        }
    }

    void read_map(){
        for (int i = 0; i < map_dimensions.first){
            for (int j = 0; j < map_dimensions.second){
                Pos pos = {i, j};
                Cell c = c(pos);
                if (c.type = STARSHIP){
                    if (starship(c.sid))
                }

            }
        }
    }

    void initialize_game(){
        n_players = number_players;
        get_allies();
        map_dimensions = {number_rows(), number_universe_columns()};
        win_dimensions = {first(map_dimensions), number_window_columns()};
        read_map();
    }
    /**
     * Play method.
     *
     * This method will be invoked once per each round.
     * You have to read the board here to place your actions
     * for this round.
     *
     */
    virtual void play () {
        if (round() == 0) initialize_game();
    }


};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);

