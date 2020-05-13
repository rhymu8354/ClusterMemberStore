/**
 * @file Database.cpp
 *
 * This file contains the implementation of support routes
 * found amongst the data types defined for use in the Database interface.
 */

#include <ClusterMemberStore/Database.hpp>
#include <ostream>

namespace ClusterMemberStore {

    ColumnDefinition::ColumnDefinition(
        const std::string& name,
        const std::string& type,
        bool isKey,
        bool isUnique
    )
        : name(name)
        , type(type)
        , isKey(isKey)
        , isUnique(isUnique)
    {
    }

    bool ColumnDefinition::operator==(const ColumnDefinition& other) const {
        return (
            (name == other.name)
            && (type == other.type)
            && (isKey == other.isKey)
            && (isUnique == other.isUnique)
        );
    }

    bool ColumnDefinition::operator!=(const ColumnDefinition& other) const {
        return !(*this == other);
    }

    void PrintTo(
        const ColumnDefinition& columnDefinition,
        std::ostream* os
    ) {
        *os << '{';
        *os << "name: " << columnDefinition.name;
        *os << ", type: " << columnDefinition.type;
        *os << ", isKey: " << (columnDefinition.isKey ? "true" : "false");
        *os << '}';
    }

    bool TableDefinition::operator==(const TableDefinition& other) const {
        return columnDefinitions == other.columnDefinitions;
    }

    bool TableDefinition::operator!=(const TableDefinition& other) const {
        return !(*this == other);
    }

    void PrintTo(
        const TableDefinition& tableDefinition,
        std::ostream* os
    ) {
        *os << '{';
        bool first = true;
        for (const auto& column: tableDefinition.columnDefinitions) {
            if (!first) {
                *os << ", ";
            }
            first = false;
            PrintTo(column, os);
        }
        *os << '}';
    }

}
