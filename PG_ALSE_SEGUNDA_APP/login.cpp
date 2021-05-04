#include "login.h"
#include "ui_login.h"
#include "QMessageBox"
#include "QDebug"

LOGIN::LOGIN(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LOGIN)
{
    ui->setupUi(this);
}

LOGIN::~LOGIN()
{
    delete ui;
}

void LOGIN::on_BOTON_LOGIN2_clicked()
{
    QString user=ui->user_line->text();
    QString passw=ui->passw_line->text();
    QSqlQuery buscar;
    QString pass;
    QString consulta;
    QString nombre;
    consulta.append("SELEC * FROM user where user='"+user+"'");
    buscar.prepare(consulta);
    if(buscar.exec())
    {
        qDebug()<<"consulta realizada";
        while(buscar.next())
        {
            pass=buscar.value(1).toByteArray().constData();
            nombre=buscar.value(0).toByteArray().constData();
        }
    }else
    {
        qDebug()<<"Error de consulta";
        QMessageBox::critical(this,tr("ERROR"),tr("Usuario no existe, por favor verifique"));
    }
    if(pass==passw)
    {
        QMessageBox::information(this,tr("Bienvenido"),tr("Bienvenido: %1").arg(nombre));
    }
    else
    {
        QMessageBox::critical(this,tr("ERROR"),tr("Contraseña Incorrecta"));
    }
}
