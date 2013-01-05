#ifndef SUDOKUDELEGATE_H
#define SUDOKUDELEGATE_H

#include <QStyledItemDelegate>

class SudoKuDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit SudoKuDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const{
        Q_UNUSED(index)
        Q_UNUSED(option)
        editor->setGeometry(option.rect);
    }
    
signals:
    
public slots:
    
};

#endif // SUDOKUDELEGATE_H
