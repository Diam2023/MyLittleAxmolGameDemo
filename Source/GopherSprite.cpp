//
// Created by 35691 on 3/16/2024.
//

#include "GopherSprite.h"


GopherSprite *GopherSprite::create(const ax::Rect &position_, const ax::Vec2 &boardOffset) {
    auto gopher = new GopherSprite();
    gopher->updateDisplay();
    gopher->setPosition(position_.origin + boardOffset);
    gopher->setContentSize(position_.size);

    gopher->autorelease();
    return gopher;
}

void GopherSprite::updateDisplay() {
    switch (status) {

        case GopherStatus::Show: {
            initWithFile("res/pop.png");
        }

        case GopherStatus::Hide: {
            initWithFile("res/hide.png");
        }
    };

}


