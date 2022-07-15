//
// Created by mine268 on 2022-7-13.
//

#pragma once

#include <vector>
#include <map>
#include <string>
#include <functional>

#include "Triangle.h"

namespace mr {

    template<std::size_t TxDim = 2, typename VT = float>
    class TriangleMesh {

        friend class ObjectLoader;

        using TriangleType = Triangle<2, VT>;

        std::vector<TriangleType> triangles{};

        std::map<std::string, std::vector<std::size_t>> groupedTri;

    public:
        TriangleMesh() = default;

        TriangleMesh(TriangleMesh const &) = default;

        TriangleMesh(TriangleMesh &&) noexcept;

        TriangleMesh &operator=(TriangleMesh &&) noexcept;

        TriangleMesh &operator=(TriangleMesh const &) = default;

        TriangleType const &at(std::size_t) const;

        TriangleType &at(std::size_t);

        void addTriangle(TriangleType const &);

        std::size_t getSize() const;

        std::vector<TriangleType> const &getTriangles() const;

        std::vector<TriangleType> &getTriangles();
    };

    template<std::size_t TxDim, typename VT>
    const typename TriangleMesh<TxDim, VT>::TriangleType &TriangleMesh<TxDim, VT>::at(std::size_t ix) const {
        return triangles.at(ix);
    }

    template<std::size_t TxDim, typename VT>
    typename TriangleMesh<TxDim, VT>::TriangleType &TriangleMesh<TxDim, VT>::at(std::size_t ix) {
        return triangles.at(ix);
    }

    template<std::size_t TxDim, typename VT>
    void TriangleMesh<TxDim, VT>::addTriangle(const TriangleMesh::TriangleType &t) {
        triangles.push_back(t);
    }


    template<std::size_t TxDim, typename VT>
    std::size_t TriangleMesh<TxDim, VT>::getSize() const {
        return triangles.size();
    }

    template<std::size_t TxDim, typename VT>
    std::vector<Triangle<2, VT>> const &TriangleMesh<TxDim, VT>::getTriangles() const {
        return std::add_const_t<std::vector<Triangle<2, VT>> &>(triangles);
    }

    template<std::size_t TxDim, typename VT>
    std::vector<Triangle<2, VT>> &TriangleMesh<TxDim, VT>::getTriangles() {
        return triangles;
    }

    template<std::size_t TxDim, typename VT>
    TriangleMesh<TxDim, VT>::TriangleMesh(TriangleMesh &&rhs) noexcept :
            triangles{std::move(rhs.triangles)},
            groupedTri{std::move(rhs.groupedTri)} {
    }

    template<std::size_t TxDim, typename VT>
    TriangleMesh<TxDim, VT> &TriangleMesh<TxDim, VT>::operator=(TriangleMesh &&rhs) noexcept {
        this->triangles = std::move(rhs.triangles);
        this->groupedTri = std::move(rhs.groupedTri);
        return *this;
    }

} // mr
