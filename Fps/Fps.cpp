#include "FpsGame.h"
#include <memory>

using namespace std;

int main() {
    auto game = std::make_shared<FpsGame>();
    game->RunGame();
    return 0;
}