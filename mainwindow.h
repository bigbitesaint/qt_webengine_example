#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QFocusEvent>
#include <QDebug>
#include <QSizePolicy>
#include <QtWebEngineWidgets>
#include <QPushButton>
#include <QVBoxLayout>
#include <QCursor>



class FramelessHtmlViewer : public QDialog
{
    public:
        explicit FramelessHtmlViewer(const QString file, QWidget *parent = nullptr)
            :QDialog(parent, Qt::CustomizeWindowHint)
        {

            m_view.load(QUrl(file));

            //setModal(true);
            QVBoxLayout *layout = new QVBoxLayout;

            QHBoxLayout *btn_layout = new QHBoxLayout;
            btn_layout->setAlignment(Qt::AlignRight);

            QPushButton *close_btn = new QPushButton("X", this);
            close_btn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
            close_btn->setCursor(Qt::PointingHandCursor);
            close_btn->setStyleSheet("border:none;");


            connect(close_btn, &QPushButton::clicked, this, &QWidget::deleteLater);

            btn_layout->addWidget(close_btn);
            layout->addLayout(btn_layout);
            layout->addWidget(&m_view);
            setLayout(layout);

        }

        virtual ~FramelessHtmlViewer() override
        {
            qDebug() << "DESTRUCTOR";
        }
    protected:


        void mousePressEvent(QMouseEvent *event) override
        {
            m_drag_started = true;
            m_offset = this->pos() - mapToGlobal(event->pos());
        }



        void mouseReleaseEvent(QMouseEvent *event) override
        {
            Q_UNUSED(event);
            m_drag_started = false;
        }


        void mouseMoveEvent(QMouseEvent *event) override
        {
            if (m_drag_started)
            {
                move(mapToGlobal(event->pos()) + m_offset);
            }
        }


    private:
        bool m_drag_started;
        QPoint m_offset;
        QWebEngineView m_view;
};


class LinkButton : public QPushButton
{
    public:
        explicit LinkButton(const QString label, QWidget* parent=nullptr)
            :QPushButton(label, parent)
        {
            setStyleSheet("QPushButton{border:none;}  QPushButton:hover {color: blue; text-decoration: underline;}");
            installEventFilter(this);
            setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum));
        }

    protected:
        bool eventFilter(QObject *src, QEvent *event)
        {
            Q_UNUSED(src)
            if (event->type() == QEvent::Enter)
            {
                setCursor(Qt::PointingHandCursor);
                return true;
            }
            else if (event->type() == QEvent::Leave)
            {
                setCursor(Qt::ArrowCursor);
                return true;
            }

            return false;
        }
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow() override;

    protected:
        void closeEvent(QCloseEvent *event) override
        {
            Q_UNUSED(event);
            //dumpObjectTree();
            deleteLater();
        }

    private:
        bool showHint(const QString file, const QPoint top_left);
};

#endif // MAINWINDOW_H
