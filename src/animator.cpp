#include "animator.hpp"

#include <algorithm>
#include <filesystem>

Animator::Animator(const std::string& animName, float totalFrameTime, bool lerp) : totalFrameTime(totalFrameTime), lerp(lerp)
{
    std::vector<std::string> paths;
    for (const auto& entry : std::filesystem::recursive_directory_iterator("res/tex/" + animName))
    {
        if (!entry.is_directory()) paths.push_back(entry.path().string());
    }
    std::sort(paths.begin(), paths.end());
    for (auto& path : paths) textures.push_back(LoadTexture(path.c_str()));
    prevFrame = textures.size() - 1;
}

void Animator::Draw()
{
    DrawPositioned();
}

void Animator::DrawPositioned(const glm::vec2& pos, Color tint)
{
    if (lerp)
    {
        float currAlpha = glm::clamp((totalFrameTime - frameTime) / totalFrameTime, 0.0f, 1.0f);
        unsigned char bakTint = tint.a;
        tint.a *= (1.0f - currAlpha);
        DrawTextureV(textures[currFrame], VEC_CAST(pos), tint);
        tint.a = bakTint * currAlpha;
        DrawTextureV(textures[prevFrame], VEC_CAST(pos), tint);
    }
    else DrawTextureV(textures[currFrame], VEC_CAST(pos), tint);
}

void Animator::Update(float dt)
{
    frameTime += dt;
    while (frameTime >= totalFrameTime)
    {
        frameTime -= totalFrameTime;
        prevFrame = currFrame;
        currFrame++;
        currFrame %= textures.size();
    }
}

Animator::~Animator()
{
    for (auto& tex : textures) UnloadTexture(tex);
}