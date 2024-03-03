#pragma once

#include "assetHolder.hpp"
#include "body.hpp"
#include "global.hpp"
#include <vector>

// Texture wrapper.
struct Tex
{
    Texture2D tex;

    // Make a texture.
    Tex(const std::string& path)
    {
        tex = LoadTexture(path.c_str());
    }

    // DESTROY.
    ~Tex()
    {
        UnloadTexture(tex);
    }

};

// For animating the scene.
struct Animator : Actor
{
    std::vector<SHARED<Tex>> textures;
    float frameTime = 0.0f;
    float totalFrameTime;
    std::size_t currFrame = 0;
    std::size_t prevFrame;
    bool lerp;

    // Create a new animator.
    Animator(AssetHolder<Tex>& holderTex, const std::string& animName, float totalFrameTime, bool lerp = false);

    // Draw animator.
    virtual void Draw() override;

    // Draw in position.
    void DrawPositioned(const glm::vec2& pos = glm::vec2(0.0f), Color tint = WHITE, Rectangle source = { 0.0f, 0.0f, -1.0f, -1.0f });

    // Update animator.
    virtual void Update(float dt) override;

    // DESTROY.
    virtual ~Animator() override {}

};