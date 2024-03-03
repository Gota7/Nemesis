#include "nemesis.hpp"

#include "player.hpp"
#include "scenario.hpp"

Nemesis::Nemesis(Scenario& scenario, const glm::vec2& pos, const glm::vec2& axis, float delay) : axis(axis)
{
    queueSize = (std::size_t)(delay * FPS) + 1;
    posQueue = PTR_MAKE(glm::vec2[], queueSize);
    body.pos = body.prevPos = pos;
    for (auto& actor : scenario.actors)
    {
        Player* player = dynamic_cast<Player*>(actor.get());
        if (!player) continue;
        toFollow = &player->body;
        prevPos = player->body.prevPos;
        return;
    }
    DBG_PRINT("ERR: Nemesis can only be placed *after* a player!");
    toFollow = nullptr;
}

void Nemesis::Draw()
{
    glm::vec2 pos = body.pos - glm::vec2(PLAYER_RAD, PLAYER_RAD);
    DrawRectangleV(VEC_CAST(pos), { PLAYER_RAD * 2.0f, PLAYER_RAD * 2.0f }, GREEN);
}

void Nemesis::Update(float dt)
{
    if (!toFollow) return;
    if (initRun)
    {
        posQueue[posInd++] = toFollow->prevPos; // Use previous position as it is always guaranteed to be in a legal spot.
        if (posInd >= queueSize)
        {
            posInd = 0;
            initRun = false;
        }
        return;
    }
    glm::vec2 newPos = posQueue[posInd];
    posQueue[posInd++] = toFollow->prevPos;
    posInd %= queueSize; // Micro-optimization case study would be interesting on if this is faster than branching.

    // Follow.
    glm::vec2 vel = newPos - prevPos;
    if (axis.x == 0.0f && axis.y == 0.0f) body.vel = vel;

    // Reflect along axis. https://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector
    else
    {
        body.vel = vel - 2.0f * glm::dot(vel, axis) * axis; // r = v - 2(v dot a)a
    }
    body.vel *= (float)FPS; // Scale for each frame.
    body.Move(dt);
    prevPos = newPos;

    // HAWHAW.
    glm::vec2 dist = toFollow->prevPos - body.pos;
    if (glm::dot(dist, dist) <= PLAYER_RAD * PLAYER_RAD * 3.5) toFollow->flags |= Flags::FLAGS_SHALL_DIE;

}