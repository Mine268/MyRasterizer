//
// Created by mine268 on 2022-7-16.
//

#pragma once

#include <numeric>

#include "TriangleMesh.h"
#include "Matrix.h"
#include "Vector.h"

namespace mr {

    template<std::size_t TxDim = 2>
    struct MeshObject {

        mr::TriangleMesh<TxDim, float> mesh;

        mr::Matrix<4, 4, float> modelMat{};

        explicit MeshObject(const TriangleMesh<TxDim, float> &);

        explicit MeshObject(TriangleMesh<TxDim, float> &&);

        void scale(float);

        void rotate(const mr::Vector<3, float> &, float);

        void translate(const mr::Vector<3, float> &);

        mr::Matrix<4, 4, float> getModelMat();

    private:

        float scaleFactor{1.f}, rotAngle{0.f};

        mr::Vector<3, float> rotDirection{0, 0, 1}, translationVec{0, 0, 0};

        // scale, rotate, translate
        void updateModelMat();

    };

    template<std::size_t TxDim>
    MeshObject<TxDim>::MeshObject(const TriangleMesh<TxDim, float> &m) : mesh{m} {}

    template<std::size_t TxDim>
    MeshObject<TxDim>::MeshObject(TriangleMesh<TxDim, float> &&m) : mesh{std::move(m)} {}

    template<std::size_t TxDim>
    void MeshObject<TxDim>::scale(float s) {
        scaleFactor = s;
    }

    template<std::size_t TxDim>
    void MeshObject<TxDim>::rotate(const Vector<3, float> &axis, float angle) {
        rotDirection = axis;
        rotAngle = angle;
    }

    template<std::size_t TxDim>
    void MeshObject<TxDim>::translate(const Vector<3, float> &trans) {
        translationVec = trans;
    }

    template<std::size_t TxDim>
    mr::Matrix<4, 4, float> MeshObject<TxDim>::getModelMat() {
        updateModelMat();
        return mesh;
    }

    template<std::size_t TxDim>
    void MeshObject<TxDim>::updateModelMat() {
        auto scaleMat = mr::Matrix<4, 4, float>{
                scaleFactor, 0, 0, 0,
                0, scaleFactor, 0, 0,
                0, 0, scaleFactor, 0,
                0, 0, 0, 1};
        auto transMat = mr::Matrix<4, 4, float>{
                0, 0, 0, translationVec.at(0),
                0, 0, 0, translationVec.at(1),
                0, 0, 0, translationVec.at(2),
                0, 0, 0, 1
        };
        static auto identity3 = mr::Matrix<3, 3, float>{
                1, 0, 0, 0, 1, 0, 0, 0, 1
        };
        auto rotVecDual = rotDirection.getDual();
        auto rotMat3 = identity3
                + (1 - std::cos(rotAngle)) * rotVecDual * rotVecDual
                + std::sin(rotAngle) * rotVecDual;
        auto rotMat = mr::Matrix<4, 4, float>{
                rotMat3.at(0, 0), rotMat3.at(0, 1), rotMat3.at(0, 2), 0,
                rotMat3.at(1, 0), rotMat3.at(1, 1), rotMat3.at(1, 2), 0,
                rotMat3.at(2, 0), rotMat3.at(2, 1), rotMat3.at(2, 2), 0,
                0, 0, 0, 1
        };
        mesh = transMat * rotMat * scaleMat;
    }

} // mr
