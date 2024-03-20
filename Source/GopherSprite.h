//
// Created by 35691 on 3/16/2024.
//

#ifndef MYGAMEDEMO_GOPHERSPRITE_H
#define MYGAMEDEMO_GOPHERSPRITE_H

#include <axmol.h>

enum class GopherStatus {
    Hide,
    Show
};

class TimerAdapter {
public:
    virtual void func(float) = 0;
};


class GopherSprite : public ax::Sprite, public TimerAdapter {

public:

    GopherSprite() : status(GopherStatus::Hide), score(-1) {};

    /**
     * Create Gopher to position
     * @param position_
     * @return
     */
    static GopherSprite *create(const ax::Rect &position_, const ax::Vec2 &boardOffset = {0, 0});

    GopherStatus getStatus() {
        return status;
    }

    void pop(int score_) {
        if (status != GopherStatus::Show) {
            score_ = score;
            status = GopherStatus::Show;
            updateDisplay();
            // timer to hide
        }
    }

    void func(float dt) {
        AXLOG("call");
        hide();
    }

    void hide() {
        if (status != GopherStatus::Hide) {
            score = -1;
            status = GopherStatus::Hide;
            updateDisplay();
        }
    }

    int operator*() const {
        return score;
    }

    void updateDisplay();

    void setArea(const ax::Rect &area_) {
        area = area_;
    }

private:

    GopherStatus status;

    ax::Rect area;

    int score;
};


#endif //MYGAMEDEMO_GOPHERSPRITE_H
