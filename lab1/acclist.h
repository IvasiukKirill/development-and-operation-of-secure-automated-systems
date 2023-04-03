#ifndef ACCLIST_H
#define ACCLIST_H
#include <QDialog>
#include "dbmodel.h"

namespace Ui {
class AccList;
}

class AccList : public QDialog {
  Q_OBJECT

 public:
  explicit AccList(QString key, QWidget *parent = nullptr);
  ~AccList();
  QString key;

 private slots:
  void addRow(const DBModel::Row row);
  void on_addAccBtn_clicked();
  void on_searchButton_clicked();

  void on_searchInput_cursorPositionChanged(int arg1, int arg2);

  void on_tableWidget_cellDoubleClicked(int row, int column);

private:
  Ui::AccList *ui;
};

#endif  // ACCLIST_H
