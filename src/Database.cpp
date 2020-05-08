/**
 * @file Database.cpp
 *
 * This file contains the implementation of support routes
 * found amongst the data types defined for use in the Database interface.
 */

#include <ClusterMemberStore/Database.hpp>

namespace ClusterMemberStore {

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
