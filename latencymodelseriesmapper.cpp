#include "latencymodelseriesmapper.hpp"

#include <QPointF>
#include <QVector>
#include <algorithm>
#include <iterator>

LatencyModelSeriesMapper::LatencyModelSeriesMapper(QObject* parent) : QObject(parent) {}

void LatencyModelSeriesMapper::connectSignals() {
  if (m_latencyModel == nullptr || m_series == nullptr) {
    return;
  }

  QObject::connect(m_latencyModel, &LatencyDataModel::latencyAdded, this, &LatencyModelSeriesMapper::updateSeries);
}

void LatencyModelSeriesMapper::disconnectSignals() {
  if (m_latencyModel == nullptr || m_series == nullptr) {
    return;
  }

  QObject::disconnect(m_latencyModel, &LatencyDataModel::latencyAdded, this, &LatencyModelSeriesMapper::updateSeries);
}

void LatencyModelSeriesMapper::updateSeries(double) {
  QVector<QPointF> seriesData;
  seriesData.reserve(m_latencyModel->size());
  unsigned i = 0;

  std::transform(m_latencyModel->begin(), m_latencyModel->end(), std::back_inserter(seriesData),
                 [&i](double value) -> QPointF {
                   return {static_cast<double>(i++), value};
                 });

  m_series->replace(seriesData);
}

void LatencyModelSeriesMapper::setModel(LatencyDataModel* model) {
  disconnectSignals();
  m_latencyModel = model;
  connectSignals();
  emit modelChanged(m_latencyModel);
}

void LatencyModelSeriesMapper::setSeries(QtCharts::QXYSeries* series) {
  disconnectSignals();
  m_series = series;
  connectSignals();
  emit seriesChanged(m_series);
}

LatencyDataModel* LatencyModelSeriesMapper::model() const { return m_latencyModel; }

QtCharts::QXYSeries* LatencyModelSeriesMapper::series() const { return m_series; }
