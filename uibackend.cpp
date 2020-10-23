#include "uibackend.hpp"

UIBackend::UIBackend(QObject *parent) : QObject(parent) {}

void UIBackend::setWindowPosition(QPoint newPosition) {
  m_windowPosition = newPosition;
  windowPositionChanged(newPosition);
}

QPoint UIBackend::windowPosition() const { return m_windowPosition; }
