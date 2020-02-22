#include "logicalprocessing.h"

LogicalProcessing::LogicalProcessing(QObject *parent) : QObject(parent)
{
    this->setParent(parent);
}

void LogicalProcessing::logicStatusSlot(int *status)
{

}

void LogicalProcessing::logicPutImageSlot(int putCommnd)
{

}
