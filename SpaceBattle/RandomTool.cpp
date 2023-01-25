#include "RandomTool.h"

namespace
{
static std::random_device rdevice;
static std::mt19937 rng(rdevice());
static std::uniform_int_distribution<std::mt19937::result_type> dist;
} // namespace

namespace random_tool
{
uint32_t RandomValueInRange(uint32_t val)
{
    return dist(rng) % val;
}
}; // namespace random_tool