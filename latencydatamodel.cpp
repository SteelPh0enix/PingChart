#include "latencydatamodel.hpp"

#include <algorithm>
#include <limits>

LatencyDataModel::LatencyDataModel(unsigned maxSize, QObject *parent) : QObject(parent) {
  setMaxSize(maxSize);
  resetStatistics();
}

void LatencyDataModel::setMaxSize(unsigned size) {
  m_maxSize = size;
  m_latencyData.reserve(m_maxSize);
}

unsigned LatencyDataModel::maxSize() const { return m_maxSize; }

unsigned LatencyDataModel::size() const { return m_latencyData.size(); }

double LatencyDataModel::maxLatency() const { return m_maxLatency; }

double LatencyDataModel::minLatency() const { return m_minLatency; }

double LatencyDataModel::avgLatency() const { return m_avgLatency; }

void LatencyDataModel::resetStatistics() {
  m_minLatency = std::numeric_limits<double>::max();
  m_maxLatency = std::numeric_limits<double>::min();
  m_avgLatency = 0.;
}

LatencyDataModel::Iterator LatencyDataModel::begin() const { return m_latencyData.constBegin(); }

LatencyDataModel::Iterator LatencyDataModel::end() const { return m_latencyData.constEnd(); }

void LatencyDataModel::addLatency(double latency) {
  if (size() >= maxSize()) {
    m_latencyData.removeFirst();
  } else {
    emit sizeChanged(m_latencyData.size() + 1);
  }

  m_latencyData.append(latency);
  emit latencyAdded(latency);
  recalculateStatistics();
}

void LatencyDataModel::clear() {
  m_latencyData.clear();
  emit sizeChanged(size());
}

void LatencyDataModel::recalculateStatistics() {
  double lastValue = m_latencyData.last();
  if (m_maxLatency < lastValue) {
    m_maxLatency = lastValue;
    emit maxLatencyChanged(m_maxLatency);
  }

  if (m_minLatency > lastValue) {
    m_minLatency = lastValue;
    emit minLatencyChanged(m_minLatency);
  }

  m_avgLatency = std::accumulate(m_latencyData.constBegin(), m_latencyData.constEnd(), 0) / size();
  emit avgLatencyChanged(m_avgLatency);
}
