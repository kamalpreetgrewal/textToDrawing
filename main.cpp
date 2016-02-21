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
    QRegularExpression exp1("^[0-9]*$");
    QVector<QString> v;
    QString c;
    ofile.open(QIODevice::ReadOnly);
    // read whole content
    while (!ofile.atEnd()) {
        c = ofile.readLine();
        if (c.contains(exp1))
        {
            v.append(c);
        }
        qDebug() << v;
    }

    ofile.close();

    // creating the entity class' object and calling its function
    entity e;
    QString str = "wall";
    int num_walls;
    num_walls = content.count(str);

    DL_Dxf *abc = e.return_dxf();
    DL_WriterA *def = e.return_dw();
    e.startDXF(abc, def);
    int j=0;
    for (int i = 0; i<num_walls;i++)
    {
        e.createWall(abc, def, v.at(j).toFloat(), v.at(j+1).toFloat(),
                     v.at(j+2).toFloat(), v.at(j+3).toFloat(),
                     "wall", 256, 1, "CONINUOUS");
        j=j+5;
    }
    e.createFlange(abc, def, 20, 60, 100);
    //w.createFlower(abc,def,fl.at(0),fl.);
    e.closeDXF(def);

    QProcess::execute("librecad myfile.dxf");
}
