#include "core/util.h"
#include "gaussian.h"

namespace royer {
    GaussianPlayer::GaussianPlayer( unsigned long long seed, std::string name ) :
        rng(seed),
        _name(name)
    {}

    int GaussianPlayer::random( int max ) {
        return std::uniform_int_distribution<int>(0, max)( rng );
    }

    int GaussianPlayer::generate_guess() {
        int sum = 0;
        for( int i = 0; i < core::player_count(); i++ )
            if( core::chopsticks(i) > 0 )
                sum += random(core::chopsticks(i));
        return sum;
    }

    std::string GaussianPlayer::name() const {
        return _name;
    }

    void GaussianPlayer::begin_game() {
        // no-op
    }

    int GaussianPlayer::hand() {
        return random(core::chopsticks(core::index(this)));
    }

    int GaussianPlayer::guess() {
        int guess = generate_guess();
        while( !core::valid_guess(guess) )
            guess = generate_guess();
        return guess;
    }

    void GaussianPlayer::end_round() {
        // no-op
    }

    void GaussianPlayer::end_game() {
        // no-op
    }

} // namespace royer
