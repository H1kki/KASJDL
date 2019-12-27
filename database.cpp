#include "database.h"

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

DataBase::~DataBase()
{

}


void DataBase::connectToDataBase()
{
    if(!QFile(DATABASE_NAME).exists()){
        this->restoreDataBase();
    } else {
        this->openDataBase();
    }
}

bool DataBase::restoreDataBase()
{
    if(this->openDataBase()){
        if(!this->createTable()){
            return false;
        } else {
            return true;
        }
    } else {
        qDebug() << "Не удалось восстановить базу данных";
        return false;
    }
    return false;
}

bool DataBase::openDataBase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName(DATABASE_NAME);
    if(db.open()){
        return true;
    } else {
        return false;
    }
}

void DataBase::closeDataBase()
{
    db.close();
}

bool DataBase::createTable()
{
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE " TABLE " ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            TABLE_NAME      " VARCHAR(255)    NOT NULL,"
                            TABLE_COUNT     " INTEGER         NOT NULL,"
                            TABLE_PRICE     " DOUBLE          NOT NULL,"
                            TABLE_DATE      " DATE            NOT NULL"
                        " )"
                    )){
        qDebug() << "DataBase: error of create " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

bool DataBase::inserIntoTable(const QVariantList &data)
{
    QSqlQuery query;
    query.prepare("INSERT INTO " TABLE " ( " TABLE_NAME ", "
                                             TABLE_COUNT ", "
                                             TABLE_PRICE ", "
                                             TABLE_DATE " ) "
                  "VALUES (:Name, :Count, :Price, :Date )");
    query.bindValue(":Name",       data[0].toString());
    query.bindValue(":Count",      data[1].toInt());
    query.bindValue(":Price",      data[2].toDouble());
    query.bindValue(":Date",       data[3].toDate());
    if(!query.exec()){
        qDebug() << "error insert into " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
}

bool DataBase::deleteData(int id){
    QSqlQuery query;
    if(!query.exec("DELETE FROM " TABLE "WHERE id = " + QString::number(id) + ")")){
        qDebug() << "error delete from " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    }
    else {
        return true;
    }
}
