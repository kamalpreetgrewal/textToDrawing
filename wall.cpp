#include "wall.h"

wall::wall()
{
    dxf = new DL_Dxf();
    exportVersion = DL_Codes::AC1015;
    dw = dxf->out("myfile.dxf", exportVersion);
    if (dw==NULL) {
        printf("Cannot open file 'myfile.dxf' \
               for writing.");
               // abort function e.g. with return
    }
}

void wall::startDXF(DL_Dxf *dxf, DL_WriterA *dw)
{
    dxf->writeHeader(*dw);
    dw->sectionEnd();
    dw->sectionEntities();
}

void wall::createWall(DL_Dxf *dxf, DL_WriterA *dw, float l, float h, float x, float y)
{
    dxf->writeLine(*dw, DL_LineData(x, y, 0.0, x+l, y, 0.0),
                   DL_Attributes("mainLayer", 256, -1, "BYLAYER"));
    dxf->writeLine(*dw, DL_LineData(x+l, y, 0.0, x+l, y+h, 0.0),
                   DL_Attributes("mainLayer", 256, -1, "BYLAYER"));
    dxf->writeLine(*dw, DL_LineData(x+l, y+h, 0.0, x, y+h, 0.0),
                   DL_Attributes("mainLayer", 256, -1, "BYLAYER"));
    dxf->writeLine(*dw, DL_LineData(x, y+h, 0.0, x, y, 0.0),
                   DL_Attributes("mainLayer", 256, -1, "BYLAYER"));
}

void wall::closeDXF(DL_WriterA *dw)
{
    dw->sectionEnd();
    dw->dxfEOF();
    dw->close();
}

DL_Dxf* wall::return_dxf(){
  return dxf;
}

DL_WriterA* wall::return_dw(){
  return dw;
}

wall::~wall()
{
    delete dw;
    delete dxf;
}
