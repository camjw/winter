#ifndef WINTER_TRANSFORM_H
#define WINTER_TRANSFORM_H

#include "component.h"
#include <maths/float3.h>
#include <maths/matrix4x4.h>
#include <maths/quaternion.h>
#include <vector>

class Entity;
class Transform: public Component
{
public:
    Transform(Entity* entity);

    const float2& get_position() const
    {
        return _position;
    }

    const float& get_rotation() const
    {
        return _rotation;
    }

    const float2& get_scale() const
    {
        return _scale;
    }

    void set_position(const float2& position)
    {
        _position = position;
        is_dirty = true;
    }

    void set_rotation(float rotation)
    {
        _rotation = rotation;
        is_dirty = true;
    }

    void set_scale(const float2& scale)
    {
        _scale = scale;
        is_dirty = true;;
    }

    Matrix4x4 get_model_matrix()
    {
        if (is_dirty)
        {
            recalculate_transform();
        }

        return cached_transform_matrix;
    }

    void set_parent(std::shared_ptr<Transform> parent_transform);

    const std::vector<Transform*>& get_children() const
    {
        return children;
    }

    std::vector<Transform*> children;

    const std::shared_ptr<Transform> parent() const
    {
        return _parent;
    }

private:
    std::shared_ptr<Transform> _parent = nullptr;

    bool is_dirty;
    Matrix4x4 cached_transform_matrix;

    float2 _position = float2::zero();
    float _rotation = 0;
    float2 _scale = float2::one();
    int layer_index = 0;

    inline void recalculate_transform()
    {
        cached_transform_matrix = Matrix4x4::identity();

        cached_transform_matrix = Matrix4x4::scale(float3(_scale, 1.0f)) * cached_transform_matrix;
        cached_transform_matrix = Matrix4x4::rotation(quaternion::angle_axis(_rotation, float3(0, 0, 1))) * cached_transform_matrix;
        cached_transform_matrix = Matrix4x4::translate(float3(_position, layer_index)) * cached_transform_matrix;
    }
};

#endif