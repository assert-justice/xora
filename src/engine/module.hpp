#pragma once

class Module{
    public:
    void init(bool* hasError);
    void cleanup();
    protected:
    virtual bool initInternal() = 0;
    virtual void cleanupInternal() = 0;
    private:
    bool isInitalized = false;
};