#include "server/server.hpp"

#include <spdlog/spdlog.h>

namespace blyss::server
{
    const uint64_t ms_per_frame = 50;
    const uint64_t frame_leeway = 10;
    const uint64_t slow_warning_reset_ms = 5000;

    struct reset_slow_warning_scope
    {
        std::shared_ptr<server> server;
    };

    struct timer_scope
    {
        std::shared_ptr<server> server;
    };

    void timer_callback(uv_timer_t* handle)
    {
        auto s = static_cast<timer_scope*>(handle->data);
        s->server->frame();
    }

    void reset_slow_warning_callback(uv_timer_t* handle)
    {
        auto s = static_cast<reset_slow_warning_scope*>(handle->data);
        s->server->reset_show_slow_warning();
        delete handle;
        delete s;
    }

    server::server(uv_loop_t* loop)
        : loop_{loop}
        , frame_timer_{std::make_unique<uv_timer_t>()}
        , previous_time_{0}
        , show_slow_warning_{true}
    {
        uv_loop_init(loop_);
        previous_time_ = uv_now(loop_);

        uv_timer_init(loop_, frame_timer_.get());
    }

    void server::start()
    {
        const auto scope = new timer_scope{ shared_from_this() };
        frame_timer_->data = static_cast<void*>(scope);
        uv_timer_start(frame_timer_.get(), timer_callback, 0, ms_per_frame + 20);
    }

    void server::run_frame() const
    {
        uv_run(loop_, UV_RUN_NOWAIT);
    }

    void server::run_forever() const
    {
        uv_run(loop_, UV_RUN_DEFAULT);
    }

    void server::frame()
    {
        check_too_slow();
    }

    void server::check_too_slow()
    {
        const auto current_time = uv_now(loop_);
        const auto diff = current_time - previous_time_;
        if (show_slow_warning_ && diff > ms_per_frame + frame_leeway)
        {
            const auto missed_ms = diff - ms_per_frame;
            spdlog::warn("Server is running {0:d} ms behind! Consider getting a faster cpu...", missed_ms);
            show_slow_warning_ = false;

            const auto handle = new uv_timer_t;
            uv_timer_init(loop_, handle);
            const auto scope = new reset_slow_warning_scope{ shared_from_this() };
            handle->data = static_cast<void*>(scope);
            uv_timer_start(handle, reset_slow_warning_callback, slow_warning_reset_ms, 0);
        }
        previous_time_ = current_time;
    }

    void server::reset_show_slow_warning()
    {
        show_slow_warning_ = true;
    }

    void server::stop() const
    {
        uv_timer_stop(frame_timer_.get());
        delete static_cast<timer_scope*>(frame_timer_->data);
    }
}