#include "scenario.hpp"

#include "animator.hpp"
#include "gate.hpp"
#include "numbers.hpp"
#include "player.hpp"
#include <yaml-cpp/yaml.h>

namespace YAML
{
    template<>
    struct convert<Color>
    {
        static bool decode(const Node& node, Color& rhs)
        {
            if (!node.IsSequence() || node.size() != 4) return false;
            rhs.r = node[0].as<float>();
            rhs.g = node[1].as<float>();
            rhs.b = node[2].as<float>();
            rhs.a = node[3].as<float>();
            return true;
        }
    };
}

using ScenarioLoadFunc = std::function<void(Scenario& scn, const YAML::Node& node)>;

void ScenarioLoadAnimator(Scenario& scn, const YAML::Node& node)
{
    scn.actors.push_back(PTR_MAKE(Animator,
        node["Name"].as<std::string>(),
        node["Time"].as<float>(),
        node["Lerp"].as<bool>()
    ));
}

void ScenarioLoadGate(Scenario& scn, const YAML::Node& node)
{
    scn.actors.push_back(PTR_MAKE(Gate,
        scn,
        node["Name"].as<std::string>()
    ));
}

void ScenarioLoadNumber(Scenario& scn, const YAML::Node& node)
{
    scn.actors.push_back(PTR_MAKE(Numbers,
        glm::vec2(node["X"].as<float>(), node["Y"].as<float>()),
        node["Num"].as<unsigned int>(),
        node["Color"].as<Color>()
    ));
}

void ScenarioLoadPlayer(Scenario& scn, const YAML::Node& node)
{
    PTR<Player> player = PTR_MAKE(Player, scn, node["Color"].as<Color>());
    player->body.pos = glm::vec2(node["X"].as<float>(), node["Y"].as<float>());
    scn.actors.push_back(std::move(player));
}

std::map<std::string, ScenarioLoadFunc> ACTOR_LOAD_FUNCS =
{
    { "Animator", ScenarioLoadAnimator },
    { "Gate", ScenarioLoadGate },
    { "Number", ScenarioLoadNumber },
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