#pragma once

#include <memory>

#include <uv.h>

#include "server/perf_watcher.hpp"

namespace blyss::server
{
    class server : public std::enable_shared_from_this<server>
    {
        uv_loop_t* loop_;
        uv_timer_t frame_timer_{};
        std::shared_ptr<perf_watcher> perf_watcher_;
        std::weak_ptr<server> self_ptr_;
        

    public:
        explicit server(uv_loop_t* loop);

        server(const server&) = delete;
        server(server&&) = delete;
        server& operator=(const server&) = delete;
        server& operator=(server&&) = delete;

        void frame();
        void run_frame() const;
        void run_forever() const;
        void start();
        void stop();
    };
}
