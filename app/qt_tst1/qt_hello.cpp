#include "mainwindow.h"
#include <QApplication>
#include "qt_hello.hpp"

int qt_hello()
{
  int argc;
  
  QApplication a(argc, NULL);
  MainWindow w;
  w.show();

  return a.exec();
}
