//
// Created by mine268 on 2022-7-16.
//

#pragma once

#include <numeric>

#include "TriangleMesh.h"
#include "Matrix.h"

namespace mr {

    template<std::size_t TxDim = 2, typename T = float>
    class MeshObject {

        mr::TriangleMesh<TxDim, T> mesh;

        mr::Matrix<4, 4, T> modelMat{}, viewMat{}, MVMat{}, invMVMat{}, projMat{};

    public:

        template<typename A, typename B>
        MeshObject(A &&, B &&, B &&, B &&);

        void setModelMat(mr::Matrix<4, 4, T> &&);

        void setViewMat(mr::Matrix<4, 4, T> &&);

        void setProjMat(mr::Matrix<4, 4, T> &&);

        const mr::Matrix<4, 4, T> &getModelMat() const;

        const mr::Matrix<4, 4, T> &getViewMat() const;

        const mr::Matrix<4, 4, T> &getProjMat() const;

        std::size_t getSize() const;

        mr::Triangle<TxDim, T> &at(std::size_t);

        mr::Triangle<TxDim, T> const &at(std::size_t) const;

        mr::Triangle<TxDim, T> getModelTriangle(std::size_t) const;

        mr::Triangle<TxDim, T> getWorldTriangle(std::size_t) const;

        mr::Triangle<TxDim, T> getScreenTriangle(std::size_t) const;

    };

    template<std::size_t TxDim, typename T>
    template<typename A, typename B>
    MeshObject<TxDim, T>::MeshObject(A &&model, B &&m,  B &&v, B &&p) :
            mesh{std::forward<mr::TriangleMesh<TxDim, T>>(model)},
            modelMat{std::forward<mr::Matrix<4, 4, T>>(m)},
            viewMat{std::forward<mr::Matrix<4, 4, T>>(v)},
            projMat{std::forward<mr::Matrix<4, 4, T>>(p)} {
        MVMat = viewMat * modelMat;
        invMVMat = MVMat.inverse().transpose();
    }

    template<std::size_t TxDim, typename T>
    void MeshObject<TxDim, T>::setModelMat(mr::Matrix<4, 4, T> &&m) {
        modelMat = std::forward<mr::Matrix<4, 4, T>>(m);
        MVMat = viewMat * modelMat;
        invMVMat = MVMat.inverse().transpose();
    }

    template<std::size_t TxDim, typename T>
    void MeshObject<TxDim, T>::setViewMat(mr::Matrix<4, 4, T> &&m) {
        viewMat = std::forward<mr::Matrix<4, 4, T>>(m);
        MVMat = viewMat * modelMat;
        invMVMat = MVMat.inverse().transpose();
    }

    template<std::size_t TxDim, typename T>
    void MeshObject<TxDim, T>::setProjMat(mr::Matrix<4, 4, T> &&m) {
        projMat = std::forward<mr::Matrix<4, 4, T>>(m);
    }

    template<std::size_t TxDim, typename T>
    const Matrix<4, 4, T> &MeshObject<TxDim, T>::getModelMat() const {
        return modelMat;
    }

    template<std::size_t TxDim, typename T>
    const Matrix<4, 4, T> &MeshObject<TxDim, T>::getViewMat() const {
        return viewMat;
    }

    template<std::size_t TxDim, typename T>
    const Matrix<4, 4, T> &MeshObject<TxDim, T>::getProjMat() const {
        return projMat;
    }

    template<std::size_t TxDim, typename T>
    std::size_t MeshObject<TxDim, T>::getSize() const {
        return mesh.getSize();
    }

    template<std::size_t TxDim, typename T>
    Triangle<TxDim, T> &MeshObject<TxDim, T>::at(std::size_t i) {
        return mesh.at(i);
    }

    template<std::size_t TxDim, typename T>
    const Triangle<TxDim, T> &MeshObject<TxDim, T>::at(std::size_t i) const {
        return mesh.at(i);
    }

    template<std::size_t TxDim, typename T>
    Triangle<TxDim, T> MeshObject<TxDim, T>::getModelTriangle(std::size_t i) const {
        return mesh.at(i);
    }

    template<std::size_t TxDim, typename T>
    Triangle<TxDim, T> MeshObject<TxDim, T>::getWorldTriangle(std::size_t i) const {
        auto tri = mesh.at(i);
        for (auto &v: tri.vertex) {
            v.position = (MVMat * v.position.pToVec4()).pToVec3();
            v.normal = (invMVMat * v.normal.vToVec4()).vToVec3();
            v.normal.normalize();
        }
        return tri;
    }

    template<std::size_t TxDim, typename T>
    Triangle<TxDim, T> MeshObject<TxDim, T>::getScreenTriangle(std::size_t i) const {
        return Triangle<TxDim, T>();
    }

} // mr
