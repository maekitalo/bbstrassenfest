/*
 * Copyright (C) 2013 Tommi Maekitalo
 *
 */

#include <strassenfest.h>
#include <cxxtools/serializationinfo.h>

namespace
{
  cxxtools::Date str2date(const std::string& s)
  {
    try
    {
      return cxxtools::Date(s, "%Y-%m-%d");
    }
    catch (const std::exception&)
    {
      return cxxtools::Date(s, "%d.%m.%Y");
    }
  }
}

void operator>>= (const cxxtools::SerializationInfo& si, Strassenfest& strassenfest)
{
    si.getMember("id")            >>= strassenfest._id;
    si.getMember("bezirk")        >>= strassenfest._bezirk;
    si.getMember("bezeichnung")   >>= strassenfest._bezeichnung;
    si.getMember("strasse")       >>= strassenfest._strasse;
    si.getMember("plz")           >>= strassenfest._plz;

    std::string s;

    si.getMember("von")           >>= s;
    strassenfest._von = str2date(s);

    si.getMember("bis")           >>= s;
    strassenfest._bis = str2date(s);

    si.getMember("zeit")          >>= strassenfest._zeit;
    si.getMember("veranstalter")  >>= strassenfest._veranstalter;
    si.getMember("mail")          >>= strassenfest._mail;
    si.getMember("www")           >>= strassenfest._www;
    si.getMember("bemerkungen")   >>= strassenfest._bemerkungen;
}
