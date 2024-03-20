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


class GopherSprite : public ax::Sprite {

public:

    GopherSprite() : status(GopherStatus::Hide), score(-1) {};

    /**
     * Create Gopher to position
     * @param position_
     * @return
     */
    GopherSprite *create(ax::Rect position_);

    GopherStatus getStatus() {
        return status;
    }

    void pop(int score_) {
        if (status != GopherStatus::Show) {
            score_ = score;
            status = GopherStatus::Show;
            updateDisplay();
        }
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

protected:
    void updateDisplay();

private:

    GopherStatus status;

    int score;
};


#endif //MYGAMEDEMO_GOPHERSPRITE_H
