#include <QCoreApplication>
#include <QDebug>
#include <iostream>

#include "cmakeclient.h"
#include "request.h"

#include <QJsonObject>
#include <QJsonDocument>

void processReply(QJsonObject object){
  QJsonDocument doc;
  doc.setObject(object);

  std::cout << doc.toJson().toStdString() << '\n';
}

void processReplyB(QString a, QString b){

  qDebug() << a << b;
}


int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  CMakeClient::CMakeClient cl;

  QObject::connect(&cl, &CMakeClient::CMakeClient::reply,
                   &processReply);

  QObject::connect(&cl, &CMakeClient::CMakeClient::errorReply,
                   &processReplyB);

  QObject::connect(&cl, &CMakeClient::CMakeClient::messageReply,
                   &processReplyB);


  CMakeClient::HandShakeRequest hr(QLatin1String("D:/Luca/Documents/projects/C++/CMakeClient/CMakeClient/CMakeSample"),
                                   QLatin1String("D:/Luca/Documents/projects/C++/CMakeClient/build/Desktop Qt 5.7.0 MSVC2015_64bit/CMakeSample"),
                                   QLatin1String("Ninja"));

//  if(!cl.startCMakeServer()){
//      return a.exit();
//    }

//  cl.sendRequest(hr);
//  cl.sendRequest(CMakeClient::ConfigureRequest());
//  cl.sendRequest(CMakeClient::GeneralRequest("compute"));
//  cl.sendRequest(CMakeClient::GeneralRequest("codemodel"));
//  cl.sendRequest(CMakeClient::GeneralRequest("reply"));

  return a.exec();
}
