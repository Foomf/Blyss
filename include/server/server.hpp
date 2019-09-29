#pragma once

#include <memory>
#include <vector>

#include <uv.h>

#include "server/perf_watcher.hpp"
#include "server/world.hpp"
#include "server/i_player.hpp"

namespace blyss::server
{
    class server
    {
        uv_loop_t* loop_;
        uv_timer_t frame_timer_{};
        perf_watcher perf_watcher_;
        world world_{};
        std::vector<std::unique_ptr<i_player>> players_;

    public:
        explicit server(uv_loop_t* loop);
        ~server();

        server(const server&) = delete;
        server(server&&) = delete;
        server& operator=(const server&) = delete;
        server& operator=(server&&) = delete;

        void frame();
        void run_frame() const;
        void run_forever() const;
        void start();
        void stop();
        world& get_world();
        void add_player(std::unique_ptr<i_player> player);
    };
}
