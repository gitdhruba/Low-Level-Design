#include "./BoardEntity.hpp"


BoardEntity::BoardEntity(
    BoardEntityType _type,
    int _start,
    int _end
) {
    this->type = _type;
    this->start = _start;
    this->end = _end;
}

BoardEntityType BoardEntity::getType() const {
    return this->type;
}

int BoardEntity::getStart() const {
    return this->start;
}

int BoardEntity::getEnd() const {
    return this->end;
}

void BoardEntity::setType(BoardEntityType type) {
    this->type = type;
}

void BoardEntity::setStart(int start) {
    this->start = start;
}

void BoardEntity::setEnd(int end) {
    this->end = end;
}