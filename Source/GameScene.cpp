#include "GameScene.h"

#include "BoardSprite.h"

#define OUTSIDE_SPACE 20

#define SCORE_TAG  0x82
#define WEAPON_TAG 0x52
#define BOARD_TAG  0x42

#define RANDOM_POP_TIMER_NAME "RandomPopTimer"
#define RANDOM_POP_TIMER_SPLIT 160.f

USING_NS_AX;


static auto createHitAction() -> auto {
    // Down
    auto actionDown = RotateBy::create(.1f, 30.0f);
    // Then up
    auto actionUp = RotateBy::create(.1f, -30.0f);
    auto actionSequence = Sequence::create(actionDown, actionUp, nullptr);

    return actionSequence;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char *filename) {
    printf("Error while loading: %s\n", filename);
    printf(
            "Depending on how you compiled you might have to add 'Content/' in front of filenames in "
            "GameScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init() {
    if (!Scene::init()) {
        return false;
    }
    Director::getInstance()->getGLView()->setCursorVisible(false);

    auto visibleSize = _director->getVisibleSize();
    auto origin = _director->getVisibleOrigin();
    auto safeArea = _director->getSafeAreaRect();
    auto safeOrigin = safeArea.origin;

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
                                           AX_CALLBACK_1(GameScene::menuCloseCallback, this));

    if (closeItem == nullptr || closeItem->getContentSize().width <= 0 || closeItem->getContentSize().height <= 0) {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    } else {
        float x = safeOrigin.x + safeArea.size.width - closeItem->getContentSize().width / 2;
        float y = safeOrigin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

#if IS_PC
    // PC

    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = AX_CALLBACK_1(GameScene::onMouseDown, this);
    mouseListener->onMouseUp = AX_CALLBACK_1(GameScene::onMouseUp, this);
    mouseListener->onMouseMove = AX_CALLBACK_1(GameScene::onMouseMove, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
#else
    // PE

    auto touchListener = EventListenerTouchAllAtOnce::create();
    touchListener->onTouchesBegan = AX_CALLBACK_2(GameScene::onTouchesBegan, this);
    touchListener->onTouchesMoved = AX_CALLBACK_2(GameScene::onTouchesMoved, this);
    touchListener->onTouchesEnded = AX_CALLBACK_2(GameScene::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
#endif


    auto drawNode = DrawNode::create();
    drawNode->setPosition(Vec2(0, 0));
    addChild(drawNode);

    drawNode->drawRect(safeArea.origin + Vec2(1, 1), safeArea.origin + safeArea.size - Vec2(1, 1), Color4F::BLUE);

    // Center algorithm
    auto board = BoardSprite::create(visibleSize.height - OUTSIDE_SPACE, 4);
    auto tempBoardSize = Vec2{visibleSize.height - OUTSIDE_SPACE, visibleSize.height - OUTSIDE_SPACE};
    auto position = (visibleSize - tempBoardSize) / 2;
    board->setPosition(position);
    board->setTag(BOARD_TAG);
    addChild(board);

    score = 0;
    auto scoreLabel = Label::createWithTTF("Score:0000", "fonts/Marker Felt.ttf", 24);
    scoreLabel->setPosition(
            Vec2(scoreLabel->getContentSize().width / 2 + 10,
                 origin.y + visibleSize.height - scoreLabel->getContentSize().height));
    scoreLabel->setTag(SCORE_TAG);
    this->addChild(scoreLabel, 1);


    auto weaponSprite = Sprite::create("res/weapon.png");
    weaponSprite->setPosition(scoreLabel->getContentSize() - weaponSprite->getContentSize() / 2);
    auto resourceScale = board->getBoardBlockSize().width / weaponSprite->getContentSize().width;
    weaponSprite->setScale(resourceScale);
    weaponSprite->setTag(WEAPON_TAG);
    weaponSprite->setAnchorPoint({.3f, .45f});
    // Top of screen
    this->addChild(weaponSprite, 1);

#if IS_PC
    weaponSprite->setVisible(true);
#else
    weaponSprite->setVisible(false);
#endif

    // TODO Waiting test
//    this->schedule(AX_CALLBACK_1(GameScene::randomPopGophersTimer, this), RANDOM_POP_TIMER_SPLIT,
//                   RANDOM_POP_TIMER_NAME);

    scheduleUpdate();

    return true;
}

void GameScene::updateScore(uint64_t score) {
    this->score = score;
    auto scoreLabel = (Label *) this->getChildByTag(SCORE_TAG);
    scoreLabel->setString(StringUtils::format("Score:%04llu", score));
}

template<class R, class C, class... Args>
R getRetValue(R(C::*)(Args...));

void GameScene::randomPopGophersTimer(float dt) {

//    auto boardSprite = (BoardSprite *) this->getChildByTag(BOARD_TAG);
//
//    int8_t limit = 3;
//    auto res = this->gophers.end();
//    decltype(getRetValue(&BoardSprite::randomBlock)) randomBlock;
//
//    do {
//        randomBlock = boardSprite->randomBlock();
//        res = this->gophers.find(randomBlock);
//        limit--;
//        if (limit <= 0) {
//            return;
//        }
//    } while (res != this->gophers.end());
//
//    auto gopher = GopherSprite::create(boardSprite->getBlockByBlockIndex(randomBlock));
//    addChild(gopher);
//    gophers[randomBlock] = gopher;

}

#if IS_PC

void GameScene::onMouseDown(Event *event) {
    EventMouse *e = static_cast<EventMouse *>(event);
//    AXLOG("onMouseDown detected, Key: %d", static_cast<int>(e->getMouseButton()));

    auto weaponSprite = (Sprite *) this->getChildByTag(WEAPON_TAG);
    weaponSprite->setPosition(e->getCursorX(), e->getCursorY());
    hitPosition.emplace(e->getCursorX(), e->getCursorY());
    weaponSprite->runAction(createHitAction());
}

void GameScene::onMouseUp(Event *event) {
//    EventMouse *e = static_cast<EventMouse *>(event);
//    AXLOG("onMouseUp detected, Key: %d", static_cast<int>(e->getMouseButton()));
}

void GameScene::onMouseMove(Event *event) {
    // updateScore(score + 1);
    EventMouse *e = static_cast<EventMouse *>(event);
//    AXLOG("onMouseMove detected, X:%f  Y:%f", e->getCursorX(), e->getCursorY());


    // running when action empty!
    auto weaponSprite = (Sprite *) this->getChildByTag(WEAPON_TAG);
    if (weaponSprite->getNumberOfRunningActions() <= 0) {
        weaponSprite->setPosition({e->getCursorX(), e->getCursorY()});
    }
//    auto moveTarget = MoveTo::create(.2f, {e->getCursorX(), e->getCursorY()});
//    weaponSprite->runAction(moveTarget);
}

#else


void GameScene::onTouchesBegan(const std::vector<ax::Touch *> &touches, ax::Event *event) {
    auto weaponSprite = (Sprite *) this->getChildByTag(WEAPON_TAG);
    for (auto &&t: touches) {
        weaponSprite->setPosition(t->getLocation());
        weaponSprite->runAction(createHitAction());
        hitPosition.emplace(t->getLocation());
        AXLOG("onTouchesBegan detected, X:%f  Y:%f", t->getLocation().x, t->getLocation().y);
    }
}

void GameScene::onTouchesMoved(const std::vector<ax::Touch *> &touches, ax::Event *event) {
//    for (auto &&t: touches) {
//
//        AXLOG("onTouchesMoved detected, X:%f  Y:%f", t->getLocation().x, t->getLocation().y);
//    }
}

void GameScene::onTouchesEnded(const std::vector<ax::Touch *> &touches, ax::Event *event) {
    for (auto &&t: touches) {
        // AXLOG("onTouchesEnded detected, X:%f  Y:%f", t->getLocation().x, t->getLocation().y);
    }
}
#endif

//void GameScene::onMouseScroll(Event *event) {
// Test generate random block draw
//    EventMouse *e = static_cast<EventMouse *>(event);
//    AXLOG("onMouseScroll detected, X:%f  Y:%f", e->getScrollX(), e->getScrollY());
//}


void GameScene::update(float delta) {
    BoardSprite *boardSprite = nullptr;

    // Assert initialize
    Vec2 startSpace;
    Vec2 endSpace;

    switch (_gameState) {
        case GameState::init: {
            boardSprite = (BoardSprite *) this->getChildByTag(BOARD_TAG);

            startSpace = (_director->getVisibleSize() - boardSprite->getBoardSize()) / 2;
            endSpace = startSpace + boardSprite->getBoardSize();

            _gameState = GameState::update;
            break;
        }

        case GameState::update: {
            if (boardSprite == nullptr) {
                boardSprite = (BoardSprite *) this->getChildByTag(BOARD_TAG);
                if (boardSprite == nullptr) {
                    // Error Game over
                    _gameState = GameState::end;
                    break;
                }
            }

            while (!hitPosition.empty()) {
                auto pos = hitPosition.front();
                if (pos > startSpace && pos < endSpace) {
                    auto boardPos = pos - startSpace;
                    if (auto posIndex = boardSprite->getBlockIndexByPosition(boardPos);
                            (posIndex.first != -1)) {
                        AXLOG("You Hit Area Index: %d %d", posIndex.first, posIndex.second);

                        // inner
                        if (auto gopher = gophers.find(posIndex);
                                ((gopher != gophers.end()) && (*gopher).second != 0)) {
                            // Add score
                            updateScore(score + (*gopher).second);
                            AXLOG("Score+ %d", (*gopher).second);
                            // TODO wait play some hit action
                        }

                    }
                }

                hitPosition.pop();
            }
            break;
        }

        case GameState::pause: {
            // TODO Wait complate
        }

        case GameState::end: {

            // TODO replace Game Over Scene and send game score
        }

    } //switch
}

void GameScene::menuCloseCallback(Ref *sender) {
    // Close the axmol game scene and quit the application
    _director->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use
     * _director->end() as given above,instead trigger a custom event created in RootViewController.mm
     * as below*/

    // EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void GameScene::generateGophers(uint8_t num) {

}

void GameScene::initCache() {

    auto frame = SpriteFrame::create("res/main.png", {0, 0});

    // 2000 / 2

}

