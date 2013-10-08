/*
 * Copyright (C) 2013 Tommi Maekitalo
 *
 */

#ifndef STRASSENFEST_H
#define STRASSENFEST_H

#include <string>
#include <vector>
#include <cxxtools/date.h>
#include <cxxtools/string.h>

namespace cxxtools
{
  class SerializationInfo;
}

class Strassenfest
{
    friend void operator>>= (const cxxtools::SerializationInfo& si, Strassenfest& strassenfest);

    int _id;
    cxxtools::String _bezirk;
    cxxtools::String _bezeichnung;
    cxxtools::String _strasse;
    std::string _plz;
    cxxtools::Date _von;
    cxxtools::Date _bis;
    std::string _zeit;
    cxxtools::String _veranstalter;
    std::string _mail;
    std::string _www;
    cxxtools::String _bemerkungen;

public:

    int id() const                               { return _id; }

    const cxxtools::String& bezirk() const       { return _bezirk; }
    const cxxtools::String& bezeichnung() const  { return _bezeichnung; }
    const cxxtools::String& strasse() const      { return _strasse; }
    const std::string&      plz() const          { return _plz; }
    const cxxtools::Date&   von() const          { return _von; }
    const cxxtools::Date&   bis() const          { return _bis; }
    const std::string&      zeit() const         { return _zeit; }
    const cxxtools::String& veranstalter() const { return _veranstalter; }
    const std::string&      mail() const         { return _mail; }
    const std::string&      www() const          { return _www; }
    const cxxtools::String& bemerkungen() const  { return _bemerkungen; }
};

void operator>>= (const cxxtools::SerializationInfo& si, Strassenfest& strassenfest);

typedef std::vector<Strassenfest> Strassenfeste;

#endif // STRASSENFEST_H
