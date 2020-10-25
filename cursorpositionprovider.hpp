#ifndef CURSORPOSITIONPROVIDER_HPP
#define CURSORPOSITIONPROVIDER_HPP

#include <QObject>
#include <QtQml>

class CursorPositionProvider : public QObject
{
  Q_OBJECT
  QML_ELEMENT
 public:
  explicit CursorPositionProvider(QObject *parent = nullptr);

  Q_INVOKABLE QPointF cursorPosition() const;

 signals:

};

#endif // CURSORPOSITIONPROVIDER_HPP
