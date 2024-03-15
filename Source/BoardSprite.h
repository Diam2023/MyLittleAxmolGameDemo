#ifndef MYGAMEDEMO_BOARDSPRITE_H
#define MYGAMEDEMO_BOARDSPRITE_H

#include "axmol.h"

class BoardSprite : public ax::Sprite {

protected:
    uint8_t boardNumber;

    ax::Vec2 boardSize;

    ax::Vec2 boardBlockSize;
public:

    uint8_t getBoardNumber() const {
        return boardNumber;
    }

    void setBoardNumber(uint8_t boardNumber) {
        BoardSprite::boardNumber = boardNumber;
    }

    const ax::Vec2 &getBoardSize() const {
        return boardSize;
    }

    void setBoardSize(const ax::Vec2 &boardSize) {
        BoardSprite::boardSize = boardSize;
    }

    const ax::Vec2 &getBoardBlockSize() const {
        return boardBlockSize;
    }

    void setBoardBlockSize(const ax::Vec2 &boardBlockSize) {
        BoardSprite::boardBlockSize = boardBlockSize;
    }

    /**
     * No inner if -1
     * @param pos
     * @return
     */
    std::pair<int16_t, int16_t> getBlockIndexByPosition(const ax::Vec2 &pos);

    /**
     * get blockRectangle area use block index
     * @param blockIndex
     * @return
     */
    ax::Rect getBlockByBlockIndex(std::pair<uint8_t, uint8_t> blockIndex) const;

public:

    /**
     * Init BoardSprite with board size
     * @param size size
     * @param split split
     * @return BoardSprite
     */
    static BoardSprite *create(float size, uint8_t split);


};

#endif //MYGAMEDEMO_BOARDSPRITE_H
