#ifndef PROJECTCREATOR_H
#define PROJECTCREATOR_H

#include <QDir>

#include <QDialog>
#include <QRegularExpression>
#include <QFileDialog>

namespace Ui {
class ProjectCreator;
}

class ProjectCreator : public QDialog
{
    Q_OBJECT

public:
    explicit ProjectCreator(QWidget *parent = nullptr);
    ~ProjectCreator();

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
