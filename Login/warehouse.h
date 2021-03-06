#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <QDialog>

namespace Ui {
class warehouse;
}

class warehouse : public QDialog
{
    Q_OBJECT

public:
    explicit warehouse(QWidget *parent = 0);
    ~warehouse();

private slots:
    void on_pushButton_Wback_clicked();

    void on_pushButton_save_WT_clicked();

    void refreshtable();

    void on_pushButton_delete_WT_clicked();

    void on_pushButton_Update_WT_clicked();

private:
    Ui::warehouse *ui;
};

#endif // WAREHOUSE_H
