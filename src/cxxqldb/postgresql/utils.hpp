#pragma once
#include <string>
#include <optional>
#include <fmt/format.h>

namespace cxxqldb::postgresql {

template<class Name, class Value>
void push_config_mem(
  std::string& info,
  const Name& name, 
  const std::optional<Value>& value
) {
  if(!value) return;
  std::string next;
  if constexpr(std::is_same_v<Value, bool>) {
    next = fmt::format(" {}={:d}", name, value.value());
  } else if constexpr(std::is_same_v<Value, std::string>){
    next = fmt::format(" {}='{}'", name, value.value());
  } else {
    next = fmt::format(" {}={}", name, value.value());
  }
  info += (next.c_str() + (int)(info.empty()));
}
  
} // namespace cxxqldb::postgresql

#define CXXQL_PG_PUSH_CONF_MEM(info, conf, name) \
  push_config_mem(info, #name, conf.name)
