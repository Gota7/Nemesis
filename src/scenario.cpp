#include "scenario.hpp"

#include "animator.hpp"
#include "player.hpp"
#include <yaml-cpp/yaml.h>

using ScenarioLoadFunc = std::function<void(Scenario& scn, const YAML::Node& node)>;

void ScenarioLoadAnimator(Scenario& scn, const YAML::Node& node)
{
    scn.actors.push_back(PTR_MAKE(Animator, node["Name"].as<std::string>(), node["Time"].as<float>(), node["Lerp"].as<bool>()));
}

void ScenarioLoadPlayer(Scenario& scn, const YAML::Node& node)
{
    PTR<Player> player = PTR_MAKE(Player);
    player->body.pos = glm::vec2(node["X"].as<float>(), node["Y"].as<float>());
    scn.actors.push_back(std::move(player));
}

std::map<std::string, ScenarioLoadFunc> ACTOR_LOAD_FUNCS =
{
    { "Animator", ScenarioLoadAnimator },
    { "Player", ScenarioLoadPlayer },
};

Scenario::Scenario(Game& game, std::size_t num) : game(game)
{
    YAML::Node root = YAML::LoadFile("res/scn/" + std::to_string(num) + ".yaml");
    if (root["Actors"])
    {
        for (auto actor : root["Actors"])
        {
            std::string type = actor.first.as<std::string>();
            auto found = ACTOR_LOAD_FUNCS.find(type);
            if (found != ACTOR_LOAD_FUNCS.end()) found->second(*this, actor.second);
        }
    }
}

void Scenario::Draw()
{
    for (auto& actor : actors) actor->Draw();
}

void Scenario::Update(float dt)
{
    for (auto& actor : actors) actor->Update(dt);
}