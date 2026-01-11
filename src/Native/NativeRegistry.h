#ifndef CIPR_NATIVE_REGISTRY_H
#define CIPR_NATIVE_REGISTRY_H

#include <memory>
#include "Environment/Environment.h"

namespace NativeRegistry {
    void registerAll(const std::shared_ptr<Environment>& env);
}

#endif //CIPR_NATIVE_REGISTRY_H