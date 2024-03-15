#include "BoardSprite.h"

USING_NS_AX;

BoardSprite *BoardSprite::create(float size, uint8_t split) {
    auto *sprite = new BoardSprite();

    sprite->setContentSize({size, size});
    auto splitSpace = size / split;

    // set board arg
    sprite->setBoardNumber(split);
    sprite->setBoardSize({size, size});
    sprite->setBoardBlockSize({splitSpace, splitSpace});

    // draw board
    for (uint8_t widthIndex = 0; widthIndex < split; widthIndex++) {

        for (uint8_t heightIndex = 0; heightIndex < split; heightIndex++) {

            // rectangle position
            float start = heightIndex * splitSpace;
            float end = widthIndex * splitSpace;

            auto drawNode = DrawNode::create();
            drawNode->drawRect({start, end}, {start + splitSpace, end + splitSpace}, Color4F::RED);
            sprite->addChild(drawNode);
        }
    }

    if (sprite->init()) {
        sprite->autorelease();
        return sprite;
    }
    AX_SAFE_DELETE(sprite);
}

std::pair<int16_t, int16_t> BoardSprite::getBlockIndexByPosition(const Vec2 &pos) {
    auto res = std::make_pair(-1, -1);
    if (pos < boardSize) {
        // legal

        auto targetPosition = pos / boardBlockSize;
        res.first = (uint8_t) targetPosition.x;
        res.second = (uint8_t) targetPosition.y;
    }

    return res;
}

ax::Rect BoardSprite::getBlockByBlockIndex(std::pair<uint8_t, uint8_t> blockIndex) const {
    auto rec = Rect{-1, -1, -1, -1};
    if (blockIndex.first < boardNumber && blockIndex.second < boardNumber) {
        // legal
        rec.setRect((float) blockIndex.first * boardBlockSize.x, (float) blockIndex.second * boardBlockSize.y,
                    boardBlockSize.width, boardBlockSize.height);
    }

    return rec;
}



