/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 Copyright (c) 2019-present Axmol Engine contributors (see AUTHORS.md).

 https://axmolengine.github.io/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "MainScene.h"

#include "GameScene.h"

USING_NS_AX;

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char *filename) {
    printf("Error while loading: %s\n", filename);
    printf(
            "Depending on how you compiled you might have to add 'Content/' in front of filenames in "
            "MainScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainScene::init() {
    if (!Scene::init()) {
        return false;
    }

    auto visibleSize = _director->getVisibleSize();
    auto origin = _director->getVisibleOrigin();
    auto safeArea = _director->getSafeAreaRect();
    auto safeOrigin = safeArea.origin;

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
                                           AX_CALLBACK_1(MainScene::menuCloseCallback, this));

    if (closeItem == nullptr || closeItem->getContentSize().width <= 0 || closeItem->getContentSize().height <= 0) {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    } else {
        float x = safeOrigin.x + safeArea.size.width - closeItem->getContentSize().width / 2;
        float y = safeOrigin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    // Create Start Button
    auto startItem = MenuItemLabel::create(Label::createWithTTF("Start", "fonts/Marker Felt.ttf", 40),
                                             AX_CALLBACK_1(MainScene::startGame, this));
    if (startItem == nullptr) {
        problemLoading("'startButton'");
    } else {
        startItem->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    }

    // show menu
    auto menu = Menu::create(closeItem, startItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // add a label shows "My Little Game Demo"
    // create and initialize a label

    auto label = Label::createWithTTF("My Little Game Demo", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr) {
        problemLoading("'fonts/Marker Felt.ttf'");
    } else {
        // position the label on the center of the screen
        label->setPosition(
                Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // draw blue border
    auto drawNode = DrawNode::create();
    drawNode->setPosition(Vec2(0, 0));
    addChild(drawNode);
    drawNode->drawRect(safeArea.origin + Vec2(1, 1), safeArea.origin + safeArea.size, Color4F::BLUE);

    // scheduleUpdate() is required to ensure update(float) is called on every loop
    scheduleUpdate();

    return true;
}

void MainScene::startGame(Ref *sender) {
    auto gameScene = utils::createInstance<GameScene>();
    _director->pushScene(gameScene);
}

void MainScene::update(float delta) {
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

void MainScene::menuCloseCallback(Ref *sender) {
    // Close the axmol game scene and quit the application
    _director->end();
    // EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}
