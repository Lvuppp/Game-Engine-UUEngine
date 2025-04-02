#ifndef PROJECTCREATOR_H
#define PROJECTCREATOR_H

#include <QDir>

#include <QDialog>
#include <QRegularExpression>
#include <QFileDialog>

namespace Ui {
class ProjectCreator;
}

class cProjectCreator : public QDialog
{
    Q_OBJECT

public:
    explicit cProjectCreator(QWidget *parent = nullptr);
    ~cProjectCreator();

signals:
    void getFolderPath(QString path);

private slots:
    void accept() override;

    void on_findFolderButton_clicked();

private:
    Ui::ProjectCreator *ui;

    QRegularExpression m_fileRegex;
};

#endif // PROJECTCREATOR_H
