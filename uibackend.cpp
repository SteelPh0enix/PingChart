#include "uibackend.hpp"

UIBackend::UIBackend(QObject* parent) : QObject(parent) {}

void UIBackend::setWindowPosition(QPoint const& newPosition) {
  m_windowPosition = newPosition;
  emit windowPositionChanged(m_windowPosition);
}

void UIBackend::setDestinationIP(QString const& newIP) {
  m_destinationIP = newIP;
  emit destinationIPChanged(m_destinationIP);
}

QPoint UIBackend::windowPosition() const { return m_windowPosition; }

QString UIBackend::destinationIP() const { return m_destinationIP; }
