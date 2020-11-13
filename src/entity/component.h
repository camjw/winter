#ifndef WINTER_COMPONENT_H
#define WINTER_COMPONENT_H

class Component
{
public:
    virtual void start() { }
    virtual void update() { }
    virtual void late_update() { }
    virtual void awake() { }

    void set_enabled(bool is_enabled)
    {
        if (!this->is_enabled && is_enabled)
        {
            awake();
        }

        this->is_enabled = is_enabled;
    }

private:
    bool is_enabled;
};

#endif // WINTER_COMPONENT_H
