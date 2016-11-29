/*******************************************************************************
This file is part of the CMakeClient project.
Copyright (C) 2016  Luca Carella <bkarelb at hotmail dot it>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*******************************************************************************/

#include "cmakeclient.h"
#include "request.h"

#include <iostream>
#include <memory>

#include <QJsonDocument>

static const char* CMAKE = "cmake";
static const char* CMAKE_OPTION = "-E";
static const char* CMAKE_OPTION_ARG = "server";
static const char* CMAKE_OPTION_ARG_1 = "--debug";
static const char* CMAKE_OPTION_ARG_2 = "--experimental";

static const char* REQUEST_HEADER = "[== \"CMake Server\" ==[";
static const char* REQUEST_TAIL = "]== \"CMake Server\" ==]";

CMakeClient::CMakeClient::CMakeClient()
  : m_cmakeProcess{}
{
  connect(&m_cmakeProcess, &QIODevice::readyRead,
          this, &CMakeClient::processReply);
}

CMakeClient::CMakeClient::~CMakeClient()
{
  stopCMakeServer();
}

bool CMakeClient::CMakeClient::startCMakeServer()
{
  QStringList args;
  args << CMAKE_OPTION
       << CMAKE_OPTION_ARG
       << CMAKE_OPTION_ARG_1
       << CMAKE_OPTION_ARG_2;

  //  m_cmakeProcess.setProcessChannelMode(QProcess::ForwardedChannels);

  m_cmakeProcess.start(CMAKE, args, QIODevice::ReadWrite);
  m_cmakeProcess.waitForStarted();
  // INFO: make sure the program is started and the first response is readed;
//  m_cmakeProcess.waitForReadyRead();

  if(!m_cmakeProcess.isOpen())
    return false;

  return true;
}

void CMakeClient::CMakeClient::processReply()
{
  auto reply = m_cmakeProcess.readAllStandardOutput();
  // remove header and tail from input
  auto data = reply.split('\n');
  data.removeAll(REQUEST_HEADER);
  data.removeAll(REQUEST_TAIL);
  data.removeAll("");

  for(auto &line : data){
      auto error = std::make_unique<QJsonParseError>();
      auto jsonDoc = QJsonDocument::fromJson(line, error.get());

      if(jsonDoc.isNull()){
          std::cout << "Error: " << error->errorString().toStdString() << '\n';
          continue;
        }

      auto jsonObject = jsonDoc.object();


      auto type = jsonObject["type"].toString();
      auto inReplyTo = jsonObject["inReplyTo"].toString();

      if(!type.isNull()){
          if(type == QLatin1String("error")){
              auto errorMessage = jsonObject["errorMessage"].toString();
              emit errorReply(inReplyTo, errorMessage);
            }
          else if(type == QLatin1String("message")){
              auto message = jsonObject["message"].toString();
              emit messageReply(inReplyTo, message);
            }
          else if(type == QLatin1String("progress")){
              auto currentProgress = jsonObject["currentProgress"].toInt();
              auto minimumProgress = jsonObject["minimumProgress"].toInt();
              auto maximumProgress = jsonObject["maximumProgress"].toInt();

              emit progressReply(ProgressReply{minimumProgress, maximumProgress, currentProgress});
            }
          else {
              emit this->reply(jsonObject);
            }
        }
    }
}


void CMakeClient::CMakeClient::sendRequest(const Request &request)
{
  if(!m_cmakeProcess.waitForStarted())
    return;

  QJsonDocument doc;
  QByteArray data;
  doc.setObject(request.object());

  data += REQUEST_HEADER;
  data += '\n';
  data += doc.toJson();
  data += '\n';
  data += REQUEST_TAIL;
  data += '\n';

  m_cmakeProcess.write(data);
//  m_cmakeProcess.waitForReadyRead();
}


void CMakeClient::CMakeClient::stopCMakeServer()
{
  m_cmakeProcess.waitForBytesWritten();
  m_cmakeProcess.close();
}

