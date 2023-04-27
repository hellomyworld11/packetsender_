#include "multicastsetup.h"
#include "ui_multicastsetup.h"

#include <QMessageBox>

MulticastSetup::MulticastSetup(PacketNetwork *pNetwork, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MulticastSetup)
{
    this->packetNetwork = pNetwork;
    ui->setupUi(this);

    setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    setWindowTitle(tr("IPv4 Multicast Setup (Experimental)"));

    init();
}

void MulticastSetup::setIP(QString ip)
{
    ui->ipaddressEdit->setText(ip);
    ui->joinButton->setFocus();
}

void MulticastSetup::init()
{
    QList<int> udpPorts = this->packetNetwork->getUDPPortsBound();

    if(udpPorts.isEmpty()) {
        ui->infoLabel->setText(tr("There are no bound UDP ports"));
    } else {
        int joinedPort = udpPorts.first();
        QString infoText = tr("UDP socket bound to ");
        infoText.append(QString::number(joinedPort));
        infoText.append(tr(" will join the multicast group"));
        ui->infoLabel->setText(infoText);
    }



    QStringList mcastStringList = packetNetwork->multicastStringList();
    ui->mcastLW->clear();
    ui->mcastLW->addItems(mcastStringList);
}

MulticastSetup::~MulticastSetup()
{
    delete ui;
}

void MulticastSetup::on_joinButton_clicked()
{

    QString ip = ui->ipaddressEdit->text().trimmed();

    if (!PacketNetwork::isMulticast(ip)) {
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Not Multicast."));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText(tr("IP must be an IPv4 multicast address.\n(224.0.0.0 to 239.255.255.255)"));
        msgBox.exec();
        ui->ipaddressEdit->setFocus();
        ui->ipaddressEdit->selectAll();
        return;
    }


    if(!packetNetwork->IPv4Enabled()) {

        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("IPv4-only."));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText(tr("Packet Sender supports multicast when binded to IPv4. \nTurn off IPv6 and switch to IPv4 mode?"));
        int yesno = msgBox.exec();
        if (yesno == QMessageBox::No) {
            return;
        }
        packetNetwork->setIPmode(4);
        packetNetwork->kill();
        packetNetwork->init();

    }
    packetNetwork->joinMulticast(ip);
    QDEBUGVAR(packetNetwork->multicastStringList());
    init();
}

void MulticastSetup::on_leaveButton_clicked()
{

    QDEBUG();
    packetNetwork->leaveMulticast();
    init();
}
