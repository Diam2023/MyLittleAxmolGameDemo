//
// Created by 35691 on 3/16/2024.
//

#include "GopherSprite.h"


GopherSprite *GopherSprite::create(const ax::Rect &position_, const ax::Vec2 &boardOffset) {
    auto gopher = new GopherSprite();
    gopher->setArea({position_.origin + boardOffset, position_.size});
    gopher->updateDisplay();

    gopher->autorelease();
    return gopher;
}

void GopherSprite::updateDisplay() {
    if (status == GopherStatus::Show) {
        initWithFile("res/pop.png");
    } else {
        initWithFile("res/hide.png");
    }

    setPosition(area.origin);
    setContentSize(area.size);
}


