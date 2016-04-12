#include <iostream>
#include "libdxfrw.h"
#include "ExampleWriter.h"
#include <QFile>
#include <QRegularExpression>
#include <QDebug>
#include <QTextStream>
#include <QIODevice>
#include <QProcess>

using namespace std;

    int main()
    {
        dxfRW dxf("file.dxf");
        ExampleWriter writer(dxf);
        dxf.write(&writer, DRW::Version::AC1027, false);

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
    //            qDebug() << "wall";
            }
            if(c == "ball\n")
            {
                ++count;
                v = new QVector<QString>(4);
                (*v)[0] = c;
    //            qDebug() << "ball";
            }
            if(c == "l\n" && count >= 0 && v != NULL)
            {
    //            qDebug() << "l";
                (*v)[1] = ofile.readLine();

            }
            if(c == "h\n" && count >= 0 && v != NULL)
            {
    //            qDebug() << "h";
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
    //            qDebug() << "v : " << v;
                bigV.append(v);
                //delete v;
                //v = 0;
            }
        }
//        qDebug() << bigV.count();

        ofile.close();

//        e.createWall(10, 20, 30, 30, "wall", 256, 1, "CONTINUOUS");

        for (int i = 0; i < bigV.size(); ++i)
        {
            QVector<QString>* ab = bigV.at(i);
            if (ab->at(0) == "wall\n")
            {
                int j = 1;
                DRW_Line line;
                line.basePoint.x = ab->at(j).toDouble();
                line.basePoint.y = ab->at(j+1).toDouble();
                line.secPoint.x = ab->at(j+2).toDouble();
                line.secPoint.y = ab->at(j+3).toDouble();
                //writer.createLine(line);
                writer.addLine(line);
            }
        }

        QProcess::execute("librecad file.dxf");
        return 0;
    }
