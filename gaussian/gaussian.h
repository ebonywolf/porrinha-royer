#ifndef RANDOM_PLAYER_H
#define RANDOM_PLAYER_H

#include <random>
#include "player.h"

namespace royer {

    class GaussianPlayer : public Player {
        std::mt19937 rng;
        std::string _name;

        /* Returns a new random number with maximum value 'max'.
         * The distribution of this random number is uniform.
         */
        int random( int max );

        /* Generate a rangom guess for the game.
         * There is no guarantee that the generated guess is valid.
         */
        int generate_guess();

    public:
        GaussianPlayer( unsigned long long seed, std::string name );

        std::string name() const override;
        void begin_game() override;
        int hand() override;
        int guess() override;
        void end_round() override;
        void end_game() override;
    };

} // namespace random_player

#endif // RANDOM_PLAYER_H
