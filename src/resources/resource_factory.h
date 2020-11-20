#ifndef WINTER_RESOURCE_FACTORY_H
#define WINTER_RESOURCE_FACTORY_H

#include "resource_handle.h"
#include <constants/folder_constants.h>
#include <string>
#include <typeindex>
#include <unordered_map>

class IResourceFactory
{
public:
    IResourceFactory(std::string resource_path)
        : RESOURCE_PATH(resource_path)
    {
    }

    virtual ResourceHandle load(const std::string& path) = 0;

protected:
    std::string get_full_path(const std::string& path)
    {
        return WINTER_ROOT + "/" + RESOURCE_PATH + "/" + path;
    }

    std::string RESOURCE_PATH;
};

template <class T>
class ResourceFactory : public IResourceFactory
{
public:
    ResourceFactory(const std::string resource_path)
        : IResourceFactory(resource_path)
    {
    }

    ResourceHandle load(const std::string& name)
    {
        if (name_to_id.find(name) != name_to_id.end())
        {
            return name_to_id[name];
        }

        std::shared_ptr<T> new_resource = build(name);
        if (new_resource == nullptr)
        {
            return ResourceHandle::invalid_handle<T>();
        }

        ResourceHandle new_resource_handle = get_next_resource_handle();

        name_to_id.insert(std::pair<std::string, ResourceHandle>(name, new_resource_handle));
        id_to_resource.insert(std::pair<ResourceHandle, std::shared_ptr<T>>(new_resource_handle, new_resource));

        return new_resource_handle;
    }

    T* get(const std::string& name) const
    {
        assert(name_to_id.find(name) != name_to_id.end() && "No resource with that name.");

        return id_to_resource.at(name_to_id.at(name)).get();
    }

    T* get(const ResourceHandle& id) const
    {
        assert(id_to_resource.find(id) != id_to_resource.end() && "No resource with that id.");

        return id_to_resource.at(id).get();
    }

    bool remove(const std::string& name) const
    {
        assert("Not yet implemented");
        return false;
    }

    bool remove(const ResourceHandle& id) const
    {
        assert("Not yet implemented");
        return false;
    }

    bool clear() const
    {
        assert("Not yet implemented");
        return false;
    }

    ResourceHandle insert(const std::string& name, T&& resource)
    {
        std::shared_ptr<T> new_resource = std::make_shared<T>(std::move(resource));
        ResourceHandle new_resource_handle = get_next_resource_handle();

        name_to_id.insert(std::pair<std::string, ResourceHandle>(name, std::move(new_resource_handle)));
        id_to_resource.insert(std::pair<ResourceHandle, std::shared_ptr<T>>(new_resource_handle, new_resource));

        return new_resource_handle;
    }

    void for_each(std::function<void(T*)> callback) const
    {
        for (auto& id_resource_pair : id_to_resource)
        {
            callback(id_resource_pair.second.get());
        }
    }

private:
    ResourceHandle get_next_resource_handle()
    {
        return ResourceHandle(resource_type_index, next_resource_id++);
    }

    std::type_index resource_type_index = std::type_index(typeid(T));
    ResourceID next_resource_id = 1;
    std::unordered_map<std::string, ResourceHandle> name_to_id;
    std::unordered_map<ResourceHandle, std::shared_ptr<T>> id_to_resource;

protected:
    virtual std::shared_ptr<T> build(const std::string& name)
    {
        assert("Must be overridden");
        return nullptr;
    }
};

#endif // WINTER_RESOURCE_FACTORY_H
