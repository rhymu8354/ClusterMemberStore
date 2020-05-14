#pragma once

/**
 * @file Database.hpp
 *
 * This file specifies an abstract interface for C++ components to access a
 * database via SQL statements, as well as being able to obtain and install
 * complete snapshots of the entire database at once.
 *
 * One goal of this specification is to limit (and hopefully prevent) leakage
 * of concrete database implementation details into the business layer.
 */

#include "Value.hpp"

#include <memory>
#include <stddef.h>
#include <stdint.h>
#include <string>
#include <vector>

namespace ClusterMemberStore {

    using Blob = std::vector< uint8_t >;

    struct StepStatementResults {
        bool done = false;
        bool error = false;
    };

    /**
     * This is an abstract interface to an object which represents an
     * SQL statement prepared for use with a database.  It can be used to:
     * - input data to the database, via parameter bindings
     * - executing the statement (stepping one row at a time)
     * - retrieving data from the database, via column fetches
     */
    class PreparedStatement {
    public:
        virtual void BindParameter(
            int index,
            Value& value
        ) = 0;
        virtual Value FetchColumn(int index, Value::Type type) = 0;
        virtual void Reset() = 0;
        virtual StepStatementResults Step() = 0;
    };

    struct BuildStatementResults {
        std::shared_ptr< PreparedStatement > statement;
        bool error = false;
    };

    /**
     * This is an abstract interface for general-purpose access to some
     * kind of relational database which understands SQL statements.
     */
    class Database {
    public:
        // These are used to prepare and execute SQL statements, as well
        // as sending data to and from the database as part of executing
        // the statements.
        virtual BuildStatementResults BuildStatement(
            const std::string& statement
        ) = 0;
        virtual bool ExecuteStatement(const std::string& statement) = 0;

        // These are designed for use in obtaining blobs holding the complete
        // state of the database (schema and data) and using them to replace
        // the database using those blobs.
        virtual Blob CreateSnapshot() = 0;
        virtual void InstallSnapshot(const Blob& blob) = 0;
    };

}
