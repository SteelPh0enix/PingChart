#include <QApplication>
#include <QFileInfo>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSettings>

#include "cursorpositionprovider.hpp"
#include "uibackend.hpp"

constexpr char const *const settingsFilePath = "settings.ini";

void saveDataOnExit(QSettings &settings, UIBackend const &backend) {
  settings.beginGroup("window");
  settings.setValue("x", backend.windowPosition().x());
  settings.setValue("y", backend.windowPosition().y());
  settings.endGroup();
  qDebug() << "Saved window position: " << backend.windowPosition();
}

int main(int argc, char *argv[])
{
  QCoreApplication::setOrganizationDomain("steelph0enix.1337.cx");
  QCoreApplication::setOrganizationName("steelph0enix");
  QCoreApplication::setApplicationName("PingChart");
  QCoreApplication::setApplicationVersion("1.0");
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QSettings settings(settingsFilePath, QSettings::IniFormat);
  if (!QFileInfo::exists(settingsFilePath)) {
    settings.beginGroup("network");
    settings.setValue("destination_ip", "1.1.1.1");
    settings.endGroup();
  }

  settings.beginGroup("network");
  QString destinationIp = settings.value("destination_ip").toString();
  settings.endGroup();

  QApplication app(argc, argv);
  UIBackend backend;
  CursorPositionProvider dragHelper;

  QQmlApplicationEngine engine;

  const QUrl url(QStringLiteral("qrc:/main.qml"));

  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
          QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);

  engine.rootContext()->setContextProperty("uiBackend", &backend);
  engine.rootContext()->setContextProperty("cursorPositionProvider", &dragHelper);
  engine.load(url);

  settings.beginGroup("window");
  if (settings.contains("x") && settings.contains("y")) {
    int window_x = settings.value("x").toInt();
    int window_y = settings.value("y").toInt();
    backend.setWindowPosition({window_x, window_y});
    qDebug() << "Loaded window position: " << backend.windowPosition();
  }
  settings.endGroup();

  QObject::connect(&app, &QApplication::aboutToQuit, [&]() { saveDataOnExit(settings, backend); });

  return app.exec();
}
