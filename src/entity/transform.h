#ifndef WINTER_TRANSFORM_H
#define WINTER_TRANSFORM_H

#include "component.h"
#include <maths/maths.h>
#include <vector>

struct TransformData
{
    float2 local_position;
    float local_rotation;
    float2 local_scale;

    float4x4 parent_transform;

    static TransformData translate(TransformData original, float2 translation)
    {
        return TransformData {
            .local_position = original.local_position + translation,
            .local_rotation = original.local_rotation,
            .local_scale = original.local_scale,
            .parent_transform = original.parent_transform,
        };
    }

    static TransformData rotate(TransformData original, float rotation)
    {
        return TransformData {
            .local_position = original.local_position,
            .local_rotation = original.local_rotation + rotation,
            .local_scale = original.local_scale,
            .parent_transform = original.parent_transform,
        };
    }

    static TransformData scale(TransformData original, float2 scale)
    {
        return TransformData {
            .local_position = original.local_position,
            .local_rotation = original.local_rotation,
            .local_scale = original.local_scale * scale,
            .parent_transform = original.parent_transform,
        };
    }

    float4x4 get_model_matrix()
    {
        float4x4 output = float4x4::identity();

        output = maths::scale(float3(local_scale, 1.0f)) * output;
        output = maths::rotation(quaternion::angle_axis(local_rotation, float3(0, 0, 1))) * output;
        output = maths::translation(float3(local_position, 1)) * output;;

        return parent_transform * output;
    }
};

class Entity;
class Transform: public Component
{
public:
    Transform(Entity* entity);

    const float2& get_position() const
    {
        return _position;
    }

    const void add_position(const float2& offset)
    {
        _position += offset;
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

    float4x4 get_model_matrix()
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

    TransformData get_transform_data(float4x4 parent_transform)
    {
        return TransformData {
            .local_position = _position,
            .local_rotation = _rotation,
            .local_scale = _scale,
            .parent_transform = parent_transform
        };
    }

private:
    std::shared_ptr<Transform> _parent = nullptr;

    bool is_dirty;
    float4x4 cached_transform_matrix;

    float2 _position = float2::zero();
    float _rotation = 0;
    float2 _scale = float2::one();
    int layer_index = 0;

    inline void recalculate_transform()
    {
        cached_transform_matrix = float4x4::identity();

        cached_transform_matrix = maths::scale(float3(_scale, 1.0f)) * cached_transform_matrix;
        cached_transform_matrix = maths::rotation(quaternion::angle_axis(_rotation, float3(0, 0, 1))) * cached_transform_matrix;
        cached_transform_matrix = maths::translation(float3(_position, layer_index)) * cached_transform_matrix;
    }
};

#endif