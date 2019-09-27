#pragma once

#include <cstdint>
#include <memory>

#include <uv.h>

namespace blyss::server
{

    class perf_watcher : public std::enable_shared_from_this<perf_watcher>
    {
        uv_loop_t* loop_;
        std::uint64_t ms_per_frame_;
        std::uint64_t previous_time_;
        bool show_slow_warning_ = true;
        std::uint64_t slow_warning_reset_ms_;

    public:
        perf_watcher(uv_loop_t* loop, std::uint64_t ms_per_frame, std::uint64_t slow_warning_reset_ms);

        void update();

        void reset();
    };
}
