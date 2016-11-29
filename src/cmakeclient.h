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
