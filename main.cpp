#include <QFile>
#include <QRegularExpression>
#include <QDebug>
#include <QTextStream>
#include <QIODevice>
#include <QProcess>

#include "wall.h"

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
    ofile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&ofile);
    out << list.join("\n");
    ofile.close();

    // defining regexp to save only numbers in the parsed data in a list
    QRegularExpression exp1("^[0-9]*$");
    QRegularExpression exp2("^(?!wall)");
    QVector<QString> v, s;
    QString c;
    ofile.open(QIODevice::ReadOnly | QIODevice::Text);
    // read whole content
    while (!ofile.atEnd()) {
        c = ofile.readLine();
        if (c.contains(exp1))
        {
            v.append(c);
        }
        if (c.contains(exp2) && !c.contains(exp1))
        {
            s.append(c);
        }
    }

    ofile.close();

    // creating the wall class' object and calling its function
    wall w;
    QString str = "wall";
    int num_walls;
    num_walls = content.count(str);

    DL_Dxf *abc = w.return_dxf();
    DL_WriterA *def = w.return_dw();
    w.startDXF(abc, def);
    int j=0;
    for (int i = 0; i<num_walls;i++)
    {
        w.createWall(abc, def, v.at(j).toFloat(), v.at(j+1).toFloat(),
                     v.at(j+2).toFloat(), v.at(j+3).toFloat(), "main", 256, 5, "CONTINUOUS");
        j++;
    }
    w.createCircle();
    w.closeDXF(def);
    ofile.close();
    QProcess::execute("librecad myfile.dxf");
}
