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

#ifndef REQUEST_H
#define REQUEST_H

#include <QJsonArray>
#include <QJsonObject>

namespace CMakeClient {
  class Request
  {
  public:
    virtual ~Request();
    virtual QJsonObject object() const = 0;

  };

  class HandShakeRequest : public Request
  {
  public:
    explicit HandShakeRequest(const QString &sourceDirectory,
                              const QString &buildDirectory,
                              const QString &generator);

    virtual ~HandShakeRequest();
    void setPlatform(const QString &platform);
    void setToolSet(const QString &toolSet);

  private:
    QString m_sourceDirectory;
    QString m_buildDirectory;
    QString m_generator;
    QString m_toolSet;
    QString m_platform;

    // Request interface
  public:
    virtual QJsonObject object() const override;
  };

  class ConfigureRequest : public Request
  {
  public:
    ConfigureRequest();
    ~ConfigureRequest();

    void setCachedArgs(QJsonArray &args);
    // Request interface
  public:
    virtual QJsonObject object() const override;

  private:
    QJsonArray m_cachedArgs;
  };

  class GeneralRequest : public Request
  {
  public:
    explicit GeneralRequest(const QString &requestName);
    ~GeneralRequest();

    // Request interface
  public:
    virtual QJsonObject object() const override;

  private:
    QString m_request;
  };
} //namespace CMakeClient




#endif // REQUEST_H
