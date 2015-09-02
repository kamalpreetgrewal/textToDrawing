#ifndef WALL_H
#define WALL_H

#include <dxflib/dl_dxf.h>
#include <QString>

class wall
{
public:
    wall();
    ~wall();
    void createWall(DL_Dxf *, DL_WriterA *,float, float, float, float);
    void startDXF(DL_Dxf *, DL_WriterA *);
    void closeDXF(DL_WriterA *);

    DL_Dxf *return_dxf();
    DL_WriterA *return_dw();

    DL_Dxf *dxf;
    DL_Codes::version exportVersion;
    DL_WriterA* dw;
};

#endif // WALL_H
