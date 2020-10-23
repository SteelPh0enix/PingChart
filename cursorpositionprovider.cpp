#include "cursorpositionprovider.hpp"

#include <QCursor>

CursorPositionProvider::CursorPositionProvider(QObject *parent) : QObject(parent) {}

QPointF CursorPositionProvider::cursorPosition() const { return QCursor::pos(); }
