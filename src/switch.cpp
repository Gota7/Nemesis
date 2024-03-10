#include "switch.hpp"

#include "game.hpp"
#include "scenario.hpp"

Switch::Switch(Scenario& scenario, std::vector<PTR<Wall>>&& walls, const std::vector<std::pair<NemesisType, Color>>& nemesisTypes, const glm::vec2& pos, const std::optional<std::string>& wallsAnimName, float timer, bool flipWall, Color color) :
    scenario(scenario),
    animator(scenario.game.holderTex, "blob", FRAME_TIME_DEFAULT),
    numbers(scenario.game.holderTex, glm::vec2(0.0f), 0, color),
    wallsAnim(wallsAnimName ? PTR_MAKE(Animator, scenario.game.holderTex, *wallsAnimName, FRAME_TIME_DEFAULT) : nullptr),
    walls(std::move(walls)),
    nemesisTypes(nemesisTypes),
    pos(pos),
    timer(timer),
    color(color),
    flipWall(flipWall)
{
    for (auto& actor : scenario.actors)
    {
        Player* player = dynamic_cast<Player*>(actor.get());
        if (player) playerBodies.push_back(&player->body);
    }
    hitbox.x = animator.textures[0]->tex.width / 2.0f;
    hitbox.y = animator.textures[0]->tex.height / 2.0f;
    numbers.pos = pos - hitbox + glm::vec2(15.0f, -10.0f);
}

void Switch::Draw()
{
    if (!active) animator.DrawPositioned(pos - hitbox, color);
    if (wallsAnim) wallsAnim->DrawPositioned(glm::vec2(0.0f), (flipWall != active) ? Color { color.r, color.g, color.b, 50 } : color);
    if (currTime > 0.0f)
    {
        numbers.num = (int)(currTime + 0.99f);
        numbers.Draw();
    }
}

void SwitchReset(Switch& sw)
{
    sw.currTime = 0.0f;
    std::size_t ind = 0;
    std::size_t currActorInd = 0;
    for (auto& nemesis : sw.nemesisTypes)
    {
        for (;currActorInd < sw.scenario.actors.size(); currActorInd++)
        {
            Nemesis* n = dynamic_cast<Nemesis*>(sw.scenario.actors[currActorInd].get());
            if (!n) continue;
            std::swap(nemesis.first, n->type);
            n->color.a = 255;
            n->harmless = false;
        }
        ind++;
    }
    for (int i = (int)sw.nemesisToKill.size() - 1; i >= 0; i--)
    {
        sw.scenario.actors.erase(sw.scenario.actors.begin() + sw.nemesisToKill[i]);
    }
    sw.scenario.haltUpdate = true;
    sw.nemesisToKill.clear();
    Color col;
    for (auto& actor : sw.scenario.actors)
    {
        Player* player = dynamic_cast<Player*>(actor.get());
        if (player)
        {
            col = player->color;
            player->color = sw.color;
        }
    }
    sw.color = sw.numbers.color = col;
    sw.active = false;
}

void SwitchActivate(Switch& sw)
{
    sw.currTime = sw.timer;
    std::size_t currActorInd = 0;
    for (auto& nemesis : sw.nemesisTypes)
    {
        for (;currActorInd < sw.scenario.actors.size(); currActorInd++)
        {
            Nemesis* n = dynamic_cast<Nemesis*>(sw.scenario.actors[currActorInd].get());
            if (!n) continue;
            sw.nemesisToKill.push_back(sw.scenario.actors.size());
            sw.scenario.actors.emplace_back(PTR_MAKE(Nemesis,
                sw.scenario,
                n->path ? n->path->Copy() : nullptr,
                n->racerPath ? n->racerPath->Copy() : nullptr,
                n->body.prevPos,
                n->axis,
                n->shootDir,
                n->delay,
                n->fireDelay,
                n->speed,
                nemesis.first,
                nemesis.second
            ));
            nemesis.first = n->type;
            n->color.a = 50;
            n->harmless = true;
            currActorInd++;
            break;
        }
    }
    Color col;
    for (auto& actor : sw.scenario.actors)
    {
        Player* player = dynamic_cast<Player*>(actor.get());
        if (player)
        {
            col = player->color;
            player->color = sw.color;
        }
    }
    sw.color = sw.numbers.color = col;
    sw.active = true;
    sw.scenario.haltUpdate = true;
}

void Switch::Update(float dt)
{
    animator.Update(dt);
    numbers.Update(dt);
    if (wallsAnim) wallsAnim->Update(dt);
    if (currTime > 0.0f)
    {
        currTime -= dt;
        if (currTime <= 0.0f) SwitchReset(*this);
    }

    // OH BREAK THE WALLS.
    if (active == flipWall)
    {
        for (auto& wall : walls)
        {
            if (wall) wall->Update(dt);
        }
    }

    // Check if switch has been hit.
    if (active) return;
    float rad = (hitbox.x + hitbox.y) / 2.0f;
    for (auto body : playerBodies)
    {
        glm::vec2 diff = pos - body->prevPos;
        if (glm::length(diff) <= rad + PLAYER_RAD) // See THIS is how I should be mathing.
        {
            SwitchActivate(*this);
            return;
        }
    }

}