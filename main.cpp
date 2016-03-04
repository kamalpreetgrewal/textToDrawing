#include <QFile>
#include <QRegularExpression>
#include <QDebug>
#include <QTextStream>
#include <QIODevice>
#include <QProcess>

#include "entity.h"

int main()
{
    // reading the input file
    QFile ifile("in.txt");
    QString content;
    QStringList list;
    ifile.open(QIODevice::ReadOnly);

    // read whole content
    while (!ifile.atEnd()) {
        // defining the regexp by which splitting of contents is to be done
        QRegularExpression exp("(\\(|\\)|\\,|\\=)");
        content = ifile.readAll();
        list = content.split(exp);
    }

    // closing the file after reading has been done
    ifile.close();

    // opening the file to write the splitted data
    QFile ofile("out.txt");
    ofile.open(QIODevice::WriteOnly);
    QTextStream out(&ofile);
    out << list.join("\n");
    ofile.close();

    // defining regexp to save only numbers in the parsed data in a list
    //QRegularExpression exp1("^[0-9]*$");
    QVector<QVector<QString>*> bigV;
    QVector<QString>* v;
    QString c;
    int count = -1;

    ofile.open(QIODevice::ReadOnly);
    // read whole content
    while (!ofile.atEnd())
    {
        c = ofile.readLine();

        if(c == "wall\n")
        {
            ++count;
            v = new QVector<QString>(5);
            (*v)[0] = c;
            qDebug() << "wall";
        }
        if(c == "ball\n")
        {
            ++count;
            v = new QVector<QString>(4);
            (*v)[0] = c;
            qDebug() << "ball";
        }
        if(c == "l\n" && count >= 0 && v != NULL)
        {
            qDebug() << "l";
            (*v)[1] = ofile.readLine();

        }
        if(c == "h\n" && count >= 0 && v != NULL)
        {
            qDebug() << "h";
            (*v)[2] = ofile.readLine();

        }
        if(c == "bx\n" && count >= 0 && v != NULL)
        {
            (*v)[3] = ofile.readLine();
        }
        if(c == "by\n" && count >= 0 && v != NULL)
        {
            (*v)[4] = ofile.readLine();
        }
        if(c == "r\n" && count >= 0 && v != NULL)
        {
            (*v)[1] = ofile.readLine();
        }
        if(c == "cx\n" && count >= 0 && v != NULL)
        {
            (*v)[2] = ofile.readLine();
        }
        if(c == "cy\n" && count >= 0 && v != NULL)
        {
            (*v)[3] = ofile.readLine();
        }
        if(c == "\n" && count >= 0 && v != NULL)
        {
            qDebug() << "v : " << v;
            bigV.append(v);
            //delete v;
            //v = 0;
        }
    }
    qDebug() << bigV.count();

    ofile.close();

    // creating the entity class' object and calling its function
    entity e;

    DL_Dxf *abc = e.return_dxf();
    DL_WriterA *def = e.return_dw();
    e.startDXF(abc, def);

    for (int i = 0; i < bigV.size(); ++i)
    {
        QVector<QString>* ab = bigV.at(i);
        if (ab->at(0) == "wall\n")
        {
            int j = 1;
            e.createWall(abc, def, ab->at(j).toFloat(), ab->at(j+1).toFloat(),
                         ab->at(j+2).toFloat(), ab->at(j+3).toFloat(),
                         "wall", 256, 1, "CONINUOUS");
        }
        if (ab->at(0) == "ball\n")
        {
            int j = 1;
            //            e.createWall(abc, def, ab->at(j).toFloat(), ab->at(j+1).toFloat(),
            //                                 ab->at(j+2).toFloat(), ab->at(j+3).toFloat(),
            //                                 "wall", 256, 1, "CONINUOUS");
        }
    }

    //    e.createFlange(abc, def, 20, 60, 100);
    e.closeDXF(def);

    QProcess::execute("librecad myfile.dxf");
}
