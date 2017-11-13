#include "channelelement.h"

ChannelElement::ChannelElement(QObject *parent)
   : QAbstractItemModel(parent)
{
}

QVariant ChannelElement::headerData(int section, Qt::Orientation orientation, int role) const
{
   // FIXME: Implement me!
}

bool ChannelElement::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
   if (value != headerData(section, orientation, role)) {
      // FIXME: Implement me!
      emit headerDataChanged(orientation, section, section);
      return true;
   }
   return false;
}

QModelIndex ChannelElement::index(int row, int column, const QModelIndex &parent) const
{
   // FIXME: Implement me!
}

QModelIndex ChannelElement::parent(const QModelIndex &index) const
{
   // FIXME: Implement me!
}

int ChannelElement::rowCount(const QModelIndex &parent) const
{
   if (!parent.isValid())
      return 0;

   // FIXME: Implement me!
}

int ChannelElement::columnCount(const QModelIndex &parent) const
{
   if (!parent.isValid())
      return 0;

   // FIXME: Implement me!
}

bool ChannelElement::hasChildren(const QModelIndex &parent) const
{
   // FIXME: Implement me!
}

bool ChannelElement::canFetchMore(const QModelIndex &parent) const
{
   // FIXME: Implement me!
   return false;
}

void ChannelElement::fetchMore(const QModelIndex &parent)
{
   // FIXME: Implement me!
}

QVariant ChannelElement::data(const QModelIndex &index, int role) const
{
   if (!index.isValid())
      return QVariant();

   // FIXME: Implement me!
   return QVariant();
}

bool ChannelElement::setData(const QModelIndex &index, const QVariant &value, int role)
{
   if (data(index, role) != value) {
      // FIXME: Implement me!
      emit dataChanged(index, index, QVector<int>() << role);
      return true;
   }
   return false;
}

Qt::ItemFlags ChannelElement::flags(const QModelIndex &index) const
{
   if (!index.isValid())
      return Qt::NoItemFlags;

   return Qt::ItemIsEditable; // FIXME: Implement me!
}

bool ChannelElement::insertRows(int row, int count, const QModelIndex &parent)
{
   beginInsertRows(parent, row, row + count - 1);
   // FIXME: Implement me!
   endInsertRows();
}

bool ChannelElement::insertColumns(int column, int count, const QModelIndex &parent)
{
   beginInsertColumns(parent, column, column + count - 1);
   // FIXME: Implement me!
   endInsertColumns();
}

bool ChannelElement::removeRows(int row, int count, const QModelIndex &parent)
{
   beginRemoveRows(parent, row, row + count - 1);
   // FIXME: Implement me!
   endRemoveRows();
}

bool ChannelElement::removeColumns(int column, int count, const QModelIndex &parent)
{
   beginRemoveColumns(parent, column, column + count - 1);
   // FIXME: Implement me!
   endRemoveColumns();
}
