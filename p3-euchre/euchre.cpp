// p3-euchre.cpp : This file contains the 'main' function
// Program execution begins and ends there.
// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include "vector"
#include "Pack.h"
#include "Player.h"
#include <fstream>

using namespace std;

class Game {
public:
    Game(string noshuffle, int points)
        :noshuffle(noshuffle), points(points) {}

    //Set up players
    void set_up(string p, string t) {
        players.push_back(Player_factory(p, t));
    }

    //Set up pack by reading in a file
    void set_up_pack(istream& file) {
        pack = Pack(file);
    }

    void play() {
        dealer = 0;
        Suit trump;
        int round = 0;

        while (point1 < points && point2 < points) {
            shuffle();
            deal(round);
            make_trump(trump, round);
            play_hand(trump);
            round++;
            dealer++;
            if (dealer == 4) {
                dealer = 0;
            }
        }

        if (point1 >= points) {
            cout << players[0]->get_name() << " and "
                << players[2]->get_name() << " win!" << endl << endl;
        }
        else {
            cout << players[1]->get_name() << " and "
                << players[3]->get_name() << " win!" << endl << endl;

        }
        for (size_t i = 0; i < players.size(); ++i) {
            delete players[i];
        }
    }

private:
    vector<Player*> players;
    Pack pack;
    string noshuffle;
    int points;
    int dealer = 0;
    int point1 = 0;
    int point2 = 0;
    int order_up_team = -1;

    void shuffle() {
        if (noshuffle == "noshuffle") {
            pack.reset();
        }
        else if (noshuffle == "shuffle") {
            pack.shuffle();
        }
    }

    void deal(int round) {
        int first = (dealer + 1) % 4;
        int second = (dealer + 2) % 4;
        int third = (dealer + 3) % 4;

        //First batch
        players[first]->add_card(pack.deal_one());
        players[first]->add_card(pack.deal_one());
        players[first]->add_card(pack.deal_one());
        players[second]->add_card(pack.deal_one());
        players[second]->add_card(pack.deal_one());
        players[third]->add_card(pack.deal_one());
        players[third]->add_card(pack.deal_one());
        players[third]->add_card(pack.deal_one());
        players[dealer]->add_card(pack.deal_one());
        players[dealer]->add_card(pack.deal_one());

        //Second Batch
        players[first]->add_card(pack.deal_one());
        players[first]->add_card(pack.deal_one());
        players[second]->add_card(pack.deal_one());
        players[second]->add_card(pack.deal_one());
        players[second]->add_card(pack.deal_one());
        players[third]->add_card(pack.deal_one());
        players[third]->add_card(pack.deal_one());
        players[dealer]->add_card(pack.deal_one());
        players[dealer]->add_card(pack.deal_one());
        players[dealer]->add_card(pack.deal_one());
    }


    int trump_one(Suit& order_up_suit, Card up_card, Suit& trump, int round) {
        for (int i = dealer + 1; i < players.size(); ++i) {
            if (players[i]->make_trump(up_card,
                i == dealer, round, order_up_suit)) {
                cout << players[i]->get_name() << " orders up "
                    << order_up_suit << endl << endl;
                trump = order_up_suit;
                if (round == 1) {
                    players[dealer]->add_and_discard(up_card);
                }
                return i;
            }
            else {
                cout << players[i]->get_name() << " passes" << endl;
            }
        }
        for (int i = 0; i <= dealer; ++i) {
            if (players[i]->make_trump(up_card,
                i == dealer, round, order_up_suit)) {
                cout << players[i]->get_name() << " orders up "
                    << order_up_suit << endl << endl;
                trump = order_up_suit;
                if (round == 1) {
                    players[dealer]->add_and_discard(up_card);

                }
                return i;
            }
            else {
                cout << players[i]->get_name() << " passes" << endl;
            }
        }
        return -1;
    }


    void make_trump(Suit& trump, int round) {
        int order_up_player = -1;
        Card up_card = pack.deal_one();
        cout << "Hand " << round << endl;
        cout << players[dealer]->get_name() << " deals" << endl;
        cout << up_card << " turned up" << endl;

        Suit order_up_suit;

        //Round1 Make Trump
        int round_temp = 1;
        order_up_player = trump_one(order_up_suit, up_card, trump, round_temp);
        //If someone orders up
        if (order_up_player != -1) {
            if (order_up_player % 2 == 0) {
                order_up_team = 1;
            }
            else {
                order_up_team = 2;
            }
            return;
        }

        //Round2 Make Trump
        ++round_temp;
        order_up_player = trump_one(order_up_suit, up_card, trump, round_temp);
        if (order_up_player % 2 == 0) {
            order_up_team = 1;
        }
        else {
            order_up_team = 2;
        }
    }



