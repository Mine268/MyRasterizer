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
