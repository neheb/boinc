// The contents of this file are subject to the BOINC Public License
// Version 1.0 (the "License"); you may not use this file except in
// compliance with the License. You may obtain a copy of the License at
// http://boinc.berkeley.edu/license_1.0.txt
//
// Software distributed under the License is distributed on an "AS IS"
// basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See the
// License for the specific language governing rights and limitations
// under the License.
//
// The Original Code is the Berkeley Open Infrastructure for Network Computing.
//
// The Initial Developer of the Original Code is the SETI@home project.
// Portions created by the SETI@home project are Copyright (C) 2002
// University of California at Berkeley. All Rights Reserved.
//
// Contributor(s):
//

#ifndef _DB_BASE_
#define _DB_BASE_

#include "mysql.h"

struct CURSOR {
    bool active;
    MYSQL_RES *rp;
};

// represents a connection to a database
//
class DB_CONN {
public:
    DB_CONN();
    int open(char* name, char* host, char* user, char* passwd);
    int do_query(char*);
    void close();
    int insert_id();
    void print_error(char*);
    const char* error_string();
    bool is_high_priority;

    MYSQL* mysql;
};

// Base for derived classes that can access the DB
// Defines various generic operations on DB tables
//
class DB_BASE {
public:
    DB_BASE(DB_CONN&, char *table_name);
    int insert();
    int update();
    int update_field(char*);
    int lookup_id(int id);
    int lookup(char*);
    int enumerate(char* clause="");
    int end_enumerate();
    int count(int&, char* clause="");
    int sum(double&, char* field, char* clause="");
    int get_double(char* query, double&);
    int get_integer(char* query, int&);
    bool is_high_priority;

    DB_CONN* db;
    const char *table_name;
    CURSOR cursor;
    virtual int get_id();
    virtual void db_print(char*);
    virtual void db_parse(MYSQL_ROW&);
};

#define strcpy2(x, y) \
    { \
        char* z = y; \
        if (!z) { \
            x[0]=0; \
        } else { \
            strlcpy(x, z, sizeof(x)); \
        } \
    }

void escape_string(char* field, int len);
void unescape_string(char* p, int len);

#endif
