/*
 * Copyright (C) 2013 Tommi Maekitalo
 *
 */

#ifndef STRASSENFESTMANAGER_H
#define STRASSENFESTMANAGER_H

#include <strassenfest.h>
#include <strassenfestresult.h>
#include <cxxtools/http/client.h>
#include <cxxtools/date.h>

class StrassenfestManager
{
    cxxtools::http::Client _client;

  public:
    StrassenfestManager();

    explicit StrassenfestManager(const cxxtools::http::Client& client)
      : _client(client)
    { }

    std::vector<std::string> getBezirke();

    StrassenfestResult search(const std::string& keyword, const std::string& bezirk,
        const cxxtools::Date& von_from, const cxxtools::Date& von_to, const cxxtools::Date& bis,
        unsigned ipp, unsigned page);

    Strassenfeste getAll();
    Strassenfeste getAllByBezirk(const std::string& bezirk);
};

#endif // STRASSENFESTMANAGER_H

