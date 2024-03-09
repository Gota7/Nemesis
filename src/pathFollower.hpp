#pragma once

#include <glm/glm.hpp>
#include <vector>

// For anything following a path.
struct PathFollower
{
    std::vector<glm::vec2> points;
    std::size_t currPoint;
    float distToNextPoint;

    // Make a new path follower.
    PathFollower(const std::vector<glm::vec2>& points, std::size_t currPoint = 0);

    // Advance position.
    glm::vec2 Advance(float dist);

    // Get eliptical points. Can shrink or grow radius based on this approach.
    static std::vector<glm::vec2> GatherPartialEllipsePoints(const glm::vec2& center, float startRad, float endRad, float degress, std::size_t numPoints);

};