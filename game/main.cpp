#include <QApplication>
#include <graphicviewexample.hpp>

// Главный класс
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  a.addLibraryPath(a.applicationDirPath()+"/plugins");

  graphicViewExample s;
  s.show();
  return a.exec();
}
