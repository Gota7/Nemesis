#include "mirror.hpp"

#include "random.hpp"

Mirror::Mirror(AssetHolder<Tex>& holderTex, const glm::vec2& startPos, const glm::vec2& dir, Color color, bool dirIsEndPos) : animator(holderTex, "mirror", FRAME_TIME_DEFAULT), color(color)
{
    glm::vec2 n = dirIsEndPos ? glm::normalize(dir - startPos) : glm::normalize(dir);
    float sign = (n.x < 0.0f) ? 1.0f : -1.0f;
    rot = glm::acos(glm::dot(n, glm::vec2(0.0f, 1.0f))) * RAD2DEG * sign; // Cos of angle between two vectors is (a dot b) / (mag(a) * mag(b)). Note we are using normalized vectors.
    glm::vec2 currPos = startPos;
    currPos.x -= animator.textures[0]->tex.width / 2.0f;
    float min = currPos.x;
    float advance = animator.textures[0]->tex.height;
    std::size_t numTextures = animator.textures.size();
    bool cond;
    do
    {
        segments.emplace_back(currPos, RandomNum(0, numTextures - 1));
        currPos += n * advance;
        cond = dirIsEndPos ? (glm::length(startPos - currPos) < glm::length(startPos - dir)) : (currPos.x >= min && currPos.x < RES_WIDTH && currPos.y >= 0.0f && currPos.y < RES_HEIGHT);
    } while (cond);
}

void Mirror::Draw()
{
    for (auto& seg : segments)
    {
        std::size_t ind = seg.texInd + animator.currFrame;
        ind %= animator.textures.size();
        DrawTextureEx(animator.textures[ind]->tex, VEC_CAST(seg.pos), rot, 1.0f, color);
    }
}

void Mirror::Update(float dt)
{
    animator.Update(dt);
}