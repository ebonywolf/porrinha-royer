#include <chrono>
#include <cstdlib>
#include <iostream>
#include "gaussian.h"
#include "ai.h"

namespace royer {

    const char gaussian_help_message[] =
"[gaussian] options\n"
"Creates a random artificial intelligence based on the normal distribution\n"
"(the Gauss bell curve).\n"
"\n"
"Options:\n"
"\n"
"--name <player_name>\n"
"    Changes the player name.\n"
"    Default: Gauss.\n"
"\n"
"--seed <N>\n"
"    Chooses N as the initial seed.\n"
"    Default: based on current time.\n"
"\n"
"--help\n"
"    Display this help and quit.\n"
;

    Player * generateGauss( cmdline::args&& args ) {
        bool seed_set = false;
        unsigned long long seed = 
            std::chrono::system_clock::now().time_since_epoch().count();
        std::string name = "Gauss";

        while( args.size() > 0 ) {
            std::string arg = args.next();
            if( arg == "--help" ) {
                std::cout << gaussian_help_message;
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
            std::cout << "[gaussian]: Unknown option " << arg << '\n';
            std::exit(1);
        }

        if( !seed_set )
            std::cout << "[gaussian]: Using seed " << seed << '\n';

        return new GaussianPlayer( seed, name );
    }

} // namespace random_player
