#include "nemesis.hpp"

#include "game.hpp"
#include "player.hpp"
#include "scenario.hpp"

Nemesis::Nemesis(Scenario& scenario, PTR<PathFollower> path, PTR<PathFollower> racerPath, const glm::vec2& pos, const glm::vec2& axis, const glm::vec2& shootDir, float delay, float speed, NemesisType type, Color color) :
    scenario(scenario),
    animator(scenario.game.holderTex, "nemesis", FRAME_TIME_DEFAULT),
    path(std::move(path)),
    racerPath(std::move(racerPath)),
    axis(glm::normalize(axis)),
    shootDir(glm::normalize(shootDir)),
    speed(speed),
    color(color),
    type(type)
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
    animator.DrawPositioned(body.pos - glm::vec2(animator.textures[0]->tex.width, animator.textures[0]->tex.height) / 2.0f, color);
}

void NemesisMirror(Nemesis& nemesis, const glm::vec2& newPos, float dt)
{

    // Follow.
    glm::vec2 vel = newPos - nemesis.prevPos;
    if (nemesis.axis.x == 0.0f && nemesis.axis.y == 0.0f) nemesis.body.vel = vel;

    // Reflect along axis. https://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector
    else nemesis.body.vel = vel - 2.0f * glm::dot(vel, nemesis.axis) * nemesis.axis; // r = v - 2(v dot a)a
    nemesis.body.vel *= (float)FPS; // Scale for each frame.
    nemesis.body.Move(dt);

}

void NemesisChase(Nemesis& nemesis, const glm::vec2& newPos, float dt)
{

    // Go chase after the target.
    nemesis.body.vel = glm::normalize(newPos - nemesis.body.prevPos) * nemesis.speed;
    nemesis.body.Move(dt);

}

// Update the nemesis along a path,
void NemesisPath(Nemesis& nemesis, float dt)
{

    // Follow the path.
    if (!nemesis.path) return;
    nemesis.body.pos = nemesis.path->Advance(nemesis.speed * dt);
    nemesis.body.Move(0.0f); // To update anything needed.

}

void NemesisTank(Nemesis& nemesis, const glm::vec2&, float)
{

    // Shoot at the player.
    if (nemesis.shootDir == glm::vec2(0.0f)) do {} while (0); // TODO: SPAWN BULLET!!!
    assert(false);

}

void NemesisRacer(Nemesis& nemesis, float dt)
{

    // Time to race the player.
    if (!nemesis.racerPath) return;
    nemesis.body.pos = nemesis.path->Advance(nemesis.speed * dt);
    nemesis.body.Move(0.0f); // Update anything needed.
    float width = nemesis.animator.textures[0]->tex.width / 2.0f;
    float height = nemesis.animator.textures[0]->tex.height / 2.0f;
    if (nemesis.body.pos.x < -width || nemesis.body.pos.x >= RES_WIDTH + width || nemesis.body.pos.y < -height || nemesis.body.pos.y >- RES_HEIGHT + height) nemesis.scenario.game.Reload();

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

    // Switch type.
    switch (type)
    {
        case NemesisType::Mirror:
            NemesisMirror(*this, newPos, dt);
            break;
        case NemesisType::Chase:
            NemesisChase(*this, newPos, dt);
            break;
        case NemesisType::Path:
            NemesisPath(*this, dt);
            break;
        case NemesisType::Tank:
            NemesisTank(*this, newPos, dt);
            break;
        case NemesisType::Racer:
            NemesisRacer(*this, dt);
            break;
        default: // Frozen does nothing, what did you expect?
            break;
    }
    prevPos = newPos;

    /*
        I just realized this formula makes no sense because I was working with squares nvm I'm too far gone in level dev.
        See the true formula is collide if len(diff) <= rad1 + rad2.
        Since rad1 + rad2 ~= 2 rad1, this formula I made by accident works in a roundabout way.
        THINK. It is NOT a legal operation to square both sizes Gota!!!
        That's why the factor of 3.5 being < 4 is necessary lol.
        Next time when you optimize, actually make sure the math checks out?
    */
    glm::vec2 dist = toFollow->prevPos - body.pos;
    if (glm::dot(dist, dist) <= PLAYER_RAD * PLAYER_RAD * 3.5) toFollow->flags |= Flags::FLAGS_SHALL_DIE;

}