#include "server/server.hpp"

#include <spdlog/spdlog.h>

namespace blyss::server
{
    const std::uint64_t ms_per_frame = 50;

    void timer_callback(uv_timer_t* handle)
    {
        const auto self = static_cast<server*>(handle->data);
        self->frame();
    }

    server::server(uv_loop_t* loop)
        : loop_{loop}
        , perf_watcher_{loop_, ms_per_frame, 5000}
    {
        uv_timer_init(loop_, &frame_timer_);
    }

    server::~server()
    {
        uv_timer_stop(&frame_timer_);
    }

    void server::start()
    {
        frame_timer_.data = static_cast<void*>(this);
        uv_timer_start(&frame_timer_, timer_callback, 0, ms_per_frame + 20);
        perf_watcher_.start();
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
        perf_watcher_.update();
    }

    void server::stop()
    {
        uv_timer_stop(&frame_timer_);
    }

    world& server::get_world()
    {
        return world_;
    }
}