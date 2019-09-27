#include "server/perf_watcher.hpp"

#include <spdlog/spdlog.h>

namespace blyss::server
{
    const uint64_t frame_leeway = 10;

    struct reset_slow_warning_scope
    {
        std::shared_ptr<perf_watcher> self;
    };

    void reset_slow_warning_callback(uv_timer_t* handle)
    {
        auto scope = static_cast<reset_slow_warning_scope*>(handle->data);
        scope->self->reset();
        delete handle;
        delete scope;
    }

    perf_watcher::perf_watcher(uv_loop_t* loop, std::uint64_t ms_per_frame, std::uint64_t slow_warning_reset_ms)
        : loop_{loop}
        , ms_per_frame_{ms_per_frame}
        , previous_time_{ uv_now(loop_) }
        , slow_warning_reset_ms_{slow_warning_reset_ms}
    {
    }

    void perf_watcher::update()
    {
        const auto current_time = uv_now(loop_);
        const auto diff = current_time - previous_time_;
        previous_time_ = current_time;

        if (show_slow_warning_ && diff > ms_per_frame_ + frame_leeway)
        {
            show_message(diff - ms_per_frame_);
        }
    }

    void perf_watcher::reset()
    {
        show_slow_warning_ = true;
    }

    void perf_watcher::show_message(const std::uint64_t missed_ms)
    {
        spdlog::warn("Server is running {0:d} ms behind! Consider getting a faster cpu...", missed_ms);
        show_slow_warning_ = false;

        const auto handle = new uv_timer_t;
        uv_timer_init(loop_, handle);
        const auto scope = new reset_slow_warning_scope{ shared_from_this() };
        handle->data = static_cast<void*>(scope);
        uv_timer_start(handle, reset_slow_warning_callback, slow_warning_reset_ms_, 0);
    }

}