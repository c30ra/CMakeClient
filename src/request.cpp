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

#include "request.h"

CMakeClient::Request::~Request()
{

}

CMakeClient::HandShakeRequest::HandShakeRequest(const QString &sourceDirectory,
                                   const QString &buildDirectory,
                                   const QString &generator)
  : m_sourceDirectory{sourceDirectory},
    m_buildDirectory{buildDirectory},
    m_generator{generator},
    m_toolSet{QString()},
    m_platform{QString()}
{  }

CMakeClient::HandShakeRequest::~HandShakeRequest()
{  }

void CMakeClient::HandShakeRequest::setPlatform(const QString &platform)
{
  m_platform = platform;
}

void CMakeClient::HandShakeRequest::setToolSet(const QString &toolSet)
{
  m_toolSet = toolSet;
}

QJsonObject CMakeClient::HandShakeRequest::object() const
{
  static const auto MAJOR_VERSION = 1;
  auto jsonObject = QJsonObject();

//  jsonObject["cookie"] = "zimstern";
  jsonObject["type"] = "handshake";

  auto protocolVersion = QJsonObject();
  protocolVersion["major"] = MAJOR_VERSION;

  jsonObject["protocolVersion"] = protocolVersion;
  jsonObject["sourceDirectory"] = m_sourceDirectory;
  jsonObject["buildDirectory"] = m_buildDirectory;
  jsonObject["generator"] = m_generator;

  if(!m_platform.isEmpty()){
      jsonObject["platform"] = m_platform;
    }
  if(!m_toolSet.isEmpty()){
      jsonObject["toolset"] = m_toolSet;
    }

  return jsonObject;
}


CMakeClient::ConfigureRequest::ConfigureRequest()
{ }

CMakeClient::ConfigureRequest::~ConfigureRequest()
{ }

void CMakeClient::ConfigureRequest::setCachedArgs(QJsonArray &args)
{
  m_cachedArgs = args;
}

QJsonObject CMakeClient::ConfigureRequest::object() const
{
  auto jsonObject = QJsonObject();
  jsonObject["type"] = "configure";
  jsonObject["cacheArguments"] = m_cachedArgs;

  return jsonObject;
}

CMakeClient::GeneralRequest::GeneralRequest(const QString &requestName)
  : m_request{requestName}
{  }

CMakeClient::GeneralRequest::~GeneralRequest()
{  }

QJsonObject CMakeClient::GeneralRequest::object() const
{
  auto jsonObject = QJsonObject();
  jsonObject["type"] = m_request;

  return jsonObject;
}
