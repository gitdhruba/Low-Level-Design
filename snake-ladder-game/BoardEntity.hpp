enum class BoardEntityType : int {
    NORMAL,
    SNAKE,
    LADDER
};

class BoardEntity {
private:
    BoardEntityType type;
    int start, end;

public:
    BoardEntity(
        BoardEntityType _type,
        int _start,
        int _end
    );

    ~BoardEntity() {}

    BoardEntityType getType() const;

    int getStart() const;

    int getEnd() const;

    void setType(BoardEntityType);

    void setStart(int);

    void setEnd(int);
};