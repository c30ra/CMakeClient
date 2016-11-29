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

#ifndef CMAKECLIENTSIDE_H
#define CMAKECLIENTSIDE_H

#include <memory>

#include <QObject>
#include <QProcess>

#include <QJsonObject>

namespace CMakeClient {
  class Request;
  struct ProgressReply
  {
    int progressMinimum;
    int progressMaximum;
    int currentProgress;
  };

  class CMakeClient : public QObject
  {
    Q_OBJECT
  public:
    CMakeClient();
    ~CMakeClient();
    bool startCMakeServer();

    void sendRequest(const Request &request);

  public slots:
    void stopCMakeServer();

  signals:
    void errorReply(QString inReplyTo, QString errorMessage);
    void messageReply(QString inReplyTo, QString message);
    void progressReply(const ProgressReply &reply);
    void reply(QJsonObject object);

  private:
    QProcess m_cmakeProcess;

  private slots:
    void processReply();
  };

} //namespace CMakeClient

#endif // CMAKECLIENTSIDE_H
