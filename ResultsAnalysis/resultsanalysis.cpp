#include "resultsanalysis.h"


ResultsAnalysis::ResultsAnalysis(QObject *parent)
{
    this->setParent(parent);
}

ResultsAnalysis::~ResultsAnalysis()
{
    checkMap.clear();
}

void ResultsAnalysis::initCheckMap()
{
    char ch = 'A';
    for (int i = 10; i <= 38; i++)
    {
        if ((i == 11) || (i == 22) || (i == 33))
        {
            i++;
        }
        checkMap.insert(ch,i);
        ch++;
    }
}

int ResultsAnalysis::computeQuadraticPower(int variable)
{
    int result;
    if (variable == 0)
    {
        return 1;
    }
    result = 2 * computeQuadraticPower(variable - 1);
    return result;
}

bool ResultsAnalysis::numberCheck(QString &number,bool correct)
{
    if(number.length()!=11)
    {
        return false;
    }

    int sum=0;
    int i = 1;
    foreach (QChar ch , number)
    {/* 计算校验总值 */
        if (i == 11)
        {
            break;
        }
        if (i > 4)
        {
            sum += (ch.toLatin1()-'0') * (computeQuadraticPower(i-1));
        }
        else
        {
            if (checkMap.value(ch)!=0)
            {
                sum += checkMap.value(ch) * computeQuadraticPower(i - 1);
            }
            else
            {/* 箱号前4位必须是英文,箱号格式错误 */
                return false;
            }
        }
        i++;
    }
    int die=sum % 11;
    if (die!=number[10].toLatin1()-'0')
    {
        if(0<=die && die <=9)
        {
            if(correct){/* 矫正结果 */
                number[10]=die+'0';
                return true;
            }
        }
        return false;
    }
    return true;
}