    int one_trick(int& t1_tricks, int& t2_tricks, int leader, Suit& trump) {
        Card lead = players[leader]->lead_card(trump);
        cout << lead << " led by " << players[leader]->get_name() << endl;
        Card max = lead;
        int max_ind = leader;
        Card temp;
        for (int i = leader + 1; i < players.size(); ++i) {
            temp = players[i]->play_card(lead, trump);
            cout << temp << " played by " << players[i]->get_name() << endl;
            if (Card_less(max, temp, lead, trump)) {
                max = temp;
                max_ind = i;
            }
        }
        for (int i = 0; i < leader; ++i) {
            temp = players[i]->play_card(lead, trump);
            cout << temp << " played by " << players[i]->get_name() << endl;
            if (Card_less(max, temp, lead, trump)) {
                max = temp;
                max_ind = i;
            }
        }
        if (max_ind % 2 == 0) {
            ++t1_tricks;
        }
        else {
            ++t2_tricks;
        }
        cout << players[max_ind]->get_name()
            << " takes the trick" << endl << endl;
        return max_ind;
    }


    void play_hand(Suit& trump) {
        int eldest = dealer + 1;
        int t1_tricks = 0;
        int t2_tricks = 0;
        if (eldest == players.size()) {
            eldest = 0;
        }
        int round = 0;
        int leader;
        leader = one_trick(t1_tricks, t2_tricks, eldest, trump);

        round = 1;

        while (round < 5) {
            leader = one_trick(t1_tricks, t2_tricks, leader, trump);
            ++round;
        }

        if (t1_tricks > t2_tricks) {
            cout << players[0]->get_name() << " and "
                << players[2]->get_name() << " win the hand" << endl;
            if (order_up_team == 1) {
                if (t1_tricks < 5) {
                    ++point1;
                }
                else {
                    point1 = point1 + 2;
                    cout << "march!" << endl;
                }
            }
            else {
                point1 = point1 + 2;
                cout << "euchred!" << endl;
            }
        }
        else {
            cout << players[1]->get_name() << " and "
                << players[3]->get_name() << " win the hand" << endl;
            if (order_up_team == 2) {
                if (t2_tricks < 5) {
                    ++point2;
                }
                else {
                    point2 = point2 + 2;
                    cout << "march!" << endl;

                }
            }
            else {
                point2 = point2 + 2;
                cout << "euchred!" << endl;

            }
        }
        cout << players[0]->get_name() << " and "
            << players[2]->get_name() << " have "
            << point1 << " points" << endl;
        cout << players[1]->get_name() << " and "
            << players[3]->get_name() << " have "
            << point2 << " points" << endl << endl;
    }
};

int main(int argc, char** argv) {
    // Read command line args and check for errors
    string file = argv[1];
    string noshuffle = argv[2];
    int points = atoi(argv[3]);

    //Check all assertions
    if (argc != 12) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
            << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
            << "NAME4 TYPE4" << endl;
        return 1;
    }
    if (noshuffle != "shuffle" && noshuffle != "noshuffle") {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
            << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
            << "NAME4 TYPE4" << endl;
        return 2;
    }
    if (points < 1 || points > 100) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
            << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
            << "NAME4 TYPE4" << endl;
        return 3;
    }

    for (int i = 5; i <= 11; i = i + 2) {
        string type = argv[i];
        if (type != "Human" && type != "Simple") {
            cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
                << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
                << "NAME4 TYPE4" << endl;
            return 3;
        }
    }

    //Verify the pack input file opens successfully
    ifstream ifs;
    ifs.open(file);
    if (!ifs.is_open()) {
        cout << "Error opening " << file << endl;
        return 1;
    }

    //Print the executable and all arguments on the first line.
    for (int i = 0; i < argc; ++i) {
        cout << argv[i] << " ";
    }
    cout << endl;


    Game game(noshuffle, points);
    game.set_up_pack(ifs);
    game.set_up(argv[4], argv[5]);
    game.set_up(argv[6], argv[7]);
    game.set_up(argv[8], argv[9]);
    game.set_up(argv[10], argv[11]);

    game.play();
    ifs.close();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files,
// or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again,
//go to File > Open > Project and select the .sln file