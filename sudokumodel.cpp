#include "sudokumodel.h"

#include <QColor>
#include <QDebug>

SudoKuModel::SudoKuModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    initializeFromString("530070000600195000098000060800060003400803001700020006060000280000419005000080079");
}

void SudoKuModel::solve(){
    if(searchForSolution(toString()))
        qDebug()<<"The Game has at least 1 solution";
    else qDebug()<<"The Game has no solutions";
}

bool SudoKuModel::searchForSolution(QString board){
    int i = board.indexOf('0');
    //qDebug()<<board;

    if(i < 0){
       //If the search is over and there is a solution generate the board from that and end this
       initializeFromString(board);
       return true;
    }

    //from a given block, we can fill in 0----------------->9 ; each leading to a possible path for finding the solution
    bool eliminatePath[10];
    for(int j =0;j < 10; j++)
        eliminatePath[j] = false;

    //Now simply store the numbers which are already occuring in the paths that we want to eliminate
    for(int j=0; j < 81; j++){
        if( (i/9 == j/9)|| // if it is in the same row
                (i -j)%9 == 0 ||  //if it is in the same column
                (i/27 == j/27 && (i%9)/3 == (j%9)/3) ){ //same box
            eliminatePath[board[j].toLatin1()-'0'] = true;
        }
    }

    //explore the remaining paths which arent meant to be eliminated
    for(int j = 1; j <= 9;j ++){
        if(!eliminatePath[j]){
            QString next = board.left(i)+QString::number(j)+board.mid(i+1);
            //qDebug()<<next;
            if(searchForSolution( next ))
                return true;
        }
    }

    return false;
}

int SudoKuModel::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent)
    return 9;
}

int SudoKuModel::columnCount(const QModelIndex &parent) const{
    Q_UNUSED(parent)
    return 9;
}

QVariant SudoKuModel::data(const QModelIndex &index, int role) const{
    if(index.isValid()){
        int r = index.row(), c = index.column();

        if(role == Qt::DisplayRole){
            if(!m_data[r][c])
                return "";
            else
                return QString::number( m_data[index.row()][index.column()] );
            }

        //Some fancy formatting because we are too lazy to build
        //a custom delegate to do this entirely in View
        if(role == Qt::BackgroundColorRole){
            if( (r/3)%2 || (c/3)%2 ){
                if(r/3 == c/3) return QColor(250,250,250);
                else return QColor(140,240,140);
            }
            else return QColor(255,255,255);
        }
    }
    return QVariant();
}

bool SudoKuModel::setData(const QModelIndex &index, const QVariant &value, int role){
    QString v = value.toString();
    if(v == "")
        v = "0";
    int result = v.toInt();
    if(index.isValid() && role == Qt::EditRole &&
            result >= 0 && result <= 9 &&
            m_data[index.row()][index.column()] != result ){

        m_data[index.row()][index.column()] = result;
        emit(dataChanged(index,index));
        return true;
    }

    return false;
}

Qt::ItemFlags SudoKuModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return Qt::ItemIsSelectable |  Qt::ItemIsEditable | Qt::ItemIsEnabled ;
}

void SudoKuModel::initializeFromString(QString number){
    for(int i = 0; i < 81; i++ )
        m_data[i/9][i%9] = number[i].toLatin1() - '0';
    QModelIndex start = createIndex(0,0);
    QModelIndex end = createIndex(9,9);
    emit(dataChanged(start,end));
}

QString SudoKuModel::toString(){
    QString result = "";
    for(int i=0; i < 9; i++)
        for(int j=0; j < 9; j++)
            //if(m_data[i][j])
              result += QString::number (m_data[i][j]);
            //else result += "0";

    return result;
}
