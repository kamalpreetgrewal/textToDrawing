#include "ExampleWriter.h"
ExampleWriter::ExampleWriter(dxfRW &dxfW) : dxfW(dxfW) {
}

void ExampleWriter::addLine(const DRW_Line &data) {
    std::cout << "b" << data.basePoint.x;
    b = data;
    ++count;
//    dxfW.writeLine(&b);
    writeEntities();
}

void ExampleWriter::writeEntities() {
    if (count > 0) {
        std::cout << "d" << b.basePoint.x;
    }
}
