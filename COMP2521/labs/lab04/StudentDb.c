// Implementation of the Student DB ADT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"
#include "Record.h"
#include "StudentDb.h"
#include "Tree.h"

struct studentDb
{
    Tree byZid;
    Tree byName;
};

////////////////////////////////////////////////////////////////////////
// Comparison functions

/**
 * Compares two records by zid only and returns:
 * - A negative number if the first record is less than the second
 * - Zero if the records are equal
 * - A positive number if the first record is greater than the second
 */
int compareByZid(Record r1, Record r2)
{
    return RecordGetZid(r1) - RecordGetZid(r2);
}

/**
 * Compares two records by name (family name first) and then by
 * zid if the names are equal, and returns:
 * - A negative number if the first record is less than the second
 * - Zero if the records are equal
 * - A positive number if the first record is greater than the second
 */
int compareByName(Record r1, Record r2)
{
    // If last name is the same
    if (strcmp(RecordGetFamilyName(r1), RecordGetFamilyName(r2)) == 0)
    {
        // If given name is the same
        if (strcmp(RecordGetGivenName(r1), RecordGetGivenName(r2)) == 0)
        {
            // If id is the same
            if (RecordGetZid(r1) == RecordGetZid(r2))
                return 0;
            else
                return RecordGetZid(r1) - RecordGetZid(r2);
        }
        return strcmp(RecordGetGivenName(r1), RecordGetGivenName(r2));
    }
    return strcmp(RecordGetFamilyName(r1), RecordGetFamilyName(r2));

    // Better solution 
    /*
    int famComp = strcmp(RecordGetFamilyName(r1), RecordGetFamilyName(r2);
    if (famComp) == 0)
    {
        if (strcmp(RecordGetGivenName(r1), RecordGetGivenName(r2)) == 0)
        {
            // If id is the same
            if (RecordGetZid(r1) == RecordGetZid(r2))
                return 0;
            else
                return RecordGetZid(r1) - RecordGetZid(r2);
        }
        return strcmp(RecordGetGivenName(r1), RecordGetGivenName(r2));
    }
    return famComp;
    */
}

////////////////////////////////////////////////////////////////////////

StudentDb DbNew(void)
{
    StudentDb db = malloc(sizeof(*db));
    if (db == NULL)
    {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    db->byZid = TreeNew(compareByZid);
    // TODO: Modify this line to use compareByName once you have
    //       implemented it
    db->byName = TreeNew(compareByName);
    return db;
}

void DbFree(StudentDb db)
{
    TreeFree(db->byZid, false);
    TreeFree(db->byName, true);
    free(db);
}

////////////////////////////////////////////////////////////////////////

bool DbInsertRecord(StudentDb db, Record r)
{
    if (TreeInsert(db->byZid, r))
    {
        TreeInsert(db->byName, r);
        return true;
    }
    else
    {
        return false;
    }
}

////////////////////////////////////////////////////////////////////////

bool DbDeleteByZid(StudentDb db, int zid)
{
    Record dummy = RecordNew(zid, "", "");
    Record r = TreeSearch(db->byZid, dummy);

    if (r != NULL)
    {
        TreeDelete(db->byZid, r);
        TreeDelete(db->byName, r);
        RecordFree(r);
        RecordFree(dummy);
        return true;
    }
    else
    {
        RecordFree(dummy);
        return false;
    }
}

////////////////////////////////////////////////////////////////////////

Record DbFindByZid(StudentDb db, int zid)
{
    Record dummy = RecordNew(zid, "", "");
    Record r = TreeSearch(db->byZid, dummy);
    RecordFree(dummy);
    return r;
}

////////////////////////////////////////////////////////////////////////

List DbFindByName(StudentDb db, char *familyName, char *givenName)
{
    // TODO: Complete this function
    Record dummy_lower = RecordNew(MIN_ZID, familyName, givenName);
    Record dummy_upper = RecordNew(MAX_ZID, familyName, givenName);

    List l = TreeSearchBetween(db->byName, dummy_lower, dummy_upper);

    free(dummy_lower);
    free(dummy_upper);
    return l;
}

////////////////////////////////////////////////////////////////////////

void DbListByZid(StudentDb db)
{
    TreeListInOrder(db->byZid);
}

void DbListByName(StudentDb db)
{
    // TODO: Complete this function
    TreeListInOrder(db->byName);
}
