/*
 * Copyright (C) 2013 Tommi Maekitalo
 *
 */

#include <strassenfestresult.h>
#include <cxxtools/serializationinfo.h>

void operator>>= (const cxxtools::SerializationInfo& si, StrassenfestResult& strassenfestResult)
{
  const cxxtools::SerializationInfo& siMessages = si.getMember("messages");
  siMessages.getMember("messages") >>= strassenfestResult._messages;
  siMessages.getMember("success") >>= strassenfestResult._success;

  const cxxtools::SerializationInfo& siResults = si.getMember("results");
  siResults.getMember("count") >>= strassenfestResult._resultCount;
  siResults.getMember("items_per_page") >>= strassenfestResult._itemsPerPage;

  si.getMember("index") >>= strassenfestResult._strassenfeste;
}
