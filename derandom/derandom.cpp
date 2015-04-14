#include "core/util.h"
#include "derandom.h"

namespace royer {
    bool DerandomPlayer::quantile::is_gaussian() const {
        /* We will consider that the player is gaussian
         * if the difference between the internal quantiles and external quantiles
         * is greater than 12.5%.
         *
         * (The value 12.5% is purely arbitrary.)
         */
        return std::fabs(internal - external)/(internal + external) > 0.125;
    }

    DerandomPlayer::DerandomPlayer( unsigned long long seed, std::string name ) :
        rng(seed),
        _name(name)
    {}

    int DerandomPlayer::random( int max ) {
        return std::uniform_int_distribution<int>(0, max)( rng );
    }

    void DerandomPlayer::compute_counts() {
        gaussian_count = random_count = 0;
        for( int i = 0; i < core::player_count(); i++ ) {
            if( i == my_index )
                continue;
            if( core::guess(i) == core::NOT_PLAYING )
                continue;
            if( !quantiles[i].already_played )
                continue;
            gaussian_count += quantiles[i].is_gaussian();
            random_count += !quantiles[i].is_gaussian();
        }
    }


    std::string DerandomPlayer::name() const {
        return _name;
    }

    void DerandomPlayer::begin_game() {
        my_index = core::index(this);
        quantiles = std::vector<quantile>(core::player_count());
    }

    int DerandomPlayer::hand() {
        compute_counts();
        if( gaussian_count == 0 && random_count == 0 ) 
            /* No data information. Let's be pure random. */
            my_hand = random(core::chopsticks(my_index));
        else if( gaussian_count == 0 )
            /* No gaussians. Let's try to push the final number
             * as close to the mean as possible,
             * so that we may guess right, while the others will guess randomly.
             */
            my_hand = core::chopsticks(my_index)/2;
        else if( random_count == 0 )
            /* All gaussians. Let's try to move the final value
             * as further from the mean as possible. */
            my_hand = random(1) * core::chopsticks(my_index)/2;
        else
            /* Mixed gaussians/pure randoms. Let's be pure random. */
            my_hand = random(core::chopsticks(my_index));

        return my_hand;
    }

    int DerandomPlayer::guess() {
        /* Guess algorithm chosen arbitrarily.
         *
         * The player will begin by guessing the central value,
         * then central + 1, central - 1, central + 2, central - 2, etc.
         */
        int min = my_hand;
        int max = core::chopstick_count() - core::chopsticks(my_index) + my_hand;
        int guess = (max + min) / 2;
        int shift = 1;
        while( !core::valid_guess(guess) ) {
            guess += shift;
            shift = - 1 - shift;
        }
        return guess;
    }

    void DerandomPlayer::end_round() {
        for( int i = 0; i < core::player_count(); i++ ) {
            if( i == my_index )
                continue;
            if( core::guess(i) < 0 )
                continue;

            // TODO: implement correctly the algorithm described in derandom.h
            double half = core::chopstick_count() / 2.0;
            int guess = core::guess(i);
            double dist = std::fabs( half - guess ) / half;
            /* dist is 0 if half == guess,
             * and 1 if guess == 0 or guess == max. */
            quantiles[i].internal += dist;
            quantiles[i].external += 1 - dist;
            quantiles[i].already_played = true;
        }
    }

    void DerandomPlayer::end_game() {
        // no-op
    }

} // namespace royer
