#pragma once

#include "animator.hpp"
#include "game.hpp"
#include "scene.hpp"

// Forward declare.
struct Scenario;

// Credits launcher actor.
struct CreditsLauncher : Actor
{
    Scenario& scenario;
    Body* toFollow;

    // Make a new credits launcher.
    CreditsLauncher(Scenario& scenario);

    // Draw the credits launcher.
    virtual void Draw() override {}

    // Update the credits launcher.
    virtual void Update(float dt) override;

};

// Credits scene.
struct Credits : Scene
{
    Animator title;
    Animator by7Games;
    Animator credits;
    Animator thankYou;
    float currTime = 0.0f;
    float titleA = 0.0f;
    float by7GamesA = 0.0f;
    float creditsA = 0.0f;
    float thankYouA = 0.0f;

    // Make new credits.
    Credits(Game& game);

    // Draw credits.
    virtual void Draw() override;

    // Update credits.
    virtual void Update(float dt) override;

};