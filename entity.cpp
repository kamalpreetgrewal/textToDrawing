#include "entity.h"

entity::entity()
{
    dxf = new DL_Dxf();
    exportVersion = DL_Codes::AC1015;
    dw = dxf->out("myfile.dxf", exportVersion);
    if (dw==NULL) {
        printf("Cannot open file 'myfile.dxf' \
               for writing.");
    }

    num_layers = 2;
}

void entity::startDXF(DL_Dxf *dxf, DL_WriterA *dw)
{
    dxf->writeHeader(*dw);
    dw->sectionEnd();
    dw->sectionEntities();
}

void entity::createWall(DL_Dxf *dxf, DL_WriterA *dw, float l, float h,
                        float x, float y, string layer, int color,
                        int width, string lineType)
{
    dxf->writeLine(*dw, DL_LineData(x, y, 0.0, x+l, y, 0.0),
                   DL_Attributes(layer, color, width, lineType));
    dxf->writeLine(*dw, DL_LineData(x+l, y, 0.0, x+l, y+h, 0.0),
                   DL_Attributes(layer, color, width, lineType));
    dxf->writeLine(*dw, DL_LineData(x+l, y+h, 0.0, x, y+h, 0.0),
                   DL_Attributes(layer, color, width, lineType));
    dxf->writeLine(*dw, DL_LineData(x, y+h, 0.0, x, y, 0.0),
                   DL_Attributes(layer, color, width, lineType));
}

void entity::createFlange(DL_Dxf *dxf, DL_WriterA *dw, float r, float cx,
                          float cy)
{
    dxf->writeCircle(*dw, DL_CircleData(cx, cy, 0.0, r),
                     DL_Attributes("flange", 255, 1, "CONTINUOUS"));
    dxf->writeCircle(*dw, DL_CircleData(cx, cy, 0.0, r+20),
                     DL_Attributes("flange", 255, 1, "CONTINUOUS"));
    float theta = 0;
    float radius = 3;
    cy = cy + r - 50;
    cx = cx + r - 30;
    for (int i=0; i<8; i++)
    {
        cx = cx + r * cos(theta);
        cy = cy + r * sin(theta);
        dxf->writeCircle(*dw, DL_CircleData(cx, cy, 0.0, radius),
                         DL_Attributes("flange", 255, 1, "CONTINUOUS"));
        theta +=2 * M_PI / 8;
    }
}

void entity::closeDXF(DL_WriterA *dw)
{
    dw->sectionEnd();
    dw->dxfEOF();
    dw->close();
}

DL_Dxf* entity::return_dxf(){
    return dxf;
}

DL_WriterA* entity::return_dw(){
    return dw;
}

entity::~entity()
{
    delete dw;
    delete dxf;
}
