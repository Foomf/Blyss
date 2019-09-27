#include "server/server.hpp"

#include <spdlog/spdlog.h>

namespace blyss::server
{
    const std::uint64_t ms_per_frame = 50;

    struct timer_scope
    {
        std::shared_ptr<server> server;
    };

    void timer_callback(uv_timer_t* handle)
    {
        auto s = static_cast<timer_scope*>(handle->data);
        s->server->frame();
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
        perf_watcher_->update();
    }

    void server::stop() const
    {
        uv_timer_stop(frame_timer_.get());
        delete static_cast<timer_scope*>(frame_timer_->data);
    }
}