#pragma once

/**
 * @file Database.hpp
 *
 * This file specifies an abstract interface for C++ components to access a
 * database in an exclusive manner in the context of a member of a larger
 * cluster (such as in the Raft Consensus Algorithm).  In this context,
 * the database represents one member's data store, exclusively accessed
 * by that member, and potentially overwritten completely if the cluster
 * leader installs a new snapshot.
 *
 * It needs to be forward-looking and able to support implementations of
 * various databases, not just the ones we need today.
 *
 * One goal of this specification is to limit (and hopefully prevent) leakage
 * of concrete database implementation details into the business layer.
 */

#include <stddef.h>
#include <stdint.h>
#include <string>
#include <unordered_map>
#include <vector>

namespace ClusterMemberStore {

    struct ColumnDefinition {
        std::string name;
        std::string type; // includes DB-specific type metadata (e.g. "varchar(100)")
        bool isKey = false;
        bool isUnique = false;

        bool operator==(const ColumnDefinition& other) const;
        bool operator!=(const ColumnDefinition& other) const;
    };

    /**
     * This is a support function for Google Test to print out
     * values of the ColumnDefinition type.
     *
     * @param[in] columnDefinition
     *     This is the ColumnDefinition value to print.
     *
     * @param[in] os
     *     This points to the stream to which to print the
     *     ColumnDefinition value.
     */
    void PrintTo(
        const ColumnDefinition& columnDefinition,
        std::ostream* os
    );

    enum class DataType {
        Text,
        Real,
        Integer,
        Boolean,
    };

    union Data {
        std::string* text;
        double real;
        intmax_t integer;
        bool boolean;
    };

    struct Value {
        Data data;
        DataType type;
    };

    struct ColumnDescriptor {
        std::string name;
        Value value;
    };

    enum class RowSelectorType {
        All,      // (no filter)
        ColumnMatch, // key = value
    };

    union RowSelectorData {
        struct {
            std::string* columnName;
            Value value;
        } columnMatch;
    };

    struct RowSelector {
        RowSelectorData data;
        RowSelectorType type;
    };

    using ColumnDefinitions = std::vector< ColumnDefinition >;
    using ColumnDescriptors = std::vector< ColumnDescriptor >;
    using ColumnSelector = std::vector< std::string >;
    using DataSet = std::vector< ColumnDescriptors >;
    using Blob = std::vector< uint8_t >;

    struct TableDefinition {
        ColumnDefinitions columnDefinitions;

        bool operator==(const TableDefinition& other) const;
        bool operator!=(const TableDefinition& other) const;
    };

    /**
     * This is a support function for Google Test to print out
     * values of the TableDefinition type.
     *
     * @param[in] tableDefinition
     *     This is the TableDefinition value to print.
     *
     * @param[in] os
     *     This points to the stream to which to print the
     *     TableDefinition value.
     */
    void PrintTo(
        const TableDefinition& tableDefinition,
        std::ostream* os
    );

    using TableDefinitions = std::unordered_map< std::string, TableDefinition >;

    /**
     * This is an abstract interface for general-purpose access to some
     * kind of relational database.
     */
    class Database {
    public:
        // These are meant to be used primarily (hopefully exclusively) by
        // database migrations.
        virtual void CreateTable(
            const std::string& tableName,
            const TableDefinition& tableDefinition
        ) = 0;
        virtual TableDefinitions DescribeTables() = 0;
        virtual void RenameTable(
            const std::string& oldTableName,
            const std::string& newTableName
        ) = 0;
        virtual void AddColumn(
            const std::string& tableName,
            const ColumnDefinition& columnDefinition
        ) = 0;
        virtual void DestroyColumn(
            const std::string& tableName,
            const std::string& columnName
        ) = 0;
        virtual void DestroyTable(
            const std::string& tableName
        ) = 0;

        // These are for general use by applications as well as database
        // migrations.
        virtual void CreateRow(
            const std::string& tableName,
            const ColumnDescriptors& columns
        ) = 0;
        virtual DataSet RetrieveRows(
            const std::string& tableName,
            const RowSelector& rowSelector,
            const ColumnSelector& columnSelector
        ) = 0;
        virtual size_t UpdateRows(
            const std::string& tableName,
            const RowSelector& rowSelector,
            const ColumnDescriptors& columns
        ) = 0;
        virtual size_t DestroyRows(
            const std::string& tableName,
            const RowSelector& rowSelector
        ) = 0;

        // These are especially designed for use by the Raft Consensus
        // Algorithm when installing snapshots of state from one server to
        // another.
        virtual Blob CreateSnapshot() = 0;
        virtual void InstallSnapshot(const Blob& blob) = 0;
    };

}
