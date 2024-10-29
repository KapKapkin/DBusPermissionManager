#include "db.h"
#include <SQLiteCpp/SQLiteCpp.h>

using namespace db;

// Database

Database *Database::p_instance = nullptr;

Database::Database() : mDb("db.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
{
}

Database &Database::Instance()
{
    if (!p_instance)
    {
        p_instance = new Database();
    }
    return *p_instance;
}

SQLite::Statement Database::execute(const std::string &request)
{
    SQLite::Statement query(this->mDb, request);
    return query;
}

Database::~Database()
{
    if (p_instance)
        delete p_instance;
}