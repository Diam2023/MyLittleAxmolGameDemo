#include "GameScene.h"

#include "BoardSprite.h"

#define OUTSIDE_SPACE 20
#define SCORE_TAG 0x82

USING_NS_AX;

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

    // Some templates (uncomment what you  need)
    auto touchListener = EventListenerTouchAllAtOnce::create();
    touchListener->onTouchesBegan = AX_CALLBACK_2(GameScene::onTouchesBegan, this);
    touchListener->onTouchesMoved = AX_CALLBACK_2(GameScene::onTouchesMoved, this);
    touchListener->onTouchesEnded = AX_CALLBACK_2(GameScene::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);


    auto drawNode = DrawNode::create();
    drawNode->setPosition(Vec2(0, 0));
    addChild(drawNode);

    drawNode->drawRect(safeArea.origin + Vec2(1, 1), safeArea.origin + safeArea.size - Vec2(1, 1), Color4F::BLUE);

    // Center algorithm
    auto board = BoardSprite::create(visibleSize.height - OUTSIDE_SPACE, 4);
    auto tempBoardSize = Vec2{visibleSize.height - OUTSIDE_SPACE, visibleSize.height - OUTSIDE_SPACE};
    auto position = (visibleSize - tempBoardSize) / 2;
    board->setPosition(position);
    addChild(board);

    score = 0;
    auto scoreLabel = Label::createWithTTF("Score:0000", "fonts/Marker Felt.ttf", 24);
    scoreLabel->setPosition(
            Vec2(scoreLabel->getContentSize().width / 2 + 10,
                 origin.y + visibleSize.height - scoreLabel->getContentSize().height));
    scoreLabel->setTag(SCORE_TAG);
    this->addChild(scoreLabel, 1);

    // scheduleUpdate() is required to ensure update(float) is called on every loop
    scheduleUpdate();

    return true;
}

void GameScene::updateScore(uint64_t score) {
    this->score = score;
    std::stringstream ss;
    ss << "Score: ";
    ss << score;
    auto scoreLabel = (Label*) this->getChildByTag(SCORE_TAG);
    scoreLabel->setString(StringUtils::format("Score:%04llu", score));
}

void GameScene::onTouchesBegan(const std::vector<ax::Touch *> &touches, ax::Event *event) {
    for (auto &&t: touches) {
        AXLOG("onTouchesBegan detected, X:%f  Y:%f", t->getLocation().x, t->getLocation().y);
    }
}

void GameScene::onTouchesMoved(const std::vector<ax::Touch *> &touches, ax::Event *event) {
    for (auto &&t: touches) {
        AXLOG("onTouchesMoved detected, X:%f  Y:%f", t->getLocation().x, t->getLocation().y);
    }
}

void GameScene::onTouchesEnded(const std::vector<ax::Touch *> &touches, ax::Event *event) {
    for (auto &&t: touches) {
        AXLOG("onTouchesEnded detected, X:%f  Y:%f", t->getLocation().x, t->getLocation().y);
    }
}

void GameScene::update(float delta) {
    switch (_gameState) {
        case GameState::init: {
            _gameState = GameState::update;
            break;
        }

        case GameState::update: {
            break;
        }

        case GameState::pause: {
        }

        case GameState::end: {
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
