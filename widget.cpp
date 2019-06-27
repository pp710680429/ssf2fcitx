#include "widget.h"
#include "ui_widget.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QDesktopWidget>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    转换程序 = QCoreApplication::applicationDirPath() + "/ssf2skin";

    this->setWindowIcon(QIcon(QPixmap(":/icon/logo")));

    //让打开时界面显示在正中
    QDesktopWidget *deskdop = QApplication::desktop();
    move((deskdop->width() - this->width())/2, (deskdop->height() - this->height())/2);

    //new变量和建立一些局部变量
    安装存放目录_字符串 = QString(QDir::homePath() + "/.config/fcitx/skin/");
    QDir 安装存放目录(安装存放目录_字符串);
    process =new QProcess;

    //先检查目录存在不，若是不存在，则先建立
    if(!安装存放目录.exists()){
        if(!安装存放目录.mkdir(安装存放目录_字符串)) ;
        QMessageBox::warning(0,tr("提示"),QString("安装存放目录“%1”不存在，请检查！").arg(安装存放目录_字符串),QMessageBox::Ok);
    }

    //设置背景图片
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,QBrush(QPixmap(":/icon/background").scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));// 使用平滑的缩放方式
    this->setPalette(palette);// 给widget加上背景图
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonImport_clicked()
{
    ssf文件 = QFileDialog::getOpenFileNames(
                this,
                tr("请选择ssf文件（搜狗皮肤）"),
                QDir::homePath(),
                "ssf (*.ssf)");

    //如果没有选择，就直接返回
    if(ssf文件.isEmpty()) return;

    //如果选择了文件，则把文件显示在列表中
    for(QString 单个文件 : ssf文件){
        ui->listWidget->addItem(单个文件);
    }
}

void Widget::on_pushButtonTransformation_clicked()
{
    //如果列表是空，则直接返回
    if(ui->listWidget->count() == 0){
        return ;
    }

    //开始进行转换
    for(QString 单个文件: ssf文件){
        int first = 单个文件.lastIndexOf ("/");
        QString 保存文件名 = 单个文件.right (单个文件.length ()-first-1);
        保存文件名 = 安装存放目录_字符串 + 保存文件名;
        qDebug() << 保存文件名;
        process->start(转换程序 , QStringList() << "-i" << 单个文件 << "-o" << 保存文件名);
        process->waitForFinished();
    }

    QMessageBox::information(0,tr("提示"),QString("转换完毕！请检查！"),QMessageBox::Ok);
}

