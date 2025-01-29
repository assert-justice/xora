#include "vm.hpp"
#include "utils/fs.hpp"
#include "vm_engine.hpp"
#include "vm_system.hpp"

bool VM::initInternal()
{
    py_initialize();
    bool hasError = false;
    py_GlobalRef mod;
    // Bind system functions
    bindSystem();
    // Bind engine functions
    bindEngine();
    // Read main script
    auto text = readFile(&hasError, "main.py");
    if(hasError) {
        printf("Unable to read file %s\n", "main.py");
        return false;
    }
    hasError = !py_exec(text.c_str(), "main.py", EXEC_MODE, NULL);
    if(hasError) {
        py_printexc();
        return false;
    }
    initFn = py_getglobal(py_name("init"));
    if(initFn != NULL){
        hasError = !py_call(initFn, 0, NULL);
    }
    updateFn = py_getglobal(py_name("update"));
    drawFn = py_getglobal(py_name("draw"));
    return !hasError;
}

void VM::cleanupInternal()
{
    py_finalize();
}

bool VM::update()
{
    if(updateFn == NULL) return true;
    bool ok = py_call(updateFn, 0, NULL);
    if(!ok) py_printexc();
    return ok;
}

bool VM::draw()
{
    if(drawFn == NULL) return true;
    bool ok = py_call(drawFn, 0, NULL);
    if(!ok) py_printexc();
    return ok;
}
