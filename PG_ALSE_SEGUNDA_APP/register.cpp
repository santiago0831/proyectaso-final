#include "register.h"
#include "ui_register.h"
#include "QDebug"
#include "error_404.h"
#include "QMessageBox"

REGISTER::REGISTER(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::REGISTER)
{
    ui->setupUi(this);
    CrearTabla();
}

REGISTER::~REGISTER()
{
    delete ui;
}
void REGISTER::CrearTabla()
{
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS user("
                    "user VARCHAR(25),"
                    "create_passw VARCHAR(25),"
                    "cnf_passw VARCHAR(25) PRIMARY KEY"
                    ");");
    QSqlQuery crear;
    crear.prepare(consulta);
    if(crear.exec())
    {
        qDebug()<<"Tabla Creada";
    }else
    {
        qDebug()<<"Tabla no creada"<<crear.lastError();
    }
}

void REGISTER::on_BOTON_REGI2_clicked()
{
    QString user=ui->create_user->text();
    QString create_passw=ui->create_passw->text();
    QString cnf_passw=ui->cnf_passw->text();
    qDebug()<<user;
    qDebug()<<create_passw;
    qDebug()<<cnf_passw;
    QSqlQuery insertar_db;
    insertar_db.prepare("INSERT INTO user(user,create_passw,cnf_passw)"
                    "VALUES (:user,:create_passw,:cnf_passw)");
    insertar_db.bindValue(":user",user);
    insertar_db.bindValue(":create_passw",create_passw);
    insertar_db.bindValue(":cnf_passw",cnf_passw);
    if(insertar_db.exec())
    {
        qDebug()<<"Datos ingresados a la tabla";
    }
    else
    {
        qDebug()<<"Error al ingresar los datos"<<insertar_db.lastError();
        QMessageBox::critical (this,tr("ERROR"),tr("El usuario ya está en uso"));
    }

    //error_404 *error = new error_404(0);
    //error->show();

}
