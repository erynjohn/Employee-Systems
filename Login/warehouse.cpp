#include "warehouse.h"
#include "ui_warehouse.h"
#include "employeemainmenu.h"
#include "loginpage.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>
#include <QString>
#include <QMessageBox>

warehouse::warehouse(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::warehouse)

{
    ui->setupUi(this);
    refreshtable();

}

warehouse::~warehouse()
{
    delete ui;
}
void warehouse::on_pushButton_Wback_clicked()
{

    // hide old window and show new window from object //
        this->hide();
        EmployeeMainMenu empMenu;
        empMenu.setModal(true);
        empMenu.exec();
}
void warehouse::on_pushButton_save_WT_clicked()
{
    //Save info into warehouse database//
    QString Wname, line, qty, material, status;
    Wname=ui->lineEdit_Wname->text();
    material=ui->lineEdit_material_WT->text();
    line=ui->lineEdit_linenum->text();
    qty=ui->lineEdit_qty->text();
    status=ui->lineEdit_status->text();

    QSqlQuery query;
    query.prepare( "INSERT INTO Warehouse (WarehouseName, LineNumber,Quantity, Material, Status) VALUES (?, ?, ?, ?, ?)" );
    query.addBindValue(Wname);
    query.addBindValue(line);
    query.addBindValue(qty);
    query.addBindValue(material);
    query.addBindValue(status);


    {
        if(!query.exec())
        {
            QMessageBox::warning(this, "Error", "Duplicate ID or Line Item!");
        }
    }
    refreshtable();

}

void warehouse::refreshtable()
{
    LoginPage conn;

    // Refresh tool database //
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery* qry = new QSqlQuery(conn.db);

    qry->prepare("SELECT * FROM Warehouse");
    qry->exec();
    model->setQuery(*qry);
    ui->tableView->setModel(model);
    qDebug() << (model->rowCount());

    QTableView *view = new QTableView;
    view->setModel(model);
    view->resizeColumnsToContents();
}

void warehouse::on_pushButton_delete_WT_clicked()
{
    // Delete selected row using badge number //
    QString line;
    line=ui->lineEdit_linenum_delete->text();
    QSqlQuery query;
    query.prepare("DELETE FROM Warehouse WHERE LineNumber='"+line+"'");

    {
        if(!query.exec())
        {
            QMessageBox::warning(this, "Error", "Duplicate ID or Line Item!");
        }
    }
    refreshtable();

}

void warehouse::on_pushButton_Update_WT_clicked()
{
    //Update warehouse database //
    QString Wname, qty, material, status, line;
    Wname=ui->lineEdit_Wname->text();
    line=ui->lineEdit_linenum->text();
    qty=ui->lineEdit_qty->text();
    material=ui->lineEdit_material_WT->text();
    status=ui->lineEdit_status->text();

    QSqlQuery query;
    query.prepare("UPDATE Warehouse SET WarehouseName='"+Wname+"', LineNumber='"+line+"', Quantity='"+qty+"', Material='"+material+"',Status='"+status+"' WHERE LineNumber='"+line+"'");
    {
        if(!query.exec())
        {
            QMessageBox::warning(this, "Error", "Duplicate ID or Line Item!");
        }

    }
    refreshtable();
}
