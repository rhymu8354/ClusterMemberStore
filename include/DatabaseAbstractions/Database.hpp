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

#include <initializer_list>
#include <memory>
#include <stddef.h>
#include <stdint.h>
#include <string>
#include <vector>

namespace DatabaseAbstractions {

    using Blob = std::vector< uint8_t >;

    struct StepStatementResults {
        /**
         * This flag is set if there are no more rows to fetch with the
         * statement.
         */
        bool done = false;

        /**
         * This gets a value if stepping the statement results in an error.
         */
        std::string error;
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
            const Value& value
        ) = 0;
        virtual void BindParameters(std::initializer_list< const Value > values) = 0;
        virtual Value FetchColumn(int index, Value::Type type) = 0;
        virtual void Reset() = 0;
        virtual StepStatementResults Step() = 0;
    };

    struct BuildStatementResults {
        std::shared_ptr< PreparedStatement > statement;
        std::string error;
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
        virtual std::string ExecuteStatement(const std::string& statement) = 0;

        // These are designed for use in obtaining blobs holding the complete
        // state of the database (schema and data) and using them to replace
        // the database using those blobs.
        virtual Blob CreateSnapshot() = 0;
        virtual void InstallSnapshot(const Blob& blob) = 0;
    };

}
