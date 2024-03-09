#include "scenario.hpp"

#include "animator.hpp"
#include "game.hpp"
#include "gate.hpp"
#include "mirror.hpp"
#include "nemesis.hpp"
#include "numbers.hpp"
#include "player.hpp"
#include "switch.hpp"
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
    template<>
    struct convert<glm::vec2>
    {
        static bool decode(const Node& node, glm::vec2& rhs)
        {
            if (!node.IsSequence() || node.size() != 2) return false;
            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            return true;
        }
    };
    template<>
    struct convert<Direction>
    {
        static bool decode(const Node& node, Direction& rhs)
        {
            if (!node.IsScalar()) return false;
            std::string name = node.as<std::string>();
            if (name == "Up") rhs = Direction::DIR_UP;
            else if (name == "Down") rhs = Direction::DIR_DOWN;
            else if (name == "Left") rhs = Direction::DIR_LEFT;
            else if (name == "Right") rhs = Direction::DIR_RIGHT;
            else return false;
            return true;
        }
    };
    template<>
    struct convert<NemesisType>
    {
        static bool decode(const Node& node, NemesisType& rhs)
        {
            if (!node.IsScalar()) return false;
            std::string name = node.as<std::string>();
            if (name == "Mirror") rhs = NemesisType::Mirror;
            else if (name == "Chase") rhs = NemesisType::Chase;
            else if (name == "Path") rhs = NemesisType::Path;
            else if (name == "Frozen") rhs = NemesisType::Frozen;
            else if (name == "Tank") rhs = NemesisType::Tank;
            else if (name == "Racer") rhs = NemesisType::Racer;
            else return false;
            return true;
        }
    };
}

using ScenarioLoadFunc = std::function<void(Scenario& scn, const YAML::Node& node)>;

void ScenarioLoadAnimator(Scenario& scn, const YAML::Node& node)
{
    scn.actors.push_back(PTR_MAKE(Animator,
        scn.game.holderTex,
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

void ScenarioLoadMirror(Scenario& scn, const YAML::Node& node)
{
    scn.actors.push_back(PTR_MAKE(Mirror,
        scn.game.holderTex,
        glm::vec2(node["X"].as<float>(), node["Y"].as<float>()),
        node["Dir"].as<glm::vec2>(),
        node["Color"].as<Color>()
    ));
}

template <typename T>
T ScenarioNodeOrDefault(const YAML::Node& node, const T& defaultVal)
{
    if (node.IsDefined()) return node.as<T>();
    else return defaultVal;
}

PTR<PathFollower> ScenarioLoadPathFollower(const YAML::Node& node)
{
    if (node.IsDefined()) return PTR_MAKE(PathFollower, node["Points"].as<std::vector<glm::vec2>>(), ScenarioNodeOrDefault<std::size_t>(node["StartNode"], 0));
    else return nullptr;
}

void ScenarioLoadNemesis(Scenario& scn, const YAML::Node& node)
{
    scn.actors.push_back(PTR_MAKE(Nemesis,
        scn,
        ScenarioLoadPathFollower(node["Path"]),
        ScenarioLoadPathFollower(node["RacerPath"]),
        node["X"].IsDefined() ? glm::vec2(node["X"].as<float>(), node["Y"].as<float>()) : glm::vec2(0.0f),
        ScenarioNodeOrDefault(node["Axis"], glm::vec2(0.0f)),
        ScenarioNodeOrDefault(node["ShootDir"], glm::vec2(0.0f)),
        ScenarioNodeOrDefault(node["Delay"], 0.0f),
        ScenarioNodeOrDefault(node["Speed"], 0.0f),
        ScenarioNodeOrDefault(node["Type"], NemesisType::Mirror),
        node["Color"].as<Color>()
    ));
}

void ScenarioLoadNumber(Scenario& scn, const YAML::Node& node)
{
    scn.actors.push_back(PTR_MAKE(Numbers,
        scn.game.holderTex,
        glm::vec2(node["X"].as<float>(), node["Y"].as<float>()),
        node["Num"].as<unsigned int>(),
        node["Color"].as<Color>()
    ));
}

void ScenarioLoadPlayer(Scenario& scn, const YAML::Node& node)
{
    scn.actors.push_back(PTR_MAKE(Player,
        scn,
        glm::vec2(node["X"].as<float>(), node["Y"].as<float>()),
        node["Color"].as<Color>()
    ));
}

std::vector<PTR<Wall>> ScenarioLoadWalls(Scenario& scn, const YAML::Node& node)
{
    std::vector<PTR<Wall>> ret;
    if (!node.IsDefined()) return ret;
    for (auto& wall : node)
    {
        ret.emplace_back(PTR_MAKE(Wall,
            scn,
            wall["Pos"].as<float>(),
            wall["LeftTopLimit"].as<float>(),
            wall["RightBottomLimit"].as<float>(),
            wall["Direction"].as<Direction>()
        ));
    }
    return ret;
}

std::vector<std::pair<NemesisType, Color>> ScenarioLoadNemesisTypes(const YAML::Node& node)
{
    std::vector<std::pair<NemesisType, Color>> ret;
    if (!node.IsDefined()) return ret;
    for (auto& nemesis : node)
    {
        ret.emplace_back(
            nemesis["Type"].as<NemesisType>(),
            nemesis["Color"].as<Color>()
        );
    }
    return ret;
}

void ScenarioLoadSwitch(Scenario& scn, const YAML::Node& node)
{
    scn.actors.push_back(PTR_MAKE(Switch,
        scn,
        ScenarioLoadWalls(scn, node["Walls"]),
        ScenarioLoadNemesisTypes(node["NemesisTypes"]),
        glm::vec2(node["X"].as<float>(), node["Y"].as<float>()),
        node["WallsAnim"].IsDefined() ? std::optional<std::string>(node["WallsAnim"].as<std::string>()) : std::nullopt,
        ScenarioNodeOrDefault(node["Timer"], 0.0f),
        node["FlipWall"].as<bool>(),
        node["Color"].as<Color>()
    ));
}

std::map<std::string, ScenarioLoadFunc> ACTOR_LOAD_FUNCS =
{
    { "Animator", ScenarioLoadAnimator },
    { "Gate", ScenarioLoadGate },
    { "Mirror", ScenarioLoadMirror },
    { "Nemesis", ScenarioLoadNemesis },
    { "Number", ScenarioLoadNumber },
    { "Player", ScenarioLoadPlayer },
    { "Switch", ScenarioLoadSwitch },
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
    for (auto& actor : actors)
    {
        actor->Update(dt);
        if (haltUpdate) break;
    }
    haltUpdate = false;
}