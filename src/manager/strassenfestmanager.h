/*
 * Copyright (C) 2013 Tommi Maekitalo
 *
 */

#ifndef STRASSENFESTMANAGER_H
#define STRASSENFESTMANAGER_H

#include <model/strassenfest.h>
#include <cxxtools/http/client.h>
#include <cxxtools/date.h>

namespace manager
{

class StrassenfestManager
{
    cxxtools::http::Client _client;

  public:
    StrassenfestManager();

    explicit StrassenfestManager(const cxxtools::http::Client& client)
      : _client(client)
    { }

    std::vector<std::string> getBezirke();
    model::Strassenfeste getAll();
    model::Strassenfeste getAllByBezirk(const std::string& bezirk);
    model::Strassenfeste search(const std::string& keyword, const cxxtools::Date& from, const cxxtools::Date& to);
};

}

#endif // STRASSENFESTMANAGER_H

