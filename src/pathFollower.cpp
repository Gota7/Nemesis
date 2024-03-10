#include "pathFollower.hpp"

PathFollower::PathFollower(const std::vector<glm::vec2>& points, std::size_t currPoint) : points(points), currPoint(currPoint)
{
    if (this->points.size() < 1) this->points.emplace_back(0.0f);
    if (this->points.size() < 2) this->points.emplace_back(this->points.back());
    std::size_t nextPoint = currPoint + 1;
    nextPoint %= this->points.size();
    glm::vec2 diff = points[currPoint] - points[nextPoint];
    distToNextPoint = glm::length(diff);
}

glm::vec2 PathFollower::Advance(float dist)
{
    distToNextPoint -= dist;
    std::size_t nextPoint = currPoint + 1;
    nextPoint %= points.size();
    glm::vec2 diff = points[nextPoint] - points[currPoint];
    float lenDiff = glm::length(diff);
    while (distToNextPoint <= 0.0f)
    {
        currPoint++;
        currPoint %= points.size();
        nextPoint = currPoint + 1;
        nextPoint %= points.size();
        diff = points[nextPoint] - points[currPoint];
        lenDiff = glm::length(diff);
        distToNextPoint += lenDiff;
    }
    float beta = distToNextPoint / lenDiff;
    return points[currPoint] * beta + points[nextPoint] * (1.0f - beta);
}

// std::vector<glm::vec2> PathFollower::GatherPartialEllipsePoints(const glm::vec2& center, float startRad, float endRad, float degress, std::size_t numPoints)
// {
//     assert(false);
//     return {};
// }