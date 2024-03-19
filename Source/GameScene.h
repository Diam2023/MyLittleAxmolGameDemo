#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "axmol.h"


#define IS_PC (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || \
    (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)


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


#if IS_PC
    // mouse

    void onMouseDown(ax::Event *event);

    void onMouseUp(ax::Event *event);

    void onMouseMove(ax::Event *event);

#else

    // touch
    void onTouchesBegan(const std::vector<ax::Touch *> &touches, ax::Event *event);

    void onTouchesMoved(const std::vector<ax::Touch *> &touches, ax::Event *event);

    void onTouchesEnded(const std::vector<ax::Touch *> &touches, ax::Event *event);

#endif

//    void GameScene::onMouseScroll(ax::Event *event);

    // a selector callback
    void menuCloseCallback(Ref *sender);

    void updateScore(uint64_t score);

    /**
     * Generate gophers
     * @param num number of generate
     */
    void generateGophers(uint8_t num = 1);

    /**
     * Random generate the gophers
     * @param dt
     */
    void randomPopGophersTimer(float dt);


    void initCache();

private:
    GameState _gameState = GameState::init;

    uint64_t score = 0;

    // prepare a score
    // default is -1
    std::map<std::pair<uint8_t, uint8_t>, uint8_t> gophers;

    std::queue<ax::Vec2> hitPosition;
};

#endif  // __GAME_SCENE_H__
