#ifndef SUDOKUMODEL_H
#define SUDOKUMODEL_H

#include <QAbstractTableModel>

class SudoKuModel : public QAbstractTableModel
{
    Q_OBJECT

    int m_data[9][9];

    bool searchForSolution(QString board);

public:
    explicit SudoKuModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    inline void initializeFromString(QString number);
    inline QString toString();

signals:

public slots:
    void solve();

};

#endif // SUDOKUMODEL_H
