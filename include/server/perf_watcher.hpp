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
        bool show_slow_warning_ = false;
        std::uint64_t slow_warning_reset_ms_;
        uv_timer_t show_warning_timer_{};
        std::weak_ptr<perf_watcher> self_ptr_;

        void show_message(std::uint64_t missed_ms);

    public:
        perf_watcher(uv_loop_t* loop, std::uint64_t ms_per_frame, std::uint64_t slow_warning_reset_ms);
        ~perf_watcher() = default;

        perf_watcher(const perf_watcher&) = delete;
        perf_watcher(perf_watcher&&) = delete;
        perf_watcher& operator=(const perf_watcher&) = delete;
        perf_watcher& operator=(perf_watcher&&) = delete;

        void update();

        void reset();

        void start();
    };
}
