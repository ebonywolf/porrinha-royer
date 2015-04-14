#ifndef ROYER_NULLSTREAM_H
#define ROYER_NULLSTREAM_H

#include <iostream>

namespace royer {
    /* This stream is unopened; this means it will print nothing
     * to anywhere, effectively working as a '/dev/null' of streams.
     */
    extern std::ostream null_stream;
} // namespace royer

#endif // ROYER_NULLSTREAM_H
