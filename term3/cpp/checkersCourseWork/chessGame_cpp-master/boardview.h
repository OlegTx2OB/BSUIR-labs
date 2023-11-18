#pragma once
#include <QGraphicsRectItem>
#include <QList>
#include <QPoint>
#include "boardfield.h"
#include "figurefield.h"

class BoardView: public QGraphicsRectItem
{
private:
    QList<BoardField*> fields;
    QList<FigureField*> pawns;
    QGraphicsTextItem *checkWarningTitleTextItem;
    QGraphicsTextItem *checkWarningDescriptionTextItem;
public:
    static int numberOfRowsColumns;
    static int startXPosition;
    static int startYPosition;

    BoardView();

    QList<BoardField*> getFields();
    void draw();
    void initializeFiguresFields(QList<FigureClass*> pawns);
    FigureField* getFigureAtBoardPosition(BoardPosition boardPosition);
    FigureField* getFigureAtMousePosition(QPoint point);
    void moveActiveFigureToMousePosition(QPoint point, FigureClass *pawn);
    void placeActiveFigureAtBoardPosition(FigureClass *pawn, BoardPosition boardPosition);
    void removeFigureAtBoardPosition(BoardPosition boardPosition);
    void setFigureMoveCheckWarning(bool visible);
    void promoteFigureAtBoardPosition(BoardPosition boardPosition);

private:
    void placeBoardFields();
    void createFieldsColumn(int xPosition, int columnNumber);
    void drawBoardFrame();
    void drawBoardFrameAtPosition(QPoint point, QRectF rect, QString title);
    void drawCheckWarningTextItems();
    QPointF getCoordinatesForBoardPosition(BoardPosition position);
};
