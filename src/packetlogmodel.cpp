#include "packetlogmodel.h"

#include <QClipboard>
#include <QApplication>

#include "settings.h"
PacketLogModel::PacketLogModel(QObject *parent)
    : QAbstractTableModel(parent)
{

    packetList.clear();
    tableHeaders.clear();
    useEllipsis = true;
}

QVariant PacketLogModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            return tableHeaders.at(section);
        }
    }
    return QVariant();
}

int PacketLogModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    //QDEBUGVAR(packetList.size());

    return packetList.size();

}

int PacketLogModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return tableHeaders.size();

}

QVariant PacketLogModel::data(const QModelIndex &index, int role) const
{
    const static QString TIME_STR = Settings::logHeaderTranslate(Settings::TIME_STR);
    const static QString FROMIP_STR = Settings::logHeaderTranslate(Settings::FROMIP_STR);
    const static QString FROMPORT_STR = Settings::logHeaderTranslate(Settings::FROMPORT_STR);
    const static QString TOADDRESS_STR = Settings::logHeaderTranslate(Settings::TOADDRESS_STR);
    const static QString TOPORT_STR = Settings::logHeaderTranslate(Settings::TOPORT_STR);
    const static QString METHOD_STR = Settings::logHeaderTranslate(Settings::METHOD_STR);
    const static QString ERROR_STR = Settings::logHeaderTranslate(Settings::ERROR_STR);
    const static QString ASCII_STR = Settings::logHeaderTranslate(Settings::ASCII_STR);
    const static QString HEX_STR = Settings::logHeaderTranslate(Settings::HEX_STR);


    if (!index.isValid())
        return QVariant();


    int row = index.row();
    Packet packet = packetList.at(row);

    if (role == Qt::DecorationRole) {
        if (index.column() == 0) {

            return packet.getIcon();

        }
        return QVariant();
    }

    if (role == Qt::UserRole)
    {
        return row;
    }

    if (role == Qt::ToolTipRole)
    {
        return (tr("Data portion is ") + QString::number(packet.getByteArray().size()) + tr(" bytes"));
    }

    if ((role == Qt::DisplayRole) || (role == Qt::EditRole))
    {
        if(index.column() == tableHeaders.indexOf(TIME_STR)) {
            return packet.timestamp.toString(DATETIMEFORMAT);
        }
        if(index.column() == tableHeaders.indexOf(FROMIP_STR)) {
            return packet.fromIP;
        }
        if(index.column() == tableHeaders.indexOf(FROMPORT_STR)) {
            if(packet.fromPort == 0) {
                return QVariant();
            } else {
            return packet.fromPort;
            }
        }
        if(index.column() == tableHeaders.indexOf(TOADDRESS_STR)) {
            return packet.toIP;
        }
        if(index.column() == tableHeaders.indexOf(TOPORT_STR)) {
            if(packet.port == 0) {
                return QVariant();
            } else {
            return packet.port;
            }
        }
        if(index.column() == tableHeaders.indexOf(METHOD_STR)) {
            return packet.tcpOrUdp;
        }
        if(index.column() == tableHeaders.indexOf(ERROR_STR)) {
            return packet.errorString;
        }
        if(index.column() == tableHeaders.indexOf(ASCII_STR)) {
            QString ascii = packet.asciiString();
            if(packet.isHTTP()) {
                ascii = packet.requestPath;
            }
            if(useEllipsis && (ascii.size() > 1024)) {
                ascii.truncate(1000);
                ascii.append("[...]");
            }
            return ascii;
        }
        if(index.column() == tableHeaders.indexOf(HEX_STR)) {
            QString hex = packet.hexString;
            if(packet.isHTTP()) {
                hex = packet.asciiString();
            }
            if(useEllipsis && (hex.size() > 1024)) {
                hex.truncate(1000);
                hex.append("[...]");
            }
            return hex;
        }

    }

    return QVariant();

}

bool PacketLogModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

    Q_UNUSED(index)
    Q_UNUSED(value)

    if (role == Qt::EditRole)
    {
        //do nothing.
    }
    return true;

}

Qt::ItemFlags PacketLogModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}


const Packet PacketLogModel::getPacket(QModelIndex index)
{

    int row = index.row();
    if(packetList.size() >= row) {
        return packetList.at(row);
    }

    const Packet pkt;
    return  pkt;

}

int PacketLogModel::size()
{
    return packetList.size();

}

const Packet PacketLogModel::getPacket(int index)
{
    if(packetList.size() >= index) {
        return packetList.at(index);
    }

    const Packet pkt;
    return  pkt;

}

void PacketLogModel::setTableHeaders(QStringList headers)
{
    beginResetModel();
    tableHeaders = headers;
    endResetModel();
}

void PacketLogModel::removeFirst()
{
    packetList.removeFirst();
}


void PacketLogModel::removeLast()
{
    packetList.removeLast();
}

const QList<Packet> PacketLogModel::list()
{
    const QList<Packet> retList = packetList;

    return retList;
}

void PacketLogModel::clear()
{
    beginResetModel();
    packetList.clear();
    endResetModel();
}

void PacketLogModel::prepend(Packet packet)
{
    beginResetModel();
    packetList.prepend(packet);
    endResetModel();

    QDEBUGVAR(packetList.size());
}

void PacketLogModel::append(Packet packet)
{
    beginResetModel();
    packetList.append(packet);
    endResetModel();

    QDEBUGVAR(packetList.size());
}

void PacketLogModel::setPacketData(QList<Packet> packets)
{
    beginResetModel();
    packetList.clear();
    packetList.append(packets);
    endResetModel();
}
