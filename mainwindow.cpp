#include "mainwindow.h"
#include <QDialog>
#include <QUrl>
#include <QPushButton>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget* mainWidget = new QWidget(this);
    LinkButton *text_a = new LinkButton("reg_test_a", mainWidget);
    LinkButton *text_b = new LinkButton("reg_test_b", mainWidget);

    mainWidget->setLayout(new QVBoxLayout);
    mainWidget->layout()->addWidget(text_a);
    mainWidget->layout()->addWidget(text_b);

    setCentralWidget(mainWidget);


    connect(text_a, &QPushButton::clicked, this, [this](){
        showHint("file:///html/text_a.html", QCursor::pos());
    });

    connect(text_b, &QPushButton::clicked, this, [this](){
        showHint("file:///html/text_b.html", QCursor::pos());
    });

}


bool MainWindow::showHint(const QString file, const QPoint top_left)
{
    FramelessHtmlViewer *dialog = new FramelessHtmlViewer(file, this);
    dialog->move(top_left.x(), top_left.y());
    dialog->resize(400, 300);
    dialog->show();


    return true;
}

MainWindow::~MainWindow()
{
    qDebug() << Q_FUNC_INFO;
}
