#pragma once
#include "core/Context.h"
#include "systems/SCollisionDetection.h"

struct SCollisionResponse {
    static void resolve(Context& ctx, std::vector<Contact>& contacts);
    static void resolveWallCollisions(Context& ctx);
};