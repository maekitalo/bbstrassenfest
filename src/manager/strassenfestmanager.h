/*
 * Copyright (C) 2013 Tommi Maekitalo
 *
 */

#ifndef STRASSENFESTMANAGER_H
#define STRASSENFESTMANAGER_H

#include <strassenfest.h>
#include <strassenfestresult.h>
#include <cxxtools/date.h>
#include <cxxtools/http/client.h>
#include <vector>
#include <string>

class StrassenfestManager
{
  public:
    StrassenfestManager();

    // manager methods

    std::vector<std::string> getBezirke();

    StrassenfestResult search(const std::string& keyword, const std::string& bezirk,
        const cxxtools::Date& von_from, const cxxtools::Date& von_to, const cxxtools::Date& bis,
        unsigned ipp, unsigned page);

    Strassenfeste getAll();
    Strassenfeste getAllByBezirk(const std::string& bezirk);

  private:
    cxxtools::http::Client _client;
};

#endif // STRASSENFESTMANAGER_H

