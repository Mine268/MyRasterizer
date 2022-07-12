//
// Created by mine268 on 2022-7-12.
//

#include "ObjectLoader.h"

#include <fstream>

namespace mr {
    void ObjectLoader::loadObject(const std::string &path) {
        std::fstream fstrm{path};
        if (fstrm.bad()) {
            std::cerr << "[ObjectLoader] Failed to open the file: "
                      << path
                      << "\n";
        } else {
            // # o v vt vn f g usemtl mtllib
        }

        fstrm.close();
    }
} // mr