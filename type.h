#pragma once

enum class BaseType { INT, FLOAT, BOOL, STRING, VOID, ERROR };

struct Type {
    BaseType base      = BaseType::ERROR;
    bool     is_array  = false;
    int      array_size = -1;

    bool operator==(const Type& o) const { return base == o.base && is_array == o.is_array; }
    bool operator!=(const Type& o) const { return !(*this == o); }
};

inline Type mk_int()    { return {BaseType::INT,    false, -1}; }
inline Type mk_float()  { return {BaseType::FLOAT,  false, -1}; }
inline Type mk_bool()   { return {BaseType::BOOL,   false, -1}; }
inline Type mk_string() { return {BaseType::STRING, false, -1}; }
inline Type mk_void()   { return {BaseType::VOID,   false, -1}; }
inline Type mk_error()  { return {BaseType::ERROR,  false, -1}; }
inline Type mk_array(BaseType b, int sz = -1) { return {b, true, sz}; }

inline bool is_numeric(const Type& t) {
    return !t.is_array && (t.base == BaseType::INT || t.base == BaseType::FLOAT);
}
inline bool is_error(const Type& t) { return t.base == BaseType::ERROR; }

inline const char* type_name(BaseType b) {
    switch (b) {
        case BaseType::INT:    return "numerus";
        case BaseType::FLOAT:  return "flux";
        case BaseType::BOOL:   return "veritas";
        case BaseType::STRING: return "scriptum";
        case BaseType::VOID:   return "nullrite";
        default:               return "<error>";
    }
}
