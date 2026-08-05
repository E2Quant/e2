/*
 * =====================================================================================
 *
 *       Filename:  IoEventLoop.hpp
 *
 *    Description:  IoEventLoop
 *
 *        Version:  1.0
 *        Created:  2026/08/03 14时50分02秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  vyouzhi (vz), vyouzhi@gmail.com
 *   Organization:  Etomc2.com
 *        LICENSE:  BSD-3-Clause license
 *
 *  Copyright (c) 2019-2022, vyouzhi
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  * Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the distribution.
 *  * Neither the name of vyouzhi and/or the DataFrame nor the
 *  names of its contributors may be used to endorse or promote products
 *  derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL vyouzhi BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * =====================================================================================
 */

#ifndef IOEVENTLOOP_INC
#define IOEVENTLOOP_INC
#include <fcntl.h>
#include <poll.h>
#include <unistd.h>

#include <cstddef>
#include <functional>
#include <iostream>
#include <vector>

#include "utility/Log.hpp"
namespace e2 {
using EventCallback = std::function<void(int)>;

// Sets a file descriptor to non-blocking mode
static bool set_nonblocking(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) return false;
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK) == 0;
}

/*
 * ================================
 *        Class:  IoEventLoop
 *  Description:
 * ================================
 */
class IoEventLoop {
public:
    /* =============  LIFECYCLE     =================== */
    IoEventLoop() {}; /* constructor */

    /* =============  ACCESSORS     =================== */

    /* =============  MUTATORS      =================== */
    void add_read_fd(int fd, EventCallback callback)
    {
        if (!set_nonblocking(fd)) {
            std::cerr << "Failed to set fd " << fd << " to non-blocking.\n";
            return;
        }

        pollfd pfd{};
        pfd.fd = fd;
        pfd.events = POLLIN;  // Monitor for incoming data read availability
        pfd.revents = 0;

        fds_.push_back(pfd);
        callbacks_.push_back(callback);
    }

    // Runs the main event processing loop
    void run()
    {
        running_ = true;

        while (running_) {
            // Block indefinitely until at least one monitored event triggers
            // (-1 timeout)
            int num_events = poll(fds_.data(), fds_.size(), -1);

            if (num_events < 0) {
                if (errno == EINTR)
                    continue;  // Restart if interrupted by a signal
                llog::bug("poll() error occurred.");
                break;
            }

            // Iterate backwards to safely handle removals or loop modifications
            // during execution
            for (size_backwards_t i = fds_.size(); i > 0; --i) {
                size_t idx = i - 1;

                // Check if the OS flagged a read or error event on this
                // descriptor
                if (fds_[idx].revents & (POLLIN | POLLERR | POLLHUP)) {
                    // Dispatch the registered callback
                    callbacks_[idx](fds_[idx].fd);

                    // Clear out returned events for the next tick
                    fds_[idx].revents = 0;
                }
            }
        }
    }

    void stop() { running_ = false; }
    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */
    using size_backwards_t = std::size_t;
    std::vector<pollfd> fds_;
    std::vector<EventCallback> callbacks_;
    bool running_ = false;
}; /* -----  end of class IoEventLoop  ----- */

}  // namespace e2
#endif /* ----- #ifndef IOEVENTLOOP_INC  ----- */
