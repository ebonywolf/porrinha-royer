#include <chrono>
#include <cstdlib>
#include <iostream>
#include "derandom.h"
#include "ai.h"

namespace royer {

    const char derandom_help_message[] =
"[derandom] options\n"
"Creates a 'derandom' artificial intelligence,\n"
"an intelligence desingned to beat random AIs.\n"
"\n"
"The AI tries to fit its oponents into totally random\n"
"and gaussian-like players, and play against them.\n"
"\n"
"Options:\n"
"\n"
"--name <player_name>\n"
"    Changes the player name.\n"
"    Default: Derandom.\n"
"\n"
"--seed <N>\n"
"    Chooses N as the initial seed for the random moves.\n"
"    Default: based on current time.\n"
"\n"
"--keep\n"
"    This player will keep collected statistics between games.\n"
"    Default: do not keep.\n"
"\n"
"--verbose\n"
"    Prints the decision outcome to the screen.\n"
"    Default: silent.\n"
"\n"
"--help\n"
"    Display this help and quit.\n"
;

    Player * generateDerandom( cmdline::args&& args ) {
        bool seed_set = false;
        bool verbose = false;
        bool keep = false;
        unsigned long long seed = 
            std::chrono::system_clock::now().time_since_epoch().count();
        std::string name = "Derandom";

        while( args.size() > 0 ) {
            std::string arg = args.next();
            if( arg == "--help" ) {
                std::cout << derandom_help_message;
                std::exit(0);
            }
            if( arg == "--name" ) {
                name = args.next();
                continue;
            }
            if( arg == "--seed" ) {
                args >> seed;
                seed_set = true;
                continue;
            }
            if( arg == "--keep" ) {
                keep = true;
                continue;
            }
            if( arg == "--verbose" ) {
                verbose = true;
                continue;
            }
            std::cout << "[derandom]: Unknown option " << arg << '\n';
            std::exit(1);
        }

        if( !seed_set )
            std::cout << "[derandom]: Using seed " << seed << '\n';

        auto * ptr = new DerandomPlayer( seed, name, keep );
        if( verbose )
            ptr->out( std::cout );
        return ptr;
    }

} // namespace random_player
