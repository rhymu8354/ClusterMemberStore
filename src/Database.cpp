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

    bool TableDefinition::operator==(const TableDefinition& other) const {
        return columnDefinitions == other.columnDefinitions;
    }

    bool TableDefinition::operator!=(const TableDefinition& other) const {
        return !(*this == other);
    }

}
