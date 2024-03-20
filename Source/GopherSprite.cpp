//
// Created by 35691 on 3/16/2024.
//

#include "GopherSprite.h"


GopherSprite *GopherSprite::create(ax::Rect position_) {
    auto gopher = new GopherSprite();
    updateDisplay();
    gopher->setPosition(position_.origin);
    gopher->setContentSize(position_.size);

    if (gopher->init()) {
        gopher->autorelease();
        return gopher;
    }
    AX_SAFE_DELETE(gopher);
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


