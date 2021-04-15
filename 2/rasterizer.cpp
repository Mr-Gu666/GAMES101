// clang-format off
//
// Created by goksu on 4/6/19.
//

#include <algorithm>
#include <vector>
#include "rasterizer.hpp"
#include <opencv2/opencv.hpp>
#include <math.h>

#define openMSAA true

rst::pos_buf_id rst::rasterizer::load_positions(const std::vector<Eigen::Vector3f> &positions)
{
    auto id = get_next_id();
    pos_buf.emplace(id, positions);

    return {id};
}

rst::ind_buf_id rst::rasterizer::load_indices(const std::vector<Eigen::Vector3i> &indices)
{
    auto id = get_next_id();
    ind_buf.emplace(id, indices);

    return {id};
}

rst::col_buf_id rst::rasterizer::load_colors(const std::vector<Eigen::Vector3f> &cols)
{
    auto id = get_next_id();
    col_buf.emplace(id, cols);

    return {id};
}

auto to_vec4(const Eigen::Vector3f& v3, float w = 1.0f)
{
    return Vector4f(v3.x(), v3.y(), v3.z(), w);
}

static bool insideTriangle(float x, float y, const Vector3f* _v)
{   
    // TODO : Implement this function to check if the point (x, y) is inside the triangle represented by _v[0], _v[1], _v[2]
    bool op[3] = {true,true,true};
    Vector3f vxy = {x,y,0};

    for(int i=0;i<3;++i){
        Vector3f temp1 = _v[i]-_v[(i+1)%3];
        Vector3f temp2 = vxy-_v[(i+1)%3];
        if(temp1.cross(temp2)[2]<0){
            op[i] = false;
        }
    }

    return (op[0]==op[1] && op[1]==op[2]);
}

static std::tuple<float, float, float> computeBarycentric2D(float x, float y, const Vector3f* v)
{
    //std::cout<<"x:"<<x<<" y:"<<y<<" v:"<<v[0].x()<<" "<<v[0].y()<<" "<<v[1].x()<<" "<<v[1].y()<<" "<<v[2].x()<<" "<<v[2].y()<<std::endl;
    float c1 = (x*(v[1].y() - v[2].y()) + (v[2].x() - v[1].x())*y + v[1].x()*v[2].y() - v[2].x()*v[1].y()) / (v[0].x()*(v[1].y() - v[2].y()) + (v[2].x() - v[1].x())*v[0].y() + v[1].x()*v[2].y() - v[2].x()*v[1].y());
    float c2 = (x*(v[2].y() - v[0].y()) + (v[0].x() - v[2].x())*y + v[2].x()*v[0].y() - v[0].x()*v[2].y()) / (v[1].x()*(v[2].y() - v[0].y()) + (v[0].x() - v[2].x())*v[1].y() + v[2].x()*v[0].y() - v[0].x()*v[2].y());
    float c3 = (x*(v[0].y() - v[1].y()) + (v[1].x() - v[0].x())*y + v[0].x()*v[1].y() - v[1].x()*v[0].y()) / (v[2].x()*(v[0].y() - v[1].y()) + (v[1].x() - v[0].x())*v[2].y() + v[0].x()*v[1].y() - v[1].x()*v[0].y());
    //std::cout<<"c1:"<<c1<<" c2:"<<c2<<" c3:"<<c3<<std::endl;
    return {c1,c2,c3};
}

void rst::rasterizer::draw(pos_buf_id pos_buffer, ind_buf_id ind_buffer, col_buf_id col_buffer, Primitive type)
{
    auto& buf = pos_buf[pos_buffer.pos_id];
    auto& ind = ind_buf[ind_buffer.ind_id];
    auto& col = col_buf[col_buffer.col_id];

    float f1 = (50 - 0.1) / 2.0;
    float f2 = (50 + 0.1) / 2.0;

    Eigen::Matrix4f mvp = projection * view * model;
    for (auto& i : ind)
    {
        Triangle t;
        Eigen::Vector4f v[] = {
                mvp * to_vec4(buf[i[0]], 1.0f),
                mvp * to_vec4(buf[i[1]], 1.0f),
                mvp * to_vec4(buf[i[2]], 1.0f)
        };
        //Homogeneous division
        for (auto& vec : v) {
            vec /= vec.w();
        }
        //Viewport transformation
        for (auto & vert : v)
        {
            vert.x() = 0.5*width*(vert.x()+1.0);
            vert.y() = 0.5*height*(vert.y()+1.0);
            vert.z() = vert.z() * f1 + f2;
        }

        for (int i = 0; i < 3; ++i)
        {
            t.setVertex(i, v[i].head<3>());
            t.setVertex(i, v[i].head<3>());
            t.setVertex(i, v[i].head<3>());
        }

        auto col_x = col[i[0]];
        auto col_y = col[i[1]];
        auto col_z = col[i[2]];

        t.setColor(0, col_x[0], col_x[1], col_x[2]);
        t.setColor(1, col_y[0], col_y[1], col_y[2]);
        t.setColor(2, col_z[0], col_z[1], col_z[2]);

        rasterize_triangle(t);
    }
}

