#include "numbers.hpp"

#include <array>

#define ROW_0_TO_6_Y_OFF 9.0f
#define ROW_7_TO_9_Y_OFF 132.0f
#define ROW_HEIGHT 125.0f

std::array<glm::vec2, 10> NUMBERS_X_OFF_WIDTH =
{
    glm::vec2(2, 77),
    glm::vec2(93, 75),
    glm::vec2(175, 74),
    glm::vec2(252, 67),
    glm::vec2(322, 65),
    glm::vec2(395, 58),
    glm::vec2(458, 68),
    glm::vec2(8, 73),
    glm::vec2(87, 76),
    glm::vec2(176, 65),
};

Numbers::Numbers(AssetHolder<Tex>& holderTex, const glm::vec2& pos, unsigned int num, Color color) : animator(holderTex, "numbers", FRAME_TIME_DEFAULT), pos(pos), num(num), color(color) {}

void Numbers::Draw()
{
    unsigned int currPow = 0;
    unsigned int pow = 0;
    float currX = pos.x;
    while (num >= pow)
    {
        unsigned int rem = (unsigned int)((int)(num / ((pow == 0.0f) ? 1.0f : pow)) % 10); // Do the math it works.
        animator.DrawPositioned(glm::vec2(currX, pos.y), color, {
            NUMBERS_X_OFF_WIDTH[rem].x,
            (rem < 7) ? ROW_0_TO_6_Y_OFF : ROW_7_TO_9_Y_OFF,
            NUMBERS_X_OFF_WIDTH[rem].y,
            ROW_HEIGHT
        });
        pow = (unsigned int)glm::pow(10.0f, (float)(++currPow));
        currX -= NUMBERS_X_OFF_WIDTH[rem].y;
    }
}

void Numbers::Update(float dt)
{
    animator.Update(dt);
}