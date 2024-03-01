#pragma once

#include <functional>
#include <optional>
#include <vector>

// State machine function.
template <typename T>
using StateMachineFunc = std::optional<std::function<void(T&)>>;

// State machine entry.
template <typename T>
struct StateMachineEntry
{
    StateMachineFunc<T> onEnter;
    StateMachineFunc<T> onUpdate;
    StateMachineFunc<T> onExit;
    bool updateOnEnter;

    // Create a new state machine entry.
    StateMachineEntry(
        const StateMachineFunc<T>& onEnter = std::nullopt,
        const StateMachineFunc<T>& onUpdate = std::nullopt,
        const StateMachineFunc<T>& onExit = std::nullopt,
        bool updateOnEnter = true
    ) : onEnter(onEnter), onUpdate(onUpdate), onExit(onExit), updateOnEnter(updateOnEnter) {}

};

// Enable a state-switching state.
template <typename T>
struct StateMachine
{
    std::vector<StateMachineEntry<T>> states;
    long currState;
    long prevState = -1;

    // Make a new state machine.
    StateMachine(std::vector<StateMachineEntry<T>>&& states, long currState = -1) : states(std::move(states)), currState(currState) {}

    // Execute the state machine.
    void Execute(T& item)
    {
        if (currState != prevState)
        {
            prevState = currState;
        }
        else if ((std::size_t)currState < states.size() && states[currState].onUpdate)
        {
            (*states[currState].onUpdate)(item);
        }
    }

};