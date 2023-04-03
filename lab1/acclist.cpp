#include "acclist.h"
#include <QListWidget>
#include <QListWidgetItem>
#include "QFile"
#include <QClipboard>
#include "QJsonArray"
#include "QJsonDocument"
#include "QJsonObject"
#include "addacc.h"
#include "crypt.h"
#include "dbmodel.h"
#include "qaesencryption.h"
#include "ui_acclist.h"

AccList::AccList(QString key, QWidget *parent)  // передаем ключ в это окно
    : QDialog(parent), ui(new Ui::AccList) {
  ui->setupUi(this);
  this->key = key;
  qInfo() << "key in acclist" << this->key;
  DBModel db(this->key);
  auto json = db.json;
  for (int i = 0; i < json.size(); ++i) {
    this->addRow(db.getRow(i));
  }
}

AccList::~AccList() { delete ui; }

void AccList::addRow(const DBModel::Row row) {  // добавление записей в GUI


      ui->tableWidget->insertRow(ui->tableWidget->rowCount());
      ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(row.url));
      QTableWidgetItem *item = new QTableWidgetItem;
      item->setText("********");
      item->setData(Qt::UserRole, row.login);
      ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, item );

      QTableWidgetItem *item2 = new QTableWidgetItem;
      item2->setText("********");
      item2->setData(Qt::UserRole, row.pass);
      ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2, item2 );

}

void AccList::on_addAccBtn_clicked() {  // добавление записей в json
  addAcc NewWindow;
  NewWindow.setModal(true);
  if (NewWindow.exec() == QDialog::Accepted) {
    auto row = NewWindow.getInputValues();

    DBModel db(this->key);
    auto eRow = db.encrypt(row);
    this->addRow(eRow);

    db.writeRowToJSON(eRow);
  }
}

void AccList::on_searchButton_clicked() {
        for (int var = 0; var < ui->tableWidget->rowCount(); ++var) {
            ui->tableWidget->setRowHidden(var,false);
            if(ui->tableWidget->item(var,0)->text().contains(ui->searchInput->text()) == 0){
                ui->tableWidget->hideRow(var);
            }
        }
}



void AccList::on_searchInput_cursorPositionChanged(int arg1, int arg2)
{

}


void AccList::on_tableWidget_cellDoubleClicked(int row, int column)
{
    QByteArray etext = ui->tableWidget->item(row,column)->data(Qt::UserRole).toByteArray();
    QString text = Crypt::decrypt(etext,this->key,this->key);
    QApplication::clipboard()->setText(text);
}

