#include "../include/mesh.hpp"


mesh::mesh(Eigen::Vector3f &&a, Eigen::Vector3f &&b, Eigen::Vector3f &&c,
                    Eigen::Vector3f &&na, Eigen::Vector3f &&nb, Eigen::Vector3f &&nc,
                    Eigen::Vector2f &&ua, Eigen::Vector2f &&ub, Eigen::Vector2f &&uc,
                    Eigen::Vector3f &&ka, Eigen::Vector3f &&kd, Eigen::Vector3f &&ks,
                    float ns, float ni, float _d, int _illum) {
    std::get<0>(this->vertex) = std::forward<Eigen::Vector3f>(a);
    std::get<1>(this->vertex) = std::forward<Eigen::Vector3f>(b);
    std::get<2>(this->vertex) = std::forward<Eigen::Vector3f>(c);
    
    std::get<0>(this->norm) = std::forward<Eigen::Vector3f>(na);
    std::get<1>(this->norm) = std::forward<Eigen::Vector3f>(nb);
    std::get<2>(this->norm) = std::forward<Eigen::Vector3f>(nc);

    std::get<0>(this->texture_coord) = std::forward<Eigen::Vector2f>(ua);
    std::get<1>(this->texture_coord) = std::forward<Eigen::Vector2f>(ub);
    std::get<2>(this->texture_coord) = std::forward<Eigen::Vector2f>(uc);

    this->Ka = std::forward<Eigen::Vector3f>(ka);
    this->Kd = std::forward<Eigen::Vector3f>(kd);
    this->Ks = std::forward<Eigen::Vector3f>(ks);

    this->Ns = ns; this->Ni = ni; this->d = _d; this->illum = _illum;
}


float mesh::size() const {
    Eigen::Vector3f v1 = std::get<1>(this->vertex) - std::get<0>(this->vertex);
    Eigen::Vector3f v2 = std::get<2>(this->vertex) - std::get<0>(this->vertex);
    auto size2 = v1.cross(v2).norm();
    return size2 * .5;
}

