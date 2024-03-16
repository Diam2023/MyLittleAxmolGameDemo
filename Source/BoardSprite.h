#ifndef MYGAMEDEMO_BOARDSPRITE_H
#define MYGAMEDEMO_BOARDSPRITE_H

#include "axmol.h"

/**
 * BoardSprite use for display the board of game
 */
class BoardSprite : public ax::Sprite {

protected:
    /**
     * How many block on one line in board
     */
    uint8_t boardNumber = 0;

    /**
     * Size of the board
     */
    ax::Vec2 boardSize = {0, 0};

    /**
     * Size of a block
     */
    ax::Vec2 boardBlockSize = {0, 0};
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

    /**
     * Generate random index block
     * @return pair random index
     */
    std::pair<uint8_t, uint8_t> randomBlock();


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
