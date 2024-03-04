#pragma once

// Forward declare.
struct Game;

// A scene to render instead of a scenario.
struct Scene
{
    Game& game;

    // Make a new scene.
    Scene(Game& game) : game(game) {}

    // Draw the scene.
    virtual void Draw() = 0;

    // Update the scene.
    virtual void Update(float dt) = 0;

    // Kill the scene.
    void Kill();

    // DESTROY.
    virtual ~Scene() {}

};