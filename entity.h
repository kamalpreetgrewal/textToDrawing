#ifndef ENTITY_H
#define ENTITY_H

#include <dxflib/dl_dxf.h>
#include <QString>
#include <qmath.h>

class entity
{
public:
    entity();
    ~entity();
    void createWall(DL_Dxf *, DL_WriterA* ,float, float, float, float,
                    string, int, int, string);
    //void createFlower(DL_Dxf *, DL_WriterA*, float, float, float);
    void createFlange(DL_Dxf *, DL_WriterA*, float, float, float);
    void startDXF(DL_Dxf *, DL_WriterA *);
    void closeDXF(DL_WriterA *);

    DL_Dxf *return_dxf();
    DL_WriterA *return_dw();

    DL_Dxf *dxf;
    DL_Codes::version exportVersion;
    DL_WriterA* dw;

    int num_layers;
};

#endif // ENTITY_H
