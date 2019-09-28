#include "server/server.hpp"

#include <spdlog/spdlog.h>

namespace blyss::server
{
    const std::uint64_t ms_per_frame = 50;

    void timer_callback(uv_timer_t* handle)
    {
        const auto data = *static_cast<std::weak_ptr<server>*>(handle->data);
        if (auto s = data.lock())
        {
            s->frame();
        }
    }

    server::server(uv_loop_t* loop)
        : loop_{loop}
        , frame_timer_{std::make_unique<uv_timer_t>()}
        , perf_watcher_{std::make_unique<perf_watcher>(loop_, ms_per_frame, 5000)}
    {
        uv_timer_init(loop_, frame_timer_.get());
    }

    void server::start()
    {
        self_ptr_ = shared_from_this();
        frame_timer_->data = static_cast<void*>(&self_ptr_);
        uv_timer_start(frame_timer_.get(), timer_callback, 0, ms_per_frame);
        perf_watcher_->start();
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
        perf_watcher_->update();
    }

    void server::stop() const
    {
        uv_timer_stop(frame_timer_.get());
    }
}