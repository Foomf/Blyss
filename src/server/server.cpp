#include "server/server.hpp"

#include <spdlog/spdlog.h>

namespace blyss::server
{
    void timer_callback(uv_timer_t* handle)
    {
        auto s = static_cast<server*>(handle->data);
        s->frame();
    }

    server::server()
        : loop_{loop_ptr(new uv_loop_t, uv_loop_close)}
        , frame_timer_{std::make_unique<uv_timer_t>()}
    {
        uv_loop_init(loop_.get());
        uv_timer_init(loop_.get(), frame_timer_.get());
        frame_timer_->data = static_cast<void*>(this);
        uv_timer_start(frame_timer_.get(), timer_callback, 0, 1000);
    }

    void server::run_frame() const
    {
        uv_run(loop_.get(), UV_RUN_NOWAIT);
    }

    void server::run_forever() const
    {
        uv_run(loop_.get(), UV_RUN_DEFAULT);
    }

    void server::frame()
    {
        spdlog::info("Frame!");
    }

}