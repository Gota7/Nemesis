#include "animator.hpp"

#include <algorithm>
#include <filesystem>

Animator::Animator(AssetHolder<Tex>& holderTex, const std::string& animName, float totalFrameTime, bool lerp) : totalFrameTime(totalFrameTime), lerp(lerp)
{
    std::vector<std::string> paths;
    for (const auto& entry : std::filesystem::recursive_directory_iterator("res/tex/" + animName))
    {
        if (!entry.is_directory()) paths.push_back(entry.path().string());
    }
    std::sort(paths.begin(), paths.end());
    for (auto& path : paths) textures.emplace_back(holderTex.Load(path, path));
    prevFrame = textures.size() - 1;
}

void Animator::Draw()
{
    DrawPositioned();
}

void Animator::DrawPositioned(const glm::vec2& pos, Color tint, Rectangle source)
{
    Texture2D& tex = textures[currFrame]->tex;
    if (source.width == -1.0f) source.width = tex.width;
    if (source.height == -1.0f) source.height = tex.height;
    if (lerp)
    {
        float currAlpha = glm::clamp((totalFrameTime - frameTime) / totalFrameTime, 0.0f, 1.0f);
        unsigned char bakTint = tint.a;
        tint.a *= (1.0f - currAlpha);
        DrawTextureRec(tex, source, VEC_CAST(pos), tint);
        tint.a = bakTint * currAlpha;
        DrawTextureRec(textures[prevFrame]->tex, source, VEC_CAST(pos), tint);
    }
    else DrawTextureRec(tex, source, VEC_CAST(pos), tint);
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