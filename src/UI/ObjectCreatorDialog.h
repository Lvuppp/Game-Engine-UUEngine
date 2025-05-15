#ifndef OBJECTCREATORDIALOG_H
#define OBJECTCREATORDIALOG_H

#include <QDialog>

namespace Ui {
class ObjectCreatorDialog;
}

class ObjectCreatorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ObjectCreatorDialog(QWidget *parent = nullptr);
    ~ObjectCreatorDialog();

private slots:
    void accept() override;

private:
    Ui::ObjectCreatorDialog *ui;
};

#endif // OBJECTCREATORDIALOG_H
