//
// Created by mine268 on 2022-7-16.
//

#pragma once

#include <numeric>

#include "TriangleMesh.h"
#include "Matrix.h"
#include "Vector.h"
#include "mr_tookit.h"

namespace mr {

    template<std::size_t TxDim = 2>
    struct MeshObject {

        explicit MeshObject(const TriangleMesh<TxDim, float> &);

        explicit MeshObject(TriangleMesh<TxDim, float> &&);

        MeshObject &scaleX(float);

        MeshObject &scaleY(float);

        MeshObject &scaleZ(float);

        MeshObject &rotate(const mr::Vector<3, float> &, float);

        MeshObject &translate(const mr::Vector<3, float> &);

        const mr::Matrix<4, 4, float> &getModelMat() const;

    private:

        mr::TriangleMesh<TxDim, float> mesh;

        mr::Matrix<4, 4, float> modelMat{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

    };

    template<std::size_t TxDim>
    MeshObject<TxDim>::MeshObject(const TriangleMesh<TxDim, float> &m) : mesh{m} {}

    template<std::size_t TxDim>
    MeshObject<TxDim>::MeshObject(TriangleMesh<TxDim, float> &&m) : mesh{std::move(m)} {}

    template<std::size_t TxDim>
    MeshObject<TxDim> &MeshObject<TxDim>::scaleX(float s) {
        modelMat.at(0, 0) *= s;
    }

    template<std::size_t TxDim>
    MeshObject<TxDim> &MeshObject<TxDim>::scaleY(float s) {
        modelMat.at(1, 1) *= s;
    }

    template<std::size_t TxDim>
    MeshObject<TxDim> &MeshObject<TxDim>::scaleZ(float s) {
        modelMat.at(2, 2) *= s;
    }

    template<std::size_t TxDim>
    MeshObject<TxDim> &MeshObject<TxDim>::rotate(const Vector<3, float> &axis, float angle) {
        auto rotVecDual = axis.getDual();
        auto rotMat3 = mr::Matrix<3, 3, float>{1, 0, 0, 0, 1, 0, 0, 0, 1}
                       + (1 - std::cos(angle)) * rotVecDual * rotVecDual
                       + std::sin(angle) * rotVecDual;
        modelMat = mr::Matrix<4, 4, float>{
                rotMat3.at(0, 0), rotMat3.at(0, 1), rotMat3.at(0, 2), 0,
                rotMat3.at(1, 0), rotMat3.at(1, 1), rotMat3.at(1, 2), 0,
                rotMat3.at(2, 0), rotMat3.at(2, 1), rotMat3.at(2, 2), 0,
                0, 0, 0, 1
        } * modelMat;
    }

    template<std::size_t TxDim>
    MeshObject<TxDim> &MeshObject<TxDim>::translate(const Vector<3, float> &trans) {
        modelMat.at(0, 3) = modelMat.at(0, 3) + trans.at(0);
        modelMat.at(1, 3) = modelMat.at(1, 3) + trans.at(1);
        modelMat.at(2, 3) = modelMat.at(2, 3) + trans.at(2);
    }

    template<std::size_t TxDim>
    const mr::Matrix<4, 4, float> &MeshObject<TxDim>::getModelMat() const {
        return mesh;
    }

} // mr
