#include "../include/utils.hpp"

/**
 * 将 OBJ_loader 的读取结果转换为 mesh_object 格式
 * @param loader objl:Loader 加载器
 * @param mesh_ix OBJ 文件中 mesh 模型的编号
 * 
 * @return 返回 mesh 对象的 vector
*/
mesh_object loader_to_mesh_object(const objl::Loader& loader, std::size_t mesh_ix) {
    mesh_object ret;
    auto& loader_mesh = loader.LoadedMeshes[mesh_ix];

    // 逐个遍历 index
    for (std::size_t t_ix = 0; t_ix < loader_mesh.Indices.size(); t_ix += 3) {
        auto v1ix = loader_mesh.Indices[t_ix];
        auto v2ix = loader_mesh.Indices[t_ix + 1];
        auto v3ix = loader_mesh.Indices[t_ix + 2];
        ret.emplace_back(
            // 坐标
            Eigen::Vector3f(loader_mesh.Vertices[v1ix].Position.X, loader_mesh.Vertices[v1ix].Position.Y, loader_mesh.Vertices[v1ix].Position.Z),
            Eigen::Vector3f(loader_mesh.Vertices[v2ix].Position.X, loader_mesh.Vertices[v2ix].Position.Y, loader_mesh.Vertices[v2ix].Position.Z),
            Eigen::Vector3f(loader_mesh.Vertices[v3ix].Position.X, loader_mesh.Vertices[v3ix].Position.Y, loader_mesh.Vertices[v3ix].Position.Z),
            // 法线
            Eigen::Vector3f(loader_mesh.Vertices[v1ix].Normal.X, loader_mesh.Vertices[v1ix].Normal.Y, loader_mesh.Vertices[v1ix].Normal.Z),
            Eigen::Vector3f(loader_mesh.Vertices[v2ix].Normal.X, loader_mesh.Vertices[v2ix].Normal.Y, loader_mesh.Vertices[v2ix].Normal.Z),
            Eigen::Vector3f(loader_mesh.Vertices[v3ix].Normal.X, loader_mesh.Vertices[v3ix].Normal.Y, loader_mesh.Vertices[v3ix].Normal.Z),
            // uv
            Eigen::Vector2f(loader_mesh.Vertices[v1ix].TextureCoordinate.X, loader_mesh.Vertices[v1ix].TextureCoordinate.Y),
            Eigen::Vector2f(loader_mesh.Vertices[v2ix].TextureCoordinate.X, loader_mesh.Vertices[v2ix].TextureCoordinate.Y),
            Eigen::Vector2f(loader_mesh.Vertices[v3ix].TextureCoordinate.X, loader_mesh.Vertices[v3ix].TextureCoordinate.Y),
            // Ka Kd Ks
            Eigen::Vector3f(loader_mesh.MeshMaterial.Ka.X, loader_mesh.MeshMaterial.Ka.Y, loader_mesh.MeshMaterial.Ka.Z),
            Eigen::Vector3f(loader_mesh.MeshMaterial.Kd.X, loader_mesh.MeshMaterial.Kd.Y, loader_mesh.MeshMaterial.Kd.Z),
            Eigen::Vector3f(loader_mesh.MeshMaterial.Ka.X, loader_mesh.MeshMaterial.Ka.Y, loader_mesh.MeshMaterial.Ka.Z),
            // ns ni d illum
            loader_mesh.MeshMaterial.Ns, loader_mesh.MeshMaterial.Ni, loader_mesh.MeshMaterial.d, loader_mesh.MeshMaterial.illum
        );
    }

    return ret;
}


Eigen::Vector4f eu2homo(const Eigen::Vector3f& x3d) {
    Eigen::Vector4f ret = Eigen::Vector4f::Ones();
    ret.topRows(3) = x3d;
    return ret;
}


Eigen::Vector3f homo2eu(const Eigen::Vector4f& x4d) {
    Eigen::Vector3f ret = x4d.topRows(3);
    ret /= x4d(3);
    return ret;
}


// 分量运算当然更快，但是我懒得写了
std::tuple<float, float, float>
get_bc_weight(float x, float y,
              const Eigen::Vector2f& v1,
              const Eigen::Vector2f& v2,
              const Eigen::Vector2f& v3) {
    Eigen::Vector2f q(x, y);
    Eigen::Vector2f u1, u2, u3;
    Eigen::Matrix2f det1, det2, det3;
    u1 = v1 - q;
    u2 = v2 - q;
    u3 = v3 - q;
    det1 << u1, u2;
    det2 << u2, u3;
    det3 << u3, u1;
    auto d1 = det1.determinant();
    auto d2 = det2.determinant();
    auto d3 = det3.determinant();
    auto d = d1 + d2 + d3;
    return std::make_tuple(d2 / d, d3 / d, d1 / d);
}
