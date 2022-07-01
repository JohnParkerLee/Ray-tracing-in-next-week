#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
// #include "aabb.h"
#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

class hittable_list : public hittable
{
public:
    hittable_list() {}
    hittable_list(shared_ptr<hittable> object) { add(object); }

    void clear()
    {
        objects.clear();
    }

    void add(shared_ptr<hittable> object)
    {
        objects.push_back(object);
    }

    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;
    virtual bool bounding_box(double time0, double time1, aabb& output_box) const override;

public:
    /*
        shared_ptr<double> double_ptr = make_shared<double>(0.37);
        shared_ptr<vec3>   vec3_ptr   = make_shared<vec3>(1.414214, 2.718281, 1.618034);
        shared_ptr<sphere> sphere_ptr = make_shared<sphere>(point3(0,0,0), 1.0);
    */
    std::vector<shared_ptr<hittable>> objects;

};

bool hittable_list::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
{
    hit_record temp_rec;
    bool hit_anything = false;
    auto closet_so_far = t_max;

    for(const auto& object:objects){
        if(object->hit(r, t_min, closet_so_far, temp_rec)){
            hit_anything = true;
            closet_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

bool hittable_list::bounding_box(double time0, double time1, aabb& output_box) const{
    if(objects.empty()) return false;

    aabb temp_box;
    bool first_box = true;

    for(const auto& object:objects){
        if(!object->bounding_box(time0, time1, temp_box)) return false;
        output_box = first_box?temp_box:surrounding_box(output_box, temp_box);
        first_box = false;
    }

    return true;
}

#endif