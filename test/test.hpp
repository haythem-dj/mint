#pragma once

#include <mint/mint.hpp>

#include "player.hpp"

class test : public mnt::application
{
public:
    b8 initialize() override;
    void shutdown() override;
    void update(f32 dt) override;
    void render() override;
    void on_event(mnt::event& event) override;

private:
    mnt::engine* m_engine = nullptr;
    mnt::graphics::renderer* m_renderer = nullptr;

    player m_player;
};