#include "channellist.h"

ChannelList::ChannelList(QObject *parent)
   : QAbstractListModel(parent)
{
   m_data.append("1");
   m_data.append("2");
   m_data.append("3");
}

QVariant ChannelList::headerData(int section, Qt::Orientation orientation, int role) const
{
   // FIXME: Implement me!
}

bool ChannelList::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
   if (value != headerData(section, orientation, role)) {
      // FIXME: Implement me!
      emit headerDataChanged(orientation, section, section);
      return true;
   }
   return false;
}

int ChannelList::rowCount(const QModelIndex &parent) const
{
   // For list models only the root node (an invalid parent) should return the list's size. For all
   // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
   if (parent.isValid())
      return 0;

   // FIXME: Implement me!
   return m_data.size();
}

QVariant ChannelList::data(const QModelIndex &index, int role) const
{
   if (!index.isValid())
      return QVariant();

   // FIXME: Implement me!
   switch (role)
   {
    case ColorRole:
        return QVariant(index.row() < 2 ? "orange" : "skyblue");
    case TextRole:
        return m_data.at(index.row());
    default:
        return QVariant();
    }
}

bool ChannelList::setData(const QModelIndex &index, const QVariant &value, int role)
{
   if (data(index, role) != value) {
      // FIXME: Implement me!
      switch (role)
      {
       case ColorRole:
           return false;   // This property can not be set
       case TextRole:
           m_data[index.row()] = value.toString();
           break;
       default:
           return false;
       }
      emit dataChanged(index, index, QVector<int>() << role);
      return true;
   }
   return false;
}

Qt::ItemFlags ChannelList::flags(const QModelIndex &index) const
{
   if (!index.isValid())
      return Qt::NoItemFlags;

   return Qt::ItemIsEditable; // FIXME: Implement me!
}

bool ChannelList::insertRows(int row, int count, const QModelIndex &parent)
{
   beginInsertRows(parent, row, row + count - 1);
   // FIXME: Implement me!
   endInsertRows();
}

bool ChannelList::removeRows(int row, int count, const QModelIndex &parent)
{
   beginRemoveRows(parent, row, row + count - 1);
   // FIXME: Implement me!
   endRemoveRows();
}

QHash<int, QByteArray> ChannelList::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[ColorRole] = "color";
    roles[TextRole]  = "text";
    roles[DrawArea]  = "area";
    return roles;
}

void ChannelList::add()
{
    beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.append("new");
    endInsertRows();

    m_data[0] = QString("Size: %1").arg(m_data.size());
    QModelIndex index = createIndex(0, 0, static_cast<void *>(0));
    emit dataChanged(index, index);
}
