#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "axmol.h"


class GameScene : public ax::Scene {
    enum class GameState {
        init = 0,
        update,
        pause,
        end
    };

public:
    bool init() override;

    void update(float delta) override;

    // touch
    void onTouchesBegan(const std::vector<ax::Touch *> &touches, ax::Event *event);

    void onTouchesMoved(const std::vector<ax::Touch *> &touches, ax::Event *event);

    void onTouchesEnded(const std::vector<ax::Touch *> &touches, ax::Event *event);

    // a selector callback
    void menuCloseCallback(Ref *sender);

    void updateScore(uint64_t score);

private:
    GameState _gameState = GameState::init;

    uint64_t score = 0;
};

#endif  // __GAME_SCENE_H__
