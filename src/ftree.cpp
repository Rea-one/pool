#include "ftree.h"



ftree::ftree(QObject *parent): QObject{parent}
{

}

void ftree::init()
{
    model = new QFileSystemModel(this);
    model->setRootPath(QDir::currentPath());
    model->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files);
    model->setNameFilterDisables(false);
}

std::string ftree::get_path()
{
    return model->filePath(model->index(0, 0)).toStdString();
}