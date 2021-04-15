//
// Created by LEI XU on 4/11/19.
//

#ifndef RASTERIZER_TRIANGLE_H
#define RASTERIZER_TRIANGLE_H

#include <Eigen/Eigen>


using namespace Eigen;
class Triangle{

public:
    // 存3个点的坐标
    Vector3f v[3]; /*the original coordinates of the triangle, v0, v1, v2 in counter clockwise order*/
    /*Per vertex values*/
    // 顶点颜色
    Vector3f color[3]; //color at each vertex;
    // 顶点材质
    Vector2f tex_coords[3]; //texture u,v
    // 每个顶点的法线向量
    Vector3f normal[3]; //normal vector for each vertex

    //Texture *tex;
    Triangle();

    // 第i个点的坐标
    void setVertex(int ind, Vector3f ver); /*set i-th vertex coordinates */
    // 第i个点的法向量
    void setNormal(int ind, Vector3f n); /*set i-th vertex normal vector*/
    // 设置第i个点的颜色
    void setColor(int ind, float r, float g, float b); /*set i-th vertex color*/
    // 获得颜色
    Vector3f getColor() const { return color[0]*255; } // Only one color per triangle.
    // 设置第i个顶点的材质
    void setTexCoord(int ind, float s, float t); /*set i-th vertex texture coordinate*/
    std::array<Vector4f, 3> toVector4() const;

    Eigen::Vector3f a() const { return v[0]; }
    Eigen::Vector3f b() const { return v[1]; }
    Eigen::Vector3f c() const { return v[2]; }
};






#endif //RASTERIZER_TRIANGLE_H
