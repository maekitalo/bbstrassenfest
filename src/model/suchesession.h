/*
 * Copyright (C) 2013 Tommi Maekitalo
 *
 */

#ifndef SUCHESESSION_H
#define SUCHESESSION_H

struct SucheSession
{
    std::string q;
    std::string bezirk;
    std::string von_from;
    std::string von_to;
    cxxtools::Date from;
    cxxtools::Date to;
    unsigned pageNo;
    unsigned itemsPerPage;

    // Initialisierung SucheSession wird beim anlegen der Session durchgeführt:
    SucheSession()
      : pageNo(1),
        itemsPerPage(20)
    { }
};

#endif // SUCHESESSION_H

