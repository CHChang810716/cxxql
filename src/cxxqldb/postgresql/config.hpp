#pragma once
#include <functional>
#include <optional>

#include <libpq-fe.h>

namespace cxxqldb::postgresql {

struct config {

  std::optional<std::string>  host;
  std::optional<std::string>  hostaddr;
  std::optional<std::string>  port;
  std::optional<std::string>  dbname;
  std::optional<std::string>  user;
  std::optional<std::string>  password;
  std::optional<std::string>  passfile;
  std::optional<int>          connect_timeout;
  std::optional<std::string>  client_encoding = "utf8";
  std::optional<std::string>  options;
  std::optional<std::string>  application_name;
  std::optional<std::string>  fallback_application_name;
  std::optional<bool>         keepalives = true;
  std::optional<int>          keepalives_idle;
  std::optional<int>          keepalives_interval;
  std::optional<int>          keepalives_count;
  std::optional<std::string>  sslmode; 
  // disable, allow, prefer, required, verify-ca, verify-full
  std::optional<bool>         sslcompression;
  std::optional<std::string>  sslcert;
  std::optional<std::string>  sslkey;
  std::optional<std::string>  sslrootcert;
  std::optional<std::string>  sslcrl;
  std::optional<std::string>  requirepeer;
  std::optional<std::string>  krbsrvname;
  std::optional<std::string>  gsslib;
  std::optional<std::string>  service;
  std::optional<std::string>  target_session_attrs;

  std::function<void(const std::string&)> debug;

  std::function<void(PGconn*)> pre_connect;
  std::function<void(PGconn*)> post_connect;

};

}