#include <SQLiteCpp/SQLiteCpp.h>
#include <format>
#include <iostream>
#include <optional>

#include "db.h"

using namespace db;

// Database

Database *Database::p_instance = nullptr;

Database::Database()
    : mDb("db.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) {}

Database &Database::Instance() {
  if (!p_instance) {
    p_instance = new Database();
  }
  return *p_instance;
}

Database::~Database() {
  if (p_instance)
    delete p_instance;
}

void Database::initDB() {
  SQLite::Transaction transaction(mDb);
  mDb.exec("CREATE TABLE IF NOT EXISTS files (id INTEGER PRIMARY KEY "
           "AUTOINCREMENT, name varchar(10) NOT NULL UNIQUE); ");
  mDb.exec("CREATE TABLE IF NOT EXISTS permissions (file_id INTEGER, "
           "permission INTEGER, FOREIGN KEY (file_id) REFERENCES files (id) ON "
           "DELETE CASCADE, PRIMARY KEY (file_id, permission));");
  transaction.commit();
}

void Database::setPermission(const std::string &path,
                             const int32_t &permission) {
  SQLite::Statement setPermission(mDb,
                                  "INSERT INTO permissions VALUES (?, ?);");

  if (!hasPermission(path, permission)) {
    int file_id = addFile(path);
    setPermission.bind(1, file_id);
    setPermission.bind(2, permission);
    setPermission.exec();
  }
}
bool Database::hasPermission(const std::string &path,
                             const int32_t &permission) {
  SQLite::Statement getPermissionQuery(
      mDb, "SELECT * FROM permissions WHERE file_id = ? AND permission = ?;");
  std::optional<int> file_id = getFileId(path);
  if (file_id.has_value()) {
    getPermissionQuery.bind(1, file_id.value());
    getPermissionQuery.bind(2, permission);
    if (getPermissionQuery.executeStep()) {
      return true;
    }
  }
  return false;
}

std::optional<int> Database::getFileId(const std::string &path) {
  SQLite::Statement getFileQuery(mDb, "SELECT * FROM files WHERE name = ?;");
  getFileQuery.bind(1, path);
  if (getFileQuery.executeStep()) {
    return getFileQuery.getColumn(0);
  }
  return std::nullopt;
}

int Database::addFile(const std::string &path) {

  SQLite::Statement insertFileQuery(mDb, "INSERT INTO files VALUES (NULL, ?);");
  auto file_id = getFileId(path);
  if (!file_id) {
    insertFileQuery.bind(1, path);
    insertFileQuery.exec();
    return getFileId(path).value();
  }
  return file_id.value();
}