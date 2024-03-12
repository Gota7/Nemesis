#pragma once

#include "animator.hpp"
#include "game.hpp"
#include "scene.hpp"
#include "title.hpp"

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
    Animator byGota7;
    Animator credits;
    Animator thankYou;
    float timer = 3.0f;
    float origTimer;
    float titleA = 0.0f;
    float byGota7A = 0.0f;
    float creditsA = 0.0f;
    float thankYouA = 0.0f;

    // Make new credits.
    Credits(Game& game);

    // Draw credits.
    virtual void Draw() override;

    // Update credits.
    virtual void Update(float dt) override;

};