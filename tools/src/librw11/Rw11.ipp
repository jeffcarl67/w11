// $Id: Rw11.ipp 1078 2018-12-08 14:19:03Z mueller $
//
// Copyright 2013-2018 by Walter F.J. Mueller <W.F.J.Mueller@gsi.de>
//
// This program is free software; you may redistribute and/or modify it under
// the terms of the GNU General Public License as published by the Free
// Software Foundation, either version 3, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY, without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
// for complete details.
// 
// Revision History: 
// Date         Rev Version  Comment
// 2018-12-07  1078   1.0.1  use std::shared_ptr instead of boost
// 2013-03-06   495   1.0    Initial version
// 2013-01-27   478   0.1    First draft
// ---------------------------------------------------------------------------

/*!
  \file
  \brief   Implemenation (inline) of Rw11.
*/

// all method definitions in namespace Retro
namespace Retro {

//------------------------------------------+-----------------------------------
//! FIXME_docs

inline const std::shared_ptr<RlinkServer>& Rw11::ServerSPtr() const
{
  return fspServ;
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

inline RlinkServer& Rw11::Server() const
{
  return *fspServ;
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

inline RlinkConnect& Rw11::Connect() const
{
  return fspServ->Connect();
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

inline RlogFile& Rw11::LogFile() const
{
  return fspServ->LogFile();
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

inline size_t Rw11::NCpu() const
{
  return fNCpu;
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

inline bool Rw11::IsStarted() const
{
  return fStarted;
}


} // end namespace Retro
