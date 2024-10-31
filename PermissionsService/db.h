#ifndef DB_H
#define DB_H

#include <SQLiteCpp/SQLiteCpp.h>
#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include "common.h"

namespace db {

const std::string DB_FILENAME = "db.db";

class Database {
public:
  static Database &Instance();

  void initDB();
  void setPermission(const std::string &path, const int32_t &permissionEnumCod);
  bool hasPermission(const std::string &path, const int32_t &permissionEnumCod);
  std::optional<int> getFileId(const std::string &path);
  int addFile(const std::string &path);

private:
  explicit Database();
  ~Database();
  Database(const Database &) = delete;
  Database &operator=(const Database &) = delete;

  SQLite::Database mDb;
  static Database *p_instance;
};

} // namespace db

#endif