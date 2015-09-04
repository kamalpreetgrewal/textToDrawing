#include <QCoreApplication>
#include <QFile>
#include <QRegularExpression>
#include <QDebug>
#include <QTextStream>
#include <QIODevice>

#include "wall.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // reading the input file
    QFile ifile("in.txt");
    QString content ;
    QStringList list;
    ifile.open(QIODevice::ReadOnly | QIODevice::Text);

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

    qDebug() << v;
    qDebug() << s.at(4).toUtf8();
    ofile.close();

    string layerName = "\"" + s.at(4).toUtf8().constData() + "\"";
    std::cout << layerName;

    // creating the wall class' object and calling its function
    wall w;
    DL_Dxf *abc = w.return_dxf();
    DL_WriterA *def = w.return_dw();
    w.startDXF(abc, def);
//    w.createWall(abc, def, v.at(0).toFloat(), v.at(1).toFloat(),
//                v.at(2).toFloat(), v.at(3).toFloat(), s.at(4).toUtf8().constData(),
//                 256, 5, s.at(5).toUtf8().constData());
//    w.createWall(abc, def, v.at(5).toFloat(),v.at(6).toFloat(),
//             v.at(7).toFloat(), v.at(8).toFloat(), "main", 256, 5, "CONTINUOUS");
    w.closeDXF(def);
    ofile.close();
    return a.exec();
}
