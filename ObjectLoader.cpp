//
// Created by mine268 on 2022-7-12.
//

#include <fstream>
#include <tuple>

#include "ObjectLoader.h"
#include "mr_tookit.h"

namespace mr {
    TriangleMesh<2, float> ObjectLoader::loadObject(const std::string &path) {
        std::fstream fstrm;
        mr::TriangleMesh<2, float> mesh;
        fstrm.open(path, std::ios::in);
        if (!fstrm.is_open()) {
            std::cerr << "[ObjectLoader] Failed to open the file: "
                      << path
                      << "\n";
        } else {
            // # o v vt vn f g usemtl mtllib
            std::string line;
            std::string first_token;
            while (!fstrm.eof()) {
                std::getline(fstrm, line);
                // skip comment and empty lines
                if (line.empty() || line == "\n" || line.at(0) == '#') {
                    continue;
                }

                int curr = 0;
                while (line.at(curr++) != ' ');
                first_token = line.substr(0, curr - 1);

                if (first_token == "o") {
                    modelName = line.substr(curr + 1, line.size() - curr);
                } else if (first_token == "v") {
                    auto [x, y, z] = getThreeFloats(line);
                    positions.emplace_back(x, y, z);
                } else if (first_token == "vt") {
                    auto [u, v] = getTwoFloats(line);
                    uvs.emplace_back(u, v);
                } else if (first_token == "vn") {
                    auto [x, y, z] = getThreeFloats(line);
                    normals.emplace_back(x, y, z);
                } else if (first_token == "f") {
                    updateTriangles(mesh, line);
                } else if (first_token == "g") {
                    currGroupName = line.substr(curr + 1, line.size() - curr);
                }
            }
        }

        fstrm.close();

        return std::move(mesh);
    }

    std::tuple<float, float> ObjectLoader::getTwoFloats(const std::string &str) {
        std::size_t curr0 = 0, curr1 = 0;
        while (str.at(curr0++) != ' ');
        curr1 = curr0;
        while (str.at(curr1++) != ' ');
        return std::make_tuple(
                std::stof(str.substr(curr0, curr1 - curr0 - 1)),
                std::stof(str.substr(curr1, str.size() - curr1))
        );
    }

    std::tuple<float, float, float> ObjectLoader::getThreeFloats(const std::string &str) {
        std::size_t curr0 = 0, curr1 = 0, curr2 = 0;
        while (str.at(curr0++) != ' ');
        curr1 = curr0;
        while (str.at(curr1++) != ' ');
        curr2 = curr1;
        while (str.at(curr2++) != ' ');
        return std::make_tuple(
                std::stof(str.substr(curr0, curr1 - curr0 - 1)),
                std::stof(str.substr(curr1, curr2 - curr1 - 1)),
                std::stof(str.substr(curr2, str.size() - curr2))
        );
    }

    void ObjectLoader::updateTriangles(TriangleMesh<2, float> &mesh, const std::string &facet_str) {
        std::size_t curr0 = 0, curr1 = 0, curr2 = 0;
        while (facet_str.at(curr0++) != ' ');
        curr1 = curr0;
        while (facet_str.at(curr1++) != ' ');
        curr2 = curr1;
        while (facet_str.at(curr2++) != ' ');
        Vertex<3, 2, float> v[3] = {
                createVertexFromStr(facet_str.substr(curr0, curr1 - 1 - curr0)),
                createVertexFromStr(facet_str.substr(curr1, curr2 - 1 - curr1)),
                createVertexFromStr(facet_str.substr(curr2, facet_str.size() - curr2))
        };
        for (std::size_t i = 0; i < 3; ++i) {
            if (mr::isZero(v[i].normal.length2())) {
                v[i].normal = Vector<3, float>::cross(
                        v[i].normal - v[(i + 2) % 3].normal,
                        v[(i + 1) % 3].normal - v[i].normal
                );
            }
        }
        mesh.triangles.emplace_back(v[0], v[1], v[2]);
        auto ctn = mesh.groupedTri.find(currGroupName);
        if (ctn == mesh.groupedTri.end()) {
            mesh.groupedTri[currGroupName]
                    = std::vector<std::size_t> {mesh.getSize() - 1};
        } else {
            (*ctn).second.emplace_back(mesh.getSize() - 1);
        }
    }

    Vertex<3, 2, float> ObjectLoader::createVertexFromStr(const std::string &token) {
        std::optional<std::size_t> v_ix, vt_ix, vn_ix;
        std::size_t start = 0, end = 0;

        while (end < token.size() && token.at(end++) != '/');
        if (end == token.size()) {
            v_ix.emplace(std::stof(token.substr(start, end - start)));
        } else {
            v_ix.emplace(std::stof(token.substr(start, end - 1 - start)));
        }

        if (end == token.size()) goto end_of_dec;
        start = end;
        while (end < token.size() && token.at(end++) != '/');
        if (end - 1 > start) {
            vt_ix.emplace(std::stof(token.substr(start, end - 1 - start)));
        }

        if (end == token.size()) goto end_of_dec;
        start = end;
        while (end < token.size()) ++end;
        if (end > start) {
            vn_ix.emplace(std::stof(token.substr(start, end - start)));
        }

        end_of_dec:
        Vertex<3, 2, float> ret;
        ret.position = this->positions.at(v_ix.value() - 1);

        if (vt_ix.has_value()) {
            ret.texture = this->uvs.at(vt_ix.value() - 1);
        } else {
            ret.texture.set(UV_DEFAULT, UV_DEFAULT);
        }

        if (vn_ix.has_value()) {
            ret.normal = this->normals.at(vn_ix.value() - 1);
        } else {
            ret.normal.set(0, 0, 0);
        }

        return std::move(ret);
    }

} // mr