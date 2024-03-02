#include "game.hpp"
#include "window.hpp"

PTR<Game> game;

void Draw()
{
    game->Draw();
}

void Update()
{
    game->Update(GetFrameTime());
}

int main()
{
    Window window;
    game = PTR_MAKE(Game);
    window.Run(Draw, Update);
    game.reset();
    return 0;
}