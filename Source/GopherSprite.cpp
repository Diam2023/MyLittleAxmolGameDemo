//
// Created by 35691 on 3/16/2024.
//

#include "GopherSprite.h"


GopherSprite *GopherSprite::create(ax::Rect position_) {
    auto gopher = new GopherSprite();

    if (gopher->init()) {
        gopher->autorelease();
        return gopher;
    }
    AX_SAFE_DELETE(gopher);
}