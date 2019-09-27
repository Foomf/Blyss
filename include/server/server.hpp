#pragma once

#include <memory>

#include <uv.h>

namespace blyss::server
{
    using loop_ptr = std::unique_ptr<uv_loop_t, decltype(&uv_loop_close)>;

    class server
    {
        loop_ptr loop_;
        std::unique_ptr<uv_timer_t> frame_timer_;
        uint64_t previous_time_;
        bool show_slow_warning_;

        void check_too_slow();

    public:
        server();

        server(const server&) = delete;
        server(server&&) = delete;
        server& operator=(const server&) = delete;
        server& operator=(server&&) = delete;

        void reset_show_slow_warning();
        void frame();
        void run_frame() const;
        void run_forever() const;
    };
}
