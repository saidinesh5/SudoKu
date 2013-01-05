#include <QComboBox>
#include "sudokudelegate.h"

SudoKuDelegate::SudoKuDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

QWidget* SudoKuDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    Q_UNUSED(option)
    Q_UNUSED(index)

    QComboBox *c = new QComboBox(parent);
    c->setItemData(0,"");
    for(int i=1;i < 10;i++)
        c->setItemData(i,QString::number(i));
    return c;
}

void SudoKuDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const{
    int i = index.data().toInt();
    (reinterpret_cast<QComboBox*>(editor))->setCurrentIndex(i);
}

void SudoKuDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const{
    int i = (reinterpret_cast<QComboBox*>(editor))->currentIndex();
    QString data = i? "":QString::number(i);
    model->setData(index,data);
}
