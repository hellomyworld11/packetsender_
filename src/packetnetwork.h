/*
 * This file is part of Packet Sender
 *
 * Licensed GPL v2
 * http://PacketSender.com/
 *
 * Copyright NagleCode, LLC
 *
 */
#ifndef PACKETNETWORK_H
#define PACKETNETWORK_H

#include <QObject>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QTcpServer>
#include <QStringList>
#include <QTime>
#include <QThread>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QDebug>
#include <QDateTime>
#include <QHash>
#include <QHostAddress>
#include "tcpthread.h"
#include "packet.h"
#ifndef CONSOLE_BUILD
#include "persistentconnection.h"
#endif
#include <threadedtcpserver.h>

class PacketNetwork : public QObject
{
        Q_OBJECT
    public:
        explicit PacketNetwork(QObject *parent = nullptr);
        void init();

        QString debugQByteArray(QByteArray debugArray);

        QString getUDPPortString();
        QString getTCPPortString();
        QString getSSLPortString();

        QList<int> getUDPPortsBound();
        QList<int> getTCPPortsBound();
        QList<int> getSSLPortsBound();

        QStringList multicastStringList();

        bool consoleMode;

        void kill();
        QString responseData;
        bool sendResponse;
        bool sendSmartResponse;
        bool activateUDP;
        bool activateTCP;
        bool activateSSL;
        bool receiveBeforeSend;
        bool translateMacroSend;
        int delayAfterConnect;
        bool persistentConnectCheck;
        bool isSecure;
        void setIPmode(int mode);
        static QString getIPmode();

        bool UDPListening();
        bool TCPListening();
        bool SSLListening();

        bool IPv6Enabled();
        bool IPv4Enabled();

        QNetworkAccessManager * http;

        QList<SmartResponseConfig> smartList;

        static QHostAddress resolveDNS(QString hostname);

        static bool isMulticast(QString ip);

        void joinMulticast(QString address);
        bool canSendMulticast(QString address);
        void reJoinMulticast();
        void leaveMulticast();
        QUdpSocket * findMulticast(QString multicast);
signals:
        void packetReceived(Packet sendpacket);
        void toStatusBar(const QString & message, int timeout = 0, bool override = false);
        void packetSent(Packet sendpacket);


public slots:
        void packetReceivedECHO(Packet sendpacket);
        void toStatusBarECHO(const QString & message, int timeout = 0, bool override = false);
        void packetSentECHO(Packet sendpacket);
        void readPendingDatagrams();
        void disconnected();
        void packetToSend(Packet sendpacket);

private slots:
        void httpFinished(QNetworkReply* pReply);
        void httpError(QNetworkRequest* pReply);
        void sslErrorsSlot(QNetworkReply *reply, const QList<QSslError> &errors);

private:
        //mapping of joined multicast groups
        //format is 239.255.120.19:5009, 239.255.120.23:5009
        QStringList joinedMulticast;

        QList<ThreadedTCPServer *> allTCPServers();

        QList<QNetworkAccessManager *> httpList;

        QList<TCPThread *> tcpthreadList;
#ifdef CONSOLE_BUILD
        QList<void *> pcList;
#else
        QList<PersistentConnection *> pcList;
#endif
        //PS now supports any number of servers.
        QList<ThreadedTCPServer *> tcpServers;
        QList<ThreadedTCPServer *> sslServers;
        QList<QUdpSocket *> udpServers;

};

#endif // PACKETNETWORK_H
