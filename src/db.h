#ifndef DB_H
#define DB_H

#include <SQLiteCpp/SQLiteCpp.h>

#include <vector>
#include <memory>
#include <string>

namespace db
{

    class Database;

    const std::string DB_FILENAME = "db.db";

    class Database
    {
    public:
        static Database &Instance();
        SQLite::Statement execute(const std::string &request);

    protected:
        explicit Database();
        ~Database();
        Database(const Database &) = delete;
        Database &operator=(const Database &) = delete;

        friend class DatabaseDestroyer;

    private:
        SQLite::Database mDb;
        static Database *p_instance;
    };
}

#endif