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