//Screen space rasterization
void rst::rasterizer::rasterize_triangle(const Triangle& t) {
    auto v = t.toVector4();
    
    // TODO : Find out the bounding box of current triangle.
    // iterate through the pixel and find if the current pixel is inside the triangle

    float min_x = std::min( std::min(v[0][0],v[1][0]) , v[2][0]);
    float max_x = std::max( std::max(v[0][0],v[1][0]) , v[2][0]);
    float min_y = std::min( std::min(v[0][1],v[1][1]) , v[2][1]);
    float max_y = std::max( std::max(v[0][1],v[1][1]) , v[2][1]);

    min_x = (int)std::floor(min_x);
    max_x = (int)std::ceil(max_x);
    min_y = (int)std::floor(min_y);
    max_y = (int)std::ceil(max_y);

    // If so, use the following code to get the interpolated z value.
    //auto[alpha, beta, gamma] = computeBarycentric2D(x, y, t.v);
    //float w_reciprocal = 1.0/(alpha / v[0].w() + beta / v[1].w() + gamma / v[2].w());
    //float z_interpolated = alpha * v[0].z() / v[0].w() + beta * v[1].z() / v[1].w() + gamma * v[2].z() / v[2].w();
    //z_interpolated *= w_reciprocal;

    // TODO : set the current pixel (use the set_pixel function) to the color of the triangle (use getColor function) if it should be painted.
    
    if(openMSAA){
        MSAA(min_x,max_x,min_y,max_y,t,v);
        return ;
    }

    for(int i=min_x;i<=max_x;++i){
        for(int j=min_y;j<=max_y;++j){
            if(insideTriangle((float)i+0.5,(float)j+0.5,t.v)){
                auto temp = computeBarycentric2D((float)i+0.5, (float)j+0.5, t.v);
                float alpha = std::get<0>(temp);
                float beta = std::get<1>(temp);
                float gamma = std::get<2>(temp);
                float w_reciprocal = 1.0/(alpha / v[0].w() + beta / v[1].w() + gamma / v[2].w());
                float z_interpolated = alpha * v[0].z() / v[0].w() + beta * v[1].z() / v[1].w() + gamma * v[2].z() / v[2].w();
                z_interpolated *= w_reciprocal;
                if(depth_buf[get_index(i,j)] > z_interpolated){
                    Vector3f col = t.getColor();
                    Vector3f point((float)i,(float)j,z_interpolated);
                    set_pixel(point,col);
                    depth_buf[get_index(i,j)] = z_interpolated;
                }
            }
        }
    }
}

void rst::rasterizer::set_model(const Eigen::Matrix4f& m)
{
    model = m;
}

void rst::rasterizer::set_view(const Eigen::Matrix4f& v)
{
    view = v;
}

void rst::rasterizer::set_projection(const Eigen::Matrix4f& p)
{
    projection = p;
}

void rst::rasterizer::clear(rst::Buffers buff)
{
    if ((buff & rst::Buffers::Color) == rst::Buffers::Color)
    {
        std::fill(frame_buf.begin(), frame_buf.end(), Eigen::Vector3f{0, 0, 0});
    }
    if ((buff & rst::Buffers::Depth) == rst::Buffers::Depth)
    {
        std::fill(depth_buf.begin(), depth_buf.end(), std::numeric_limits<float>::infinity());
    }
    /*
    if ((buff & rst::Buffers::Color) == rst::Buffers::Color)
    {
        std::fill(color_buf.begin(), color_buf.end(), Eigen::Vector3f{0, 0, 0});
    }
    */
}

rst::rasterizer::rasterizer(int w, int h) : width(w), height(h)
{
    frame_buf.resize(w * h);
    depth_buf.resize(4 * w * h);
    //color_buf.resize(4 * w * h);
}

int rst::rasterizer::get_index(int x, int y, int d)
{
    return (height-1-y)*width + x+d;
    //return x*4*height + y + d;
}

void rst::rasterizer::set_pixel(const Eigen::Vector3f& point, const Eigen::Vector3f& color,int d)
{
    //old index: auto ind = point.y() + point.x() * width;
    auto ind = get_index(point.x(),point.y(),d);
    frame_buf[ind] = color;

}

// clang-format on
// depth_buf 一定要扩充 不然被更新为最小之后会默认被绿色占据，模糊的边界得不到着色
// 着色要扩充吗？
// 对像素中的每个样本进行深度值比较，混合颜色
void rst::rasterizer::MSAA(int min_x,int max_x,int min_y,int max_y,const Triangle &t,const std::array<Eigen::Vector4f,3> &v){
    float next[4][2] = {{0.25,0.25},{0.25,0.75},{0.75,0.25},{0.75,0.75}};
    for(int i=min_x;i<=max_x;++i){
        for(int j=min_y;j<=max_y;++j){
            int count = 0;
            for(int k=0;k<4;++k){
                if(insideTriangle(i+next[k][0],j+next[k][1],t.v)){
                    auto temp = computeBarycentric2D((float)i+next[k][0], (float)j+next[k][1], t.v);
                    float alpha = std::get<0>(temp);
                    float beta = std::get<1>(temp);
                    float gamma = std::get<2>(temp);
                    float w_reciprocal = 1.0/(alpha / v[0].w() + beta / v[1].w() + gamma / v[2].w());
                    float z_interpolated = alpha * v[0].z() / v[0].w() + beta * v[1].z() / v[1].w() + gamma * v[2].z() / v[2].w();
                    z_interpolated *= w_reciprocal;
                    int idx = i*height*4 + j*4 + k;
                    if(depth_buf[idx]>z_interpolated){
                        depth_buf[idx] = z_interpolated;
                        ++count;
                    }
                }
            }
            if(count>0){
                //std::cout<<"in"<<std::endl;
                int index = get_index(i,j,0);
                frame_buf[index] += t.getColor()*count/4;
            }
        }
    }
}