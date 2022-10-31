#pragma once
#include <memory>

#define DCL_PTR(X)\
using X##SPtr = std::shared_ptr<X>;\
using X##UPtr = std::unique_ptr<X>;\
using X##WPtr = std::weak_ptr<X>;\
using X##CPtr = std::shared_ptr<X>;

#define FWD_PTR(X)\
class X;\
using X##SPtr = std::shared_ptr<X>;\
using X##UPtr = std::unique_ptr<X>;\
using X##WPtr = std::weak_ptr<X>;\
using X##CPtr = std::shared_ptr<X>;

#define FWD_PTR_STRUCT(X)\
struct X;\
using X##SPtr = std::shared_ptr<X>;\
using X##UPtr = std::unique_ptr<X>;\
using X##WPtr = std::weak_ptr<X>;\
using X##CPtr = std::shared_ptr<X>;
