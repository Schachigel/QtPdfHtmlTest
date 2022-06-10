#include <QTextDocument>
#include <QPrinter>
#include <QFile>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
namespace {
QString fileToString( const QString& filename)
{
    QFile f(filename);
    if( ! f.open(QFile::ReadOnly))
        return "file open error";
    return f.readAll();
}
void stringToFile( const QString& content, const QString& fullFileName)
{
    QFile textFile(fullFileName);
    textFile.open(QFile::WriteOnly);
    textFile.write(content.toUtf8());
    textFile.close();
}

}

void MainWindow::on_btnGo_clicked()
{
    const QString html =fileToString ("../in.html");
    const QString css =fileToString( "../in.css");

    QPrinter printer;
    // set A4
    QPageLayout pl =printer.pageLayout ();
    pl.setPageSize (QPageSize(QPageSize::A4));
    printer.setPageLayout (pl);

    QTextDocument doc;
    // adjust to printer pagesizse
    doc.setPageSize (pl.pageSize ().size (QPageSize::Unit::Point));

    doc.setDefaultStyleSheet (css);
    doc.setHtml (html);

    printer.setOutputFileName ("../out.pdf");
    doc.print(&printer);

    stringToFile (doc.toHtml (), "../out.html");
}

